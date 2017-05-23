/*
  Copyrights reserved
  Written by Paul Hwang
  File name: root_class.cpp
*/

#include "../utils_dir/logit.h"
#include "base_mgr_dir/base_mgr_class.h"
#include "go_base_dir/go_base_class.h"
#include "../utils_dir/transport_class.h"
#include "root_class.h"

RootClass::RootClass (void)
{
  this->theBaseMgrObject = new BaseMgrClass(this);
  this->theGoBaseObject = new GoBaseClass(this);
  this->theTransportObject = new TransportClass(this);

  if (1) {
  	this->logit("RootClass", "init");
  }
}

RootClass::~RootClass (void)
{
}

BaseMgrClass* RootClass::baseMgrObject(void)
{
  return this->theBaseMgrObject;
}

GoBaseClass* RootClass::goBaseObject(void)
{
  return this->theGoBaseObject;
}

TransportClass* RootClass::transportObject(void)
{
  return this->theTransportObject;
}

char const* RootClass::objectName (void)
{
  return "RootClass";
}

void RootClass::startEngine (void)
{

}

void RootClass::logit (char const* str0_val, char const* str1_val)
{
	LOGIT(str0_val, str1_val);
}

void RootClass::abend (char const* str0_val, char const* str1_val)
{
	ABEND(str0_val, str1_val);
}


