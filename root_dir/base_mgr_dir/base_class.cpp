/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_class.cpp
*/

#include "base_mgr_class.h"
#include "base_class.h"

BaseClass::BaseClass (BaseMgrClass* base_mgr_object_val) {
  this->theBaseMgrObject = base_mgr_object_val;

  if (1) {
    this->logit("BaseClass", "init");
  }
}

BaseClass::~BaseClass () {
}

char const* BaseClass::objectName () {
  return "BaseClass";
}

BaseMgrClass* BaseClass::baseMgrObject () {
  return this->theBaseMgrObject;
}

void BaseClass::receiveData (char* data_val) {
  this->logit("receiveData", data_val);
  //base->portObject()->receiveStringData(data_val);
}

void BaseClass::logit (char const* str0_val, char const* str1_val) {
	this->baseMgrObject()->baseMgrLogit(str0_val, str1_val);
}

void BaseClass::abend (char const* str0_val, char const* str1_val) {
  this->baseMgrObject()->baseMgrAbend(str0_val, str1_val);
}

