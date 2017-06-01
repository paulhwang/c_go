/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_server_class.cpp
*/

#include "tp_server_class.h"

TpServerClass::TpServerClass (void *transport_object_val, unsigned short port_val)
{
	this->transport_object = transport_object_val;
	this->thePort = port_val;
}

TpServerClass::~TpServerClass (void)
{
}
