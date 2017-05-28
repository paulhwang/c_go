/*
  Copyrights reserved
  Written by Paul Hwang
  File name: suspend_class.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include "suspend_class.h"

SuspendClass::SuspendClass (void)
{
    this->mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    this->cond = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
    pthread_mutex_init(this->mutex, NULL);
    pthread_cond_init(this->cond, NULL);
}

SuspendClass::~SuspendClass (void)
{
    free(this->mutex);
    free(this->cond);
}

void SuspendClass::waitForEvent(void)
{

}

void SuspendClass::wakeUp(void)
{

}
