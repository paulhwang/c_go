/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_BASE_CLASS_H__
#define __GO_BASE_CLASS_H__

class go_root_class;
class GoEngineClass;
class GoBoardClass;
class GoPortClass;
class GoConfigClass;
class GoGameClass;

class GoBaseClass {
  public:
    GoBaseClass(go_root_class* root_object_val);
    ~GoBaseClass();

    char const* objectName();
    go_root_class* rootObject();
    GoEngineClass* engineObject();
    GoBoardClass* boardObject();
    GoPortClass* portObject();
    GoConfigClass* configObject();
    GoGameClass* gameObject();

  private:
  	go_root_class* theRootObject;
  	GoEngineClass* theEngineObject;
    GoBoardClass* theBoardObject;
    GoPortClass* thePortObject;
    GoConfigClass* theConfigObject;
    GoGameClass* theGameObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
