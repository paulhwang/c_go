/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../includes/common.h"

#ifndef __GO_TRANSPORT_CLASS_H__
#define __GO_TRANSPORT_CLASS_H__

class EngineClass;
//#include "../root_dir/root_class.h"

class TransportClass {
  public:
    TransportClass(void *engine_object_val);
    ~TransportClass();

    void *engineObject();

    void startServer(ushort port_val);
    void startClient(ulong ip_addr_val, ushort port_val);

  private:
    void *theEngineObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
