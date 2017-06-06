/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang.h
*/

#pragma once
#include "stdio.h"
#include "string.h"
#include <malloc.h>
#include "extern_dir/phwang_base.h"
#include "extern_dir/phwang_class.h"
#include "tp_dir/tp_connect.h"

/* init */
inline void phwangInit (void)
{
    initPhwangObject();
}

/* logit */
#define LOGIT_BUF_SIZE 512

inline void phwangLogit (char const* str0_val, char const* str1_val)
{
    thePhwangObject->logit(str0_val, str1_val);
}

inline void phwangAbend (char const* str0_val, char const* str1_val)
{
    thePhwangObject->abend(str0_val, str1_val);
}

inline void phwangPrintBoard (char const* data_val, int board_size_val)
{
    thePhwangObject->printBoard(data_val, board_size_val);
}

/* encode */
inline void phwangEncodeNumber (char *str_val, int number_val, int size_val)
{
    thePhwangObject->encodeNumber(str_val, number_val, size_val);
}

inline int phwangDecodeNumber (char *str_val, int size_val)
{
    return thePhwangObject->decodeNumber(str_val, size_val);
}

inline void phwangEncodeIdIndex (char *str_val, int id_val, int id_size_val, int index_val, int index_size_val)
{
    thePhwangObject->encodeIdIndex(str_val, id_val, id_size_val, index_val, index_size_val);
}

inline void phwangDecodeIdIndex (char *str_val, int *id_ptr_val, int id_size_val, int *index_ptr_val, int index_size_val)
{
    thePhwangObject->decodeIdIndex(str_val, id_ptr_val, id_size_val, index_ptr_val, index_size_val);
}

/* queue */
inline void *phwangMallocQueue(int size_val)
{
    return thePhwangObject->mallocQueue(size_val);
}

inline void phwangFreeQueue(void *queue_val)
{
    thePhwangObject->freeQueue(queue_val);
}

inline void phwangEnqueue(void *queue_val, void *data_val)
{
    thePhwangObject->enqueue(queue_val, data_val);
}

inline void *phwangDequeue(void *queue_val)
{
    return thePhwangObject->dequeue(queue_val);
}

/* tp */
inline void *phwangMallocTpServer (
                void *caller_object_val,
                unsigned short port_val,
                void (*accept_callback_func_val)(void *, void *),
                void *accept_callback_parameter_val,
                void (*receive_callback_func_val)(void *, void *),
                void *receive_callback_parameter_val)
{
    return thePhwangObject->mallocTpServer(
                caller_object_val,
                port_val,
                accept_callback_func_val,
                accept_callback_parameter_val,
                receive_callback_func_val,
                receive_callback_parameter_val);
}

inline void *phwangTpConnect(
                unsigned long ip_addr_val,
                unsigned short port_val,
                void (*receive_callback_val)(void *, void *),
                void *receive_object_val)
{
    return thePhwangObject->tpConnect(
                ip_addr_val, 
                port_val, 
                receive_callback_val, 
                receive_object_val);
}

inline void phwangFreeTpServer(void *tp_server_object_val)
{
    thePhwangObject->freeTpServer(tp_server_object_val);
}

inline void phwangFreeTpTransfer(void *tp_transfer_object_val)
{
    thePhwangObject->freeTpTransfer(tp_transfer_object_val);
}

inline void phwangTpTransmit(void *tp_transfer_object_val, char *data_val)
{
    thePhwangObject->tpTransmit(tp_transfer_object_val, data_val);
}
