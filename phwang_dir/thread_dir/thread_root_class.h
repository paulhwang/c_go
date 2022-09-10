/*
  Copyrights reserved
  Written by Paul Hwang
  File name: thread_root_class.h
*/

#pragma once

class ThreadRootClass
{
    char const *objectName(void) {return "ThreadRootClass";}
    int theDebugCode;

public:
    ThreadRootClass(int debug_code_val);
    ~ThreadRootClass(void);

    int pthreadCreate(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
};
