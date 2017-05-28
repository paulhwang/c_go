/*
  Copyrights reserved
  Written by Paul Hwang
  File name: suspend_class.h
*/

#pragma once

#include "logit.h"

class SuspendClass
{

public:
    SuspendClass(void);
    ~SuspendClass(void);

    void suspend(void);
    void wakeUp(void);
};
