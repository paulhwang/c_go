/*
  Copyrights reserved
  Written by Paul Hwang
  File name: root_class.h
*/

#ifndef __GO_ROOT_CLASS_H__
#define __GO_ROOT_CLASS_H__

class BaseMgrClass;
//#include "go_base_dir/go_base_class.h"
class GoBaseClass;
//#include "../utils_dir/transport_class.h"
class TransportClass;

class RootClass {
  public:
    RootClass(void);
    ~RootClass(void);

    char const* objectName(void);
    BaseMgrClass* baseMgrObject(void);
    GoBaseClass* goBaseObject(void);
    TransportClass* transportObject(void);
    void startEngine(void);

  private:
    BaseMgrClass* theBaseMgrObject;
    GoBaseClass* theGoBaseObject;
    TransportClass* theTransportObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
