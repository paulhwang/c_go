/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang.cpp
*/

#include "phwang.h"
#include "phwang_class.h"

PhwangClass *thePhwangObject = 0;

/* init */
void phwangInit (void)
{
	if (!thePhwangObject) {
		thePhwangObject = new PhwangClass();
	}
}

/* logit */
void phwangLogit (char const* str0_val, char const* str1_val)
{
    thePhwangObject->logit(str0_val, str1_val);
}

void phwangAbend (char const* str0_val, char const* str1_val)
{
    thePhwangObject->abend(str0_val, str1_val);
}

void phwangPrintBoard (char const* data_val, int board_size_val)
{
    thePhwangObject->printBoard(data_val, board_size_val);
}

/* encode */
void phwangEncodeNumber (char *str_val, int number_val, int size_val)
{
    thePhwangObject->encodeNumber(str_val, number_val, size_val);
}

int phwangDecodeNumber (char *str_val, int size_val)
{
    return thePhwangObject->decodeNumber(str_val, size_val);
}

void phwangEncodeIdIndex (char *str_val, int id_val, int id_size_val, int index_val, int index_size_val)
{
    thePhwangObject->encodeIdIndex(str_val, id_val, id_size_val, index_val, index_size_val);
}

void phwangDecodeIdIndex (char *str_val, int *id_ptr_val, int id_size_val, int *index_ptr_val, int index_size_val)
{
    thePhwangObject->decodeIdIndex(str_val, id_ptr_val, id_size_val, index_ptr_val, index_size_val);
}

/* queue */
void *phwangMallocQueue (int size_val)
{
    return thePhwangObject->mallocQueue(size_val);
}

void phwangFreeQueue (void *queue_val)
{
    thePhwangObject->freeQueue(queue_val);
}

void phwangEnqueue (void *queue_val, void *data_val)
{
    thePhwangObject->enqueue(queue_val, data_val);
}

void *phwangDequeue (void *queue_val)
{
    return thePhwangObject->dequeue(queue_val);
}

/* list_mgr */
void *phwangMallocListMgr (char *caller_name_val, int id_size_val, int index_size_val, int global_entry_id_val)
{
    return thePhwangObject->mallocListMgr(caller_name_val, id_size_val, index_size_val, global_entry_id_val);
}

void *phwangListMgrSearchEntry(void *list_mgr_val, char *data_val)
{
    return thePhwangObject->listMgrSearchEntry(list_mgr_val, data_val);
}

/* tp */
void *phwangMallocTpServer (
                void *caller_object_val,
                unsigned short port_val,
                void (*accept_callback_func_val)(void *, void *),
                void *accept_callback_parameter_val,
                void (*receive_callback_func_val)(void *, void *),
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
                void (*receive_callback_val)(void *, void *),
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
