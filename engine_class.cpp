/*
  Copyrights reserved
  Written by Paul Hwang
  File name: engine_class.cpp
*/

#include "engine_class.h"

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

void EngineClass::startEngine (void)
{

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

