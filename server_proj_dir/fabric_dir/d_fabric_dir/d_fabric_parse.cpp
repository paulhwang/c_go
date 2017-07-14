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
    if (*data_val != WEB_FABRIC_PROTOCOL_COMMAND_IS_GET_LINK_DATA) {
        this->logit("exportedparseFunction", data_val);
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_MALLOC_LINK) {
        this->processSetupLink(data_val + 1);
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
        this->processSetupSession(data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_MALLOC_SESSION_REPLY) {
        this->processSetupSessionReply(data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_PUT_SESSION_DATA) {
        this->processPutSessionData(data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_GET_SESSION_DATA) {
        this->processGetSessionData(data_val + 1);
        return;
    }

    this->abend("exportedparseFunction", data_val);
}

void DFabricClass::processSetupLink (char *data_val)
{
    char *downlink_data;
    char *data_ptr;

    this->debug(true, "processSetupLink", data_val);

    LinkClass *link = this->theFabricObject->mallocLink(data_val);
    if (!link) {
        this->abend("processSetupLink", "null link");
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
    this->debug(false, "processGetLinkData", data_val);

    char *link_id_index_val = data_val;
    char *end_val = link_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;
    char *downlink_data;
    char *data_ptr;

    LinkClass *link = this->theFabricObject->searchLink(link_id_index_val, data_val - 1);
    if (!link) {
        this->logit("+++++++++++++ABEND::processGetLinkData", "link does not exist");
        downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA;
        this->transmitFunction(downlink_data);
        return;
    }
    downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA;
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA_NAME_LIST;
    phwangEncodeNumber(data_ptr, this->theFabricObject->nameListObject()->nameListTag(), WEB_FABRIC_PROTOCOL_NAME_LIST_TAG_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_NAME_LIST_TAG_SIZE;
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

    LinkClass *link = this->theFabricObject->searchLink(link_id_index_val, data_val - 1);
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

void DFabricClass::processSetupSession (char *data_val)
{
    this->debug(true, "processSetupSession", data_val);

    char *link_id_index_val = data_val;
    char *theme_info_val = link_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;
    char *his_name_val = theme_info_val + 8;
    char *downlink_data;
    char *uplink_data;
    char *data_ptr;

    SessionClass *session = this->theFabricObject->searchLinkAndMallocSession(link_id_index_val);
    if (!session) {
        this->abend("processSetupSession", "null session");
        downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_MALLOC_SESSION;
        strcpy(data_ptr, "null session");
        this->transmitFunction(downlink_data);
        return;
    }

    GroupClass *group = this->theFabricObject->mallocGroup(theme_info_val);
    if (!group) {
        this->abend("processSetupSession", "null group");
        downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_MALLOC_SESSION;
        strcpy(data_ptr, "null group");
        this->transmitFunction(downlink_data);
        return;
    }

    group->insertSession(session);
    session->bindGroup(group);

    uplink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = FABRIC_THEME_PROTOCOL_COMMAND_IS_SETUP_ROOM;
    memcpy(data_ptr, group->groupIdIndex(), GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE);
    data_ptr += GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE;
    strcpy(data_ptr, theme_info_val);
    this->theFabricObject->uFabricObject()->transmitFunction(uplink_data);

    if (strcmp(his_name_val, session->linkObject()->linkName())) {
        LinkClass *his_link = this->theFabricObject->searchLinkByName(his_name_val);
        if (!his_link) {
            this->abend("processSetupSession", "null his_link");
            ////////////////TBD
            return;
        }

        SessionClass *his_session = his_link->mallocSession();
        if (!his_session) {
            this->abend("processSetupSession", "null his_session");
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

void DFabricClass::processSetupSessionReply (char *data_val)
{
    this->debug(true, "processSetupSessionReply", data_val);

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

void DFabricClass::processPutSessionData (char *data_val)
{
    this->debug(true, "processPutSessionData", data_val);

    char *link_and_session_id_index_val = data_val;
    char *end_val = link_and_session_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

    char *downlink_data;
    char *uplink_data;
    char *data_ptr;

    SessionClass *session = this->theFabricObject->serachLinkAndSession(link_and_session_id_index_val);
    if (!session) {
        downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_PUT_SESSION_DATA;
        strcpy(data_ptr, "null session");
        this->transmitFunction(downlink_data);
        this->abend("processPutSessionData", "null session");
        return;
    }

    char *room = session->groupObject()->roomIdIndex();
    if (!room) {
        downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_PUT_SESSION_DATA;
        strcpy(data_ptr, "null room");
        this->transmitFunction(downlink_data);
        this->abend("processPutSessionData", "null room");
        return;
    }

    /* transfer data up */
    uplink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = FABRIC_THEME_PROTOCOL_COMMAND_IS_PUT_ROOM_DATA;
    memcpy(data_ptr, room, ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    data_ptr += ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE;
    strcpy(data_ptr, link_and_session_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    this->theFabricObject->uFabricObject()->transmitFunction(uplink_data);

    //return;
    /* send the response down */
    downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_PUT_SESSION_DATA;
    memcpy(data_ptr, session->linkObject()->linkIdIndex(), LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE);
    data_ptr += LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;
    memcpy(data_ptr, session->sessionIdIndex(), SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
    strcpy(data_ptr, "job is done");
    this->transmitFunction(downlink_data);
}

void DFabricClass::processGetSessionData (char *data_val)
{
    char *link_and_session_id_index_val = data_val;
    char *end_val = link_and_session_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

    this->debug(true, "processGetSessionData", data_val);

    char *downlink_data;
    char *data_ptr;

    SessionClass *session = this->theFabricObject->serachLinkAndSession(link_and_session_id_index_val);
    if (!session) {
        downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_PUT_SESSION_DATA;
        strcpy(data_ptr, "null session");
        this->transmitFunction(downlink_data);
        this->abend("processPutSessionData", "null session");
        return;
    }

    char *data = session->getPendingDownLinkData();
    downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_SESSION_DATA;
    memcpy(data_ptr, session->linkObject()->linkIdIndex(), LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE);
    data_ptr += LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;
    memcpy(data_ptr, session->sessionIdIndex(), SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
    strcpy(data_ptr, data);
    this->theFabricObject->dFabricObject()->transmitFunction(downlink_data);
}
