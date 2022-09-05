/*
  Copyrights reserved
  Written by Paul Hwang
  File name: thread_root_class.h
*/

#pragma once

class ThreadRootClass
{
    char const *objectName(void) {return "ThreadRootClass";}

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    ThreadRootClass(int debug_code_val);
    ~ThreadRootClass(void);

    int pthreadCreate(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
};
