/*
  Copyrights reserved
  Written by Paul Hwang
  File name: transport_exports.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include "transport_class.h"

void TransportClass::startServer (ushort port_val)
{
    this->startServerThread(port_val);
}
