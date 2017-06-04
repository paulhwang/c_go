/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang.h
*/

#pragma once
#include "stdio.h"
#include "string.h"

/* logit.cpp */
#define LOGIT_BUF_SIZE 512
void phwangLogit(char const* str0_val, char const* str1_val);
void phwangAbend(char const* str0_val, char const* str1_val);
void phwangPrintBoard(char const* data_val, int board_size_val);

/* queue.cpp */
void *phwangMallocQueue(int size_val);
void phwangFreeQueue(void *queue_val);
void phwangEnqueue(void *queue_val, void *data_val);
void *phwangDequeue(void *queue_val);