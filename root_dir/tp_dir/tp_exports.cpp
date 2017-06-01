/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_exports.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include "tp_class.h"
#include "tp_transfer_class.h"

TpTransferClass *TpClass::startServer (unsigned short port_val)
{
	TpTransferClass *tp_transfer_object = new TpTransferClass(this);
	if (tp_transfer_object) {
    	this->startServerThread(tp_transfer_object, port_val);
    	return tp_transfer_object;
    }
    else {
    	return 0;
    }
}
