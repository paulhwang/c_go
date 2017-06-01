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
    this->theTpTransferObject = new TpTransferClass(this);
	  if (this->theTpTransferObject) {
    	  this->startServerThread(this->theTpTransferObject, port_val);
    	  return this->theTpTransferObject;
    }
    else {
    	  return 0;
    }
}
