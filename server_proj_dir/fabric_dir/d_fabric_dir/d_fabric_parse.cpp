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
#include "../name_list_class.h"

void DFabricClass::exportedparseFunction (char *data_val)
{
    this->logit("exportedparseFunction", data_val);

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_MALLOC_LINK) {
        this->processMallocLink(data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_GET_LINK_DATA) {
        this->processGetLinkData(data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_GET_NAME_LIST) {
        this->processGetNameList(data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_MALLOC_SESSION) {
        this->processMallocSession(data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_MALLOC_SESSION_REPLY) {
        this->processMallocSessionReply(data_val + 1);
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
    char *downlink_data;
    char *data_ptr;

    this->debug(true, "processMallocLink", data_val);

    LinkClass *link = this->theFabricObject->mallocLink(data_val);
    if (!link) {
        this->abend("processMallocLink", "null link");
        downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_MALLOC_LINK;
        strcpy(data_ptr, "null link");
        this->transmitFunction(downlink_data);
        return;
    }

    downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_MALLOC_LINK;
    strcpy(data_ptr, link->linkIdIndex());
    this->transmitFunction(downlink_data);
}

void DFabricClass::processGetLinkData (char *data_val)
{
    this->debug(true, "processGetLinkData", data_val);

    char *link_id_index_val = data_val;
    char *end_val = link_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;
    char *downlink_data;
    char *data_ptr;

    LinkClass *link = this->theFabricObject->searchLink(link_id_index_val);
    if (!link) {
        this->abend("processGetLinkData", "link does not exist");
        downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA;
        strcpy(data_ptr, "link does not exist");
        this->transmitFunction(downlink_data);
        return;
    }
    downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA;
    phwangEncodeNumber(data_ptr, this->theFabricObject->nameListObject()->nameListTag(), NAME_LIST_CLASS_NAME_LIST_TAG_SIZE);
    data_ptr += NAME_LIST_CLASS_NAME_LIST_TAG_SIZE;
    *data_ptr = 0;

    char *pending_session = link->getPendingSessionSetup();
    if (pending_session) {
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA_PENDING_SESSION;
        strcpy(data_ptr, pending_session);
    }

    this->transmitFunction(downlink_data);
}

void DFabricClass::processGetNameList (char *data_val)
{
    this->debug(true, "processGetNameList", data_val);

    char *link_id_index_val = data_val;
    char *name_list_tag_val = link_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;
    char *end_val = name_list_tag_val + 3;
    char *downlink_data;
    char *data_ptr;

    LinkClass *link = this->theFabricObject->searchLink(link_id_index_val);
    if (!link) {
        this->abend("processGetNameList", "link does not exist");
        downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_NAME_LIST;
        strcpy(data_ptr, "link does not exist");
        this->transmitFunction(downlink_data);
        return;
    }

    int name_list_tag = phwangDecodeNumber(name_list_tag_val, NAME_LIST_CLASS_NAME_LIST_TAG_SIZE);
    char *name_list = this->theFabricObject->nameListObject()->getNameList(name_list_tag);

    downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_NAME_LIST;
    if (name_list) {
        strcpy(data_ptr, name_list);
    }
    this->transmitFunction(downlink_data);
}

void DFabricClass::processMallocSession (char *data_val)
{
    this->debug(true, "processMallocSession", data_val);

    char *link_id_index_val = data_val;
    char *theme_info_val = link_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;
    char *his_name_val = theme_info_val + 8;
    char *downlink_data;
    char *uplink_data;
    char *data_ptr;

    SessionClass *session = this->theFabricObject->searchLinkAndMallocSession(link_id_index_val);
    if (!session) {
        this->abend("processMallocSession", "null session");
        downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_MALLOC_SESSION;
        strcpy(data_ptr, "null session");
        this->transmitFunction(downlink_data);
        return;
    }

    GroupClass *group = this->theFabricObject->mallocGroup(theme_info_val);
    if (!group) {
        this->abend("processMallocSession", "null group");
        downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_MALLOC_SESSION;
        strcpy(data_ptr, "null group");
        this->transmitFunction(downlink_data);
        return;
    }

    group->insertSession(session);
    session->bindGroup(group);

    uplink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = FABRIC_THEME_PROTOCOL_COMMAND_IS_MALLOC_ROOM;
    memcpy(data_ptr, group->groupIdIndex(), GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE);
    data_ptr += GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE;
    strcpy(data_ptr, theme_info_val);
    this->theFabricObject->uFabricObject()->transmitFunction(uplink_data);

    if (strcmp(his_name_val, session->linkObject()->linkName())) {
        LinkClass *his_link = this->theFabricObject->searchLinkByName(his_name_val);
        if (!his_link) {
            this->abend("processMallocSession", "null his_link");
            ////////////////TBD
            return;
        }

        SessionClass *his_session = his_link->mallocSession();
        if (!his_session) {
            this->abend("processMallocSession", "null his_session");
            ////////////////TBD
            return;
        }

        group->insertSession(his_session);
        his_session->bindGroup(group);
        char *theme_data = (char *) malloc (32);
        memcpy(theme_data, theme_info_val, 8);
        theme_data[8] = 0;
        his_link->setPendingSessionSetup(his_session->sessionIdIndex(), theme_data);
    }
}

void DFabricClass::processMallocSessionReply (char *data_val)
{
    this->debug(true, "processMallocSessionReply", data_val);

    char *link_and_session_id_index_val = data_val;
    char *end_val = link_and_session_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

    char *downlink_data;
    char *data_ptr;

    downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_MALLOC_SESSION_REPLY;
    memcpy(data_ptr, link_and_session_id_index_val, LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
    *data_ptr = 0;

    this->transmitFunction(downlink_data);
}

void DFabricClass::processTransferSessionData (char *data_val)
{
    this->debug(true, "processTransferSessionData", data_val);

    char *link_and_session_id_index_val = data_val;
    char *end_val = link_and_session_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

    char *downlink_data;
    char *uplink_data;
    char *data_ptr;

    SessionClass *session = this->theFabricObject->serachLinkAndSession(link_and_session_id_index_val);
    if (!session) {
        downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_TRANSFER_SESSION_DATA;
        strcpy(data_ptr, "null session");
        this->transmitFunction(downlink_data);
        this->abend("processTransferSessionData", "null session");
        return;
    }

    char *room = session->groupObject()->roomIdIndex();
    if (!room) {
        downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_TRANSFER_SESSION_DATA;
        strcpy(data_ptr, "null room");
        this->transmitFunction(downlink_data);
        this->abend("processTransferSessionData", "null room");
        return;
    }

    uplink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = FABRIC_THEME_PROTOCOL_COMMAND_IS_TRANSFER_DATA;
    memcpy(data_ptr, room, ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    data_ptr += ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE;
    strcpy(data_ptr, link_and_session_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    this->theFabricObject->uFabricObject()->transmitFunction(uplink_data);
}
