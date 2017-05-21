/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_class.cpp
*/

#include <string.h>
#include "../../utils_dir/logit.h"
#include "../root_class.h"
#include "base_class.h"
#include "base_mgr_class.h"

BaseMgrClass::BaseMgrClass (RootClass* root_object_val) {
  this->theRootObject = root_object_val;

  if (1) {
    this->logit("BaseMgrClass", "init");
  }
}

BaseMgrClass::~BaseMgrClass () {
}

char const* BaseMgrClass::objectName () {
  return "BaseMgrClass";
}

RootClass* BaseMgrClass::rootObject () {
  return this->theRootObject;
}

BaseClass* BaseMgrClass::getBase (int base_id_val) {
  return 0;
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
  char s[80];
  strcat(s, this->objectName());
  strcat(s, "::");
  strcat(s, str0_val);
  this->baseMgrLogit(s, str1_val);
}

void BaseMgrClass::abend (char const* str0_val, char const* str1_val) {
  char s[80];
  strcat(s, this->objectName());
  strcat(s, "::");
  strcat(s, str0_val);
  this->baseMgrAbend(s, str1_val);
}

