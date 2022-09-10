/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "../../protocol_dir/fabric_theme_protocol.h"
#include "../../protocol_dir/session_mgr_protocol.h"
#include "../../protocol_dir/group_mgr_protocol.h"
#include "../../protocol_dir/room_mgr_protocol.h"
#include "../../protocol_dir/fe_command_class.h"
#include "d_fabric_class.h"
#include "../fabric_class.h"
#include "../u_fabric_dir/u_fabric_class.h"
#include "../messenger_dir/messenger_class.h"
#include "../link_class.h"
#include "../session_class.h"
#include "../group_class.h"
#include "../name_list_class.h"
#include "../../db_dir/db_class.h"
#include "../../db_dir/db_account_class.h"
#include "../../db_dir/db_account_entry_class.h"

DbAccountClass *DFabricClass::dbAccountObject(void) {return theFabricObject->dbObject()->dbAccountObject();}

void DFabricClass::exportedParseFunction (void *tp_transfer_object_val, char *data_val)
{
    LinkClass *link;
    SessionClass *session;

    if (data_val[1] != FECommandClass::GET_LINK_DATA_COMMAND) {
        phwangDebugS(true, "DFabricClass::exportedParseFunction", data_val);
    }

    char type = data_val[0];
    char command = data_val[1];

    /* get ajax_id */
    char ajax_id[8];
    memcpy(ajax_id, &data_val[2], FECommandClass::AJAX_ID_SIZE);
    ajax_id[FECommandClass::AJAX_ID_SIZE] = 0;

    char *rest_data = &data_val[2 + FECommandClass::AJAX_ID_SIZE];

    switch (type) {
        case '0':
            switch (command) {
                case FECommandClass::SIGN_UP_COMMAND:
                    this->processSignUpRequest(tp_transfer_object_val, rest_data, ajax_id);
                    return;

                case FECommandClass::SETUP_LINK_COMMAND:
                    this->processSetupLinkRequest(tp_transfer_object_val, rest_data, ajax_id);
                    return;

                case FECommandClass::MESSAGE_COMMAND:
                    this->processMessageRequest(tp_transfer_object_val, rest_data, ajax_id);
                    return;

                default:
                    phwangAbendS("DFabricClass::exportedParseFunction", data_val);
                    return;
            }
            break;

        case '1':
            link = this->theFabricObject->searchLink(rest_data, data_val);
            if (!link) {
                this->sendSearchLinkFailResponse(command, tp_transfer_object_val, ajax_id);
                return;
            }
            rest_data += FECommandClass::LINK_ID_INDEX_SIZE;

            switch (command) {
                case FECommandClass::FREE_LINK_COMMAND:
                    this->processFreeLinkRequest(tp_transfer_object_val, rest_data, ajax_id, link);
                    return;

                case FECommandClass::GET_LINK_DATA_COMMAND:
                    this->processGetLinkDataRequest(tp_transfer_object_val, rest_data, ajax_id, link);
                    return;

                case FECommandClass::GET_NAME_LIST_COMMAND:
                    this->processGetNameListRequest(tp_transfer_object_val, rest_data, ajax_id, link);
                    return;

                case FECommandClass::SETUP_SESSION_COMMAND:
                    this->processSetupSessionRequest(tp_transfer_object_val, rest_data, ajax_id, link);
                    return;

                case FECommandClass::SETUP_SESSION2_COMMAND:
                    this->processSetupSession2Request(tp_transfer_object_val, rest_data, ajax_id, link);
                    return;

                case FECommandClass::SETUP_SESSION3_COMMAND:
                    this->processSetupSession3Request(tp_transfer_object_val, rest_data, ajax_id, link);
                    return;

                default:
                    phwangAbendS("DFabricClass::dbAccountObject", data_val);
                    return;
            }
            break;

        case '2':
            session = this->theFabricObject->serachLinkAndSession(rest_data);
            if (!session) {
                this->sendSearchLinkSessionFailResponse(command, tp_transfer_object_val, ajax_id);
                return;
            }
            rest_data += FECommandClass::LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

            switch (command) {
                case FECommandClass::FREE_SESSION_COMMAND:
                    this->processFreeSessionRequest(tp_transfer_object_val, rest_data, ajax_id, session);
                    return;

                case FECommandClass::PUT_SESSION_DATA_COMMAND:
                    this->processPutSessionDataRequest(tp_transfer_object_val, rest_data, ajax_id, session);
                    return;

                case FECommandClass::GET_SESSION_DATA_COMMAND:
                    this->processGetSessionDataRequest(tp_transfer_object_val, rest_data, ajax_id, session);
                    return;

                default:
                    phwangAbendS("DFabricClass::dbAccountObject", data_val);
            }

            break;

        default:
            phwangAbendS("DFabricClass::dbAccountObject", "bad type");
            break;
    }

}

void DFabricClass::sendSearchLinkFailResponse (char const command_val, void *tp_transfer_object_val, char const *ajax_id_val)
{
    phwangAbendS("DFabricClass::sendSearchLinkFailResponse", "");

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::BAD_LINK);
    *data_ptr++ = command_val;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, "link does not exist");
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::sendSearchLinkSessionFailResponse (char const command_val, void *tp_transfer_object_val, char const *ajax_id_val)
{
    phwangAbendS("DFabricClass::sendSearchLinkSessionFailResponse", "");

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::BAD_SESSION);
    *data_ptr++ = command_val;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, "link_session does not exist");
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processMessageRequest (void *tp_transfer_object_val, char *input_data_val, char const *ajax_id_val)
{
    phwangDebugS(true, "DFabricClass::processMessageRequest", input_data_val);

    char act = *input_data_val++;

    char *encoded_data = input_data_val;
    int data_size;
    char *data = phwangDecodeStringMalloc(encoded_data, &data_size);
    char *output_data;

    if (1) { /* debug */
        char buf[256];
        sprintf(buf, "act=%c data=%s\n", act, data);
        phwangDebugS(true, "DFabricClass::processMessageRequest", buf);
    }

    switch (act) {
        case 'I':
            this->messengerObject()->initMessenger();
            this->sendMessageResponce(tp_transfer_object_val, ajax_id_val, "succeed", "I_data");
            break;

        case 'R':
            output_data = this->messengerObject()->getMessage();
            phwangDebugS(true, "DFabricClass::processMessageRequest", output_data);
            this->sendMessageResponce(tp_transfer_object_val, ajax_id_val, "succeed", output_data);
            break;

        case 'W':
            this->messengerObject()->putMessage(0);
            this->sendMessageResponce(tp_transfer_object_val, ajax_id_val, "succeed", "W_data");
            break;

        default:
            break;
    }
}

#define D_FABRIC_CLASS_PROCESSS_MMW_READ_DATA_DOWN_LINK_DATA_SIZE (1 + FECommandClass::AJAX_ID_SIZE + FECommandClass::LINK_ID_INDEX_SIZE + 1)
void DFabricClass::sendMessageResponce (void *tp_transfer_object_val, char const *ajax_id_val, char const *result_val, char const *data_val)
{
    phwangDebugS(true, "DFabricClass::sendMessageResponce", result_val);

    char *encoded_result = phwangEncodeStringMalloc(result_val);
    int encoded_result_length = strlen(encoded_result);
    char *encoded_data = phwangEncodeStringMalloc(data_val);
    int encoded_data_length = strlen(encoded_data);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(D_FABRIC_CLASS_PROCESSS_MMW_READ_DATA_DOWN_LINK_DATA_SIZE + encoded_result_length + encoded_data_length, MallocClass::DATAGRAM);
    *data_ptr++ = FECommandClass::MESSAGE_RESPONSE;
    memcpy(data_ptr, ajax_id_val, FECommandClass::AJAX_ID_SIZE);
    data_ptr += FECommandClass::AJAX_ID_SIZE;

    strcpy(data_ptr, encoded_result);
    data_ptr += encoded_result_length;
    phwangFree(encoded_result);

    strcpy(data_ptr, encoded_data);
    //data_ptr += encoded_data_length;
    phwangFree(encoded_data);

    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processSignUpRequest (void *tp_transfer_object_val, char *data_val, char const *ajax_id_val)
{
    phwangDebugS(false, "DFabricClass::processSignUpRequest", data_val);

    char *encoded_account_name = data_val;
    int account_name_size;
    char *account_name = phwangDecodeStringMalloc(encoded_account_name, &account_name_size);

    char *encoded_password = encoded_account_name + account_name_size;
    int password_size;
    char *password = phwangDecodeStringMalloc(encoded_password, &password_size);

    char *encoded_email = encoded_password + password_size;
    int email_size;
    char *email = phwangDecodeStringMalloc(encoded_email, &email_size);

    phwangDebugSS(false, "DFabricClass::processSignUpRequest", account_name, password);

    int result = this->dbAccountObject()->checkAccountNameExist(account_name);
    if (result != DbAccountClass::DB_ACCOUNT_NAME_NOT_EXIST) {
        char const *result_str;
        switch (result) {
            case DbAccountClass::DB_ACCOUNT_NAME_EXIST:
                result_str = "name exist";
                break;
            case DbAccountClass::DB_ACCOUNT_SELECT_FAIL:
                result_str = "select fail";
                break;
            default:
                phwangAbendS("DFabricClass::processSignUpRequest", "result_str");
                break;
        }
        this->sendSignUpResponce(tp_transfer_object_val, ajax_id_val, result_str);
        phwangFree(account_name);
        phwangFree(password);
        phwangFree(email);
        return;
    }

    DbAccountEntryClass *account_entry = new DbAccountEntryClass();
    account_entry->setAccountName(account_name);
    account_entry->setPassword(password);
    account_entry->setEmail(email);
    this->dbAccountObject()->insertAccountEntry(account_entry);

    this->sendSignUpResponce(tp_transfer_object_val, ajax_id_val, "succeed");

    /***
    ---the buffers has been freed in the insertAccountEntry()---
    free(account_name);
    free(password);
    free(email);
    ***/
}

void DFabricClass::sendSignUpResponce (void *tp_transfer_object_val, char const *ajax_id_val, char const *result_val)
{
    phwangDebugS(false, "DFabricClass::sendSignUpResponce", result_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FECommandClass::SIGN_UP_DOWNLINK_DATA_SIZE + strlen(result_val), MallocClass::SIGN_UP);
    *data_ptr++ = FECommandClass::SIGN_UP_RESPONSE;
    memcpy(data_ptr, ajax_id_val, FECommandClass::AJAX_ID_SIZE);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, result_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processSetupLinkRequest (void *tp_transfer_object_val, char *data_val, char const *ajax_id_val)
{
    phwangDebugS(false, "DFabricClass::processSetupLinkRequest", data_val);

    char *encoded_my_name = data_val;
    int my_name_size;
    char *my_name = phwangDecodeStringMalloc(encoded_my_name, &my_name_size);

    char *encoded_password = encoded_my_name + my_name_size;
    int password_size;
    char *password = phwangDecodeStringMalloc(encoded_password, &password_size);

    phwangDebugSS(false, "DFabricClass::processSetupLinkRequest", my_name, password);

    int result = this->dbObject()->dbAccountObject()->checkPassword(my_name, password);
    if (result != DbAccountClass::DB_ACCOUNT_PASSWORD_MATCH) {
        char const*result_str;
        switch (result) {
            case DbAccountClass::DB_ACCOUNT_PASSWORD_NOT_MATCH:
                result_str = "password not match";
                break;
            case DbAccountClass::DB_ACCOUNT_NAME_NOT_EXIST:
                result_str = "name not exist";
                break;
            case DbAccountClass::DB_ACCOUNT_SELECT_FAIL:
                result_str = "select fail";
                break;
            default:
                phwangAbendS("DFabricClass::processSetupLinkRequest", "check_password_result");
                break;
        }
        this->sendSetupLinkResponce(tp_transfer_object_val, ajax_id_val, FECommandClass::FAKE_LINK_ID_INDEX, result_str);
        phwangFree(my_name);
        phwangFree(password);
        return;
    }

    LinkClass *link = this->theFabricObject->mallocLink(my_name);
    if (!link) {
        phwangAbendS("DFabricClass::processSetupLinkRequest", "null link");
        this->sendSetupLinkResponce(tp_transfer_object_val, ajax_id_val, FECommandClass::FAKE_LINK_ID_INDEX, "null link");
        phwangFree(my_name);
        phwangFree(password);
        return;
    }

    this->sendSetupLinkResponce(tp_transfer_object_val, ajax_id_val, link->linkIdIndex(), "succeed");
    phwangFree(my_name);
    phwangFree(password);
}

void DFabricClass::sendSetupLinkResponce (void *tp_transfer_object_val, char const *ajax_id_val, char const *link_id_index_val, char const *result_val)
{
    phwangDebugS(false, "DFabricClass::sendSetupLinkResponce", result_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FECommandClass::SETUP_LINK_DOWNLINK_DATA_SIZE + strlen(result_val), MallocClass::SIGN_IN);
    *data_ptr++ = FECommandClass::SETUP_LINK_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, link_id_index_val);
    data_ptr += FECommandClass::LINK_ID_INDEX_SIZE;
    strcpy(data_ptr, result_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processFreeLinkRequest (void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, LinkClass *link_val)
{
    phwangDebugS(false, "DFabricClass::processFreeLinkRequest", data_val);

    char *end_val = data_val;

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::FREE_LINK);
    *data_ptr++ = FECommandClass::FREE_LINK_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, link_val->linkIdIndex());
    this->transmitFunction(tp_transfer_object_val, downlink_data);

    this->theFabricObject->freeLink(link_val);
}

void DFabricClass::errorProcessFreeLink (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    phwangAbendS("DFabricClass::errorProcessFreeLink", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::FREE_LINK_ERROR);
    *data_ptr++ = FECommandClass::FREE_LINK_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

#define D_FABRIC_CLASS_PROCESSS_GET_LINK_DATA_DOWN_LINK_PENDING_DATA_SIZE (1 + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + LINK_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE)
#define D_FABRIC_CLASS_PROCESSS_GET_LINK_DATA_DOWN_LINK_DATA_SIZE (1 + WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + 1 + WEB_FABRIC_PROTOCOL_NAME_LIST_TAG_SIZE + 1)
#define D_FABRIC_CLASS_PROCESSS_GET_LINK_DATA_DOWN_LINK_PENDING_SESSION_SIZE (1 + WEB_FABRIC_PROTOCOL_NAME_LIST_TAG_SIZE)
void DFabricClass::processGetLinkDataRequest (void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, LinkClass *link_val)
{
    phwangDebugS(false, "DFabricClass::processGetLinkDataRequest", data_val);

    link_val->resetKeepAliveTime();

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::GET_LINK_DATA);
    *data_ptr++ = FECommandClass::GET_LINK_DATA_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    *data_ptr++ = FECommandClass::RESPOND_IS_GET_LINK_DATA_NAME_LIST;
    phwangEncodeNumber(data_ptr, this->theFabricObject->nameListObject()->nameListTag(), FECommandClass::NAME_LIST_TAG_SIZE);
    data_ptr += FECommandClass::NAME_LIST_TAG_SIZE;
    *data_ptr = 0;

    int max_session_table_array_index = phwnagListMgrGetMaxIndex(link_val->sessionListMgrObject(), "DFabricClass::processGetLinkData()");
    SessionClass **session_table_array = (SessionClass **) phwangListMgrGetEntryTableArray(link_val->sessionListMgrObject());
    for (int i = 0; i <= max_session_table_array_index; i++) {
        SessionClass *session = session_table_array[i];
        if (session) {
            char *pending_downlink_data = session->getPendingDownLinkData();
            if (pending_downlink_data) {
                *data_ptr++ = FECommandClass::RESPOND_IS_GET_LINK_DATA_PENDING_DATA;
                session->enqueuePendingDownLinkData(pending_downlink_data);
                strcpy(data_ptr, link_val->linkIdIndex());
                data_ptr += FECommandClass::LINK_ID_INDEX_SIZE;
                strcpy(data_ptr, session->sessionIdIndex());
                data_ptr += FECommandClass::SESSION_ID_INDEX_SIZE;

                if (1) { /* debug */
                    char s[128];
                    sprintf(s, "Pending data exist: %s", downlink_data);
                    phwangDebugS(true, "DFabricClass::processGetLinkDataRequest", s);
                }
            }
        }
    }

    char *pending_session = link_val->getPendingSessionSetup();
    if (pending_session) {
        *data_ptr++ = FECommandClass::RESPOND_IS_GET_LINK_DATA_PENDING_SESSION;
        strcpy(data_ptr, pending_session);
        phwangDebugSS(true, "DFabricClass::processGetLinkDataRequest", "getPendingSessionSetup ", downlink_data);
    }

    char *pending_session3 = link_val->getPendingSessionSetup3();
    if (pending_session3) {
        *data_ptr++ = FECommandClass::RESPOND_IS_GET_LINK_DATA_PENDING_SESSION3;
        strcpy(data_ptr, pending_session3);
        phwangDebugSS(true, "DFabricClass::processGetLinkDataRequest", "getPendingSessionSetup3 ", downlink_data);
    }

    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::errorProcessGetLinkData (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    phwangAbendS("DFabricClass::errorProcessGetLinkData", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::GET_LINK_DATA_ERROR);
    *data_ptr++ = FECommandClass::GET_LINK_DATA_RESPONSE;
    memcpy(data_ptr, ajax_id_val, FECommandClass::AJAX_ID_SIZE);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processGetNameListRequest (void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, LinkClass *link_val)
{
    phwangDebugS(false, "DFabricClass::processGetNameListRequest", data_val);

    char *name_list_tag_val = data_val;
    char *end_val = name_list_tag_val + 3;

    int name_list_tag = phwangDecodeNumber(name_list_tag_val, FECommandClass::NAME_LIST_TAG_SIZE);
    char *name_list = this->theFabricObject->nameListObject()->getNameList(name_list_tag);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(strlen(name_list) + FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::GET_NAME_LIST_ERROR);
    *data_ptr++ = FECommandClass::GET_NAME_LIST_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    *data_ptr = 0;
    if (name_list) {
        strcpy(data_ptr, name_list);
    }
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::errorProcessGetNameList (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    phwangAbendS("DFabricClass::errorProcessGetNameList", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::GET_NAME_LIST_ERROR);
    *data_ptr++ = FECommandClass::GET_NAME_LIST_RESPONSE;
    memcpy(data_ptr, ajax_id_val, FECommandClass::AJAX_ID_SIZE);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processSetupSessionRequest (void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, LinkClass *link_val)
{
    phwangDebugS(true, "DFabricClass::processSetupSessionRequest", data_val);

    char *theme_info_val = data_val;

    switch (*theme_info_val) {
        case 'G':
            break;

        default:
            phwangAbendSS("DFabricClass::processSetupSessionRequest", "theme not supported", theme_info_val);
    }

    int theme_len = phwangDecodeNumber(theme_info_val + 1, 3);
    char *his_name_val = theme_info_val + theme_len;
    phwangDebugSS(false, "DFabricClass::processSetupSessionRequest", "his_name_val=", his_name_val);

    SessionClass *session = link_val->mallocSession();
    if (!session) {
        this->errorProcessSetupSession(tp_transfer_object_val, ajax_id_val, "malloc_session_fail");
        return;
    }

    GroupClass *group = this->theFabricObject->mallocGroup(theme_info_val);
    if (!group) {
        this->errorProcessSetupSession(tp_transfer_object_val, ajax_id_val, "malloc_group_fail");
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
            this->errorProcessSetupSession(tp_transfer_object_val, ajax_id_val, "his_link does not exist");
            return;
        }

        SessionClass *his_session = his_link->mallocSession();
        if (!his_session) {
            this->errorProcessSetupSession(tp_transfer_object_val, ajax_id_val, "null his_session");
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
    char *downlink_data = data_ptr = (char *) phwangMalloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::SETUP_SESSION);
    *data_ptr++ = FECommandClass::SETUP_SESSION_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, session->sessionIdIndex());
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::sendSetupSessionResponce (void *tp_transfer_object_val, char const *ajax_id_val, char const *link_id_index_val, char const *result_val)
{
    phwangDebugS(false, "DFabricClass::sendSetupSessionResponce", result_val);
    /*
    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::SETUP_SESSION);
    *data_ptr++ = FECommandClass::SETUP_SESSION_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, session->sessionIdIndex());
    this->transmitFunction(tp_transfer_object_val, downlink_data);
    */
}

void DFabricClass::errorProcessSetupSession (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    phwangAbendS("DFabricClass::errorProcessSetupSession", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::SETUP_SESSION_ERROR);
    *data_ptr++ = FECommandClass::SETUP_SESSION_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::mallocRoom (GroupClass *group_val, char *theme_info_val)
{
    char *data_ptr;
    char *uplink_data = data_ptr = (char *) phwangMalloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::MALLOC_ROOM);
    *data_ptr++ = FT_Command_Class::SETUP_ROOM_COMMAND;
    memcpy(data_ptr, group_val->groupIdIndex(), GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE);
    data_ptr += GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE;
    strcpy(data_ptr, theme_info_val);
    this->theFabricObject->uFabricObject()->transmitFunction(uplink_data);
}

void DFabricClass::processSetupSession2Request (void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, LinkClass *link_val)
{
    phwangDebugS(true, "DFabricClass::processSetupSession2Request", data_val);

    char *link_id_index_val = data_val;
    char *session_id_index_val = link_id_index_val + FECommandClass::LINK_ID_INDEX_SIZE;
    char *theme_info_val = session_id_index_val + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

    LinkClass *link = this->theFabricObject->searchLink(link_id_index_val, data_val - 1);
    if (!link) {
        this->errorProcessSetupSession2(tp_transfer_object_val, ajax_id_val, "link does not exist");
        return;
    }

    SessionClass *session = link->searchSession(session_id_index_val);
    if (!session) {
        this->errorProcessSetupSession2(tp_transfer_object_val, ajax_id_val, "session does not exist");
        return;
    }

    GroupClass *group = session->groupObject();
    this->mallocRoom(group, theme_info_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::SETUP_SESSION2);
    *data_ptr++ = FECommandClass::SETUP_SESSION2_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    memcpy(data_ptr, link_id_index_val, FECommandClass::LINK_ID_INDEX_SIZE);
    data_ptr += FECommandClass::LINK_ID_INDEX_SIZE;
    memcpy(data_ptr, session_id_index_val, SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
    *data_ptr = 0;
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::errorProcessSetupSession2 (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    phwangAbendS("DFabricClass::errorProcessSetupSession2", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::SETUP_SESSION2_ERROR);
    *data_ptr++ = FECommandClass::SETUP_SESSION2_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processSetupSession3Request (void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, LinkClass *link_val)
{
    phwangDebugS(true, "DFabricClass::processSetupSession3Reques", data_val);

    char *link_and_session_id_index_val = data_val;
    char *end_val = link_and_session_id_index_val + FECommandClass::LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::SETUP_SESSION3);
    *data_ptr++ = FECommandClass::SETUP_SESSION3_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    memcpy(data_ptr, link_and_session_id_index_val, FECommandClass::LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += FECommandClass::LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
    *data_ptr = 0;
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processFreeSessionRequest (void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, SessionClass *session_val)
{
}

void DFabricClass::errorProcessFreeSession (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
}

void DFabricClass::processPutSessionDataRequest (void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, SessionClass *session_val)
{
    phwangDebugS(true, "DFabricClass::processPutSessionDataRequest", data_val);

    char *room = session_val->groupObject()->roomIdIndex();
    if (!room) {
        this->errorProcessPutSessionData(tp_transfer_object_val, ajax_id_val, "null room");
        return;
    }

    char *data_ptr;

    /* transfer data up */
    char *uplink_data = data_ptr = (char *) phwangMalloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::PUT_SESSION_DATA0);
    *data_ptr++ = FT_Command_Class::PUT_ROOM_DATA_COMMAND;
    memcpy(data_ptr, room, ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    data_ptr += ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE;
    strcpy(data_ptr, data_val);
    this->theFabricObject->uFabricObject()->transmitFunction(uplink_data);

    /* send the response down */
    char *downlink_data = data_ptr = (char *) phwangMalloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::PUT_SESSION_DATA1);
    *data_ptr++ = FECommandClass::PUT_SESSION_DATA_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    memcpy(data_ptr, session_val->linkObject()->linkIdIndex(), FECommandClass::LINK_ID_INDEX_SIZE);
    data_ptr += FECommandClass::LINK_ID_INDEX_SIZE;
    memcpy(data_ptr, session_val->sessionIdIndex(), SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
    strcpy(data_ptr, "job is done");
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::errorProcessPutSessionData (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    phwangAbendS("DFabricClass::errorProcessPutSessionData", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::PUT_SESSION_DATA_ERROR);
    *data_ptr++ = FECommandClass::PUT_SESSION_DATA_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processGetSessionDataRequest (void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, SessionClass *session_val)
{
    phwangDebugS(true, "DFabricClass::processGetSessionDataRequest", data_val);

    char *data = session_val->getPendingDownLinkData();

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::GET_SESSION_DATA);
    *data_ptr++ = FECommandClass::GET_SESSION_DATA_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    memcpy(data_ptr, session_val->linkObject()->linkIdIndex(), FECommandClass::LINK_ID_INDEX_SIZE);
    data_ptr += FECommandClass::LINK_ID_INDEX_SIZE;
    memcpy(data_ptr, session_val->sessionIdIndex(), SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
    strcpy(data_ptr, data);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::errorProcessGetSessionData (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    phwangAbendS("DFabricClass::errorProcessGetSessionData", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE, MallocClass::GET_SESSION_DATA_ERROR);
    *data_ptr++ = FECommandClass::GET_SESSION_DATA_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}
