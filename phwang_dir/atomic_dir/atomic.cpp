/*
  Copyrights reserved
  Written by Paul Hwang
  File name: atomic.c
*/

#include "../phwang.h"

void phwangIncrementAtomicCount (std::atomic<int> *count_val, char const *who_val, int max_count_val)
{
    (*count_val)++;
    if (*count_val > max_count_val) {
        printf("phwangIncrementAtomicCount(), count=%d\n", (*count_val).load());
        phwangAbendS("phwangIncrementAtomicCount", who_val);
    }
}

void phwangDecrementAtomicCount (std::atomic<int> *count_val, char const *who_val)
{
    (*count_val)--;
    if (*count_val < 0) {
        printf("phwangDecrementAtomicCount(), count=%d\n", (*count_val).load());
        phwangAbendS("phwangDecrementAtomicCount", who_val);
    }
}
