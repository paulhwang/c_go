/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_class.h
*/

#pragma once
#include <pthread.h>

#define MMW_CLASS_INPUT_QUEUE_SIZE 5000

class FabricClass;
class MmwInputClass;

class MmwClass {
    FabricClass *theFabricObject;
    MmwInputClass *theMmwInputObject;
    pthread_t theInputThread;
    void *theInputQueue;

    MmwInputClass *mmwInputObject(void) { return this->theMmwInputObject; }

    void startInputThread(void);

  public:
    void inputThreadFunction(void);
    char *readInputData(void);

    MmwClass(FabricClass *fabric_object_val);
    ~MmwClass(void);
    char const *objectName(void) {return "MmwClass";}
};
