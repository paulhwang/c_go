/*
  Copyrights reserved
  Written by Paul Hwang
  File name: messenger_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "messenger_class.h"
#include "mmw_dir/mmw_class.h"
#include "../fabric_class.h"

MessengerClass::MessengerClass (FabricClass *fabric_object_val)
{
    memset(this, 0, sizeof(MessengerClass));

    phwangDebugS(false, "MessengerClass::MessengerClass", "init");
}

MessengerClass::~MessengerClass (void)
{
}

void MessengerClass::initMessenger (void)
{
    phwangDebugS(true, "MessengerClass::initMessenger", "init");
    this->theMmwObject = new MmwClass(this->fabricObject());
}

char *MessengerClass::getMessage (void)
{
    char *data = this->theMmwObject->readInputData();
    phwangDebugS(true, "MessengerClass::getMessage", data);
    return data;
}

void MessengerClass::putMessage (char const *info_val)
{
    phwangDebugSS(true, "MessengerClass::putMessage", "data=", info_val);
}
