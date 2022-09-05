/*
  Copyrights reserved
  Written by Paul Hwang
  File name: object_class.h
*/

#pragma once

class ObjectClass
{
    char const *objectName(void) {return "ObjectClass";}

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    ObjectClass(void);
    ~ObjectClass(void);

    void incrementObjectCount(int *object_count_val, char const *object_name_val, int max_object_count_val);
    void decrementObjectCount(int *object_count_val);
};
