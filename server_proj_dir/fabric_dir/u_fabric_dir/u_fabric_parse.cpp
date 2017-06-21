/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "../../protocol_dir/fabric_theme_protocol.h"
#include "u_fabric_class.h"
#include "../fabric_class.h"
#include "../d_fabric_dir/d_fabric_class.h"

void UFabricClass::exportedParseFunction(char *data_val)
{
    this->debug(true, "exportedParseFunction", data_val);

    if (*data_val == FABRIC_THEME_PROTOCOL_RESPOND_IS_MALLOC_ROOM) {
        this->processMallocRoomResponse(++data_val);
    }
}

void UFabricClass::processMallocRoomResponse(char *data_val)
{
    this->debug(true, "processMallocRoomResponse", data_val);

    //this->theFabricObject->dFabricObject()->transmitFunction(data_val);
}

void UFabricClass::processGetSessionDataResponse(char *data_val)
{
    this->debug(true, "processGetSessionDataResponse", data_val);

}

void UFabricClass::processPutSessionDataResponse(char *data_val)
{
    this->debug(true, "processPutSessionDataResponse", data_val);

}
