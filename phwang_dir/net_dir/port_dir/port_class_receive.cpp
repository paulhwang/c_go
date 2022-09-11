/*
  Copyrights reserved
  Written by Paul Hwang
  File name: port_class_receive.cpp
*/

#include <stdlib.h>
#include <pthread.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <pwd.h>
#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "port_class.h"

void *PortClass::receiveThreadFunction (int socket_val)
{
    phwangIncrementReceiveThreadCount();

    while (1) {
        char *data = (char *) phwangMalloc(PortClass::RECEIVE_BUFFER_SIZE + 32, MallocClass::receiveThreadFunction);

        int length = read(socket_val, data, PortClass::RECEIVE_BUFFER_SIZE);
        if (length > 0) {
            data[length] = 0;
            
            phwangDebugWSISS(false, "PortClass::receiveThreadFunction", this->theWho, "len=", length, " data=", data);

            if ((*data != '{') && (*data != '[')) {
                if (1) { /* debug */
                    char s[2000];
                    sprintf(s, "(%s) data=%s len=%d", this->theWho, data, length);
                    phwangDebugWS(true, "PortClass::receiveThreadFunction", this->theWho, s);
                }
                phwangAbendS("PortClass::receiveThreadFunction: wrong header", data);
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
    PortClass *tp_transfer_object = ((tp_transfer_thread_parameter *) data_val)->tp_transfer_object;
    phwangFree(data_val);

    return tp_transfer_object->receiveThreadFunction(socket);
}

void PortClass::startReceiveThread (int socket_val)
{
    tp_transfer_thread_parameter *data = (tp_transfer_thread_parameter *) phwangMalloc(sizeof(tp_transfer_thread_parameter), MallocClass::tpTranferReceiveThreadFunction);
    data->socket = socket_val;
    data->tp_transfer_object = this;

    phwangDebugWS(false, "PortClass::startReceiveThread", this->theWho, "");

    int r = pthread_create(&this->theReceiveThread, 0, tpTranferReceiveThreadFunction, data);
    if (r) {
        printf("Error - PortClass::startReceiveThread() return code: %d\n", r);
        return;
    }
}
