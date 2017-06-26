/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "../../protocol_dir/fabric_theme_protocol.h"
#include "../../protocol_dir/session_mgr_protocol.h"
#include "../../protocol_dir/group_mgr_protocol.h"
#include "../../protocol_dir/room_mgr_protocol.h"
#include "../../protocol_dir/web_fabric_protocol.h"
#include "d_fabric_class.h"
#include "../fabric_class.h"
#include "../u_fabric_dir/u_fabric_class.h"
#include "../link_class.h"
#include "../session_class.h"
#include "../group_class.h"

void DFabricClass::exportedparseFunction (char *data_val)
{
    this->logit("exportedparseFunction", data_val);

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_MALLOC_LINK) {
        this->processMallocLink(data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_MALLOC_SESSION) {
        this->processMallocSession(data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_TRANSFER_SESSION_DATA) {
        this->processTransferSessionData(data_val + 1);
        return;
    }

    this->abend("exportedparseFunction", data_val);
}

void DFabricClass::processMallocLink (char *data_val)
{
    this->logit("processMallocLink", data_val);

    char *data_buf = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    data_buf[0] = WEB_FABRIC_PROTOCOL_RESPOND_IS_MALLOC_LINK;

    LinkClass *link = this->theFabricObject->mallocLink(data_val);
    if (!link) {
        this->abend("processMallocLink", "null link");
        strcpy(data_buf + 1, "null link");
        this->transmitFunction(data_buf);
        return;
    }

    strcpy(data_buf + 1, link->linkIdIndex());
    this->transmitFunction(data_buf);
}

void DFabricClass::processMallocSession (char *data_val)
{
    this->logit("processMallocSession", data_val);

    char *data_buf = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);

    GroupClass *group = this->theFabricObject->mallocGroup();
    if (!group) {
        this->abend("processMallocSession", "null group");
        data_buf[0] = WEB_FABRIC_PROTOCOL_RESPOND_IS_MALLOC_SESSION;
        strcpy(data_buf + 1, "null group");
        this->transmitFunction(data_buf);
        return;
    }

    SessionClass *session = this->theFabricObject->searchLinkAndMallocSession(data_val);
    if (!session) {
        this->abend("processMallocSession", "null session");
        data_buf[0] = WEB_FABRIC_PROTOCOL_RESPOND_IS_MALLOC_SESSION;
        strcpy(data_buf + 1, "null session");
        this->transmitFunction(data_buf);
        return;
    }

    group->insertSession(session);
    session->bindGroup(group);

    data_buf[0] = FABRIC_THEME_PROTOCOL_COMMAND_IS_MALLOC_ROOM;
    strcpy(data_buf + 1, group->groupIdIndex());

    this->theFabricObject->uFabricObject()->transmitFunction(data_buf);
}

void DFabricClass::processTransferSessionData (char *data_val)
{
    char *downlink_data;
    char *uplink_data;
    char *data_ptr;

    this->debug(true, "processPutSessionData", data_val);

    SessionClass *session = this->theFabricObject->serachLinkAndSession(data_val);
    if (!session) {
        downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_TRANSFER_SESSION_DATA;
        strcpy(data_ptr, "null session");
        this->transmitFunction(downlink_data);
        this->abend("processPutSessionData", "null session");
        return;
    }

    char *room = session->groupObject()->roomIdIndex();
    if (!room) {
        downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_TRANSFER_SESSION_DATA;
        strcpy(data_ptr, "null room");
        this->transmitFunction(downlink_data);
        this->abend("processPutSessionData", "null room");
        return;
    }

    uplink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = FABRIC_THEME_PROTOCOL_COMMAND_IS_TRANSFER_DATA;
    memcpy(data_ptr, room, ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    data_ptr += ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE;
    strcpy(data_ptr, data_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    this->theFabricObject->uFabricObject()->transmitFunction(uplink_data);
}
