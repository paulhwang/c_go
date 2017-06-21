/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "u_fabric_class.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "../fabric_class.h"
#include "../d_fabric_dir/d_fabric_class.h"

void UFabricClass::exportedParseFunction(char *data_val)
{
    this->logit("exportedParseFunction", data_val);
    this->theFabricObject->dFabricObject()->transmitFunction(data_val);
}
