/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang.cpp
*/
#include <pthread.h>

#include "phwang.h"
#include "phwang_class.h"
#include "malloc_dir/malloc_class.h"
#include "queue_dir/queue_root_class.h"
#include "net_dir/net_root_class.h"
#include "thread_dir/thread_root_class.h"
#include "list_mgr_dir/list_mgr_root_class.h"
#include "array_mgr_dir/array_mgr_root_class.h"

PhwangClass *thePhwangObject = 0;

/* start phwang service */
void phwangPhwangPhwang (int debug_code_val)
{
    if (!thePhwangObject) {
        thePhwangObject = new PhwangClass(debug_code_val);
        thePhwangObject->initObjects();
    }
}

int phwangPthreadCreate (pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
{
    return thePhwangObject->threadRootObject()->pthreadCreate(thread, attr, start_routine, arg);
}

/* malloc and free */
void *phwangMalloc (int size_val, int who_val)
{
    return thePhwangObject->mallocObject()->phwangMalloc(size_val, who_val);
}

void phwangFree (void *data_val)
{
    thePhwangObject->mallocObject()->phwangFree(data_val);
}

char *phwangMallocConstStrBuf (char const * str_val)
{
    return thePhwangObject->mallocObject()->mallocConstStrBuf(str_val);
}

/* queue */
void *phwangMallocSuspendedQueue (int size_val, char const *who_val)
{
    return thePhwangObject->queueRootObject()->mallocQueue(true, size_val, who_val);
}

void *phwangMallocQueue (int size_val, char const *who_val)
{
    return thePhwangObject->queueRootObject()->mallocQueue(false, size_val, who_val);
}

void phwangFreeQueue (void *queue_val, char const *who_val)
{
    if (!queue_val) {
        phwangLogitS("phwangFreeQueue", who_val);
        phwangAbendS("phwangFreeQueue", "null queue_val");
        //return 0;
    }

    thePhwangObject->queueRootObject()->freeQueue(queue_val);
}

int phwangEnqueue (void *queue_val, void *data_val)
{
    return thePhwangObject->queueRootObject()->enqueue(queue_val, data_val);
}

void *phwangDequeue (void *queue_val, char const *who_val)
{
    if (!queue_val) {
        phwangLogitS("phwangDequeue", who_val);
        phwangAbendS("phwangDequeue", "null queue_val");
        //return 0;
    }

    return thePhwangObject->queueRootObject()->dequeue(queue_val);
}

/* list_mgr */
void *phwangListMgrMalloc (char const *who_val, int id_size_val, int index_size_val, int global_entry_id_val)
{
    return thePhwangObject->listMgrRootObject()->listMgrMalloc(who_val, id_size_val, index_size_val, global_entry_id_val);
}

void phwangListMgrFree (void *list_mgr_val)
{
    thePhwangObject->listMgrRootObject()->listMgrFree(list_mgr_val);
}

void *phwangListMgrSearchEntry (void *list_mgr_val, char const *data_val, void *extra_data_val)
{
    return thePhwangObject->listMgrRootObject()->listMgrSearchEntry(list_mgr_val, data_val, extra_data_val);
}

int phwnagListMgrGetMaxIndex (void *list_mgr_val, char const *who_val)
{
    return thePhwangObject->listMgrRootObject()->listMgrGetMaxIndex(list_mgr_val, who_val);
}

void *phwangListMgrGetEntryTableArray (void *list_mgr_val)
{
    return thePhwangObject->listMgrRootObject()->listMgrGetEntryTableArray(list_mgr_val);
}

void phwangListMgrRemoveEntry (void *list_mgr_val, void *entry_val)
{
    thePhwangObject->listMgrRootObject()->listMgrRemoveEntry(list_mgr_val, entry_val);
}

/* array_mgr */
void *phwangArrayMgrMalloc(char const *who_val, char array_type_val, int max_array_size_val)
{
    return thePhwangObject->arrayMgrRootObject()->arrayMgrMalloc(who_val, array_type_val, max_array_size_val);
}

void phwangArrayMgrFree (void *array_mgr_val)
{
    thePhwangObject->arrayMgrRootObject()->arrayMgrFree(array_mgr_val);
}

void phwangArrayMgrInsertElement (void *array_mgr_val, void *element_val)
{
    thePhwangObject->arrayMgrRootObject()->arrayMgrInsertElement(array_mgr_val, element_val);
}

void phwangArrayMgrRemoveElement (void *array_mgr_val, void *element_val)
{
    thePhwangObject->arrayMgrRootObject()->arrayMgrRemoveElement(array_mgr_val, element_val);
}

void *phwangArrayMgrGetArrayTable (void *array_mgr_val, int *array_size_ptr)
{
    return thePhwangObject->arrayMgrRootObject()->arrayMgrGetArrayTable(array_mgr_val, array_size_ptr);
}

/* tp */
void *phwangMallocTpServer (
                void *caller_object_val,
                unsigned short port_val,
                void (*accept_callback_func_val)(void *, void *),
                void *accept_callback_parameter_val,
                void (*receive_callback_func_val)(void *, void *, void *),
                void *receive_callback_parameter_val,
                char const *who_val)
{
    return thePhwangObject->netRootObject()->mallocTpServer (
                caller_object_val,
                port_val,
                accept_callback_func_val,
                accept_callback_parameter_val,
                receive_callback_func_val,
                receive_callback_parameter_val,
                who_val);
}

void *phwangTpConnect (
                unsigned long ip_addr_val,
                unsigned short port_val,
                void (*receive_callback_val)(void *, void *, void *),
                void *receive_object_val,
                char const *who_val)
{
    return thePhwangObject->netRootObject()->tpConnect (
                ip_addr_val, 
                port_val, 
                receive_callback_val, 
                receive_object_val,
                who_val);
}

void phwangFreeTcpServer (void *tcp_server_object_val)
{
    thePhwangObject->netRootObject()->freeTcpServer(tcp_server_object_val);
}

void phwangFreeTpTransfer (void *tp_transfer_object_val)
{
    thePhwangObject->netRootObject()->freeTpTransfer(tp_transfer_object_val);
}

void phwangTpTransmit (void *tp_transfer_object_val, char *data_val)
{
    thePhwangObject->netRootObject()->tpTransmit(tp_transfer_object_val, data_val);
}

int phwangGetPortObjectIndex (void *port_object_val)
{
    return thePhwangObject->netRootObject()->getPortObjectIndex(port_object_val);
}

int phwangReceiveThreadCount (void)
{
    return thePhwangObject->netRootObject()->receiveThreadCount();
}

void phwangIncrementReceiveThreadCount (void)
{
    thePhwangObject->netRootObject()->incrementReceiveThreadCount();
}
