/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_threads.cpp
*/

#include "engine_class.h"

void *goBaseMgrReceiveThreadFunction (void *this_val)
{
    ((EngineClass *)this_val)->goBaseMgrReceiveThreadLoop();
}

void *transportTransmitThreadFunction (void *this_val)
{
    ((EngineClass *)this_val)->transportTransmitThreadLoop();
}
