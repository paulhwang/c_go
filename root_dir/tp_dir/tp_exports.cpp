/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_exports.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include "tp_class.h"
#include "tp_server_class.h"

TpServerClass *TpClass::startServer (unsigned short port_val)
{
	TpServerClass *transport_server_object = new TpServerClass(this, port_val);
	if (transport_server_object) {
    	this->startServerThread(transport_server_object);
    	return transport_server_object;
    }
    else {
    	return 0;
    }
}
