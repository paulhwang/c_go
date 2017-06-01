/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_class.cpp
*/

#include "tp_transfer_class.h"

TpTransferClass::TpTransferClass (void *tp_object_val, int socket_val)
{
	this->tp_object = tp_object_val;
	this->theSocket = socket_val;
}

TpTransferClass::~TpTransferClass (void)
{
}
