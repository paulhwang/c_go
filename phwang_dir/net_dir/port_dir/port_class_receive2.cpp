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

            if (0) { /* debug */
                char s[128];
                sprintf(s, "(%s) data=%s", this->theWho, raw_data);
                phwangDebugWS(true, "PortClass::receiveThreadFunction2", this->theWho, s);
            }

            if (raw_data[0] == '{') {
                length = raw_length - (1 + PortClass::DATA_LENGTH_SIZE + 1);
                length1 = phwangDecodeNumber(&raw_data[1], PortClass::DATA_LENGTH_SIZE);
                if (length != length1) {
                    char s[128];
                    sprintf(s, "(%s) length not match!!! data=%s len=%d %d", this->theWho, raw_data, length, length1);
                    phwangAbendWS("PortClass::receiveThreadFunction2", this->theWho, s);
                }

                data = (char *) phwangMalloc(length + 32, MallocClass::receiveThreadFunction2);
                memcpy(data, &raw_data[1 + PortClass::DATA_LENGTH_SIZE], length);
                data[length] = 0;
             }
            else {
                if (1) { /* debug */
                    char s[2000];
                    sprintf(s, "(%s) data=%s len=%lu", this->theWho, raw_data, strlen(raw_data));
                    phwangDebugWS(true, "PortClass::receiveThreadFunction2", this->theWho, s);
                }
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
