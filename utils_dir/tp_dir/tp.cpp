/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp.cpp
*/

#include "../phwang.h"
#include "tp_transfer_class.h"

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
