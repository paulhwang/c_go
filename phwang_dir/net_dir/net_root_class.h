/*
  Copyrights reserved
  Written by Paul Hwang
  File name: net_root_class.h
*/

#pragma once

class NetRootClass
{
    char const *objectName(void) {return "NetRootClass";}

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    NetRootClass(void);
    ~NetRootClass(void);
    
    void *mallocTpServer (
            void *caller_object_val,
            unsigned short port_val,
            void (*accept_callback_func_val)(void *, void *),
            void *accept_callback_parameter_val,
            void (*receive_callback_func_val)(void *, void *, void *),
            void *receive_callback_parameter_val,
            char const *who_val);
    void *tpConnect(
            unsigned long ip_addr_val, 
            unsigned short port_val, 
            void (*receive_callback_val)(void *, void *, void *), 
            void *receive_object_val,
            char const *who_val);
    void freeTpServer(void *tp_server_object_val);
    void freeTpTransfer(void *tp_transfer_object_val);
    void tpTransmit(void *tp_transfer_object_val, char *data_val);
};