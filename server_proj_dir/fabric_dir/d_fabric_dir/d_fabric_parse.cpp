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
        phwangDebug(true, "DFabricClass::exportedParseFunction", data_val);
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
                    phwangAbend("DFabricClass::exportedParseFunction", data_val);
                    return;
            }
            break;

        case '1':
            link = this->theFabricObject->searchLink(rest_data, data_val);
            if (!link) {
                this->sendSearchLinkFailResponse(command, tp_transfer_object_val, ajax_id);
                return;
            }
            rest_data += ListMgrProtocolClass::LINK_ID_INDEX_SIZE;

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
                    phwangAbend("DFabricClass::dbAccountObject", data_val);
                    return;
            }
            break;

        case '2':
            session = this->theFabricObject->serachLinkAndSession(rest_data);
            if (!session) {
                this->sendSearchLinkSessionFailResponse(command, tp_transfer_object_val, ajax_id);
                return;
            }
            rest_data += ListMgrProtocolClass::LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

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
                    phwangAbend("DFabricClass::dbAccountObject", data_val);
            }

            break;

        default:
            phwangAbend("DFabricClass::dbAccountObject", "bad type");
            break;
    }

}

void DFabricClass::sendSearchLinkFailResponse (char const command_val, void *tp_transfer_object_val, char const *ajax_id_val)
{
    phwangAbend("DFabricClass::sendSearchLinkFailResponse", "");

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::BAD_LINK);
    *data_ptr++ = command_val;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, "link does not exist");
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::sendSearchLinkSessionFailResponse (char const command_val, void *tp_transfer_object_val, char const *ajax_id_val)
{
    phwangAbend("DFabricClass::sendSearchLinkSessionFailResponse", "");

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::BAD_SESSION);
    *data_ptr++ = command_val;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, "link_session does not exist");
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processMessageRequest (void *tp_transfer_object_val, char *input_data_val, char const *ajax_id_val)
{
    phwangDebug(true, "DFabricClass::processMessageRequest", input_data_val);

    char act = *input_data_val++;

    char *encoded_data = input_data_val;
    int data_size;
    char *data = phwangDecodeStringMalloc(encoded_data, &data_size);
    char *output_data;

    if (1) { /* debug */
        char buf[256];
        sprintf(buf, "act=%c data=%s\n", act, data);
        phwangDebug(true, "DFabricClass::processMessageRequest", buf);
    }

    switch (act) {
        case 'I':
            this->messengerObject()->initMessenger();
            this->sendMessageResponce(tp_transfer_object_val, ajax_id_val, "succeed", "I_data");
            break;

        case 'R':
            output_data = this->messengerObject()->getMessage();
            phwangDebug(true, "DFabricClass::processMessageRequest", output_data);
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

#define D_FABRIC_CLASS_PROCESSS_MMW_READ_DATA_DOWN_LINK_DATA_SIZE (1 + FECommandClass::AJAX_ID_SIZE + ListMgrProtocolClass::LINK_ID_INDEX_SIZE + 1)
void DFabricClass::sendMessageResponce (void *tp_transfer_object_val, char const *ajax_id_val, char const *result_val, char const *data_val)
{
    phwangDebug(true, "DFabricClass::sendMessageResponce", result_val);

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
    phwangDebug(false, "DFabricClass::processSignUpRequest", data_val);

    char *encoded_account_name = data_val;
    int account_name_size;
    char *account_name = phwangDecodeStringMalloc(encoded_account_name, &account_name_size);

    char *encoded_password = encoded_account_name + account_name_size;
    int password_size;
    char *password = phwangDecodeStringMalloc(encoded_password, &password_size);

    char *encoded_email = encoded_password + password_size;
    int email_size;
    char *email = phwangDecodeStringMalloc(encoded_email, &email_size);

    this->debug2(false, "processSignUpRequest", account_name, password);

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
                phwangAbend("DFabricClass::processSignUpRequest", "result_str");
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

#define D_FABRIC_CLASS_PROCESSS_SIGN_UP_DOWN_LINK_DATA_SIZE (1 + FECommandClass::AJAX_ID_SIZE + ListMgrProtocolClass::LINK_ID_INDEX_SIZE + 1)
void DFabricClass::sendSignUpResponce (void *tp_transfer_object_val, char const *ajax_id_val, char const *result_val)
{
    phwangDebug(false, "DFabricClass::sendSignUpResponce", result_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(D_FABRIC_CLASS_PROCESSS_SIGN_UP_DOWN_LINK_DATA_SIZE + strlen(result_val), MallocClass::SIGN_UP);
    *data_ptr++ = FECommandClass::SIGN_UP_RESPONSE;
    memcpy(data_ptr, ajax_id_val, FECommandClass::AJAX_ID_SIZE);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, result_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

#define D_FABRIC_CLASS_FAKE_LINK_ID_INDEX "99990000"
void DFabricClass::processSetupLinkRequest (void *tp_transfer_object_val, char *data_val, char const *ajax_id_val)
{
    phwangDebug(false, "DFabricClass::processSetupLinkRequest", data_val);

    char *encoded_my_name = data_val;
    int my_name_size;
    char *my_name = phwangDecodeStringMalloc(encoded_my_name, &my_name_size);

    char *encoded_password = encoded_my_name + my_name_size;
    int password_size;
    char *password = phwangDecodeStringMalloc(encoded_password, &password_size);

    this->debug2(false, "processSetupLink", my_name, password);

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
                phwangAbend("DFabricClass::processSetupLinkRequest", "check_password_result");
                break;
        }
        this->sendSetupLinkResponce(tp_transfer_object_val, ajax_id_val, D_FABRIC_CLASS_FAKE_LINK_ID_INDEX, result_str);
        phwangFree(my_name);
        phwangFree(password);
        return;
    }

    LinkClass *link = this->theFabricObject->mallocLink(my_name);
    if (!link) {
        phwangAbend("DFabricClass::processSetupLinkRequest", "null link");
        this->sendSetupLinkResponce(tp_transfer_object_val, ajax_id_val, D_FABRIC_CLASS_FAKE_LINK_ID_INDEX, "null link");
        phwangFree(my_name);
        phwangFree(password);
        return;
    }

    this->sendSetupLinkResponce(tp_transfer_object_val, ajax_id_val, link->linkIdIndex(), "succeed");
    phwangFree(my_name);
    phwangFree(password);
}

#define D_FABRIC_CLASS_PROCESSS_SETUP_LINK_DOWN_LINK_DATA_SIZE (1 + FECommandClass::AJAX_ID_SIZE + ListMgrProtocolClass::LINK_ID_INDEX_SIZE + 1)
void DFabricClass::sendSetupLinkResponce (void *tp_transfer_object_val, char const *ajax_id_val, char const *link_id_index_val, char const *result_val)
{
    phwangDebug(false, "DFabricClass::sendSetupLinkResponce", result_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(D_FABRIC_CLASS_PROCESSS_SETUP_LINK_DOWN_LINK_DATA_SIZE + strlen(result_val), MallocClass::SIGN_IN);
    *data_ptr++ = FECommandClass::SETUP_LINK_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, link_id_index_val);
    data_ptr += ListMgrProtocolClass::LINK_ID_INDEX_SIZE;
    strcpy(data_ptr, result_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processFreeLinkRequest (void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, LinkClass *link_val)
{
    phwangDebug(false, "DFabricClass::processFreeLinkRequest", data_val);

    char *end_val = data_val;

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::FREE_LINK);
    *data_ptr++ = FECommandClass::FREE_LINK_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, link_val->linkIdIndex());
    this->transmitFunction(tp_transfer_object_val, downlink_data);

    this->theFabricObject->freeLink(link_val);
}

void DFabricClass::errorProcessFreeLink (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    phwangAbend("DFabricClass::errorProcessFreeLink", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::FREE_LINK_ERROR);
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
    phwangDebug(false, "DFabricClass::processGetLinkDataRequest", data_val);

    link_val->resetKeepAliveTime();

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::GET_LINK_DATA);
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
                data_ptr += ListMgrProtocolClass::LINK_ID_INDEX_SIZE;
                strcpy(data_ptr, session->sessionIdIndex());
                data_ptr += ListMgrProtocolClass::SESSION_ID_INDEX_SIZE;

                if (1) { /* debug */
                    char s[128];
                    sprintf(s, "Pending data exist: %s", downlink_data);
                    this->logit("processGetLinkData", s);
                }
            }
        }
    }

    char *pending_session = link_val->getPendingSessionSetup();
    if (pending_session) {
        *data_ptr++ = FECommandClass::RESPOND_IS_GET_LINK_DATA_PENDING_SESSION;
        strcpy(data_ptr, pending_session);
        this->debug2(true, "==================processGetLinkData", "getPendingSessionSetup ", downlink_data);
    }

    char *pending_session3 = link_val->getPendingSessionSetup3();
    if (pending_session3) {
        *data_ptr++ = FECommandClass::RESPOND_IS_GET_LINK_DATA_PENDING_SESSION3;
        strcpy(data_ptr, pending_session3);
        this->debug2(true, "==================processGetLinkData", "getPendingSessionSetup3 ", downlink_data);
    }

    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::errorProcessGetLinkData (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    this->logit("+++++++++++++ABEND: errorProcessGetLinkData", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::GET_LINK_DATA_ERROR);
    *data_ptr++ = FECommandClass::GET_LINK_DATA_RESPONSE;
    memcpy(data_ptr, ajax_id_val, FECommandClass::AJAX_ID_SIZE);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processGetNameListRequest (void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, LinkClass *link_val)
{
    phwangDebug(false, "DFabricClass::processGetNameListRequest", data_val);

    char *name_list_tag_val = data_val;
    char *end_val = name_list_tag_val + 3;

    int name_list_tag = phwangDecodeNumber(name_list_tag_val, FECommandClass::NAME_LIST_TAG_SIZE);
    char *name_list = this->theFabricObject->nameListObject()->getNameList(name_list_tag);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(strlen(name_list) + ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::GET_NAME_LIST_ERROR);
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
    phwangAbend("DFabricClass::errorProcessGetNameList", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::GET_NAME_LIST_ERROR);
    *data_ptr++ = FECommandClass::GET_NAME_LIST_RESPONSE;
    memcpy(data_ptr, ajax_id_val, FECommandClass::AJAX_ID_SIZE);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processSetupSessionRequest (void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, LinkClass *link_val)
{
    phwangDebug(true, "DFabricClass::processSetupSessionRequest", data_val);

    char *theme_info_val = data_val;
    int theme_len = phwangDecodeNumber(theme_info_val + 1, 3);
    char *his_name_val = theme_info_val + theme_len;

    SessionClass *session = link_val->mallocSession();
    if (!session) {
        this->errorProcessSetupSession(tp_transfer_object_val, ajax_id_val, "null session");
        return;
    }

    GroupClass *group = this->theFabricObject->mallocGroup(theme_info_val);
    if (!group) {
        this->errorProcessSetupSession(tp_transfer_object_val, ajax_id_val, "null group");
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
    char *downlink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::SETUP_SESSION);
    *data_ptr++ = FECommandClass::SETUP_SESSION_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, session->sessionIdIndex());
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::errorProcessSetupSession (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    phwangAbend("DFabricClass::errorProcessSetupSession", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::SETUP_SESSION_ERROR);
    *data_ptr++ = FECommandClass::SETUP_SESSION_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::mallocRoom (GroupClass *group_val, char *theme_info_val)
{
    char *data_ptr;
    char *uplink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::MALLOC_ROOM);
    *data_ptr++ = FABRIC_THEME_PROTOCOL_COMMAND_IS_SETUP_ROOM;
    memcpy(data_ptr, group_val->groupIdIndex(), GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE);
    data_ptr += GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE;
    strcpy(data_ptr, theme_info_val);
    this->theFabricObject->uFabricObject()->transmitFunction(uplink_data);
}

void DFabricClass::processSetupSession2Request (void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, LinkClass *link_val)
{
    phwangDebug(true, "DFabricClass::processSetupSession2Request", data_val);

    char *link_id_index_val = data_val;
    char *session_id_index_val = link_id_index_val + ListMgrProtocolClass::LINK_ID_INDEX_SIZE;
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
    char *downlink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::SETUP_SESSION2);
    *data_ptr++ = FECommandClass::SETUP_SESSION2_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    memcpy(data_ptr, link_id_index_val, ListMgrProtocolClass::LINK_ID_INDEX_SIZE);
    data_ptr += ListMgrProtocolClass::LINK_ID_INDEX_SIZE;
    memcpy(data_ptr, session_id_index_val, SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
    *data_ptr = 0;
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::errorProcessSetupSession2 (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    phwangAbend("DFabricClass::errorProcessSetupSession2", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::SETUP_SESSION2_ERROR);
    *data_ptr++ = FECommandClass::SETUP_SESSION2_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processSetupSession3Request (void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, LinkClass *link_val)
{
    phwangDebug(true, "DFabricClass::processSetupSession3Reques", data_val);

    char *link_and_session_id_index_val = data_val;
    char *end_val = link_and_session_id_index_val + ListMgrProtocolClass::LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::SETUP_SESSION3);
    *data_ptr++ = FECommandClass::SETUP_SESSION3_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    memcpy(data_ptr, link_and_session_id_index_val, ListMgrProtocolClass::LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += ListMgrProtocolClass::LINK_ID_INDEX_SIZE + SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
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
    phwangDebug(true, "DFabricClass::processPutSessionDataRequest", data_val);

    char *room = session_val->groupObject()->roomIdIndex();
    if (!room) {
        this->errorProcessPutSessionData(tp_transfer_object_val, ajax_id_val, "null room");
        return;
    }

    char *data_ptr;

    /* transfer data up */
    char *uplink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::PUT_SESSION_DATA0);
    *data_ptr++ = FABRIC_THEME_PROTOCOL_COMMAND_IS_PUT_ROOM_DATA;
    memcpy(data_ptr, room, ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    data_ptr += ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE;
    strcpy(data_ptr, data_val);
    this->theFabricObject->uFabricObject()->transmitFunction(uplink_data);

    /* send the response down */
    char *downlink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::PUT_SESSION_DATA1);
    *data_ptr++ = FECommandClass::PUT_SESSION_DATA_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    memcpy(data_ptr, session_val->linkObject()->linkIdIndex(), ListMgrProtocolClass::LINK_ID_INDEX_SIZE);
    data_ptr += ListMgrProtocolClass::LINK_ID_INDEX_SIZE;
    memcpy(data_ptr, session_val->sessionIdIndex(), SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
    strcpy(data_ptr, "job is done");
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::errorProcessPutSessionData (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    phwangAbend("DFabricClass::errorProcessPutSessionData", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::PUT_SESSION_DATA_ERROR);
    *data_ptr++ = FECommandClass::PUT_SESSION_DATA_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processGetSessionDataRequest (void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, SessionClass *session_val)
{
    phwangDebug(true, "DFabricClass::processGetSessionDataRequest", data_val);

    char *data = session_val->getPendingDownLinkData();

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::GET_SESSION_DATA);
    *data_ptr++ = FECommandClass::GET_SESSION_DATA_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    memcpy(data_ptr, session_val->linkObject()->linkIdIndex(), ListMgrProtocolClass::LINK_ID_INDEX_SIZE);
    data_ptr += ListMgrProtocolClass::LINK_ID_INDEX_SIZE;
    memcpy(data_ptr, session_val->sessionIdIndex(), SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
    strcpy(data_ptr, data);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::errorProcessGetSessionData (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    phwangAbend("DFabricClass::errorProcessGetSessionData", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(ListMgrProtocolClass::LINK_MGR_DATA_BUFFER_SIZE + 4, MallocClass::GET_SESSION_DATA_ERROR);
    *data_ptr++ = FECommandClass::GET_SESSION_DATA_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FECommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}
