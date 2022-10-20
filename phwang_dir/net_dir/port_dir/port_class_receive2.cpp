/*
  Copyrights reserved
  Written by Paul Hwang
  File name: port_class_receive2.cpp
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

void *PortClass::receiveThreadFunction2 (void)
{
    while (1) {
        char *raw_data = (char *) phwangDequeue(this->theReceiveQueue, "PortClass::receiveThreadFunction2()");
        if (raw_data) {
            int raw_length = strlen(raw_data);
            int length;
            int length1;
            char *data;

            phwangDebugWS(false, "PortClass::receiveThreadFunction2", this->theWho, raw_data);

            if (raw_data[0] == '{') {
                length = raw_length - (1 + TCP_IP_DEF::MAX_DATA_LENGTH_SIZE + 1);
                length1 = phwangDecodeNumber(&raw_data[1], TCP_IP_DEF::MAX_DATA_LENGTH_SIZE);
                if (length != length1) {
                    phwangDebugWSISI(true, "PortClass::receiveThreadFunction2", this->theWho, "length", length, "length1", length1);
                    phwangAbendWSS("PortClass::receiveThreadFunction2", this->theWho, "length not match", raw_data);
                }

                data = (char *) phwangMalloc(length + 1, MallocClass::receiveThreadFunction2);
                memcpy(data, &raw_data[1 + TCP_IP_DEF::MAX_DATA_LENGTH_SIZE], length);
                data[length] = 0;
             }
            else {
                phwangDebugWSISS(true, "PortClass::receiveThreadFunction2", this->theWho, "len", strlen(raw_data), "data", raw_data);
                phwangAbendWS("PortClass::receiveThreadFunction2: wrong header", this->theWho, raw_data);
                continue;
            }

            phwangFree(raw_data);
            this->receiveCallback()(this, this->theReceiveObject, data);
        }
    }
    return 0;
}

void *tpTranferReceiveThreadFunction2 (void *this_val)
{
    return ((PortClass *)this_val)->receiveThreadFunction2();
}

void PortClass::startReceiveThread2 (void)
{
    phwangDebugWS(false, "PortClass::startReceiveThread2", this->theWho, "create receiveThread");

    int r = phwangPthreadCreate(&this->theReceiveThread2, NULL, tpTranferReceiveThreadFunction2, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }
}
