/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_receive.cpp
*/

#include <stdlib.h>
#include <pthread.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <pwd.h>
#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "tp_transfer_class.h"

void *TpTransferClass::receiveThreadFunction (int socket_val)
{
    phwangIncrementReceiveThreadCount();

    while (1) {
        char *data = (char *) phwangMalloc(TpTransferClass::RECEIVE_BUFFER_SIZE + 32, MallocClass::receiveThreadFunction);

        int length = read(socket_val, data, TpTransferClass::RECEIVE_BUFFER_SIZE);
        if (length > 0) {
            data[length] = 0;
            
            if (0) { /* debug */
                char s[128];
                sprintf(s, "(%s) data=%s len=%d", this->theWho, data, length);
                phwangDebugWS(true, "TpTransferClass::receiveThreadFunction", this->theWho, s);
            }

            if ((*data != '{') && (*data != '[')) {
                if (1) { /* debug */
                    char s[2000];
                    sprintf(s, "(%s) data=%s len=%d", this->theWho, data, length);
                    phwangDebugWS(true, "TpTransferClass::receiveThreadFunction", this->theWho, s);
                }
                phwangAbendS("TpTransferClass::receiveThreadFunction: wrong header", data);
                phwangFree(data);
                continue;
            }

            phwangEnqueue(this->theReceiveQueue, data);
        }
        else {
            phwangFree(data);
            usleep(10);
        }
    }
    return 0;
}

void *tpTranferReceiveThreadFunction (void *data_val)
{
    int socket = ((tp_transfer_thread_parameter *) data_val)->socket;
    TpTransferClass *tp_transfer_object = ((tp_transfer_thread_parameter *) data_val)->tp_transfer_object;
    phwangFree(data_val);

    return tp_transfer_object->receiveThreadFunction(socket);
}

void TpTransferClass::startReceiveThread (int socket_val)
{
    tp_transfer_thread_parameter *data = (tp_transfer_thread_parameter *) phwangMalloc(sizeof(tp_transfer_thread_parameter), MallocClass::tpTranferReceiveThreadFunction);
    data->socket = socket_val;
    data->tp_transfer_object = this;

    phwangDebugWS(false, "TpTransferClass::startReceiveThread", this->theWho, "");

    int r = pthread_create(&this->theReceiveThread, 0, tpTranferReceiveThreadFunction, data);
    if (r) {
        printf("Error - TpTransferClass::startReceiveThread() return code: %d\n", r);
        return;
    }
}
