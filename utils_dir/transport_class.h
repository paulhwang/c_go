/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../includes/common.h"

#ifndef __GO_TRANSPORT_CLASS_H__
#define __GO_TRANSPORT_CLASS_H__

#include "../root_dir/root_class.h"

class TransportClass {
  public:
    TransportClass(RootClass *root_object_val);
    ~TransportClass();

    RootClass* rootObject();

    void startServer(ushort port_val);
    void startClient(ulong ip_addr_val, ushort port_val);

  private:
    RootClass* theRootObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
