/*
  Copyrights reserved
  Written by Paul Hwang
  File name: engine_class.cpp
*/

#include <stdio.h>
#include "utils_dir/logit.h"
#include "root_dir/base_mgr_dir/base_mgr_class.h"
#include "engine_class.h"
#include "root_dir/root_class.h"
#include "utils_dir/transport_class.h"

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

RootClass* EngineClass::rootObject (void)
{
    return this->theRootObject;
}

TransportClass* EngineClass::transportObject (void)
{
    return this->theTransportObject;
}

void EngineClass::setTransportObject (TransportClass* val)
{
    this->theTransportObject = val;
}

void EngineClass::setBaseMgrObject (BaseMgrClass* val)
{
    this->theGoBaseMgrObject = val;
}

void* createGoRoot (void* this_val)
{
    EngineClass* engine_object = (EngineClass *)this_val;
    printf("***************createGoRoot starts\n");
    engine_object->setBaseMgrObject(new BaseMgrClass(engine_object->rootObject()));
}

void* createTransport (void* this_val)
{
    EngineClass* engine_object = (EngineClass *)this_val;

    printf("***************createTransport starts\n");
    engine_object->setTransportObject(new TransportClass(engine_object->rootObject()));
    engine_object->transportObject()->startServer(8001);
}

void EngineClass::startEngine (void)
{
    this->theRootObject = new RootClass();

    this->logit("startEngine", "create theGoThread");
    int r = pthread_create(&this->theGoThread, NULL, createGoRoot, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }

    this->logit("startEngine", "create theTransportThread");
    r = pthread_create(&this->theTransportThread, NULL, createTransport, this);
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


