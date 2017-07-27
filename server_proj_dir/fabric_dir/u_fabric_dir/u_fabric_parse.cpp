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
    this->debug(false, "exportedParseFunction", data_val);

    if (*data_val == FABRIC_THEME_PROTOCOL_RESPOND_IS_SETUP_ROOM) {
        this->processSetupRoomResponse(data_val + 1);
        return;
    }

    if (*data_val == FABRIC_THEME_PROTOCOL_RESPOND_IS_PUT_ROOM_DATA) {
        this->processPutRoomDataResponse(data_val + 1);
        return;
    }

    this->abend("exportedParseFunction", data_val);
}

void UFabricClass::processSetupRoomResponse(char *data_val)
{
    this->debug(true, "processSetupRoomResponse", data_val);

    char *ajax_id = data_val;
    char *group_id_index_val = ajax_id + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;

    char *downlink_data;
    char *data_ptr;
	char *output_data;
    int session_array_size;

    GroupClass *group = this->theFabricObject->searchGroup(group_id_index_val);
    if (group) {
        group->setRoomIdIndex(group_id_index_val + GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE);
        group->setSessionTableArray((SessionClass **) phwangArrayMgrGetArrayTable(group->sessionArrayMgr(), &session_array_size));
        SessionClass *session = group->sessionTableArray(0);

        downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_SETUP_SESSION;

        memcpy(data_ptr, ajax_id, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
        data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;

        strcpy(data_ptr, session->sessionIdIndex());
        this->theFabricObject->dFabricObject()->transmitFunction(downlink_data);
    }
}

void UFabricClass::processPutRoomDataResponse(char *data_val)
{
    char *downlink_data;
    char *data_ptr;
    int session_array_size;

    this->debug(true, "processPutRoomDataResponse", data_val);

    GroupClass *group = this->theFabricObject->searchGroup(data_val);
    if (!group) {
        this->abend("processPutRoomDataResponse", "null group");
        return;
    }
    data_val += GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE;

    group->setSessionTableArray((SessionClass **) phwangArrayMgrGetArrayTable(group->sessionArrayMgr(), &session_array_size));
    for (int i = 0; i < session_array_size; i++) {
        SessionClass *session = group->sessionTableArray(i);
        if (session) {
            session->enqueuePendingDownLinkData(data_val);

            if (0) {
            downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
            *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_PUT_SESSION_DATA;
            memcpy(data_ptr, session->linkObject()->linkIdIndex(), LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE);
            data_ptr += LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;
            memcpy(data_ptr, session->sessionIdIndex(), SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
            data_ptr += SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
            strcpy(data_ptr, data_val);
            this->theFabricObject->dFabricObject()->transmitFunction(downlink_data);
            }
        }
    }
}
