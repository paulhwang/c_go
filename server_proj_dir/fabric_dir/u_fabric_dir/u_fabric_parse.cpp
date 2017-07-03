/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "../../protocol_dir/fabric_theme_protocol.h"
#include "../../protocol_dir/web_fabric_protocol.h"
#include "../../protocol_dir/session_mgr_protocol.h"
#include "u_fabric_class.h"
#include "../fabric_class.h"
#include "../d_fabric_dir/d_fabric_class.h"
#include "../link_class.h"
#include "../session_class.h"
#include "../group_class.h"

void UFabricClass::exportedParseFunction(char *data_val)
{
    this->debug(true, "exportedParseFunction", data_val);

    if (*data_val == FABRIC_THEME_PROTOCOL_RESPOND_IS_MALLOC_ROOM) {
        this->processMallocRoomResponse(data_val + 1);
        return;
    }

    if (*data_val == FABRIC_THEME_PROTOCOL_RESPOND_IS_TRANSFER_DATA) {
        this->processTransferDataResponse(data_val + 1);
        return;
    }

    this->abend("exportedParseFunction", data_val);
}

void UFabricClass::processMallocRoomResponse(char *data_val)
{
	char *output_data;
    int session_array_size;

    this->debug(true, "processMallocRoomResponse", data_val);

    GroupClass *group = this->theFabricObject->searchGroup(data_val);
    if (group) {
        group->setRoomIdIndex(data_val + GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE);
        group->setSessionTableArray((SessionClass **) phwangArrayMgrGetArrayTable(group->sessionArrayMgr(), &session_array_size));
        SessionClass *session = group->sessionTableArray(0);
        output_data = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        output_data[0] = WEB_FABRIC_PROTOCOL_RESPOND_IS_MALLOC_SESSION;
        strcpy(output_data + 1, session->sessionIdIndex());
        this->theFabricObject->dFabricObject()->transmitFunction(output_data);
    }
}

void UFabricClass::processTransferDataResponse(char *data_val)
{
    char *downlink_data;
    char *data_ptr;
    int session_array_size;

    this->debug(true, "processTransferDataResponse", data_val);

    GroupClass *group = this->theFabricObject->searchGroup(data_val);
    if (!group) {
        this->abend("processTransferDataResponse", "null group");
        return;
    }
    data_val += GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE;

    group->setSessionTableArray((SessionClass **) phwangArrayMgrGetArrayTable(group->sessionArrayMgr(), &session_array_size));
    for (int i = 0; i < session_array_size; i++) {
        SessionClass *session = group->sessionTableArray(i);
        if (session) {
            downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
            *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_TRANSFER_SESSION_DATA;
            memcpy(data_ptr, session->linkObject()->linkIdIndex(), LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE);
            data_ptr += LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;
            memcpy(data_ptr, session->sessionIdIndex(), SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
            data_ptr += SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
            strcpy(data_ptr, data_val);
            this->theFabricObject->dFabricObject()->transmitFunction(downlink_data);
        }
    }
}
