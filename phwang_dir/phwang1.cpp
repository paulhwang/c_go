/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang1.cpp
*/

#include "phwang.h"

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
