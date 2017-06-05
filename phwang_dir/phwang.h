/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang.h
*/

#pragma once
#include "stdio.h"
#include "string.h"
#include <malloc.h>
#include "extern_dir/phwang_class.h"

extern PhwangClass *thePhwangObject;

/* logit */
#define LOGIT_BUF_SIZE 512
void phwangLogit(char const* str0_val, char const* str1_val);
void phwangAbend(char const* str0_val, char const* str1_val);
void phwangPrintBoard(char const* data_val, int board_size_val);

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
void *phwangMallocQueue(int size_val);
void phwangFreeQueue(void *queue_val);
void phwangEnqueue(void *queue_val, void *data_val);
void *phwangDequeue(void *queue_val);

/* tp */
void phwangFreeTpTransfer(void *tp_transfer_val);
void *phwangTpConnect(unsigned long ip_addr_val, unsigned short port_val, void (*receive_callback_val)(void *, void *), void *receive_object_val);
void phwangTpTransmit(void *tp_transfer_val, char *data_val);
