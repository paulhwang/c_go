/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang_class.cpp
*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include "phwang.h"
#include "phwang_class.h"
#include "queue_dir/queue_class.h"
#include "list_mgr_dir/list_mgr_class.h"
#include "array_mgr_dir/array_mgr_class.h"
#include "net_dir/tp_server_class.h"
#include "net_dir/tp_transfer_class.h"

void PhwangClass::logit (char const* str0_val, char const* str1_val)
{
    printf("%s() %s\n", str0_val, str1_val);
}

void PhwangClass::abend (char const* str0_val, char const* str1_val)
{
    phwangLogit("*****Abend*****", str0_val);
    phwangLogit(str0_val, str1_val);
    phwangLogit("*****Abend*****", str1_val);
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

    //printf("decodeNumber() input=%s\n", str_val);
    while (size_val > 0) {
        size_val--;
        number += (str_val[size_val] - '0') * factor;
        factor *= 10;
    }
    //printf("decodeNumber() output=%d\n", number);
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

/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/

void *PhwangClass::listMgrMalloc (char const *caller_name_val, int id_size_val, int index_size_val, int global_entry_id_val)
{
    ListMgrClass *list_mgr = new ListMgrClass(caller_name_val, id_size_val, index_size_val, global_entry_id_val);
    return list_mgr;
}

void PhwangClass::listMgrFree(void *list_mgr_val)
{
    if (!list_mgr_val) {
        phwangAbend("listMgrFree", "null list_mgr_val");
        return;
    }

    if (strcmp(((ListMgrClass *) list_mgr_val)->objectName(), "ListMgrClass")) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "wrong object: objectName=%s", ((ListMgrClass *) list_mgr_val)->objectName());
        phwangAbend("listMgrFree", s);
        return;
    }

    ((ListMgrClass *) list_mgr_val)->~ListMgrClass();
}

void *PhwangClass::listMgrSearchEntry(void *list_mgr_val, char *data_val, void *extra_data_val)
{
    if (!list_mgr_val) {
        phwangAbend("listMgrSearchEntry", "null list_mgr_val");
        return 0;
    }

    if (strcmp(((ListMgrClass *) list_mgr_val)->objectName(), "ListMgrClass")) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "wrong object: objectName=%s", ((ListMgrClass *) list_mgr_val)->objectName());
        phwangAbend("listMgrSearchEntry", s);
        return 0;
    }

    return ((ListMgrClass *) list_mgr_val)->searchEntry(data_val, extra_data_val);
}

int PhwangClass::listMgrGetMaxIndex (void *list_mgr_val)
{
    if (!list_mgr_val) {
        phwangAbend("listMgrGetMaxIndex", "null list_mgr_val");
        return 0;
    }

    if (strcmp(((ListMgrClass *) list_mgr_val)->objectName(), "ListMgrClass")) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "wrong object: objectName=%s", ((ListMgrClass *) list_mgr_val)->objectName());
        phwangAbend("listMgrGetMaxIndex", s);
        return 0;
    }

    return ((ListMgrClass *) list_mgr_val)->maxIndex();
}

void *PhwangClass::listMgrGetEntryTableArray (void *list_mgr_val)
{
    if (!list_mgr_val) {
        phwangAbend("listMgrGetEntryTableArray", "null list_mgr_val");
        return 0;
    }

    if (strcmp(((ListMgrClass *) list_mgr_val)->objectName(), "ListMgrClass")) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "wrong object: objectName=%s", ((ListMgrClass *) list_mgr_val)->objectName());
        phwangAbend("listMgrGetEntryTableArray", s);
        return 0;
    }

    return ((ListMgrClass *) list_mgr_val)->entryTableArray();
}

/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/

void *PhwangClass::arrayMgrMalloc(char const *caller_name_val, char array_type_val, int array_size_val)
{
    ArrayMgrClass *array_mgr = new ArrayMgrClass(caller_name_val, array_type_val, array_size_val);
    return array_mgr;
}

void PhwangClass::arrayMgrFree(void *array_mgr_val)
{
    if (!array_mgr_val) {
        phwangAbend("arrayMgrFree", "null array_mgr_val");
        return;
    }

    if (strcmp(((ArrayMgrClass *) array_mgr_val)->objectName(), "ArrayMgrClass")) {
        phwangAbend("arrayMgrFree", "wrong object");
        return;
    }

    ((ArrayMgrClass *) array_mgr_val)->~ArrayMgrClass();
}

void PhwangClass::arrayMgrInsertElement(void *array_mgr_val, void *element_val)
{
    if (!array_mgr_val) {
        phwangAbend("arrayMgrInsertElement", "null array_mgr_val");
        return;
    }

    if (strcmp(((ArrayMgrClass *) array_mgr_val)->objectName(), "ArrayMgrClass")) {
        phwangAbend("arrayMgrInsertElement", "wrong object");
        return;
    }

    ((ArrayMgrClass *) array_mgr_val)->insertElement(element_val);
}

void PhwangClass::arrayMgrRemoveElement(void *array_mgr_val, void *element_val)
{
    if (!array_mgr_val) {
        phwangAbend("arrayMgrRemoveElement", "null array_mgr_val");
        return;
    }

    if (strcmp(((ArrayMgrClass *) array_mgr_val)->objectName(), "ArrayMgrClass")) {
        phwangAbend("arrayMgrRemoveElement", "wrong object");
        return;
    }

    ((ArrayMgrClass *) array_mgr_val)->removeElement(element_val);
}

void *PhwangClass::arrayMgrGetArrayTable(void *array_mgr_val, int *array_size_ptr)
{
    if (!array_mgr_val) {
        phwangAbend("arrayMgrGetArrayTable", "null array_mgr_val");
        return 0;
    }

    if (strcmp(((ArrayMgrClass *) array_mgr_val)->objectName(), "ArrayMgrClass")) {
        phwangAbend("arrayMgrGetArrayTable", "wrong object");
        return 0;
    }

    return ((ArrayMgrClass *) array_mgr_val)->getArrayTable(array_size_ptr);
}

/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/

void *PhwangClass::mallocQueue (int do_suspend_val, int max_size_val)
{
    QueueClass *queue = new QueueClass(do_suspend_val, max_size_val);
    return queue;
}

void PhwangClass::freeQueue (void *queue_val)
{
    if (!queue_val) {
        phwangAbend("freeQueue", "null queue_val");
        return;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        phwangAbend("freeQueue", "wrong object");
        return;
    }

    ((QueueClass *) queue_val)->~QueueClass();
}

void PhwangClass::enqueue (void *queue_val, void *data_val)
{
    if (!queue_val) {
        phwangAbend("enqueue", "null queue_val");
        return;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        phwangAbend("enqueue", "wrong object");
        return;
    }

    ((QueueClass *) queue_val)->enqueueData(data_val);
}

void *PhwangClass::dequeue (void *queue_val)
{
    if (!queue_val) {
        phwangAbend("dequeue", "null queue_val");
        return 0;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        phwangAbend("dequeue", "wrong object");
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
    TpServerClass *tp_server_object = new TpServerClass(
                    caller_object_val,
                    port_val,
                    accept_callback_func_val,
                    accept_callback_parameter_val,
                    receive_callback_func_val,
                    receive_callback_parameter_val,
                    who_val);

    if (tp_server_object) {
        tp_server_object->startServerThread();
    }
    return tp_server_object;
}

#define PHWANG_TP_CONNECT_RETRY_MAX_COUNT 30

void *PhwangClass::tpConnect (
                    unsigned long ip_addr_val, 
                    unsigned short port_val, 
                    void (*receive_callback_val)(void *, void *), 
                    void *receive_object_val,
                    char const *who_val)
{
    int s;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    phwangLogit(who_val, "tpConnectServiceFunction() start");

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        phwangLogit(who_val, "tpConnectServiceFunction() open socket error");
        return 0;
    }
 
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_val);
  
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        phwangLogit(who_val, "tpConnectServiceFunction() Invalid address/ Address not supported \n");
        return 0;
    }
  
    phwangLogit(who_val, "tpConnectServiceFunction() connecting");
    int retry_count = PHWANG_TP_CONNECT_RETRY_MAX_COUNT;
    while (retry_count) {
        if (connect(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            if (!retry_count--) {
                phwangLogit(who_val, "tpConnectServiceFunction() Failed \n");
                return 0;
            }
            else {
                phwangLogit(who_val, "tpConnectServiceFunction() retry-----");
                sleep(1);
            }
        }
        else {
            break;
        }
    }

    phwangLogit(who_val, "tpConnectServiceFunction() connected");

    TpTransferClass *tp_transfer_object = new TpTransferClass(s, receive_callback_val, receive_object_val);
    tp_transfer_object->startThreads();
    return tp_transfer_object;
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
