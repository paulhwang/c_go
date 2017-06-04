/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang.h
*/

#pragma once
#include "string.h"
  
void *phwangMallocQueue(int size_val);
void phwangEenqueue(void *queue_val, void *data);
void *phwangDequeue(void *queue_val);