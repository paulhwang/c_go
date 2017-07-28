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

void DFabricClass::exportedparseFunction (void *tp_transfer_object_val, char *data_val)
{
    if (*data_val != WEB_FABRIC_PROTOCOL_COMMAND_IS_GET_LINK_DATA) {
        this->logit("exportedparseFunction", data_val);
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_MALLOC_LINK) {
        this->processSetupLink(tp_transfer_object_val, data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_GET_LINK_DATA) {
        this->processGetLinkData(tp_transfer_object_val, data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_GET_NAME_LIST) {
        this->processGetNameList(tp_transfer_object_val, data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_SETUP_SESSION) {
        this->processSetupSession(tp_transfer_object_val, data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_SETUP_SESSION2) {
        this->processSetupSession2(tp_transfer_object_val, data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_SETUP_SESSION3) {
        this->processSetupSession3(tp_transfer_object_val, data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_PUT_SESSION_DATA) {
        this->processPutSessionData(tp_transfer_object_val, data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_GET_SESSION_DATA) {
        this->processGetSessionData(tp_transfer_object_val, data_val + 1);
        return;
    }

    this->abend("exportedparseFunction", data_val);
}

void DFabricClass::processSetupLink (void *tp_transfer_object_val, char *data_val)
{
    this->debug(true, "processSetupLink", data_val);

    char *ajax_id = data_val;
    char *my_name = ajax_id + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    char *downlink_data;
    char *data_ptr;

    LinkClass *link = this->theFabricObject->mallocLink(my_name);
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
    memcpy(data_ptr, ajax_id, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    strcpy(data_ptr, link->linkIdIndex());
    this->transmitFunction1(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processGetLinkData (void *tp_transfer_object_val, char *data_val)
{
    this->debug(false, "processGetLinkData", data_val);

    char *ajax_id = data_val;
    char *link_id_index_val = ajax_id + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
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

    memcpy(data_ptr, ajax_id, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;

    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA_NAME_LIST;
    phwangEncodeNumber(data_ptr, this->theFabricObject->nameListObject()->nameListTag(), WEB_FABRIC_PROTOCOL_NAME_LIST_TAG_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_NAME_LIST_TAG_SIZE;
    *data_ptr = 0;

    int max_session_table_array_index = phwnagListMgrGetMaxIndex(link->sessionListMgrObject());
    SessionClass **session_table_array = (SessionClass **) phwangListMgrGetEntryTableArray(link->sessionListMgrObject());
    for (int i = 0; i <= max_session_table_array_index; i++) {
        SessionClass *session = session_table_array[i];
        if (session) {
            char *pending_downlink_data = session->getPendingDownLinkData();
            if (pending_downlink_data) {
                *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA_PENDING_DATA;
                session->enqueuePendingDownLinkData(pending_downlink_data);
                strcpy(data_ptr, link->linkIdIndex());
                data_ptr += 8;
                strcpy(data_ptr, session->sessionIdIndex());
                data_ptr += 8;
                this->debug(true, "==================processGetLinkData", downlink_data);
            }
        }
    }

    char *pending_session = link->getPendingSessionSetup();
    if (pending_session) {
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA_PENDING_SESSION;
        strcpy(data_ptr, pending_session);
        this->debug(true, "==================processGetLinkData", downlink_data);
    }

    char *pending_session3 = link->getPendingSessionSetup3();
    if (pending_session3) {
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA_PENDING_SESSION3;
        strcpy(data_ptr, pending_session3);
        this->debug(true, "==================processGetLinkData", downlink_data);
    }

    this->transmitFunction1(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processGetNameList (void *tp_transfer_object_val, char *data_val)
{
    this->debug(true, "processGetNameList", data_val);

    char *ajax_id = data_val;
    char *link_id_index_val = ajax_id + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
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

    memcpy(data_ptr, ajax_id, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    *data_ptr = 0;

    if (name_list) {
        strcpy(data_ptr, name_list);
    }
    this->transmitFunction1(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processSetupSession (void *tp_transfer_object_val, char *data_val)
{
    this->debug(true, "processSetupSession", data_val);

    char *ajax_id = data_val;
    char *link_id_index_val = ajax_id + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    char *theme_info_val = link_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;
    int theme_len = phwangDecodeNumber(theme_info_val + 1, 3);
    char *his_name_val = theme_info_val + theme_len;
    char *downlink_data;
    char *uplink_data;
    char *data_ptr;

    LinkClass *link = this->theFabricObject->searchLink(link_id_index_val, data_val - 1);
    if (!link) {
        this->errorProcessSetupSession("link does not exist");
        return;
    }

    SessionClass *session = this->theFabricObject->searchLinkAndMallocSession(link_id_index_val);
    if (!session) {
        this->errorProcessSetupSession("null session");
        return;
    }

    GroupClass *group = this->theFabricObject->mallocGroup(theme_info_val);
    if (!group) {
        this->errorProcessSetupSession("null group");
        return;
    }
    group->insertSession(session);
    session->bindGroup(group);

    if (!strcmp(his_name_val, session->linkObject()->linkName())) {
        this->mallocRoom(group, theme_info_val);
    }
    else {
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
        memcpy(theme_data, theme_info_val, theme_len);
        theme_data[theme_len] = 0;
        his_link->setPendingSessionSetup(his_session->sessionIdIndex(), theme_data);
    }

    downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_SETUP_SESSION;
    memcpy(data_ptr, ajax_id, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    strcpy(data_ptr, session->sessionIdIndex());
    this->transmitFunction(downlink_data);
}

void DFabricClass::errorProcessSetupSession (char const *err_msg_val)
{
    char *downlink_data;
    char *data_ptr;

    this->abend("errorProcessSetupSession", err_msg_val);

    downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_SETUP_SESSION;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(downlink_data);
}

void DFabricClass::mallocRoom (GroupClass *group_val, char *theme_info_val)
{
    char *uplink_data;
    char *data_ptr;

    uplink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = FABRIC_THEME_PROTOCOL_COMMAND_IS_SETUP_ROOM;

    memcpy(data_ptr, group_val->groupIdIndex(), GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE);
    data_ptr += GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE;
    strcpy(data_ptr, theme_info_val);
    this->theFabricObject->uFabricObject()->transmitFunction(uplink_data);
}

void DFabricClass::processSetupSession2 (void *tp_transfer_object_val, char *data_val)
{
    this->debug(true, "processSetupSession2", data_val);

    char *ajax_id = data_val;
    char *link_and_session_id_index_val = data_val + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    char *end_val = link_and_session_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

    char *downlink_data;
    char *data_ptr;

    downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_SETUP_SESSION2;

    memcpy(data_ptr, ajax_id, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;

    memcpy(data_ptr, link_and_session_id_index_val, LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
    *data_ptr = 0;

    this->transmitFunction1(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processSetupSession3 (void *tp_transfer_object_val, char *data_val)
{
    this->debug(true, "processSetupSession3", data_val);

    char *ajax_id = data_val;
    char *link_and_session_id_index_val = data_val + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    char *end_val = link_and_session_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

    char *downlink_data;
    char *data_ptr;

    downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_SETUP_SESSION3;

    memcpy(data_ptr, ajax_id, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;

    memcpy(data_ptr, link_and_session_id_index_val, LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
    *data_ptr = 0;

    this->transmitFunction1(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processPutSessionData (void *tp_transfer_object_val, char *data_val)
{
    this->debug(true, "processPutSessionData", data_val);

    char *ajax_id = data_val;
    char *link_and_session_id_index_val = data_val + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
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

    /* send the response down */
    downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_PUT_SESSION_DATA;

    memcpy(data_ptr, ajax_id, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;

    memcpy(data_ptr, session->linkObject()->linkIdIndex(), LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE);
    data_ptr += LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;

    memcpy(data_ptr, session->sessionIdIndex(), SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

    strcpy(data_ptr, "job is done");
    this->transmitFunction1(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processGetSessionData (void *tp_transfer_object_val, char *data_val)
{
    this->debug(true, "processGetSessionData", data_val);

    char *ajax_id = data_val;
    char *link_and_session_id_index_val = data_val + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    char *end_val = link_and_session_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

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

    downlink_data = data_ptr = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_NAME_LIST;

    memcpy(data_ptr, ajax_id, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;

    memcpy(data_ptr, session->linkObject()->linkIdIndex(), LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE);
    data_ptr += LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;

    memcpy(data_ptr, session->sessionIdIndex(), SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

    strcpy(data_ptr, data);
    this->transmitFunction1(tp_transfer_object_val, downlink_data);
}
