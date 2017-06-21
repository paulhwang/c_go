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
	char output_data;

    this->debug(true, "processMallocRoomResponse", data_val);

/*
    GroupClass *group;
    *output_data = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    output_data[0] = WEB_FABRIC_PROTOCOL_RESPOND_IS_MALLOC_SESSION;
    phwangEncodeIdIndex(output_data + 1, session_object_val->sessionId(), SESSION_MGR_PROTOCOL_SESSION_ID_SIZE, session_object_val->sessionIndex(), SESSION_MGR_PROTOCOL_SESSION_INDEX_SIZE);
    this->theFabricObject->dFabricObject()->transmitFunction(output_data);
*/
}

void UFabricClass::processGetSessionDataResponse(char *data_val)
{
    this->debug(true, "processGetSessionDataResponse", data_val);

}

void UFabricClass::processPutSessionDataResponse(char *data_val)
{
    this->debug(true, "processPutSessionDataResponse", data_val);

}
