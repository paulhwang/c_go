/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../define_dir/ft_command_define.h"
#include "../../define_dir/fe_command_define.h"
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

void DFabricClass::exportedParseFunction (
    void *tp_transfer_object_val,
    char *data_val)
{
    LinkClass *link;
    SessionClass *session;
    char *response_data;

    if (data_val[1] != FE_CommandClass::GET_LINK_DATA_COMMAND) {
        phwangDebugS(true, "DFabricClass::exportedParseFunction", data_val);
    }

    char type = data_val[0];
    char command = data_val[1];

    /* get ajax_id */
    char ajax_id[8];
    memcpy(ajax_id, &data_val[2], FE_CommandClass::AJAX_ID_SIZE);
    ajax_id[FE_CommandClass::AJAX_ID_SIZE] = 0;

    char *current_data = &data_val[2 + FE_CommandClass::AJAX_ID_SIZE];

    switch (type) {
        case '0':
            switch (command) {
                case FE_CommandClass::SIGN_UP_COMMAND:
                    response_data = this->processSignUpRequest(current_data);
                    response_data[0] = FE_CommandClass::SIGN_UP_RESPONSE;
                    break;

                case FE_CommandClass::SETUP_LINK_COMMAND:
                    response_data = this->processSignInRequest(current_data);
                    response_data[0] = FE_CommandClass::SETUP_LINK_RESPONSE;
                    break;

                case FE_CommandClass::MESSAGE_COMMAND:
                    this->processMessageRequest(tp_transfer_object_val, current_data, ajax_id);
                    return;

                default:
                    phwangAbendS("DFabricClass::exportedParseFunction", data_val);
                    return;
            }
            break;

        case '1':
            link = this->theFabricObject->searchLink(current_data, data_val);
            if (!link) {
                this->sendSearchLinkFailResponse(command, tp_transfer_object_val, ajax_id);
                return;
            }
            current_data += FE_CommandClass::LINK_ID_INDEX_SIZE;

            switch (command) {
                case FE_CommandClass::SIGN_OFF_COMMAND:
                    response_data = this->processSignOffRequest(link);
                    response_data[0] = FE_CommandClass::SIGN_OFF_RESPONSE;
                    break;

                case FE_CommandClass::GET_LINK_DATA_COMMAND:
                    response_data = this->processGetLinkDataRequest(tp_transfer_object_val, current_data, ajax_id, link);
                    response_data[0] = FE_CommandClass::GET_LINK_DATA_RESPONSE;
                    break;

                case FE_CommandClass::GET_NAME_LIST_COMMAND:
                    response_data = this->processGetNameListRequest(link, current_data);
                    response_data[0] = FE_CommandClass::GET_NAME_LIST_RESPONSE;
                    break;

                case FE_CommandClass::SETUP_SESSION_COMMAND:
                    response_data = this->processSetupSessionRequest(tp_transfer_object_val, current_data, ajax_id, link);
                    response_data[0] = FE_CommandClass::SETUP_SESSION_RESPONSE;
                    break;

                case FE_CommandClass::SETUP_SESSION2_COMMAND:
                    this->processSetupSession2Request(tp_transfer_object_val, current_data, ajax_id, link);
                    return;

                case FE_CommandClass::SETUP_SESSION3_COMMAND:
                    response_data = this->processSetupSession3Request(link, current_data);
                    response_data[0] = FE_CommandClass::SETUP_SESSION3_RESPONSE;
                    break;

                default:
                    phwangAbendS("DFabricClass::dbAccountObject", data_val);
                    return;
            }
            break;

        case '2':
            session = this->theFabricObject->serachLinkAndSession(current_data);
            if (!session) {
                this->sendSearchLinkSessionFailResponse(command, tp_transfer_object_val, ajax_id);
                return;
            }
            current_data += FE_CommandClass::LINK_ID_INDEX_SIZE + FE_CommandClass::SESSION_ID_INDEX_SIZE;

            switch (command) {
                case FE_CommandClass::FREE_SESSION_COMMAND:
                    this->processFreeSessionRequest(link, session);
                    response_data[0] = FE_CommandClass::FREE_SESSION_RESPONSE;
                    break;

                case FE_CommandClass::PUT_SESSION_DATA_COMMAND:
                    response_data = this->processPutSessionDataRequest(session, current_data);
                    response_data[0] = FE_CommandClass::PUT_SESSION_DATA_RESPONSE;
                    break;

                case FE_CommandClass::GET_SESSION_DATA_COMMAND:
                    response_data = this->processGetSessionDataRequest(session, current_data);
                    response_data[0] = FE_CommandClass::GET_SESSION_DATA_RESPONSE;
                    break;

                default:
                    phwangAbendS("DFabricClass::dbAccountObject", data_val);
                    return;
            }
            break;

        default:
            phwangAbendS("DFabricClass::dbAccountObject", "bad type");
            return;
    }
    memcpy(&response_data[1], ajax_id, FE_CommandClass::AJAX_ID_SIZE);
    this->transmitFunction(tp_transfer_object_val, response_data);
}

void DFabricClass::sendSearchLinkFailResponse (
    char const command_val,
    void *tp_transfer_object_val,
    char const *ajax_id_val)
{
    phwangAbendS("DFabricClass::sendSearchLinkFailResponse", "");

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FE_CommandClass::FE_DL_DATA_BUF_SIZE, MallocClass::BAD_LINK);
    *data_ptr++ = command_val;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FE_CommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, FE_CommandClass::FE_RESULT_LINK_NOT_EXIST);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::sendSearchLinkSessionFailResponse (
    char const command_val,
    void *tp_transfer_object_val,
    char const *ajax_id_val)
{
    phwangAbendS("DFabricClass::sendSearchLinkSessionFailResponse", "");

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FE_CommandClass::FE_DL_DATA_BUF_SIZE, MallocClass::BAD_SESSION);
    *data_ptr++ = command_val;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FE_CommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, FE_CommandClass::FE_RESULT_SESSION_NOT_EXIST);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::processMessageRequest (
    void *tp_transfer_object_val,
    char *input_data_val,
    char const *ajax_id_val)
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
            this->sendMessageResponce(tp_transfer_object_val, ajax_id_val, FE_CommandClass::FE_RESULT_SUCCEED, "I_data");
            break;

        case 'R':
            output_data = this->messengerObject()->getMessage();
            phwangDebugS(true, "DFabricClass::processMessageRequest", output_data);
            this->sendMessageResponce(tp_transfer_object_val, ajax_id_val, FE_CommandClass::FE_RESULT_SUCCEED, output_data);
            break;

        case 'W':
            this->messengerObject()->putMessage(0);
            this->sendMessageResponce(tp_transfer_object_val, ajax_id_val, FE_CommandClass::FE_RESULT_SUCCEED, "W_data");
            break;

        default:
            break;
    }
}

#define D_FABRIC_CLASS_PROCESSS_MMW_READ_DATA_DOWN_LINK_DATA_SIZE (1 + FE_CommandClass::AJAX_ID_SIZE + FE_CommandClass::LINK_ID_INDEX_SIZE + 1)
void DFabricClass::sendMessageResponce (
    void *tp_transfer_object_val,
    char const *ajax_id_val,
    char const *result_val,
    char const *data_val)
{
    phwangDebugS(true, "DFabricClass::sendMessageResponce", result_val);

    char *encoded_result = phwangEncodeStringMalloc(result_val);
    int encoded_result_length = strlen(encoded_result);
    char *encoded_data = phwangEncodeStringMalloc(data_val);
    int encoded_data_length = strlen(encoded_data);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(D_FABRIC_CLASS_PROCESSS_MMW_READ_DATA_DOWN_LINK_DATA_SIZE + encoded_result_length + encoded_data_length, MallocClass::DATAGRAM);
    *data_ptr++ = FE_CommandClass::MESSAGE_RESPONSE;
    memcpy(data_ptr, ajax_id_val, FE_CommandClass::AJAX_ID_SIZE);
    data_ptr += FE_CommandClass::AJAX_ID_SIZE;

    strcpy(data_ptr, encoded_result);
    data_ptr += encoded_result_length;
    phwangFree(encoded_result);

    strcpy(data_ptr, encoded_data);
    //data_ptr += encoded_data_length;
    phwangFree(encoded_data);

    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

char *DFabricClass::processSignUpRequest (char *data_val)
{
    char *response_data;
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
                result_str = FE_CommandClass::FE_RESULT_ACCOUNT_NAME_ALREADY_EXIST;
                break;

            case DbAccountClass::DB_ACCOUNT_SELECT_FAIL:
                result_str = FE_CommandClass::FE_RESULT_DB_SELECT_FAIL;
                break;

            default:
                phwangAbendS("DFabricClass::processSignUpRequest", "invalid_result");
                break;
        }
        response_data = generateSignUpResponse(FE_CommandClass::FE_RESULT_SUCCEED);
        phwangFree(account_name);
        phwangFree(password);
        phwangFree(email);
        return response_data;
    }

    DbAccountEntryClass *account_entry = new DbAccountEntryClass();
    account_entry->setAccountName(account_name);
    account_entry->setPassword(password);
    account_entry->setEmail(email);
    this->dbAccountObject()->insertAccountEntry(account_entry);

    response_data = generateSignUpResponse(FE_CommandClass::FE_RESULT_SUCCEED);
    return response_data;

    /***
    ---the buffers has been freed in the insertAccountEntry()---
    free(account_name);
    free(password);
    free(email);
    ***/
}

char *DFabricClass::generateSignUpResponse (char const *result_val)
{
    phwangDebugS(false, "DFabricClass::generateSignUpResponse", result_val);

    char *response_data = (char *) phwangMalloc(FE_CommandClass::FE_RESPONSE_BUFFER_SIZE + strlen(result_val), MallocClass::generateSignUpResponse);
    char *current_ptr = &response_data[FE_CommandClass::FE_RESPONSE_HEADER_SIZE];
    strcpy(current_ptr, result_val);
    return response_data;
}

char *DFabricClass::processSignInRequest (char *data_val)
{
    char *response_data;
    phwangDebugS(false, "DFabricClass::processSignInRequest", data_val);

    char *encoded_my_name = data_val;
    int my_name_size;
    char *my_name = phwangDecodeStringMalloc(encoded_my_name, &my_name_size);

    char *encoded_password = encoded_my_name + my_name_size;
    int password_size;
    char *password = phwangDecodeStringMalloc(encoded_password, &password_size);

    phwangDebugSS(false, "DFabricClass::processSignInRequest", my_name, password);

    int result = this->dbObject()->dbAccountObject()->checkPassword(my_name, password);
    if (result != DbAccountClass::DB_ACCOUNT_PASSWORD_MATCH) {
        char const*result_str;
        switch (result) {
            case DbAccountClass::DB_ACCOUNT_PASSWORD_NOT_MATCH:
                result_str = FE_CommandClass::FE_RESULT_PASSWORD_NOT_MATCH;
                break;
            case DbAccountClass::DB_ACCOUNT_NAME_NOT_EXIST:
                result_str = FE_CommandClass::FE_RESULT_ACCOUNT_NAME_NOT_EXIST;
                break;
            case DbAccountClass::DB_ACCOUNT_SELECT_FAIL:
                result_str = "select fail";
                break;
            default:
                phwangAbendS("DFabricClass::processSignInRequest", "check_password_result");
                break;
        }
        phwangFree(my_name);
        phwangFree(password);
        response_data = generateSignInResponse(result_str, FE_CommandClass::FAKE_LINK_ID_INDEX);
        return response_data;
    }

    LinkClass *link = this->theFabricObject->mallocLink(my_name);
    if (!link) {
        phwangAbendS("DFabricClass::processSignInRequest", "null link");
        phwangFree(my_name);
        phwangFree(password);
        response_data = generateSignInResponse(FE_CommandClass::FE_RESULT_NULL_LINK, FE_CommandClass::FAKE_LINK_ID_INDEX);
        return response_data;
    }

    phwangFree(my_name);
    phwangFree(password);
    response_data = generateSignInResponse(FE_CommandClass::FE_RESULT_SUCCEED, link->linkIdIndex());
    return response_data;
}

char *DFabricClass::generateSignInResponse (
    char const *result_val,
    char const *link_id_index_val)
{
    phwangDebugS(false, "DFabricClass::generateSignInResponse", result_val);

    char *response_data = (char *) phwangMalloc(FE_CommandClass::FE_RESPONSE_BUF_WITH_LINK_SIZE + strlen(result_val), MallocClass::generateSignInResponse);
    char *current_ptr = &response_data[FE_CommandClass::FE_RESPONSE_HEADER_SIZE];
    memcpy(current_ptr, result_val, FE_CommandClass::FE_RESULT_SIZE);
    current_ptr += FE_CommandClass::FE_RESULT_SIZE;
    strcpy(current_ptr, link_id_index_val);
    return response_data;
}

char *DFabricClass::processSignOffRequest (
    LinkClass *link_val)
{
    char *response_data;
    phwangDebugSS(false, "DFabricClass::processSignOffRequest", "link_id=", link_val->linkIdIndex());

    char link_id_buf[FE_CommandClass::LINK_ID_INDEX_SIZE + 1];
    strcpy(link_id_buf, link_val->linkIdIndex());
    this->theFabricObject->freeLink(link_val);

    response_data = generateSignInResponse(FE_CommandClass::FE_RESULT_SUCCEED, link_id_buf);
    return response_data;
}

char *DFabricClass::generateSignOffResponse (
    char const *result_val,
    char const *link_id_index_val)
{
    phwangDebugS(false, "DFabricClass::generateSignOffResponse", result_val);

    char *response_data = (char *) phwangMalloc(FE_CommandClass::FE_RESPONSE_BUF_WITH_LINK_SIZE + strlen(result_val), MallocClass::generateSignOffResponse);
    char *current_ptr = &response_data[FE_CommandClass::FE_RESPONSE_HEADER_SIZE];
    memcpy(current_ptr, result_val, FE_CommandClass::FE_RESULT_SIZE);
    current_ptr += FE_CommandClass::FE_RESULT_SIZE;
    strcpy(current_ptr, link_id_index_val);
    return response_data;
}

char *DFabricClass::processGetLinkDataRequest (
    void *tp_transfer_object_val,
    char *data_val,
    char const *ajax_id_val,
    LinkClass *link_val)
{
    char *response_data;
    phwangDebugS(false, "DFabricClass::processGetLinkDataRequest", data_val);

    link_val->resetKeepAliveTime();

    char *downlink_data = (char *) phwangMalloc(FE_CommandClass::FE_DL_DATA_BUF_SIZE, MallocClass::GET_LINK_DATA);
    char *current_ptr = &downlink_data[FE_CommandClass::FE_RESPONSE_HEADER_SIZE];

    memcpy(current_ptr, FE_CommandClass::FE_RESULT_SUCCEED, FE_CommandClass::FE_RESULT_SIZE);
    current_ptr += FE_CommandClass::FE_RESULT_SIZE;

    memcpy(current_ptr, link_val->linkIdIndex(), FE_CommandClass::LINK_ID_INDEX_SIZE);
    current_ptr += FE_CommandClass::LINK_ID_INDEX_SIZE;

    *current_ptr++ = FE_CommandClass::RESPOND_IS_GET_LINK_DATA_NAME_LIST;
    phwangEncodeNumber(current_ptr, this->theFabricObject->nameListObject()->nameListTag(), FE_CommandClass::NAME_LIST_TAG_SIZE);
    current_ptr += FE_CommandClass::NAME_LIST_TAG_SIZE;
    *current_ptr = 0;

    int max_session_table_array_index = phwnagListMgrGetMaxIndex(link_val->sessionListMgrObject(), "DFabricClass::processGetLinkData()");
    SessionClass **session_table_array = (SessionClass **) phwangListMgrGetEntryTableArray(link_val->sessionListMgrObject());
    for (int i = 0; i <= max_session_table_array_index; i++) {
        SessionClass *session = session_table_array[i];
        if (session) {
            char *pending_downlink_data = session->getPendingDownLinkData();
            if (pending_downlink_data) {
                *current_ptr++ = FE_CommandClass::RESPOND_IS_GET_LINK_DATA_PENDING_DATA;
                session->enqueuePendingDownLinkData(pending_downlink_data);
                strcpy(current_ptr, link_val->linkIdIndex());
                current_ptr += FE_CommandClass::LINK_ID_INDEX_SIZE;
                strcpy(current_ptr, session->sessionIdIndex());
                current_ptr += FE_CommandClass::SESSION_ID_INDEX_SIZE;

                phwangDebugSS(true, "DFabricClass::processGetLinkDataRequest","Pending_data_exist:", downlink_data);
            }
        }
    }

    char *pending_session_info = link_val->getPendingSessionSetup();
    if (pending_session_info) {
        *current_ptr++ = FE_CommandClass::RESPOND_IS_GET_LINK_DATA_PENDING_SESSION;
        strcpy(current_ptr, pending_session_info);
        phwangDebugSS(true, "DFabricClass::processGetLinkDataRequest", "getPendingSessionSetup ", downlink_data);
        phwangFree(pending_session_info);
    }

    char *pending_session_info3 = link_val->getPendingSessionSetup3();
    if (pending_session_info3) {
        *current_ptr++ = FE_CommandClass::RESPOND_IS_GET_LINK_DATA_PENDING_SESSION3;
        strcpy(current_ptr, pending_session_info3);
        phwangDebugSS(true, "DFabricClass::processGetLinkDataRequest", "getPendingSessionSetup3 ", downlink_data);
        phwangFree(pending_session_info3);
    }

    return downlink_data;
}

char *DFabricClass::generateGetLinkDataResponse (
    char const *result_val,
    char const *link_id_index_val,
    char const *data_val)
{
    phwangDebugS(false, "DFabricClass::generateGetLinkDataResponse", result_val);

    char *response_data = (char *) phwangMalloc(FE_CommandClass::FE_RESPONSE_BUF_WITH_LINK_SESSION_SIZE + strlen(data_val), MallocClass::generateGetLinkDataResponse);
    char *current_ptr = &response_data[FE_CommandClass::FE_RESPONSE_HEADER_SIZE];
    memcpy(current_ptr, result_val, FE_CommandClass::FE_RESULT_SIZE);
    current_ptr += FE_CommandClass::FE_RESULT_SIZE;
    memcpy(current_ptr, link_id_index_val, FE_CommandClass::LINK_ID_INDEX_SIZE);
    current_ptr += FE_CommandClass::LINK_ID_INDEX_SIZE;
    strcpy(current_ptr, data_val);
    return response_data;
}

char *DFabricClass::processGetNameListRequest (
    LinkClass *link_val,
    char *data_val)
{
    char *response_data;
    phwangDebugS(true, "DFabricClass::processGetNameListRequest", data_val);

    char *name_list_tag_val = data_val;
    char *end_val = name_list_tag_val + 3;

    int name_list_tag = phwangDecodeNumber(name_list_tag_val, FE_CommandClass::NAME_LIST_TAG_SIZE);
    char *name_list = this->theFabricObject->nameListObject()->getNameList(name_list_tag);

    if (!name_list) {
        /////////////////////////////////TBD
    }

    response_data = generateGetNameListResponse(FE_CommandClass::FE_RESULT_SUCCEED, link_val->linkIdIndex(), name_list);
    return response_data;
}

char *DFabricClass::generateGetNameListResponse (
    char const *result_val,
    char const *link_id_index_val,
    char const *data_val)
{
    phwangDebugS(false, "DFabricClass::generateGetNameListResponse", result_val);

    char *response_data = (char *) phwangMalloc(FE_CommandClass::FE_RESPONSE_BUF_WITH_LINK_SESSION_SIZE + strlen(data_val), MallocClass::generateGetNameListResponse);
    char *current_ptr = &response_data[FE_CommandClass::FE_RESPONSE_HEADER_SIZE];
    memcpy(current_ptr, result_val, FE_CommandClass::FE_RESULT_SIZE);
    current_ptr += FE_CommandClass::FE_RESULT_SIZE;
    memcpy(current_ptr, link_id_index_val, FE_CommandClass::LINK_ID_INDEX_SIZE);
    current_ptr += FE_CommandClass::LINK_ID_INDEX_SIZE;
    strcpy(current_ptr, data_val);
    return response_data;
}

char *DFabricClass::processSetupSessionRequest (
    void *tp_transfer_object_val,
    char *data_val,
    char const *ajax_id_val,
    LinkClass *link_val)
{
    char *response_data = 0;
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
        this->sendSetupSessionResponce(tp_transfer_object_val, ajax_id_val, link_val->linkIdIndex(), FE_CommandClass::FAKE_SESSION_ID_INDEX, "malloc_session_fail");
        return response_data;/////////////////////////////////
    }

    GroupClass *group = this->theFabricObject->mallocGroup(theme_info_val);
    if (!group) {
        this->sendSetupSessionResponce(tp_transfer_object_val, ajax_id_val, link_val->linkIdIndex(), session->sessionIdIndex(), "malloc_group_fail");
        return response_data;////////////////////////////////////
    }
    group->insertSession(session);
    session->bindGroup(group);

    if (!strcmp(his_name_val, session->linkObject()->linkName())) {
        this->sendSetupRoomRequestToThemeServer(group, theme_info_val);
    }
    else {
        LinkClass *his_link = this->theFabricObject->searchLinkByName(his_name_val);
        if (!his_link) {
            this->sendSetupSessionResponce(tp_transfer_object_val, ajax_id_val, link_val->linkIdIndex(), session->sessionIdIndex(), "his_link_does_not_exist");
            return response_data;//////////////////////////////
        }

        SessionClass *his_session = his_link->mallocSession();
        if (!his_session) {
            this->sendSetupSessionResponce(tp_transfer_object_val, ajax_id_val, link_val->linkIdIndex(), session->sessionIdIndex(), "null_his_session");
            return response_data;////////////////////////
        }

        group->insertSession(his_session);
        his_session->bindGroup(group);

        char *theme_data_buf = (char *) phwangMalloc(theme_len + 1, MallocClass::processSetupSessionRequest);
        memcpy(theme_data_buf, theme_info_val, theme_len);
        theme_data_buf[theme_len] = 0;
        his_link->setPendingSessionSetup(his_session->sessionIdIndex(), theme_data_buf);
        phwangFree(theme_data_buf);
    }

    //this->sendSetupSessionResponce(tp_transfer_object_val, ajax_id_val, link_val->linkIdIndex(), session->sessionIdIndex(), FE_CommandClass::FE_RESULT_SUCCEED);
    response_data = this->generatePutSessionDataResponse(FE_CommandClass::FE_RESULT_SUCCEED, link_val->linkIdIndex(), session->sessionIdIndex());
    return response_data;
}

char *DFabricClass::generateSetupSessionResponse (
    char const *result_val,
    char const *link_id_index_val,
    char const *session_id_index_val)
{
    phwangDebugS(false, "DFabricClass::generateSetupSessionResponse", result_val);

    char *response_data = (char *) phwangMalloc(FE_CommandClass::FE_RESPONSE_BUF_WITH_LINK_SESSION_SIZE, MallocClass::generateSetupSessionResponse);
    char *current_ptr = &response_data[FE_CommandClass::FE_RESPONSE_HEADER_SIZE];
    memcpy(current_ptr, result_val, FE_CommandClass::FE_RESULT_SIZE);
    current_ptr += FE_CommandClass::FE_RESULT_SIZE;
    memcpy(current_ptr, link_id_index_val, FE_CommandClass::LINK_ID_INDEX_SIZE);
    current_ptr += FE_CommandClass::LINK_ID_INDEX_SIZE;
    strcpy(current_ptr, session_id_index_val);
    return response_data;
}

void DFabricClass::sendSetupSessionResponce (
    void *tp_transfer_object_val,
    char const *ajax_id_val,
    char const *link_id_index_val,
    char const *session_id_index_val,
    char const *result_val)
{
    phwangDebugS(false, "DFabricClass::sendSetupSessionResponce", result_val);

    char *current_ptr;
    char *downlink_data = current_ptr = (char *) phwangMalloc(FE_CommandClass::FE_DL_DATA_BUF_SIZE, MallocClass::sendSetupSessionResponce);
    *current_ptr++ = FE_CommandClass::SETUP_SESSION_RESPONSE;
    strcpy(current_ptr, ajax_id_val);
    current_ptr += FE_CommandClass::AJAX_ID_SIZE;
    strcpy(current_ptr, session_id_index_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::sendSetupRoomRequestToThemeServer (GroupClass *group_val, char *theme_info_val)
{
    char *data_ptr;
    char *uplink_data = data_ptr = (char *) phwangMalloc(FT_CommandClass::FT_UL_DATA_BUF_SIZE, MallocClass::sendSetupRoomRequestToThemeServer);
    *data_ptr++ = FT_CommandClass::SETUP_ROOM_COMMAND;
    memcpy(data_ptr, group_val->groupIdIndex(), FT_CommandClass::GROUP_ID_INDEX_SIZE);
    data_ptr += FT_CommandClass::GROUP_ID_INDEX_SIZE;
    strcpy(data_ptr, theme_info_val);
    this->theFabricObject->uFabricObject()->transmitFunction(uplink_data);
}

void DFabricClass::processSetupSession2Request (
    void *tp_transfer_object_val,
    char *data_val,
    char const *ajax_id_val,
    LinkClass *link_val)
{
    phwangDebugS(true, "DFabricClass::processSetupSession2Request", data_val);

    char *link_id_index_val = data_val;
    char *session_id_index_val = link_id_index_val + FE_CommandClass::LINK_ID_INDEX_SIZE;
    char *theme_info_val = session_id_index_val + FE_CommandClass::SESSION_ID_INDEX_SIZE;

    SessionClass *session = link_val->searchSession(session_id_index_val);
    if (!session) {
        this->errorProcessSetupSession2(tp_transfer_object_val, ajax_id_val, "session does not exist");
        return;
    }

    GroupClass *group = session->groupObject();
    this->sendSetupRoomRequestToThemeServer(group, theme_info_val);
    this->sendSetupSession2Responce(tp_transfer_object_val, ajax_id_val, link_val->linkIdIndex(), session->sessionIdIndex(), FE_CommandClass::FE_RESULT_SUCCEED);
}

void DFabricClass::sendSetupSession2Responce (
    void *tp_transfer_object_val,
    char const *ajax_id_val,
    char const *link_id_index_val,
    char const *session_id_index_val,
    char const *result_val)
{
    phwangDebugS(false, "DFabricClass::sendSetupSession2Responce", result_val);

    char *current_ptr;
    char *downlink_data = current_ptr = (char *) phwangMalloc(FE_CommandClass::FE_DL_DATA_BUF_SIZE, MallocClass::SETUP_SESSION2);
    *current_ptr++ = FE_CommandClass::SETUP_SESSION2_RESPONSE;
    strcpy(current_ptr, ajax_id_val);
    current_ptr += FE_CommandClass::AJAX_ID_SIZE;
    memcpy(current_ptr, link_id_index_val, FE_CommandClass::LINK_ID_INDEX_SIZE);
    current_ptr += FE_CommandClass::LINK_ID_INDEX_SIZE;
    strcpy(current_ptr, session_id_index_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

void DFabricClass::errorProcessSetupSession2 (void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val)
{
    phwangAbendS("DFabricClass::errorProcessSetupSession2", err_msg_val);

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FE_CommandClass::FE_DL_DATA_BUF_SIZE, MallocClass::SETUP_SESSION2_ERROR);
    *data_ptr++ = FE_CommandClass::SETUP_SESSION2_RESPONSE;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += FE_CommandClass::AJAX_ID_SIZE;
    strcpy(data_ptr, err_msg_val);
    this->transmitFunction(tp_transfer_object_val, downlink_data);
}

char *DFabricClass::processSetupSession3Request (
    LinkClass *link_val,
    char *data_val)
{
    char *response_data;
    phwangDebugSS(true, "DFabricClass::processSetupSession3Reques", "data_val=", data_val);

    char session_id_buf[FE_CommandClass::SESSION_ID_INDEX_SIZE + 1];
    memcpy(session_id_buf, data_val, FE_CommandClass::SESSION_ID_INDEX_SIZE);
    session_id_buf[FE_CommandClass::SESSION_ID_INDEX_SIZE] = 0;
    phwangDebugSS(true, "DFabricClass::processSetupSession3Reques", "session_id=", session_id_buf);

    response_data = this->generateSetupSession3Response(FE_CommandClass::FE_RESULT_SUCCEED, link_val->linkIdIndex(), session_id_buf);
    return response_data;
}

char *DFabricClass::generateSetupSession3Response (
    char const *result_val,
    char const *link_id_index_val,
    char const *session_id_index_val)
{
    phwangDebugS(false, "DFabricClass::generateSetupSession3Response", result_val);

    char *response_data = (char *) phwangMalloc(FE_CommandClass::FE_RESPONSE_BUF_WITH_LINK_SESSION_SIZE, MallocClass::generateSetupSession3Response);
    char *current_ptr = &response_data[FE_CommandClass::FE_RESPONSE_HEADER_SIZE];
    memcpy(current_ptr, result_val, FE_CommandClass::FE_RESULT_SIZE);
    current_ptr += FE_CommandClass::FE_RESULT_SIZE;
    memcpy(current_ptr, link_id_index_val, FE_CommandClass::LINK_ID_INDEX_SIZE);
    current_ptr += FE_CommandClass::LINK_ID_INDEX_SIZE;
    strcpy(current_ptr, session_id_index_val);
    return response_data;
}

/* free session */

char *DFabricClass::processFreeSessionRequest (
    LinkClass *link_val,
    SessionClass *session_val)
{
    char *response_data;
    phwangDebugSSS(true, "DFabricClass::processFreeSessionRequest", "id=", link_val->linkIdIndex(), session_val->sessionIdIndex());

    char session_id_buf[FE_CommandClass::SESSION_ID_INDEX_SIZE + 1];
    strcpy(session_id_buf, session_val->sessionIdIndex());
    link_val->freeSession(session_val);

    response_data = this->generateFreeSessionResponse(FE_CommandClass::FE_RESULT_SUCCEED, link_val->linkIdIndex(), session_id_buf);
    return response_data;
}

char *DFabricClass::generateFreeSessionResponse (
    char const *result_val,
    char const *link_id_index_val,
    char const *session_id_index_val)
{
    phwangDebugS(false, "DFabricClass::generateFreeSessionResponse", result_val);

    char *response_data = (char *) phwangMalloc(FE_CommandClass::FE_RESPONSE_BUF_WITH_LINK_SESSION_SIZE, MallocClass::generateFreeSessionResponse);
    char *current_ptr = &response_data[FE_CommandClass::FE_RESPONSE_HEADER_SIZE];
    memcpy(current_ptr, result_val, FE_CommandClass::FE_RESULT_SIZE);
    current_ptr += FE_CommandClass::FE_RESULT_SIZE;
    memcpy(current_ptr, link_id_index_val, FE_CommandClass::LINK_ID_INDEX_SIZE);
    current_ptr += FE_CommandClass::LINK_ID_INDEX_SIZE;
    strcpy(current_ptr, session_id_index_val);
    return response_data;
}

/* put session data */

char *DFabricClass::processPutSessionDataRequest (
    SessionClass *session_val,
    char *data_val)
{
    char *response_data;
    phwangDebugS(true, "DFabricClass::processPutSessionDataRequest", data_val);

    char *room_id = session_val->groupObject()->roomIdIndex();
    if (!room_id) {
        response_data = this->generatePutSessionDataResponse(FE_CommandClass::FE_RESULT_NULL_ROOM, session_val->linkObject()->linkIdIndex(), session_val->sessionIdIndex());
        return response_data;
    }

    this->sendPutSessionDataRequestToThemeServer(room_id, data_val);
    response_data = this->generatePutSessionDataResponse(FE_CommandClass::FE_RESULT_SUCCEED, session_val->linkObject()->linkIdIndex(), session_val->sessionIdIndex());
    return response_data;
}

char *DFabricClass::generatePutSessionDataResponse (
    char const *result_val,
    char const *link_id_index_val,
    char const *session_id_index_val)
{
    phwangDebugS(false, "DFabricClass::generatePutSessionDataResponse", result_val);

    char *response_data = (char *) phwangMalloc(FE_CommandClass::FE_RESPONSE_BUF_WITH_LINK_SESSION_SIZE, MallocClass::generatePutSessionDataResponse);
    char *current_ptr = &response_data[FE_CommandClass::FE_RESPONSE_HEADER_SIZE];
    memcpy(current_ptr, result_val, FE_CommandClass::FE_RESULT_SIZE);
    current_ptr += FE_CommandClass::FE_RESULT_SIZE;
    memcpy(current_ptr, link_id_index_val, FE_CommandClass::LINK_ID_INDEX_SIZE);
    current_ptr += FE_CommandClass::LINK_ID_INDEX_SIZE;
    memcpy(current_ptr, session_id_index_val, FE_CommandClass::SESSION_ID_INDEX_SIZE);
    current_ptr += FE_CommandClass::SESSION_ID_INDEX_SIZE;
    *current_ptr = 0;
    return response_data;
}

void DFabricClass::sendPutSessionDataRequestToThemeServer (
    char const *room_id_val,
    char const *data_val)
{
    if (strlen(data_val) > FT_CommandClass::FT_UL_DATA_BUF_SIZE) {
        phwangAbendSI("DFabricClass::sendPutSessionDataRequestToThemeServer", "buf_size", strlen(data_val));
        return;
    }

    char *data_ptr;
    char *uplink_data = data_ptr = (char *) phwangMalloc(FT_CommandClass::FT_UL_DATA_BUF_SIZE, MallocClass::PUT_SESSION_DATA0);
    *data_ptr++ = FT_CommandClass::PUT_ROOM_DATA_COMMAND;
    memcpy(data_ptr, room_id_val, FT_CommandClass::ROOM_ID_INDEX_SIZE);
    data_ptr += FT_CommandClass::ROOM_ID_INDEX_SIZE;
    strcpy(data_ptr, data_val);
    this->theFabricObject->uFabricObject()->transmitFunction(uplink_data);
}

/* get session data */

char *DFabricClass::processGetSessionDataRequest (
    SessionClass *session_val,
    char *data_val)
{
    phwangDebugS(true, "DFabricClass::processGetSessionDataRequest", data_val);

    char *data = session_val->getPendingDownLinkData();

    if (strlen(data) > FE_CommandClass::FE_DL_DATA_BUF_SIZE) {
        phwangAbendSI("DFabricClass::processGetSessionDataRequest", "buf_size", strlen(data));
    }

    char *response_data = this->generateGetSessionDataResponse(FE_CommandClass::FE_RESULT_SUCCEED, session_val->linkObject()->linkIdIndex(), session_val->sessionIdIndex(), data);
    return response_data;
}

char *DFabricClass::generateGetSessionDataResponse (
    char const *result_val,
    char const *link_id_index_val,
    char const *session_id_index_val,
    char const *data_val)
{
    phwangDebugS(false, "DFabricClass::generateGetSessionDataResponse", result_val);

    char *response_data = (char *) phwangMalloc(FE_CommandClass::FE_RESPONSE_BUF_WITH_LINK_SESSION_SIZE + strlen(data_val), MallocClass::generateGetSessionDataResponse);
    char *current_ptr = &response_data[FE_CommandClass::FE_RESPONSE_HEADER_SIZE];
    memcpy(current_ptr, result_val, FE_CommandClass::FE_RESULT_SIZE);
    current_ptr += FE_CommandClass::FE_RESULT_SIZE;
    memcpy(current_ptr, link_id_index_val, FE_CommandClass::LINK_ID_INDEX_SIZE);
    current_ptr += FE_CommandClass::LINK_ID_INDEX_SIZE;
    memcpy(current_ptr, session_id_index_val, FE_CommandClass::SESSION_ID_INDEX_SIZE);
    current_ptr += FE_CommandClass::SESSION_ID_INDEX_SIZE;
    strcpy(current_ptr, data_val);
    return response_data;
}
