/*
  Copyrights reserved
  Written by Paul Hwang
  File name: engine_class.cpp
*/

#include <stdio.h>
#include "engine_class.h"
#include "./root_dir/root_class.h"
#include "./utils_dir/transport_class.h"

EngineClass::EngineClass(void)
{

}

EngineClass::~EngineClass(void)
{
}

char const* EngineClass::objectName (void)
{
    return "EngineClass";
}

void* createGoRoot (void* ptr_val) {
    RootClass* root_object = new RootClass();
  	root_object->transportObject()->startServer(8001);
}

void* createTransport (void* ptr_val) {
    printf("***************createTransport starts\n");
}

void EngineClass::startEngine (void)
{
    int r = pthread_create(&this->theGoThread, NULL, createGoRoot, 0);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }

    r = pthread_create(&this->theTransportThread, NULL, createTransport, 0);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }

    pthread_join(this->goThread(), NULL);
    pthread_join(this->transportThread(), NULL);
}

pthread_t EngineClass::goThread (void)
{
    return this->theGoThread;
}

pthread_t EngineClass::transportThread (void)
{
    return this->theTransportThread;
}

void logit(char const* str0_val, char const* str1_val)
{

}

void abend(char const* str0_val, char const* str1_val)
{

}

