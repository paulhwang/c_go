/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_class.cpp
*/

#include <stdio.h>
#include "../root_common.h"
#include "../../utils_dir/logit.h"
#include "base_mgr_class.h"
#include "base_class.h"
#include "../../engine_class.h"
#include "../go_base_dir/go_base_class.h"

BaseMgrClass::BaseMgrClass (EngineClass *engine_object_val)
{
    this->theEngineObject = engine_object_val;

    if (1) {
        this->logit("init", "");
    }
}

BaseMgrClass::~BaseMgrClass (void)
{
}

char const* BaseMgrClass::objectName (void)
{
    return "BaseMgrClass";
}

EngineClass* BaseMgrClass::engineObject (void)
{
    return this->theEngineObject;
}

GoBaseClass* BaseMgrClass::goBaseObject(void)
{
    return this->theGoBaseObject;
}

BaseClass* BaseMgrClass::getBase (int base_id_val) {
    return 0;
}

void BaseMgrClass::createBase (void)
{
    BaseClass *base = new BaseClass(this);
    //this->theGoBaseObject = new GoBaseClass(this);
}

void BaseMgrClass::receiveData (int base_id_val, char* data_val) {
    this->logit("receiveData", data_val);
    BaseClass* base = this->getBase(base_id_val);
    if (!base) {
        return;
    }
    //base->portObject()->receiveStringData(data_val);
}

void BaseMgrClass::baseMgrLogit (char const* str0_val, char const* str1_val) {
    LOGIT(str0_val, str1_val);
}

void BaseMgrClass::baseMgrAbend (char const* str0_val, char const* str1_val) {
    LOGIT(str0_val, str1_val);
}

void BaseMgrClass::logit (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->baseMgrLogit(s, str1_val);
}

void BaseMgrClass::abend (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->baseMgrAbend(s, str1_val);
}

