/*
  Copyrights reserved
  Written by Paul Hwang
  File name: engine_class.cpp
*/

#include <stdio.h>
#include "utils_dir/logit.h"
#include "root_dir/base_mgr_dir/base_mgr_class.h"
#include "engine_class.h"
#include "utils_dir/transport_class.h"

void* createGoBaseMgrFunction (void* this_val)
{
    ((EngineClass *)this_val)->createGoBaseMgrObject();
}

void* createTransportFunction (void* this_val)
{
    ((EngineClass *)this_val)->createTransportObject();
}

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

TransportClass* EngineClass::transportObject (void)
{
    return this->theTransportObject;
}

BaseMgrClass* EngineClass::goBaseMgrObject (void)
{
    return this->theGoBaseMgrObject;
}

void EngineClass::setTransportObject (TransportClass* val)
{
    this->theTransportObject = val;
}

void EngineClass::setGoBaseMgrObject (BaseMgrClass* val)
{
    this->theGoBaseMgrObject = val;
}

void EngineClass::createGoBaseMgrObject (void)
{
    printf("******===*********createGoRoot starts\n");
    this->setGoBaseMgrObject(new BaseMgrClass());
    this->goBaseMgrObject()->createGoBase();

}

void EngineClass::createTransportObject (void)
{
    printf("***************createTransport starts\n");
    this->setTransportObject(new TransportClass(this));
    this->transportObject()->startServer(8001);
}

void EngineClass::startEngine (void)
{
    this->logit("startEngine", "create theGoThread");
    int r = pthread_create(&this->theGoThread, NULL, createGoBaseMgrFunction, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }

    this->logit("startEngine", "create theTransportThread");
    r = pthread_create(&this->theTransportThread, NULL, createTransportFunction, this);
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

void EngineClass::logit (char const* str0_val, char const* str1_val)
{
    LOGIT(str0_val, str1_val);
}

void EngineClass::abend (char const* str0_val, char const* str1_val)
{
    ABEND(str0_val, str1_val);
}

