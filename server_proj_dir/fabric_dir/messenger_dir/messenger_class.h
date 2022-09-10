/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_server_class.h
*/

#pragma once

//#include <pthread.h>
//#include "../../protocol_dir/link_mgr_protocol.h"
//#include "../fabric_class.h"

class FabricClass;
class MmwClass;

class MessengerClass {
    char const *objectName(void) {return "MessengerClass";}

    FabricClass *theFabricObject;
    MmwClass *theMmwObject;
   
public:
    MessengerClass(FabricClass *fabric_object_val);
    ~MessengerClass(void);

    FabricClass *fabricObject(void) {return this->theFabricObject;}

    void initMessenger(void);
    char *getMessage(void);
    void putMessage(char const *info_val);
};
