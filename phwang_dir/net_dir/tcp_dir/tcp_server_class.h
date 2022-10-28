/*
  Copyrights reserved
  Written by Paul Hwang
  File name: transport_class.h
*/

#pragma once
#include <pthread.h>

class QueueMgrClass;
class TpTransferClass;

typedef struct {
    pthread_t server_thread;
    TpTransferClass *tp_transfer_object;
} StartServerOutputStruct;

class TcpServerClass {
    int debugOn_;
    void *callerObject_;
    unsigned short tcpPort_;
    void (*acceptCallbackFunc_)(void *, void *);
    void (*receiveCallbackFunc_)(void *, void *, void *);
    void *acceptCallbackParameter_;
    void *receiveCallbackParameter_;
    char const *theWho;
    pthread_t serverThread_;
    int portObjectIndex_;

public:
    TcpServerClass(
        int debug_on_val,
        void *caller_object_val,
        unsigned short tcp_port_val,
        void (*accept_callback_func_val)(void *, void *),
        void *accept_callback_parameter_val,
        void (*receive_callback_func_val)(void *, void *, void *),
        void *receive_callback_parameter_val,
        char const *who_val);
    ~TcpServerClass(void);
    char const *objectName(void) {return "TcpServerClass";}

    void *serverThreadFunc(void *data_val);
    void startServerThread(void);
};
