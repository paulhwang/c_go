/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang_class.cpp
*/

#include "phwang.h"
#include "phwang_class.h"
#include "queue_dir/queue_class.h"
#include "net_dir/tp_connect.h"
#include "net_dir/tp_server_class.h"
#include "net_dir/tp_transfer_class.h"

void PhwangClass::logit (char const* str0_val, char const* str1_val)
{
    printf("%s() %s\n", str0_val, str1_val);
}

void PhwangClass::abend (char const* str0_val, char const* str1_val)
{
    phwangLogit(str0_val, str1_val);
    phwangLogit("*****Abend*****", str0_val);
    int *junk = 0;
    *junk = 0;
}

void PhwangClass::printBoard (char const* data_val, int board_size_val)
{
    int i = strlen(data_val);
    while (i) {
        if (*data_val == '0') {
            printf(" +");
        }
        else if (*data_val == '1') {
            printf(" *");
        }
        else if (*data_val == '2') {
            printf(" O");
        }
        data_val++;
        i--;
        if (i % board_size_val == 0) {
            printf("\n");
        }
    }
}

/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/

void PhwangClass::encodeNumber (char *str_val, int number_val, int size_val)
{
    str_val[size_val] = 0;
    while (size_val > 0) {
        size_val--;
        str_val[size_val] = '0' + number_val % 10;
        number_val /= 10;
    }
}

int PhwangClass::decodeNumber (char *str_val, int size_val)
{
    int number = 0;
    int factor = 1;

    printf("-decodeNumber=%s\n", str_val);
    while (size_val > 0) {
        size_val--;
        number += (str_val[size_val] - '0') * factor;
        factor *= 10;
    }
    printf("decodeNumber=%d\n", number);
    return number;
}

void PhwangClass::encodeIdIndex (char *str_val, int id_val, int id_size_val, int index_val, int index_size_val)
{
    encodeNumber(str_val, id_val, id_size_val);
    encodeNumber(str_val + id_size_val, index_val, index_size_val);
}

void PhwangClass::decodeIdIndex (char *str_val, int *id_ptr_val, int id_size_val, int *index_ptr_val, int index_size_val)
{
    *id_ptr_val = decodeNumber(str_val, id_size_val);
    *index_ptr_val = decodeNumber(str_val + id_size_val, index_size_val);
}

void *PhwangClass::mallocQueue (int max_size_val)
{
    QueueClass *queue = new QueueClass(max_size_val);
    return queue;
}

/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/

void PhwangClass::freeQueue (void *queue_val)
{
    if (!queue_val) {
        phwangAbend("phwangFreeQueue", "null queue_val");
        return;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        phwangAbend("phwangFreeQueue", "wrong object");
        return;
    }

    ((QueueClass *) queue_val)->~QueueClass();
}

void PhwangClass::enqueue (void *queue_val, void *data_val)
{
    if (!queue_val) {
        phwangAbend("phwangEnqueue", "null queue_val");
        return;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        phwangAbend("phwangEnqueue", "wrong object");
        return;
    }

    ((QueueClass *) queue_val)->enqueueData(data_val);
}

void *PhwangClass::dequeue (void *queue_val)
{
    if (!queue_val) {
        phwangAbend("phwangDequeue", "null queue_val");
        return 0;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        phwangAbend("phwangDequeue", "wrong object");
        return 0;
    }

    return ((QueueClass *) queue_val)->dequeueData();
}

/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/

void *PhwangClass::mallocTpServer (
                        void *caller_object_val,
                        unsigned short port_val,
                        void (*accept_callback_func_val)(void *, void *),
                        void *accept_callback_parameter_val,
                        void (*receive_callback_func_val)(void *, void *),
                        void *receive_callback_parameter_val,
                        char const *who_val)
{
    return new TpServerClass(
                    caller_object_val,
                    port_val,
                    accept_callback_func_val,
                    accept_callback_parameter_val,
                    receive_callback_func_val,
                    receive_callback_parameter_val,
                    who_val);
}

void *PhwangClass::tpConnect (
                    unsigned long ip_addr_val, 
                    unsigned short port_val, 
                    void (*receive_callback_val)(void *, void *), 
                    void *receive_object_val,
                    char const *who_val)
{
    return tpConnectServiceFunction(ip_addr_val, port_val, receive_callback_val, receive_object_val, who_val);
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