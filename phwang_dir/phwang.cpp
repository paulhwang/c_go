/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang.cpp
*/
#include <pthread.h>

#include "phwang.h"
#include "phwang_class.h"
#include "abend_dir/abend_class.h"
#include "encode_dir/encode_class.h"
#include "malloc_dir/malloc_class.h"
#include "queue_dir/queue_class.h"
#include "object_dir/object_class.h"
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

/* atomic */
void phwangIncrementAtomicCount (std::atomic<int> *count_val, char const *who_val, int max_count_val)
{
    (*count_val)++;
    if (*count_val > max_count_val) {
        printf("phwangIncrementAtomicCount(), count=%d\n", (*count_val).load());
        phwangAbend("phwangIncrementAtomicCount", who_val);
    }
}

void phwangDecrementAtomicCount (std::atomic<int> *count_val, char const *who_val)
{
    (*count_val)--;
    if (*count_val < 0) {
        printf("phwangDecrementAtomicCount(), count=%d\n", (*count_val).load());
        phwangAbend("phwangDecrementAtomicCount", who_val);
    }
}

/* object count */
void phwangIncrementObjectCount1 (int *object_count_val, char const *object_name_val, int max_object_count_val)
{
    thePhwangObject->objectObject()->incrementObjectCount(object_count_val, object_name_val, max_object_count_val);
}

void phwangDecrementObjectCount (int *object_count_val)
{
    thePhwangObject->objectObject()->decrementObjectCount(object_count_val);
}

/* logit */
void phwangDebug (int on_off_val, char const *func_name_val, char const *str1_val)
{
    thePhwangObject->abendObject()->pDebug(on_off_val, func_name_val, str1_val);
}

void phwangDebug2 (int on_off_val, char const *func_name_val, char const *str1_val, char const *str2_val)
{
    thePhwangObject->abendObject()->pDebug2(on_off_val, func_name_val, str1_val, str2_val);
}

void phwangDebugInt (int on_off_val, char const *func_name_val, char const *str1_val, int int1_val)
{
    thePhwangObject->abendObject()->pDebugInt(on_off_val, func_name_val, str1_val, int1_val);
}

void phwangDebugInt2 (int on_off_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    thePhwangObject->abendObject()->pDebugInt2(on_off_val, func_name_val, str1_val, int1_val, str2_val, int2_val);
}

void phwangLogit (char const *func_name_val, char const *str1_val)
{
    thePhwangObject->abendObject()->pLogit(func_name_val, str1_val);
}

void phwangLogit2 (char const *func_name_val, char const *str1_val, char const *str2_val)
{
    thePhwangObject->abendObject()->pLogit2(func_name_val, str1_val, str2_val);
}

void phwangLogitInt (char const *func_name_val, char const *str1_val, int int1_val)
{
    thePhwangObject->abendObject()->pLogitInt(func_name_val, str1_val, int1_val);
}

void phwangLogitInt2 (char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    thePhwangObject->abendObject()->pLogitInt2(func_name_val, str1_val, int1_val, str2_val, int2_val);
}

void phwangAbend (char const *func_name_val, char const *str1_val)
{
    thePhwangObject->abendObject()->pAbend(func_name_val, str1_val);
}

void phwangAbend2 (char const *func_name_val, char const *str1_val, char const *str2_val)
{
    thePhwangObject->abendObject()->pAbend2(func_name_val, str1_val, str2_val);
}

void phwangComposeFuncName (char *buf_val, char const *object_name_val, char const *func_name_val)
{
    thePhwangObject->abendObject()->composeFuncName(buf_val, object_name_val, func_name_val);
}

void phwangComposeFuncNameExtra (char *buf_val, char const *object_name_val, char const *func_name_val, char const *extra_info_val)
{
    thePhwangObject->abendObject()->composeFuncNameExtra(buf_val, object_name_val, func_name_val, extra_info_val);
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

/* encode */
void phwangEncodeNumber (char *str_val, int number_val, int size_val)
{
    thePhwangObject->encodeObject()->encodeNumber(str_val, number_val, size_val);
}

void  phwangEncodeNumberNull (char *str_val, int number_val, int size_val)
{
    thePhwangObject->encodeObject()->encodeNumberNull(str_val, number_val, size_val);
}

char *phwangEncodeNumberMalloc (int number_val, int size_val)
{
    return thePhwangObject->encodeObject()->encodeNumberMalloc(number_val, size_val);
}

int phwangDecodeNumber (char const *str_val, int size_val)
{
    return thePhwangObject->encodeObject()->decodeNumber(str_val, size_val);
}

int phwangDecodeNumberNull (char const *str_val)
{
    return thePhwangObject->encodeObject()->decodeNumberNull(str_val);
}

int phwangGetEncodeStringMallocSize (char const *str_val)
{
    return thePhwangObject->encodeObject()->getEncodeStringMallocSize(str_val);
}

void  phwangEncodeString(char *output_buf_val, char const *input_str_val)
{
    thePhwangObject->encodeObject()->encodeString(output_buf_val, input_str_val);
}

char *phwangEncodeStringMalloc (char const *input_str_val) {
    return thePhwangObject->encodeObject()->encodeStringMalloc(input_str_val);
}

char *phwangDecodeStringMalloc (char const *input_val, int *input_size_val)
{
    return thePhwangObject->encodeObject()->decodeStringMalloc(input_val, input_size_val);
}

void phwangEncodeIdIndex (char *str_val, int id_val, int id_size_val, int index_val, int index_size_val)
{
    thePhwangObject->encodeObject()->encodeIdIndex(str_val, id_val, id_size_val, index_val, index_size_val);
}

void phwangDecodeIdIndex (char const *str_val, int *id_ptr_val, int id_size_val, int *index_ptr_val, int index_size_val)
{
    thePhwangObject->encodeObject()->decodeIdIndex(str_val, id_ptr_val, id_size_val, index_ptr_val, index_size_val);
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
        phwangLogit("phwangFreeQueue", who_val);
        phwangAbend("phwangFreeQueue", "null queue_val");
        //return 0;
    }

    thePhwangObject->queueRootObject()->freeQueue(queue_val);
}

int phwangEnqueue (void *queue_val, void *data_val)
{
    int result = thePhwangObject->queueRootObject()->enqueue(queue_val, data_val);
    if (result != QueueClass::ENQUEUE_SUCCEED) {
        phwangLogitInt("phwangEnqueue", "***fail_code=", result);
    }
    return result;
}

void *phwangDequeue (void *queue_val, char const *who_val)
{
    if (!queue_val) {
        phwangLogit("phwangDequeue", who_val);
        phwangAbend("phwangDequeue", "null queue_val");
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

void phwangFreeTpServer (void *tp_server_object_val)
{
    thePhwangObject->netRootObject()->freeTpServer(tp_server_object_val);
}

void phwangFreeTpTransfer (void *tp_transfer_object_val)
{
    thePhwangObject->netRootObject()->freeTpTransfer(tp_transfer_object_val);
}

void phwangTpTransmit (void *tp_transfer_object_val, char *data_val)
{
    thePhwangObject->netRootObject()->tpTransmit(tp_transfer_object_val, data_val);
}

int phwangReceiveThreadCount (void)
{
    return thePhwangObject->netRootObject()->receiveThreadCount();
}

void phwangIncrementReceiveThreadCount (void)
{
    thePhwangObject->netRootObject()->incrementReceiveThreadCount();
}

/* register */
void phwangRegisterProgramProcess (int *register_tag_ptr_val, char *program_name_val, unsigned short port_val)
{
    thePhwangObject->registerProgramProcess(register_tag_ptr_val, program_name_val, port_val);
}
