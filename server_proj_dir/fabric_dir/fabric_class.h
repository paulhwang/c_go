/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_class.h
*/

#pragma once

class UFabricClass;
class DFabricClass;

class FabricClass {
    UFabricClass *theUFabricObject;
    DFabricClass *theDFabricObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    FabricClass(void);
    ~FabricClass(void);
    char const* objectName(void) {return "FabricClass";}
    UFabricClass *uFabricObject(void) {return this->theUFabricObject;}
    DFabricClass *dFabricObject(void) {return this->theDFabricObject;}

    void startThreads(void);};
