/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_class.cpp
*/

#include "../../../../phwang_dir/phwang.h"
#include "mmw_class.h"
#include "mmw_input_class.h"

MmwClass::MmwClass (FabricClass *fabric_object_val)
{
    phwangDebugS(true, "MmwClass::MmwClass", "start");
    
    memset(this, 0, sizeof(*this));
    this->theFabricObject = fabric_object_val;

    this->theInputQueue = phwangMallocSuspendedQueue(MMW_CLASS_INPUT_QUEUE_SIZE, this->objectName());

    this->theMmwInputObject = new MmwInputClass(this);
    this->startInputThread();
}

MmwClass::~MmwClass (void)
{
    phwangDebugS(true, "MmwClass::~MmwClass", "exit");
}

char *MmwClass::readInputData (void)
{
    char *data = (char *) phwangDequeue(this->theInputQueue, "MmwClass");
    if (data) {
        phwangDebugS(false, "MmwClass::readInputData", "data");
    }

    return data;
}
