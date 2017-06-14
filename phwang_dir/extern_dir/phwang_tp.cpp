/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang_tp.cpp
*/

#include "../phwang.h"
#include "../net_dir/tp_connect.h"
#include "../net_dir/tp_server_class.h"
#include "../net_dir/tp_transfer_class.h"
#include "phwang_class.h"


void *PhwangClass::mallocTpServer (
                        void *caller_object_val,
                        unsigned short port_val,
                        void (*accept_callback_func_val)(void *, void *),
                        void *accept_callback_parameter_val,
                        void (*receive_callback_func_val)(void *, void *),
                        void *receive_callback_parameter_val)
{
    return new TpServerClass(
                    caller_object_val,
                    port_val,
                    accept_callback_func_val,
                    accept_callback_parameter_val,
                    receive_callback_func_val,
                    receive_callback_parameter_val);
}

void *PhwangClass::tpConnect (unsigned long ip_addr_val, unsigned short port_val, void (*receive_callback_val)(void *, void *), void *receive_object_val)
{
    return tpConnectServiceFunction(ip_addr_val, port_val, receive_callback_val, receive_object_val);
}

void PhwangClass::freeTpServer (void *tp_server_object_val)
{
    if (!tp_server_object_val) {
        phwangAbend("phwangFreeTpTransfer", "null tp_server_object_val");
        return;
    }

    if (strcmp(((TpServerClass *) tp_server_object_val)->objectName(), "TpServerClass")) {
        phwangAbend("phwangFreeTpTransfer", "wrong object");
        return;
    }

    ((TpServerClass *) tp_server_object_val)->~TpServerClass();
}

void PhwangClass::freeTpTransfer (void *tp_transfer_object_val)
{
    if (!tp_transfer_object_val) {
        phwangAbend("phwangFreeTpTransfer", "null tp_transfer_object_val");
        return;
    }

    if (strcmp(((TpTransferClass *) tp_transfer_object_val)->objectName(), "TpTransferClass")) {
        phwangAbend("phwangFreeTpTransfer", "wrong object");
        return;
    }

    ((TpTransferClass *) tp_transfer_object_val)->~TpTransferClass();
}

void PhwangClass::tpTransmit (void *tp_transfer_object_val, char *data_val)
{
    if (!tp_transfer_object_val) {
        phwangAbend("phwangTpTransmit", "null tp_transfer_object_val");
        return;
    }

    if (strcmp(((TpTransferClass *) tp_transfer_object_val)->objectName(), "TpTransferClass")) {
        phwangAbend("phwangTpTransmit", "wrong object");
        return;
    }

    ((TpTransferClass *) tp_transfer_object_val)->exportTransmitData(data_val);
}
