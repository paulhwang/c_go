/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang.cpp
*/

#include "phwang.h"
#include "phwang_class.h"
#include "abend_dir/abend_class.h"
#include "encode_dir/encode_class.h"
#include "malloc_dir/malloc_class.h"
#include "object_dir/object_class.h"

PhwangClass *thePhwangObject = 0;

/* start phwang service */
void phwangPhwangPhwang (void)
{
    if (!thePhwangObject) {
        thePhwangObject = new PhwangClass();
    }
}

/* object count */
void phwangIncrementObjectCount(int *object_count_val, char *object_name_val, int max_object_count_val)
{
    thePhwangObject->objectObject()->incrementObjectCount(object_count_val, object_name_val, max_object_count_val);
}

void phwangDecrementObjectCount(int *object_count_val)
{
    thePhwangObject->objectObject()->decrementObjectCount(object_count_val);
}

/* logit */
void phwangDebug (int on_off_val, char const *str0_val, char const *str1_val)
{
    thePhwangObject->abendObject()->phwangDebug(on_off_val, str0_val, str1_val);
}

void phwangLogit (char const *str0_val, char const *str1_val)
{
    thePhwangObject->abendObject()->phwangLogit(str0_val, str1_val);
}

void phwangAbend (char const *str0_val, char const *str1_val)
{
    thePhwangObject->abendObject()->phwangAbend(str0_val, str1_val);
}

/* */
void phwangPrintBoard (char const *data_val, int board_size_val)
{
    thePhwangObject->printBoard(data_val, board_size_val);
}

/* malloc and free */
void *phwangMalloc (int size_val, char const *who_val)
{
    thePhwangObject->phwangMalloc(size_val, who_val);
}

void phwangFree (void *data_val, char const *who_val)
{
    thePhwangObject->phwangFree(data_val, who_val);
}

/* encode */
void phwangEncodeNumber (char *str_val, int number_val, int size_val)
{
    thePhwangObject->encodeNumber(str_val, number_val, size_val);
}

int phwangDecodeNumber (char const *str_val, int size_val)
{
    return thePhwangObject->decodeNumber(str_val, size_val);
}

void phwangEncodeIdIndex (char *str_val, int id_val, int id_size_val, int index_val, int index_size_val)
{
    thePhwangObject->encodeIdIndex(str_val, id_val, id_size_val, index_val, index_size_val);
}

void phwangDecodeIdIndex (char const *str_val, int *id_ptr_val, int id_size_val, int *index_ptr_val, int index_size_val)
{
    thePhwangObject->decodeIdIndex(str_val, id_ptr_val, id_size_val, index_ptr_val, index_size_val);
}

char *encodeString (char const *input_str_val) {
    int length_size;
    int length = strlen(input_str_val);
    char *buf = (char *) malloc(length + 7); /* 1 + 5 + length + 1 */

    char *data_ptr = buf;
    if (length < 10) {
        data_ptr[0] = '1';
        length_size = 1;
    }
    else if (length < 100) {
        data_ptr[0] = '2';
        length_size = 2;
    }
    else if (length < 1000) {
        data_ptr[0] = '3';
        length_size = 3;
    }
    else if (length < 10000) {
        data_ptr[0] = '4';
        length_size = 4;
    }
    else if (length < 100000) {
        data_ptr[0] = '5';
        length_size = 5;
    }
    data_ptr++;

    phwangEncodeNumber(data_ptr, length, length_size);
    data_ptr += length_size;
    strcpy(data_ptr, input_str_val);
    return buf;
}

char *phwangDecodeString (char const *input_val, int *input_size_val)
{
    int length = 0;
    int head_size = 2;
    char *buf;

    switch (*input_val++) {
        case '5':
            length = length * 10 + *input_val - 48;
            input_val++;
            head_size++;
 
        case '4':
            length = length * 10 + *input_val - 48;
            input_val++;
            head_size++;
 
        case '3':
            length = length * 10 + *input_val - 48;
            input_val++;
            head_size++;
 
        case '2':
            length = length * 10 + *input_val - 48;
            input_val++;
            head_size++;

       case '1':
            length = length * 10 + *input_val - 48;
            input_val++;
            
            buf = (char *) malloc(length + 1);
            memcpy(buf, input_val, length);
            buf[length] = 0;
            *input_size_val = length + head_size;
            break;

        default:
            break;
    }
    return buf;
}

/* queue */
void *phwangMallocSuspendedQueue (int size_val)
{
    return thePhwangObject->mallocQueue(true, size_val);
}

void *phwangMallocQueue (int size_val)
{
    return thePhwangObject->mallocQueue(false, size_val);
}

void phwangFreeQueue (void *queue_val, char const *who_val)
{
    if (!queue_val) {
        phwangLogit("phwangFreeQueue", who_val);
        phwangAbend("phwangFreeQueue", "null queue_val");
        //return 0;
    }

    thePhwangObject->freeQueue(queue_val);
}

void phwangEnqueue (void *queue_val, void *data_val)
{
    thePhwangObject->enqueue(queue_val, data_val);
}

void *phwangDequeue (void *queue_val, char const *who_val)
{
    if (!queue_val) {
        phwangLogit("phwangDequeue", who_val);
        phwangAbend("phwangDequeue", "null queue_val");
        //return 0;
    }

    return thePhwangObject->dequeue(queue_val);
}

/* list_mgr */
void *phwangListMgrMalloc (char const *caller_name_val, int id_size_val, int index_size_val, int global_entry_id_val)
{
    return thePhwangObject->listMgrMalloc(caller_name_val, id_size_val, index_size_val, global_entry_id_val);
}

void phwangListMgrFree (void *list_mgr_val)
{
    thePhwangObject->listMgrFree(list_mgr_val);
}

void *phwangListMgrSearchEntry (void *list_mgr_val, char const *data_val, void *extra_data_val)
{
    return thePhwangObject->listMgrSearchEntry(list_mgr_val, data_val, extra_data_val);
}

int phwnagListMgrGetMaxIndex (void *list_mgr_val, char const *who_val)
{
    return thePhwangObject->listMgrGetMaxIndex(list_mgr_val, who_val);
}

void *phwangListMgrGetEntryTableArray (void *list_mgr_val)
{
    return thePhwangObject->listMgrGetEntryTableArray(list_mgr_val);
}

void *phwangListMgrRemoveEntry (void *list_mgr_val, void *entry_val)
{
    thePhwangObject->listMgrRemoveEntry(list_mgr_val, entry_val);
}

/* array_mgr */
void *phwangArrayMgrMalloc(char const *caller_name_val, char array_type_val, int max_array_size_val)
{
    return thePhwangObject->arrayMgrMalloc(caller_name_val, array_type_val, max_array_size_val);
}

void phwangArrayMgrFree (void *array_mgr_val)
{
    thePhwangObject->arrayMgrFree(array_mgr_val);
}

void phwangArrayMgrInsertElement (void *array_mgr_val, void *element_val)
{
    thePhwangObject->arrayMgrInsertElement(array_mgr_val, element_val);
}

void phwangArrayMgrRemoveElement (void *array_mgr_val, void *element_val)
{
    thePhwangObject->arrayMgrRemoveElement(array_mgr_val, element_val);
}

void *phwangArrayMgrGetArrayTable (void *array_mgr_val, int *array_size_ptr)
{
    thePhwangObject->arrayMgrGetArrayTable(array_mgr_val, array_size_ptr);
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
    return thePhwangObject->mallocTpServer (
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
    return thePhwangObject->tpConnect (
                ip_addr_val, 
                port_val, 
                receive_callback_val, 
                receive_object_val,
                who_val);
}

void phwangFreeTpServer (void *tp_server_object_val)
{
    thePhwangObject->freeTpServer(tp_server_object_val);
}

void phwangFreeTpTransfer (void *tp_transfer_object_val)
{
    thePhwangObject->freeTpTransfer(tp_transfer_object_val);
}

void phwangTpTransmit (void *tp_transfer_object_val, char *data_val)
{
    thePhwangObject->tpTransmit(tp_transfer_object_val, data_val);
}

/* register */
void phwangRegisterProgramProcess(int *register_tag_ptr_val, char *program_name_val, unsigned short port_val)
{
    thePhwangObject->registerProgramProcess(register_tag_ptr_val, program_name_val, port_val);
}
