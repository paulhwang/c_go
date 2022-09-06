/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang.h
*/

#pragma once
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <pthread.h>
#include "phwang_class.h"

/* init */
void phwangPhwangPhwang(int debug_code_val);

/* pthread */
int phwangPthreadCreate(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

/* logit */
void phwangDebug(int on_off_val, char const *func_name_val, char const *str1_val);
void phwangDebug2(int on_off_val, char const *func_name_val, char const *str1_val, char const *str2_val);

void phwangDebugInt(int on_off_val, char const *func_name_val, char const *str1_val, int int1_val);
void phwangDebugInt2(int on_off_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);

void phwangLogit(char const *func_name_val, char const *str1_val);
void phwangLogit2(char const *func_name_val, char const *str1_val, char const *str2_val);

void phwangLogitInt(char const *func_name_val, char const *str1_val, int int1_val);
void phwangLogitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);

void phwangAbend(char const *func_name_val, char const *str1_val);
void phwangAbend2(char const *func_name_val, char const *str1_val, char const *str2_val);

void phwangComposeFuncName(char *buf_val, char const *object_name_val, char const *func_name_val);

/* malloc and free */
void *phwangMalloc(int size_val, int who_val);
void  phwangFree(void *data_val);
char *phwangMallocConstStrBuf(char const * str_val);

/* encode */
void  phwangEncodeNumber(char *str_val, int number_val, int size_val);
void  phwangEncodeNumberNull(char *str_val, int number_val, int size_val);
char *phwangEncodeNumberMalloc(int number_val, int size_val);
int   phwangDecodeNumber(char const *str_val, int size_val);
int   phwangDecodeNumberNull(char const *str_val);

int   phwangGetEncodeStringMallocSize(char const *str_val);
void  phwangEncodeString (char *output_buf_val, char const *input_str_val);
char *phwangEncodeStringMalloc(char const *input_str_val);
char *phwangDecodeStringMalloc(char const *input_val, int *input_size_val);

void  phwangEncodeIdIndex(char *str_val, int id_val, int id_size_val, int index_val, int index_size_val);
void  phwangDecodeIdIndex(char const *str_val, int *id_ptr_val, int id_size_val, int *index_ptr_val, int index_size_val);

/* object_count */
void phwangIncrementObjectCount(int *object_count_val, char const *object_name_val, int max_object_count_val);
void phwangDecrementObjectCount(int *object_count_val);

/* queue */
void *phwangMallocSuspendedQueue(int size_val);
void *phwangMallocQueue(int size_val);
void  phwangFreeQueue(void *queue_val, char const *who_val);
void  phwangEnqueue(void *queue_val, void *data_val);
void *phwangDequeue(void *queue_val, char const *who_val);

/* list_mgr */
void *phwangListMgrMalloc(char const *caller_name_val, int id_size_val, int index_size_val, int global_entry_id_val);
void  phwangListMgrFree(void *list_mgr_val);
void  phwangListMgrRemoveEntry(void *list_mgr_val, void *entry_val);
void *phwangListMgrSearchEntry(void *list_mgr_val, char const *data_val, void *extra_data_val);
int   phwnagListMgrGetMaxIndex(void *list_mgr_val, char const *who_val);
void *phwangListMgrGetEntryTableArray(void *list_mgr_val);

/* array_mgr */
void *phwangArrayMgrMalloc(char const *caller_name_val, char array_type_val, int array_size_val);
void  phwangArrayMgrFree(void *array_mgr_val);
void  phwangArrayMgrInsertElement(void *array_mgr_val, void *element_val);
void  phwangArrayMgrRemoveElement(void *array_mgr_val, void *element_val);
void *phwangArrayMgrGetArrayTable(void *array_mgr_val, int *array_size_ptr);

/* tp */
void *phwangMallocTpServer(
                void *caller_object_val,
                unsigned short port_val,
                void (*accept_callback_func_val)(void *, void *),
                void *accept_callback_parameter_val,
                void (*receive_callback_func_val)(void *, void *, void *),
                void *receive_callback_parameter_val,
                char const *who_val);
void *phwangTpConnect(
                unsigned long ip_addr_val,
                unsigned short port_val,
                void (*receive_callback_val)(void *, void *, void *),
                void *receive_object_val,
                char const *who_val);
void phwangFreeTpServer(void *tp_server_object_val);
void phwangFreeTpTransfer(void *tp_transfer_object_val);
void phwangTpTransmit(void *tp_transfer_object_val, char *data_val);
int  phwangReceiveThreadCount(void);
void phwangIncrementReceiveThreadCount(void);

/* register */
void phwangRegisterProgramProcess(int *register_tag_ptr_val, char *program_name_val, unsigned short port_val);
