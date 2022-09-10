/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_thread.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "fabric_class.h"

void *FabricClassWatchDogThreadFunction (void *fabric_object_val)
{
    return ((FabricClass *) fabric_object_val)->watchDogThreadFunction();
}

void FabricClass::startWatchDogThread (void)
{
    phwangDebugS(false, "FabricClass::startWatchDogThread", "");

    int r = phwangPthreadCreate(&this->theWatchDogThread, 0, FabricClassWatchDogThreadFunction, this);
    if (r) {
        phwangLogitS("FabricClass::startWatchDogThread", "fail");
        return;
    }
}

void *FabricClass::watchDogThreadFunction (void)
{
    phwangDebugS(false, "abricClass::watchDogThreadFunction", "");
    while (1) {
        this->linkKeepAliveExamine();
        sleep(1);
    }
    return 0;
}
