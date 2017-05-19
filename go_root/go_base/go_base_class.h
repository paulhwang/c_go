/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_BASE_CLASS_H__
#define __GO_BASE_CLASS_H__

class goRootClass;
class GoEngineClass;
class GoBoardClass;
class GoPortClass;
class GoConfigClass;
class GoGameClass;

class GoBaseClass {
  public:
    GoBaseClass(goRootClass* root_object_val);
    ~GoBaseClass();

    char const* objectName();
    goRootClass* rootObject();
    GoEngineClass* engineObject();
    GoBoardClass* boardObject();
    GoPortClass* portObject();
    GoConfigClass* configObject();
    GoGameClass* gameObject();

  private:
  	goRootClass* theRootObject;
  	GoEngineClass* theEngineObject;
    GoBoardClass* theBoardObject;
    GoPortClass* thePortObject;
    GoConfigClass* theConfigObject;
    GoGameClass* theGameObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
