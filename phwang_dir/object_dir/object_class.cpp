/*
  Copyrights reserved
  Written by Paul Hwang
  File name: object_class.cpp
*/

#include "../phwang.h"
#include "object_class.h"

ObjectClass::ObjectClass (int debug_code_val)
{
    memset(this, 0, sizeof (*this));
    this->theDebugCode = debug_code_val;
}

ObjectClass::~ObjectClass(void)
{
}

void ObjectClass::incrementObjectCount(int *object_count_val, char const *object_name_val, int max_object_count_val)
{
    (*object_count_val)++;
    if (*object_count_val > max_object_count_val) {
        printf("incrementObjectCount(), count=%d\n", *object_count_val);
        phwangAbend("incrementObjectCount", object_name_val);
    }
}

void ObjectClass::decrementObjectCount(int *object_count_val)
{
    (*object_count_val)--;
    if (*object_count_val < 0) {
        printf("decrementObjectCount(), count=%d\n", *object_count_val);
        phwangAbend("decrementObjectCount", "too small");
    }
}

void ObjectClass::incrementAtomicCount(std::atomic<int> *count_val, char const *who_val, int max_count_val)
{
    (*count_val)++;
    if (*count_val > max_count_val) {
        printf("incrementAtomicCount(), count=%d\n", (*count_val).load());
        phwangAbend("incrementAtomicCount", who_val);
    }
}

void ObjectClass::decrementAtomicCount(std::atomic<int> *count_val)
{
    (*count_val)--;
    if (*count_val < 0) {
        printf("decrementAtomicCount(), count=%d\n", (*count_val).load());
        phwangAbend("decrementAtomicCount", "too small");
    }
}

void ObjectClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void ObjectClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
