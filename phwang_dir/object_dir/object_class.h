/*
  Copyrights reserved
  Written by Paul Hwang
  File name: object_class.h
*/

#pragma once

#include <atomic>

class ObjectClass
{
    char const *objectName(void) {return "ObjectClass";}
    int theDebugCode;

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    ObjectClass(int debug_code_val);
    ~ObjectClass(void);

    void incrementObjectCount(int *object_count_val, char const *who_val, int max_object_count_val);
    void decrementObjectCount(int *object_count_val);
    void incrementAtomicCount(std::atomic<int> *count_val, char const *object_name_val, int max_count_val);
    void decrementAtomicCount(std::atomic<int> *count_val);
};
