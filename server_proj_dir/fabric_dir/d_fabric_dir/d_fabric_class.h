/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_server_class.h
*/

#pragma once

#include <pthread.h>
#include "../../protocol_dir/link_mgr_protocol.h"

#define D_FABRIC_RECEIVE_QUEUE_SIZE 100

class FabricClass;

class DFabricClass {
    FabricClass *theFabricObject;
    void *theReceiveQueue;
    pthread_t theReceiveThread;
    void *theTpServerObject;
    void *theTpTransferObject;

    void startReceiveThread(void);

    void debug(int on_off_val, char const* str0_val, char const* str1_val);
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    DFabricClass(FabricClass *fabric_object_val);
    ~DFabricClass(void);
    char const* objectName(void) {return "DFabricClass";}

    /* exports */
    void exportedNetReceiveFunction(char *data_val);
    void exportedNetAcceptFunction(void *tp_transfer_object_val);
    void receiveFunction(char *data_val);

    void startThreads(void);
    void startNetServer(void);
    void receiveThreadFunction(void);
    void transmitFunction(char *data_val);
};
