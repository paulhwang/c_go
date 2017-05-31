/*
  Copyrights reserved
  Written by Paul Hwang
  File name: transport_exports.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include "transport_class.h"
#include "transport_server_class.h"

TransportServerClass *TransportClass::startServer (ushort port_val)
{
	TransportServerClass *transport_server_object = new TransportServerClass(this, port_val);
	if (transport_server_object) {
    	this->startServerThread(port_val);
    	return transport_server_object;
    }
    else {
    	return 0;
    }
}
