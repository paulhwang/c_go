/*
  Copyrights reserved
  Written by Paul Hwang
  File name: transport_server_class.cpp
*/

#include "transport_server_class.h"

TransportServerClass::TransportServerClass (void *transport_object_val, unsigned short port_val)
{
	this->transport_object = transport_object_val;
	this->port = port_val;
}

TransportServerClass::~TransportServerClass (void)
{
}
