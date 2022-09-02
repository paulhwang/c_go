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
#include "../../db_dir/db_class.h"
#include "../../db_dir/db_account_class.h"

void DFabricClass::exportedParseFunction (void *tp_transfer_object_val, char *data_val)
{
    if (1) { /* debug */
        if (*data_val != WEB_FABRIC_PROTOCOL_COMMAND_IS_GET_LINK_DATA) {
            char s[128];
            sprintf(s, "%s", data_val);
            this->logit("exportedParseFunction", s);
        }
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_SIGN_UP) {
        this->processSignUpRequest(tp_transfer_object_val, data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_SETUP_LINK) {
        this->processSetupLink(tp_transfer_object_val, data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_FREE_LINK) {
        this->processFreeLink(tp_transfer_object_val, data_val + 1);
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

    this->abend("exportedParseFunction", data_val);
}

void DFabricClass::processSignUpRequest (void *tp_transfer_object_val, char *data_val)
{
    this->debug(true, "processSignUpRequest", data_val);

    char *ajax_id = data_val;

    char *encoded_my_name = ajax_id + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    int my_name_size;
    char *my_name = phwangDecodeString(encoded_my_name, &my_name_size);

    char *encoded_password = encoded_my_name + my_name_size;
    int password_size;
    char *password = phwangDecodeString(encoded_password, &password_size);

    char *encoded_email = encoded_password + password_size;
    int email_size;
    char *email = phwangDecodeString(encoded_email, &email_size);

    if (1) { /* debug */
        char buf[256];
        sprintf(buf, "my_name=%s password=%s email=%s\n", my_name, password, email);
        this->logit("processSignUpRequest", buf);
    }

    int check_password_result = this->dbObject()->dbAccountObject()->checkPassword(my_name, password);
    if (check_password_result) {
        char const *check_password_result_str;
        switch (check_password_result) {
            case -1:
                check_password_result_str = "password not match";
                break;
            case -2:
                check_password_result_str = "name not found";
                break;
            case -3:
                check_password_result_str = "empty table";
                break;
            default:
                this->abend("processSignUpRequest", "check_password_result");
                break;
        }
        this->sendSignUpResponce(tp_transfer_object_val, ajax_id, check_password_result_str);
        free(my_name);
        free(password);
        free(email);
        return;
    }

    this->sendSignUpResponce(tp_transfer_object_val, ajax_id, "succeed");
    free(my_name);
    free(password);
    free(email);
}

#define D_FABRIC_CLASS_PROCESSS_SIGN_UP_DOWN_LINK_DATA_SIZE (1 + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + 1)
void DFabricClass::sendSignUpResponce (void *tp_transfer_object_val, char const *ajax_id_val, char const *result_val)
{
    this->debug(true, "signUpLinkResponce", result_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(D_FABRIC_CLASS_PROCESSS_SIGN_UP_DOWN_LINK_DATA_SIZE + strlen(result_val), "DFSL");
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_SETUP_LINK;
    memcpy(data_ptr, ajax_id_val, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    strcpy(data_ptr, result_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

#define D_FABRIC_CLASS_FAKE_LINK_ID_INDEX "99990000"
void DFabricClass::processSetupLink (void *tp_transfer_object_val, char *data_val)
{
    this->debug(true, "processSetupLink", data_val);

    char *ajax_id = data_val;

    char *encoded_my_name = ajax_id + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    int my_name_size;
    char *my_name = phwangDecodeString(encoded_my_name, &my_name_size);

    char *encoded_password = encoded_my_name + my_name_size;
    int password_size;
    char *password = phwangDecodeString(encoded_password, &password_size);

    if (1) { /* debug */
        char buf[256];
        sprintf(buf, "my_name=%s password=%s\n", my_name, password);
        this->logit("processSetupLink", buf);
    }

    int check_password_result = this->dbObject()->dbAccountObject()->checkPassword(my_name, password);
    if (check_password_result) {
        char const*check_password_result_str;
        switch (check_password_result) {
            case -1:
                check_password_result_str = "password not match";
                break;
            case -2:
                check_password_result_str = "name not found";
                break;
            case -3:
                check_password_result_str = "empty table";
                break;
            default:
                this->abend("processSetupLink", "check_password_result");
                break;
        }
        this->sendSetupLinkResponce(tp_transfer_object_val, ajax_id, D_FABRIC_CLASS_FAKE_LINK_ID_INDEX, check_password_result_str);
        free(my_name);
        free(password);
        return;
    }

    LinkClass *link = this->theFabricObject->mallocLink(my_name);
    if (!link) {
        this->abend("processSetupLink", "null link");
        this->sendSetupLinkResponce(tp_transfer_object_val, ajax_id, D_FABRIC_CLASS_FAKE_LINK_ID_INDEX, "null link");
        free(my_name);
        free(password);
        return;
    }

    this->sendSetupLinkResponce(tp_transfer_object_val, ajax_id, link->linkIdIndex(), "succeed");
    free(my_name);
    free(password);
}

#define D_FABRIC_CLASS_PROCESSS_SETUP_LINK_DOWN_LINK_DATA_SIZE (1 + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + 1)
void DFabricClass::sendSetupLinkResponce (void *tp_transfer_object_val, char const *ajax_id_val, char const *link_id_index_val, char const *result_val)
{
    this->debug(true, "sendSetupLinkResponce", result_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(D_FABRIC_CLASS_PROCESSS_SETUP_LINK_DOWN_LINK_DATA_SIZE + strlen(result_val), "DFSL");
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_SETUP_LINK;
    memcpy(data_ptr, ajax_id_val, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    strcpy(data_ptr, link_id_index_val);
    data_ptr += LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;
    strcpy(data_ptr, result_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processFreeLink (void *tp_transfer_object_val, char *data_val)
{
    this->debug(false, "processFreeLink", data_val);

    char *ajax_id = data_val;
    char *link_id_index_val = ajax_id + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    char *end_val = link_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;

    LinkClass *link = this->theFabricObject->searchLink(link_id_index_val, data_val - 1);
    if (!link) {
        this->errorProcessFreeLink(tp_transfer_object_val, ajax_id, "link does not exist");
        return;
    }
    this->theFabricObject->freeLink(link);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(LINK_MGR_DATA_BUFFER_SIZE + 4, "DFFL");
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_FREE_LINK;
    memcpy(data_ptr, ajax_id, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    strcpy(data_ptr, link->linkIdIndex());
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::errorProcessFreeLink (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    this->abend("errorProcessFreeLink", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(LINK_MGR_DATA_BUFFER_SIZE + 4, "DFFl");
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_FREE_LINK;
    memcpy(data_ptr, ajax_id_val, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

#define D_FABRIC_CLASS_PROCESSS_GET_LINK_DATA_DOWN_LINK_PENDING_DATA_SIZE (1 + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + LINK_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE)
#define D_FABRIC_CLASS_PROCESSS_GET_LINK_DATA_DOWN_LINK_DATA_SIZE (1 + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + 1 + WEB_FABRIC_PROTOCOL_NAME_LIST_TAG_SIZE + 1)
#define D_FABRIC_CLASS_PROCESSS_GET_LINK_DATA_DOWN_LINK_PENDING_SESSION_SIZE (1 + WEB_FABRIC_PROTOCOL_NAME_LIST_TAG_SIZE)
void DFabricClass::processGetLinkData (void *tp_transfer_object_val, char *data_val)
{
    this->debug(false, "processGetLinkData", data_val);

    char *ajax_id = data_val;
    char *link_id_index_val = ajax_id + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    char *end_val = link_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;

    LinkClass *link = this->theFabricObject->searchLink(link_id_index_val, data_val - 1);
    if (!link) {
        this->errorProcessGetLinkData(tp_transfer_object_val, ajax_id, "link does not exist");
        return;
    }
    link->resetKeepAliveTime();

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(LINK_MGR_DATA_BUFFER_SIZE + 4, "DFLD");
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA;
    memcpy(data_ptr, ajax_id, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA_NAME_LIST;
    phwangEncodeNumber(data_ptr, this->theFabricObject->nameListObject()->nameListTag(), WEB_FABRIC_PROTOCOL_NAME_LIST_TAG_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_NAME_LIST_TAG_SIZE;
    *data_ptr = 0;

    int max_session_table_array_index = phwnagListMgrGetMaxIndex(link->sessionListMgrObject(), "DFabricClass::processGetLinkData()");
    SessionClass **session_table_array = (SessionClass **) phwangListMgrGetEntryTableArray(link->sessionListMgrObject());
    for (int i = 0; i <= max_session_table_array_index; i++) {
        SessionClass *session = session_table_array[i];
        if (session) {
            char *pending_downlink_data = session->getPendingDownLinkData();
            if (pending_downlink_data) {
                *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA_PENDING_DATA;
                session->enqueuePendingDownLinkData(pending_downlink_data);
                strcpy(data_ptr, link->linkIdIndex());
                data_ptr += LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;
                strcpy(data_ptr, session->sessionIdIndex());
                data_ptr += LINK_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

                if (1) { /* debug */
                    char s[128];
                    sprintf(s, "Pending data exist: %s", downlink_data);
                    this->logit("processGetLinkData", s);
                }
            }
        }
    }

    char *pending_session = link->getPendingSessionSetup();
    if (pending_session) {
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA_PENDING_SESSION;
        strcpy(data_ptr, pending_session);
        this->debug(true, "==================processGetLinkData getPendingSessionSetup", downlink_data);
    }

    char *pending_session3 = link->getPendingSessionSetup3();
    if (pending_session3) {
        *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA_PENDING_SESSION3;
        strcpy(data_ptr, pending_session3);
        this->debug(true, "==================processGetLinkData getPendingSessionSetup3", downlink_data);
    }

    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::errorProcessGetLinkData (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    this->logit("+++++++++++++ABEND: errorProcessGetLinkData", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(LINK_MGR_DATA_BUFFER_SIZE + 4, "DFld");
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA;
    memcpy(data_ptr, ajax_id_val, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processGetNameList (void *tp_transfer_object_val, char *data_val)
{
    this->debug(true, "processGetNameList", data_val);

    char *ajax_id = data_val;
    char *link_id_index_val = ajax_id + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    char *name_list_tag_val = link_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;
    char *end_val = name_list_tag_val + 3;

    LinkClass *link = this->theFabricObject->searchLink(link_id_index_val, data_val - 1);
    if (!link) {
        this->errorProcessGetNameList(tp_transfer_object_val, ajax_id, "link does not exist");
        return;
    }

    int name_list_tag = phwangDecodeNumber(name_list_tag_val, NAME_LIST_CLASS_NAME_LIST_TAG_SIZE);
    char *name_list = this->theFabricObject->nameListObject()->getNameList(name_list_tag);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(strlen(name_list) + LINK_MGR_DATA_BUFFER_SIZE + 4, "DFNl");
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_NAME_LIST;
    memcpy(data_ptr, ajax_id, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    *data_ptr = 0;
    if (name_list) {
        strcpy(data_ptr, name_list);
    }
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::errorProcessGetNameList (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    this->abend("errorProcessGetNameList", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(LINK_MGR_DATA_BUFFER_SIZE + 4, "DFNl");
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_NAME_LIST;
    memcpy(data_ptr, ajax_id_val, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processSetupSession (void *tp_transfer_object_val, char *data_val)
{
    this->debug(true, "processSetupSession", data_val);

    char *ajax_id = data_val;
    char *link_id_index_val = ajax_id + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    char *theme_info_val = link_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;
    int theme_len = phwangDecodeNumber(theme_info_val + 1, 3);
    char *his_name_val = theme_info_val + theme_len;

    LinkClass *link = this->theFabricObject->searchLink(link_id_index_val, data_val - 1);
    if (!link) {
        this->errorProcessSetupSession(tp_transfer_object_val, ajax_id, "link does not exist");
        return;
    }

    SessionClass *session = link->mallocSession();
    if (!session) {
        this->errorProcessSetupSession(tp_transfer_object_val, ajax_id, "null session");
        return;
    }

    GroupClass *group = this->theFabricObject->mallocGroup(theme_info_val);
    if (!group) {
        this->errorProcessSetupSession(tp_transfer_object_val, ajax_id, "null group");
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
            this->errorProcessSetupSession(tp_transfer_object_val, ajax_id, "his_link does not exist");
            return;
        }

        SessionClass *his_session = his_link->mallocSession();
        if (!his_session) {
            this->errorProcessSetupSession(tp_transfer_object_val, ajax_id, "null his_session");
            return;
        }

        group->insertSession(his_session);
        his_session->bindGroup(group);

        char *theme_data = (char *) malloc (32);
        memcpy(theme_data, theme_info_val, theme_len);
        theme_data[theme_len] = 0;
        his_link->setPendingSessionSetup(his_session->sessionIdIndex(), theme_data);
    }

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(LINK_MGR_DATA_BUFFER_SIZE + 4, "DFS1");
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_SETUP_SESSION;
    memcpy(data_ptr, ajax_id, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    strcpy(data_ptr, session->sessionIdIndex());
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::errorProcessSetupSession (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    this->abend("errorProcessSetupSession", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(LINK_MGR_DATA_BUFFER_SIZE + 4, "DFs1");
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_SETUP_SESSION;
    memcpy(data_ptr, ajax_id_val, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::mallocRoom (GroupClass *group_val, char *theme_info_val)
{
    char *data_ptr;
    char *uplink_data = data_ptr = (char *) phwangMalloc(LINK_MGR_DATA_BUFFER_SIZE + 4, "DFMG");
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
    char *link_id_index_val = data_val + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    char *session_id_index_val = link_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;
    char *theme_info_val = session_id_index_val + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

    LinkClass *link = this->theFabricObject->searchLink(link_id_index_val, data_val - 1);
    if (!link) {
        this->errorProcessSetupSession2(tp_transfer_object_val, ajax_id, "link does not exist");
        return;
    }

    SessionClass *session = link->searchSession(session_id_index_val);
    if (!session) {
        this->errorProcessSetupSession2(tp_transfer_object_val, ajax_id, "session does not exist");
        return;
    }

    GroupClass *group = session->groupObject();
    this->mallocRoom(group, theme_info_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(LINK_MGR_DATA_BUFFER_SIZE + 4, "DFS2");
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_SETUP_SESSION2;
    memcpy(data_ptr, ajax_id, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    memcpy(data_ptr, link_id_index_val, LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE);
    data_ptr += LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;
    memcpy(data_ptr, session_id_index_val, SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
    *data_ptr = 0;
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::errorProcessSetupSession2 (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    this->abend("errorProcessSetupSession2", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(LINK_MGR_DATA_BUFFER_SIZE + 4, "DFs2");
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_SETUP_SESSION2;
    memcpy(data_ptr, ajax_id_val, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processSetupSession3 (void *tp_transfer_object_val, char *data_val)
{
    this->debug(true, "processSetupSession3", data_val);

    char *ajax_id = data_val;
    char *link_and_session_id_index_val = data_val + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    char *end_val = link_and_session_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(LINK_MGR_DATA_BUFFER_SIZE + 4, "DFS3");
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_SETUP_SESSION3;
    memcpy(data_ptr, ajax_id, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    memcpy(data_ptr, link_and_session_id_index_val, LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
    *data_ptr = 0;
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processFreeSession (void *tp_transfer_object_val, char *data_val)
{
}

void DFabricClass::errorProcessFreeSession (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
}

void DFabricClass::processPutSessionData (void *tp_transfer_object_val, char *data_val)
{
    this->debug(true, "processPutSessionData", data_val);

    char *ajax_id = data_val;
    char *link_and_session_id_index_val = data_val + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    char *end_val = link_and_session_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

    char *data_ptr;

    SessionClass *session = this->theFabricObject->serachLinkAndSession(link_and_session_id_index_val);
    if (!session) {
        this->errorProcessPutSessionData(tp_transfer_object_val, ajax_id, "null session");
        return;
    }
    char *room = session->groupObject()->roomIdIndex();
    if (!room) {
        this->errorProcessPutSessionData(tp_transfer_object_val, ajax_id, "null room");
        return;
    }

    /* transfer data up */
    char *uplink_data = data_ptr = (char *) phwangMalloc(LINK_MGR_DATA_BUFFER_SIZE + 4, "DFSU");
    *data_ptr++ = FABRIC_THEME_PROTOCOL_COMMAND_IS_PUT_ROOM_DATA;
    memcpy(data_ptr, room, ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    data_ptr += ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE;
    strcpy(data_ptr, link_and_session_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    this->theFabricObject->uFabricObject()->transmitFunction(uplink_data);

    /* send the response down */
    char *downlink_data = data_ptr = (char *) phwangMalloc(LINK_MGR_DATA_BUFFER_SIZE + 4, "DFPS");
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_PUT_SESSION_DATA;
    memcpy(data_ptr, ajax_id, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    memcpy(data_ptr, session->linkObject()->linkIdIndex(), LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE);
    data_ptr += LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;
    memcpy(data_ptr, session->sessionIdIndex(), SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
    strcpy(data_ptr, "job is done");
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::errorProcessPutSessionData (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    this->abend("errorProcessPutSessionData", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(LINK_MGR_DATA_BUFFER_SIZE + 4, "DFPs");
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_PUT_SESSION_DATA;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processGetSessionData (void *tp_transfer_object_val, char *data_val)
{
    this->debug(true, "processGetSessionData", data_val);

    char *ajax_id = data_val;
    char *link_and_session_id_index_val = data_val + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    char *end_val = link_and_session_id_index_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

    SessionClass *session = this->theFabricObject->serachLinkAndSession(link_and_session_id_index_val);
    if (!session) {
        this->errorProcessGetSessionData(tp_transfer_object_val, ajax_id, "null session");
        return;
    }

    char *data = session->getPendingDownLinkData();

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(LINK_MGR_DATA_BUFFER_SIZE + 4, "DFGS");
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_SESSION_DATA;
    //downlink_data = data_ptr = (char *) phwangMalloc(LINK_MGR_DATA_BUFFER_SIZE + 4, "DFXX");
    //*data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_NAME_LIST;
    memcpy(data_ptr, ajax_id, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    memcpy(data_ptr, session->linkObject()->linkIdIndex(), LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE);
    data_ptr += LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;
    memcpy(data_ptr, session->sessionIdIndex(), SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
    strcpy(data_ptr, data);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::errorProcessGetSessionData (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    this->abend("errorProcessGetSessionData", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(LINK_MGR_DATA_BUFFER_SIZE + 4, "DFGs");
    *data_ptr++ = WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_SESSION_DATA;
    memcpy(data_ptr, ajax_id_val, WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE);
    data_ptr += WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}
