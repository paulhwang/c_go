/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_connect.h
*/

#pragma once

#include "../tp_dir/tp_transfer_class.h"

TpTransferClass *tpConnectServiceFunction(unsigned long ip_addr_val, unsigned short port_val, void (*receive_callback_val)(void *, void *), void *receive_object_val);
