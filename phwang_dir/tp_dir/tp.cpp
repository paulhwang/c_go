/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp.cpp
*/

#include "../phwang.h"
#include "tp_transfer_class.h"

TpTransferClass *tpConnect(unsigned long ip_addr_val, unsigned short port_val, void (*receive_callback_val)(void *, void *), void *receive_object_val);

void phwangFreeTpTransfer (void *tp_transfer_val)
{
    if (!tp_transfer_val) {
        phwangLogit("phwangFreeTpTransfer", "null tp_transfer_val");
        return;
    }

    if (strcmp(((TpTransferClass *) tp_transfer_val)->objectName(), "TpTransferClass")) {
        phwangLogit("phwangFreeTpTransfer", "wrong object");
        return;
    }

    ((TpTransferClass *) tp_transfer_val)->~TpTransferClass();
}

void *phwangTpConnect (unsigned long ip_addr_val, unsigned short port_val, void (*receive_callback_val)(void *, void *), void *receive_object_val)
{
    void *tp_connect;
    tp_connect = tpConnect(ip_addr_val, port_val, receive_callback_val, receive_object_val);
    return tp_connect;
}

void phwangTpTransmit (void *tp_transfer_val, char *data_val)
{
    if (!tp_transfer_val) {
        phwangLogit("phwangTpTransmit", "null tp_transfer_val");
        return;
    }

    if (strcmp(((TpTransferClass *) tp_transfer_val)->objectName(), "TpTransferClass")) {
        phwangLogit("phwangTpTransmit", "wrong object");
        return;
    }

    ((TpTransferClass *) tp_transfer_val)->exportTransmitData(data_val);
}