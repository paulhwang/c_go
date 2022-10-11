/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../define_dir/result_def.h"
#include "../../define_dir/fe_def.h"
#include "../../define_dir/ft_def.h"
#include "../../define_dir/fabric_def.h"
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

DbAccountClass *DFabricClass::dbAccountObject(void) {
    return fabricObject_->dbObject()->dbAccountObject();
}

void DFabricClass::exportedParseFunction (
    void *port_object_val,
    char *data_val)
{
    char device_type = data_val[0];
    char depth = data_val[1];
    char command = data_val[2];
    char *current_ptr = &data_val[3];

    char ajax_id[SIZE_DEF::AJAX_ID_SIZE + 1];
    memcpy(ajax_id, current_ptr, SIZE_DEF::AJAX_ID_SIZE);
    ajax_id[SIZE_DEF::AJAX_ID_SIZE] = 0;
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    if (command != FE_DEF::FE_GET_LINK_DATA_COMMAND) {
        phwangDebugS(true, "DFabricClass::exportedParseFunction", data_val);
    }

    LinkClass *link;
    SessionClass *session;
    char *response_data;
    switch (depth) {
        case '0':
            switch (command) {
                case FE_DEF::FE_REGISTER_COMMAND:
                    response_data = this->processRegisterRequest(ajax_id, current_ptr);
                    break;

                case FE_DEF::FE_LOGIN_COMMAND:
                    response_data = this->processLoginRequest(ajax_id, current_ptr, device_type, port_object_val);
                    break;

                case FE_DEF::FE_MESSAGE_COMMAND:
                    response_data = this->processDatagramRequest(ajax_id, current_ptr);
                    response_data[0] = FE_DEF::FE_MESSAGE_RESPONSE;
                    break;

                default:
                    phwangAbendS("DFabricClass::exportedParseFunction_0", current_ptr);
                    return;
            }
            break;

        case '1':
            link = this->fabricObject_->searchLink(current_ptr, data_val);
            if (!link) {
                this->sendSearchLinkFailResponse(command, port_object_val, ajax_id);
                return;
            }
            current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;

            switch (command) {
                case FE_DEF::FE_LOGOUT_COMMAND:
                    response_data = this->processLogoutRequest(link, ajax_id, current_ptr);
                    break;

                case FE_DEF::FE_GET_LINK_DATA_COMMAND:
                    response_data = this->processGetLinkDataRequest(link, ajax_id);
                    break;

                case FE_DEF::FE_GET_NAME_LIST_COMMAND:
                    response_data = this->processGetNameListRequest(link, ajax_id, current_ptr);
                    break;

                case FE_DEF::FE_SETUP_SESSION_COMMAND:
                    response_data = this->processSetupSessionRequest(link, ajax_id, current_ptr);
                    break;

                default:
                    phwangAbendS("DFabricClass::exportedParseFunction_1", data_val);
                    return;
            }
            break;

        case '2':
            session = this->fabricObject_->serachLinkAndSession(current_ptr);
            if (!session) {
                this->sendSearchLinkSessionFailResponse(command, port_object_val, ajax_id);
                return;
            }
            current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE + SIZE_DEF::SESSION_ID_INDEX_SIZE;

            switch (command) {
                case FE_DEF::FE_SETUP_SESSION2_COMMAND:
                    response_data = this->processSetupSession2Request(session, ajax_id, current_ptr);
                    break;

                case FE_DEF::FE_SETUP_SESSION3_COMMAND:
                    response_data = this->processSetupSession3Request(session, ajax_id, current_ptr);
                    break;

                case FE_DEF::FE_FREE_SESSION_COMMAND:
                    response_data = this->processFreeSessionRequest(session, ajax_id);
                    break;

                case FE_DEF::FE_PUT_SESSION_DATA_COMMAND:
                    response_data = this->processPutSessionDataRequest(session, ajax_id, current_ptr);
                    break;

                case FE_DEF::FE_GET_SESSION_DATA_COMMAND:
                    response_data = this->processGetSessionDataRequest(session, ajax_id, current_ptr);
                    break;

                default:
                    phwangAbendS("DFabricClass::exportedParseFunction_2", data_val);
                    return;
            }
            break;

        default:
            phwangAbendS("DFabricClass::exportedParseFunction", "bad type");
            return;
    }

    this->transmitFunction(port_object_val, response_data);
}

void DFabricClass::sendSearchLinkFailResponse (
    char const command_val,
    void *port_object_val,
    char const *ajax_id_val)
{
    phwangAbendS("DFabricClass::sendSearchLinkFailResponse", "");

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE, MallocClass::BAD_LINK);
    *data_ptr++ = command_val;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += SIZE_DEF::AJAX_ID_SIZE;
    strcpy(data_ptr, RESULT_DEF::RESULT_LINK_NOT_EXIST);
    this->transmitFunction(port_object_val, downlink_data);
}

void DFabricClass::sendSearchLinkSessionFailResponse (
    char const command_val,
    void *port_object_val,
    char const *ajax_id_val)
{
    phwangAbendS("DFabricClass::sendSearchLinkSessionFailResponse", "");

    char *data_ptr;
    char *downlink_data = data_ptr = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE, MallocClass::BAD_SESSION);
    *data_ptr++ = command_val;
    strcpy(data_ptr, ajax_id_val);
    data_ptr += SIZE_DEF::AJAX_ID_SIZE;
    strcpy(data_ptr, RESULT_DEF::RESULT_SESSION_NOT_EXIST);
    this->transmitFunction(port_object_val, downlink_data);
}

char *DFabricClass::processDatagramRequest (
    char *ajax_id_val,
    char *input_data_val)
{
    char *response_data;
    phwangDebugS(true, "DFabricClass::processMessageRequest", input_data_val);

    char act = *input_data_val++;

    char *encoded_data = input_data_val;
    int data_size;
    char *data = phwangDecodeStringMalloc(encoded_data, &data_size);
    char const *output_data;

    if (1) { /* debug */
        char buf[256];
        sprintf(buf, "act=%c data=%s\n", act, data);
        phwangDebugS(true, "DFabricClass::processMessageRequest", buf);
    }


    switch (act) {
        case 'I':
            this->messengerObject()->initMessenger();
            output_data = "I_data";
            break;

        case 'R':
            output_data = this->messengerObject()->getMessage();
            phwangDebugS(true, "DFabricClass::processMessageRequest", output_data);
            break;

        case 'W':
            output_data = "W_data";
            this->messengerObject()->putMessage(0);
            break;

        default:
            break;
    }
    response_data = generateDatagramResponse(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, output_data);
    return response_data;
}

char *DFabricClass::generateDatagramResponse (
    char const *result_val,
    char *ajax_id_val,
    char const *data_val)
{
    phwangDebugSS(false, "DFabricClass::generateDatagramResponse", "data_val=", data_val);

    char *encoded_data = phwangEncodeStringMalloc(data_val);
    int encoded_data_length = strlen(encoded_data);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SIZE + strlen(encoded_data), MallocClass::generateDatagramResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::FE_MESSAGE_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    strcpy(current_ptr, encoded_data);
    //current_ptr += encoded_data_length;

    phwangFree(encoded_data);

    return response_data;
}

char *DFabricClass::processRegisterRequest (
    char *ajax_id_val,
    char *data_val)
{
    char *response_data;
    phwangDebugS(false, "DFabricClass::processRegisterRequest", data_val);

    char *encoded_account_name = data_val;
    int account_name_size;
    char *account_name = phwangDecodeStringMalloc(encoded_account_name, &account_name_size);

    phwangDebugS(true, "DFabricClass::processRegisterRequest", account_name);

    char result_buf[RESULT_DEF::RESULT_SIZE + 1];
    this->dbAccountObject()->checkAccountNameExist(account_name, result_buf);

    if (!strcmp(result_buf, RESULT_DEF::RESULT_ACCOUNT_NAME_NOT_EXIST)) {
        char *encoded_password = encoded_account_name + account_name_size;
        int password_size;
        char *password = phwangDecodeStringMalloc(encoded_password, &password_size);

        char *encoded_email = encoded_password + password_size;
        int email_size;
        char *email = phwangDecodeStringMalloc(encoded_email, &email_size);

        DbAccountEntryClass *account_entry = new DbAccountEntryClass();
        account_entry->setAccountName(account_name);
        account_entry->setPassword(password);
        account_entry->setEmail(email);

        response_data = generateRegisterResponse(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, account_name);

        this->dbAccountObject()->insertAccountEntry(account_entry);
        /***
        ---the buffers has been freed in the insertAccountEntry()---
        free(account_name);
        free(password);
        free(email);
        ***/

        return response_data;
        }

    else if (!strcmp(result_buf, RESULT_DEF::RESULT_ACCOUNT_NAME_ALREADY_EXIST)) {
        response_data = generateRegisterResponse(result_buf, ajax_id_val, account_name);
        phwangFree(account_name);
        return response_data;
    }

    else if (!strcmp(result_buf, RESULT_DEF::RESULT_DB_SELECT_FAIL)) {
        response_data = generateRegisterResponse(result_buf, ajax_id_val, account_name);
        phwangFree(account_name);
        return response_data;
   }

    else {
        phwangAbendSS("DFabricClass::processRegisterRequest", "unsupported_result", result_buf);
        response_data = generateRegisterResponse(RESULT_DEF::RESULT_DB_ERROR, ajax_id_val, account_name);
        phwangFree(account_name);
        return response_data;
    }
}

char *DFabricClass::generateRegisterResponse (
    char const *result_val,
    char *ajax_id_val,
    char const *account_name_val)
{
    phwangDebugS(false, "DFabricClass::generateRegisterResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUFFER_SIZE + strlen(account_name_val), MallocClass::generateRegisterResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::FE_REGISTER_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE );
    current_ptr += RESULT_DEF::RESULT_SIZE;

    strcpy(current_ptr, account_name_val);
    return response_data;
}

char *DFabricClass::processLoginRequest (
    char *ajax_id_val,
    char *data_val,
    char device_type_val,
    void *port_object_val)
{
    char *response_data;
    phwangDebugS(false, "DFabricClass::processLoginRequest", data_val);

    char *encoded_my_name = data_val;
    int my_name_size;
    char *my_name = phwangDecodeStringMalloc(encoded_my_name, &my_name_size);

    char encoded_my_name_buf[128];
    memcpy(encoded_my_name_buf, encoded_my_name, my_name_size);
    encoded_my_name_buf[my_name_size] = 0;
    phwangDebugSS(false, "DFabricClass::processLoginRequest", "my_name=", encoded_my_name_buf);

    char *encoded_password = encoded_my_name + my_name_size;
    int password_size;
    char *password = phwangDecodeStringMalloc(encoded_password, &password_size);

    phwangDebugSS(false, "DFabricClass::processLoginRequest", my_name, password);

    char result_buf[RESULT_DEF::RESULT_SIZE + 1];
    this->dbObject()->dbAccountObject()->checkPassword(my_name, password, result_buf);
    phwangFree(password);

    if (!strcmp(result_buf, RESULT_DEF::RESULT_PASSWORD_MATCH)) {
        LinkClass *link = this->fabricObject_->mallocLink(my_name, device_type_val, port_object_val);
        if (!link) {
            phwangAbendS("DFabricClass::processLoginRequest", "null_link");
            phwangFree(my_name);
            response_data = generateLoginResponse(RESULT_DEF::RESULT_NULL_LINK, ajax_id_val, SIZE_DEF::FAKE_LINK_ID_INDEX, encoded_my_name_buf);
            return response_data;
        }

        phwangFree(my_name);
        response_data = generateLoginResponse(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, link->linkIdIndex(), encoded_my_name_buf);
        return response_data;
    }

    else if ((!strcmp(result_buf, RESULT_DEF::RESULT_PASSWORD_NOT_MATCH)) ||
             (!strcmp(result_buf, RESULT_DEF::RESULT_ACCOUNT_NAME_NOT_EXIST)) ||
             (!strcmp(result_buf, RESULT_DEF::RESULT_DB_SELECT_FAIL))) {
        phwangFree(my_name);
        response_data = generateLoginResponse(result_buf, ajax_id_val, SIZE_DEF::FAKE_LINK_ID_INDEX, encoded_my_name_buf);
        return response_data;
    }

    else {
        phwangAbendSS("DFabricClass::processLoginRequest", "unsupported_result", result_buf);
        phwangFree(my_name);
        response_data = generateLoginResponse(RESULT_DEF::RESULT_DB_ERROR, ajax_id_val, SIZE_DEF::FAKE_LINK_ID_INDEX, encoded_my_name_buf);
        return response_data;
    }

/*
    if (result != DbAccountClass::DB_ACCOUNT_PASSWORD_MATCH) {
        char const*result_str;
        switch (result) {
            case DbAccountClass::DB_ACCOUNT_PASSWORD_NOT_MATCH:
                result_str = RESULT_DEF::RESULT_PASSWORD_NOT_MATCH;
                break;
            case DbAccountClass::DB_ACCOUNT_NAME_NOT_EXIST:
                result_str = RESULT_DEF::RESULT_ACCOUNT_NAME_NOT_EXIST;
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
        response_data = generateSignInResponse(result_str, SIZE_DEF::FAKE_LINK_ID_INDEX, encoded_my_name_buf);
        return response_data;
    }

    LinkClass *link = this->theFabricObject->mallocLink(my_name);
    if (!link) {
        phwangAbendS("DFabricClass::processSignInRequest", "null link");
        phwangFree(my_name);
        phwangFree(password);
        response_data = generateSignInResponse(RESULT_DEF::RESULT_NULL_LINK, SIZE_DEF::FAKE_LINK_ID_INDEX, encoded_my_name_buf);
        return response_data;
    }

    phwangFree(my_name);
    phwangFree(password);
    response_data = generateSignInResponse(RESULT_DEF::RESULT_SUCCEED, link->linkIdIndex(), encoded_my_name_buf);
    return response_data;
    */
}

char *DFabricClass::generateLoginResponse (
    char const *result_val,
    char *ajax_id_val,
    char const *link_id_index_val,
    char const *account_name_val)
{
    phwangDebugS(false, "DFabricClass::generateLoginResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SIZE + strlen(account_name_val), MallocClass::generateLoginResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::FE_LOGIN_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;

    strcpy(current_ptr, account_name_val);
    return response_data;
}

char *DFabricClass::processLogoutRequest (
    LinkClass *link_val,
    char *ajax_id_val,
    char *data_val)
{
    char *response_data;
    phwangDebugSS(false, "DFabricClass::processLogoutRequest", "link_id=", link_val->linkIdIndex());

    this->fabricObject_->freeLink(link_val);

    response_data = generateLogoutResponse(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, link_val->linkIdIndex(), data_val);
    return response_data;
}

char *DFabricClass::generateLogoutResponse (
    char const *result_val,
    char *ajax_id_val,
    char const *link_id_index_val,
    char const *data_val)
{
    phwangDebugS(false, "DFabricClass::generateLogoutResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SIZE + strlen(data_val), MallocClass::generateLogoutResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::FE_LOGOUT_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;

    strcpy(current_ptr, data_val);
    return response_data;
}

char *DFabricClass::processGetLinkDataRequest (
    LinkClass *link_val,
    char *ajax_id_val)
{
    link_val->resetKeepAliveTime();

    char *pending_session_info2 = link_val->getPendingSessionSetup2();
    int pending_session_info2_length = 0;
    if (pending_session_info2) {
        pending_session_info2_length = strlen(pending_session_info2);
    }

    char *pending_session_info3 = link_val->getPendingSessionSetup3();
    int pending_session_info3_length = 0;
    if (pending_session_info3) {
        pending_session_info3_length = strlen(pending_session_info3);
    }

    int response_data_size = FABRIC_DEF::FE_DL_COMMAND_AJAX_SIZE + 
                             RESULT_DEF::RESULT_SIZE +
                             SIZE_DEF::LINK_ID_INDEX_SIZE + 
                             1 + SIZE_DEF::NAME_LIST_TAG_SIZE +
                             1 + FE_DEF::FE_GET_LINK_DATA_LENGTH_SIZE + pending_session_info2_length +
                             1 + FE_DEF::FE_GET_LINK_DATA_LENGTH_SIZE + pending_session_info3_length +
                             1 + SIZE_DEF::SESSION_ID_INDEX_SIZE + 1;

    char *response_data = (char *) phwangMalloc(response_data_size, MallocClass::GET_LINK_DATA);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::FE_GET_LINK_DATA_RESPONSE;

    memcpy(current_ptr, RESULT_DEF::RESULT_SUCCEED, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_val->linkIdIndex(), SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;

    *current_ptr++ = FE_DEF::FE_GET_LINK_DATA_TYPE_NAME_LIST;
    phwangEncodeNumber(current_ptr, this->fabricObject_->nameListObject()->nameListTag(), SIZE_DEF::NAME_LIST_TAG_SIZE);
    current_ptr += SIZE_DEF::NAME_LIST_TAG_SIZE;
    *current_ptr = 0;

    int max_session_table_array_index = phwnagListMgrGetMaxIndex(link_val->sessionListMgrObject(), "DFabricClass::processGetLinkData()");
    SessionClass **session_table_array = (SessionClass **) phwangListMgrGetEntryTableArray(link_val->sessionListMgrObject());
    for (int i = 0; i <= max_session_table_array_index; i++) {
        SessionClass *session = session_table_array[i];
        if (session) {
            char *pending_downlink_data = session->dequeuePendingData();
            if (pending_downlink_data) {
                *current_ptr++ = FE_DEF::FE_GET_LINK_DATA_TYPE_PENDING_DATA;
                session->enqueuePendingData(pending_downlink_data);

                strcpy(current_ptr, session->sessionIdIndex());
                current_ptr += SIZE_DEF::SESSION_ID_INDEX_SIZE;

                phwangDebugSS(true, "DFabricClass::processGetLinkDataRequest","Pending_data=", response_data);
            }
        }
    }

    if (pending_session_info2) {
        *current_ptr++ = FE_DEF::FE_GET_LINK_DATA_TYPE_PENDING_SESSION2;

        char length2_buf[FE_DEF::FE_GET_LINK_DATA_LENGTH_SIZE + 1];
        phwangEncodeNumber(length2_buf, pending_session_info2_length, FE_DEF::FE_GET_LINK_DATA_LENGTH_SIZE);

        memcpy(current_ptr, length2_buf, FE_DEF::FE_GET_LINK_DATA_LENGTH_SIZE);
        current_ptr += FE_DEF::FE_GET_LINK_DATA_LENGTH_SIZE;

        memcpy(current_ptr, pending_session_info2, pending_session_info2_length);
        current_ptr += pending_session_info2_length;
        *current_ptr = 0;

        phwangDebugSS(true, "DFabricClass::processGetLinkDataRequest", "pending_session3=", response_data);

        phwangFree(pending_session_info2);
    }

    if (pending_session_info3) {
        *current_ptr++ = FE_DEF::FE_GET_LINK_DATA_TYPE_PENDING_SESSION3;

        char length3_buf[FE_DEF::FE_GET_LINK_DATA_LENGTH_SIZE + 1];
        phwangEncodeNumber(length3_buf, pending_session_info3_length, FE_DEF::FE_GET_LINK_DATA_LENGTH_SIZE);

        memcpy(current_ptr, length3_buf, FE_DEF::FE_GET_LINK_DATA_LENGTH_SIZE);
        current_ptr += FE_DEF::FE_GET_LINK_DATA_LENGTH_SIZE;

        memcpy(current_ptr, pending_session_info3, pending_session_info3_length);
        current_ptr += pending_session_info3_length;
        *current_ptr = 0;

        phwangDebugSS(true, "DFabricClass::processGetLinkDataRequest", "pending_session3=", response_data);

        phwangFree(pending_session_info3);
    }

    return response_data;
}

char *DFabricClass::processGetNameListRequest (
    LinkClass *link_val,
    char *ajax_id_val,
    char *data_val)
{
    char *response_data;
    phwangDebugS(true, "DFabricClass::processGetNameListRequest", data_val);

    char *name_list_tag_val = data_val;
    char *end_val = name_list_tag_val + 3;

    int name_list_tag = phwangDecodeNumber(name_list_tag_val, SIZE_DEF::NAME_LIST_TAG_SIZE);
    char *name_list = this->fabricObject_->nameListObject()->getNameList(name_list_tag);

    if (!name_list) {
        phwangAbendS("DFabricClass::processGetNameListRequest", data_val);
    }

    response_data = generateGetNameListResponse(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, link_val->linkIdIndex(), name_list);
    return response_data;
}

char *DFabricClass::generateGetNameListResponse (
    char const *result_val,
    char *ajax_id_val,
    char const *link_id_index_val,
    char const *data_val)
{
    phwangDebugS(false, "DFabricClass::generateGetNameListResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE + strlen(data_val), MallocClass::generateGetNameListResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::FE_GET_NAME_LIST_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;

    strcpy(current_ptr, data_val);

    return response_data;
}

char *DFabricClass::processSetupSessionRequest (
    LinkClass *link_val,
    char *ajax_id_val,
    char *data_val)
{
    char *response_data = 0;
    phwangDebugSS(true, "DFabricClass::processSetupSessionRequest", "data_val=", data_val);

    SessionClass *session = link_val->mallocSession();
    if (!session) {
        response_data = this->generateSetupSessionResponse(RESULT_DEF::RESULT_MALLOC_SESSION_FAIL, ajax_id_val, link_val->linkIdIndex(), SIZE_DEF::FAKE_SESSION_ID_INDEX, data_val);
        return response_data;
    }

    char group_mode = *data_val;
    char theme_type = *(data_val + 1);

    char *encoded_theme_info = data_val + 2;
    int theme_info_size;
    char *theme_info = phwangDecodeStringMalloc(encoded_theme_info, &theme_info_size);
    phwangDebugSS(true, "DFabricClass::processSetupSessionRequest", "theme_info=", theme_info);

    char *encoded_first_fiddle = encoded_theme_info + theme_info_size;
    int first_fiddle_size;
    char *first_fiddle = phwangDecodeStringMalloc(encoded_first_fiddle, &first_fiddle_size);
    phwangDebugSS(true, "DFabricClass::processSetupSessionRequest", "first_fiddle=", first_fiddle);

    char *encoded_second_fiddle = encoded_first_fiddle + first_fiddle_size;
    int second_fiddle_size;
    char *second_fiddle = phwangDecodeStringMalloc(encoded_second_fiddle, &second_fiddle_size);
    phwangDebugSS(true, "DFabricClass::processSetupSessionRequest", "second_fiddle=", second_fiddle);

    switch (theme_type) {
        case FE_DEF::FE_APP_IS_GO_GAME:
            break;

        default:
            phwangAbendS("DFabricClass::processSetupSessionRequest", "theme_type not supported");
    }

    GroupClass *group = this->fabricObject_->mallocGroup(group_mode, theme_type, theme_info, first_fiddle, second_fiddle);
    phwangFree(theme_info);
    phwangFree(first_fiddle);
    phwangFree(second_fiddle);
    if (!group) {
        response_data = this->generateSetupSessionResponse(RESULT_DEF::RESULT_MALLOC_GROUP_FAIL, ajax_id_val, link_val->linkIdIndex(), session->sessionIdIndex(), data_val);
        return response_data;
    }
    group->insertSession(session);
    session->bindGroup(group);

    if (group->isDominatedGroup()) {
        this->sendSetupRoomRequestToThemeServer(group);

        response_data = this->generateSetupSessionResponse(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, link_val->linkIdIndex(), session->sessionIdIndex(), data_val);
        return response_data;
    }

    LinkClass *second_link = this->fabricObject_->searchLinkByName(group->secondFiddle());
    if (!second_link) {
        response_data = this->generateSetupSessionResponse(RESULT_DEF::RESULT_SECOND_LINK_NOT_EXIST, ajax_id_val, link_val->linkIdIndex(), SIZE_DEF::FAKE_SESSION_ID_INDEX, data_val);
        return response_data;
    }

    SessionClass *second_session = second_link->mallocSession();
    if (!second_session) {
        response_data = this->generateSetupSessionResponse(RESULT_DEF::RESULT_MALLOC_SECOND_SESSION_FAIL, ajax_id_val, link_val->linkIdIndex(), SIZE_DEF::FAKE_SESSION_ID_INDEX, data_val);
        return response_data;
    }

    group->insertSession(second_session);
    second_session->bindGroup(group);

    second_link->setPendingSessionSetup2(second_session->sessionIdIndex(), group->themeType(), group->themeInfo());

    response_data = this->generateSetupSessionResponse(RESULT_DEF::RESULT_WAITING_FOR_ANSWER, ajax_id_val, link_val->linkIdIndex(), session->sessionIdIndex(), data_val);
    return response_data;
}

char *DFabricClass::generateSetupSessionResponse (
    char const *result_val,
    char *ajax_id_val,
    char const *link_id_index_val,
    char const *session_id_index_val,
    char const *data_val)
{
    phwangDebugS(false, "DFabricClass::generateSetupSessionResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE + strlen(data_val), MallocClass::generateSetupDuet3Response);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::FE_SETUP_SESSION_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;

    memcpy(current_ptr, session_id_index_val, SIZE_DEF::SESSION_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::SESSION_ID_INDEX_SIZE;

    strcpy(current_ptr, data_val);
    return response_data;
}

void DFabricClass::sendSetupRoomRequestToThemeServer (GroupClass *group_val)
{
    char *current_ptr;
    char *uplink_data = current_ptr = (char *) phwangMalloc(FABRIC_DEF::FT_UL_BUF_WITH_GROUP_SIZE + 1 + strlen(group_val->themeInfo()), MallocClass::sendSetupRoomRequestToThemeServer);

    *current_ptr++ = FT_DEF::FT_SETUP_ROOM_COMMAND;

    memcpy(current_ptr, group_val->groupIdIndex(), SIZE_DEF::GROUP_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::GROUP_ID_INDEX_SIZE;

    *current_ptr++ = group_val->themeType();

    strcpy(current_ptr, group_val->themeInfo());

    this->fabricObject_->uFabricObject()->transmitFunction(uplink_data);
}

char *DFabricClass::processSetupSession2Request (
    SessionClass *session_val,
    char *ajax_id_val,
    char *data_val)
{
    LinkClass *link = session_val->linkObject();
    char *response_data;
    phwangDebugSS(true, "DFabricClass::processSetupSession2Request", "data_val=", data_val);
    phwangDebugSSS(true, "DFabricClass::processSetupSession2Request", "id=", link->linkIdIndex(), session_val->sessionIdIndex());

    char answer = *data_val;
    //char *theme_info_val = data_val;
    GroupClass *group = session_val->groupObject();
    if (!group) {
        printf("null group\n");
    }

    if (answer == 'Y') {
        this->sendSetupRoomRequestToThemeServer(group);
    }
    else {

    }

    response_data = this->generateSetupSession2Response(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, link->linkIdIndex(), session_val->sessionIdIndex(), group->themeType(), group->themeInfo());
    return response_data;
}

char *DFabricClass::generateSetupSession2Response (
    char const *result_val,
    char *ajax_id_val,
    char const *link_id_index_val,
    char const *session_id_index_val,
    char theme_type_val,
    char const *theme_info_val)
{
    phwangDebugS(false, "DFabricClass::generateSetupSession2Response", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE + 1 + strlen(theme_info_val), MallocClass::generateSetupDuet2Response);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::FE_SETUP_SESSION2_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;

    memcpy(current_ptr, session_id_index_val, SIZE_DEF::SESSION_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::SESSION_ID_INDEX_SIZE;

    *current_ptr = theme_type_val;
    current_ptr++;

    strcpy(current_ptr, theme_info_val);

    return response_data;
}

char *DFabricClass::processSetupSession3Request (
    SessionClass *session_val,
    char *ajax_id_val,
    char *data_val)
{
    char *response_data;

    phwangDebugSS(true, "DFabricClass::processSetupSession3Request", "session_id=", session_val->sessionIdIndex());
    phwangDebugSS(true, "DFabricClass::processSetupSession3Request", "data_val=", data_val);

    response_data = this->generateSetupSession3Response(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, session_val);
    return response_data;
}

char *DFabricClass::generateSetupSession3Response (
    char const *result_val,
    char *ajax_id_val,
    SessionClass *session_val)
{
    phwangDebugSS(false, "DFabricClass::generateSetupSession3Response", "result=", result_val);
    LinkClass *link = session_val->linkObject();
    GroupClass *group = session_val->groupObject();

    char *encoded_theme_info    = phwangEncodeStringMalloc(group->themeInfo());
    char *encoded_first_fiddle  = phwangEncodeStringMalloc(group->firstFiddle());
    char *encoded_second_fiddle = phwangEncodeStringMalloc(group->secondFiddle());

    char *response_data = (char *) phwangMalloc(
        FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE + 4 + strlen(encoded_theme_info) + strlen(encoded_first_fiddle) + strlen(encoded_second_fiddle),
        MallocClass::sendSetupSessionResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::FE_SETUP_SESSION3_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link->linkIdIndex(), SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;

    memcpy(current_ptr, session_val->sessionIdIndex(), SIZE_DEF::SESSION_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::SESSION_ID_INDEX_SIZE;

    *current_ptr++ = group->roomStatus();
    *current_ptr++ = group->mode();
    *current_ptr++ = group->themeType();

    memcpy(current_ptr, encoded_theme_info, strlen(encoded_theme_info));
    current_ptr += strlen(encoded_theme_info);

    memcpy(current_ptr, encoded_first_fiddle, strlen(encoded_first_fiddle));
    current_ptr += strlen(encoded_first_fiddle);

    memcpy(current_ptr, encoded_second_fiddle, strlen(encoded_second_fiddle));
    current_ptr += strlen(encoded_second_fiddle);

    *current_ptr = 0;

    phwangFree(encoded_theme_info);
    phwangFree(encoded_first_fiddle);
    phwangFree(encoded_second_fiddle);

    phwangDebugSS(true, "DFabricClass::generateSetupSession3Response", "response_data=", response_data);

    return response_data;
}

/* free session */

char *DFabricClass::processFreeSessionRequest (
    SessionClass *session_val,
    char *ajax_id_val)
{
    LinkClass *link = session_val->linkObject();
    char *response_data;
    phwangDebugSSS(true, "DFabricClass::processFreeSessionRequest", "id=", link->linkIdIndex(), session_val->sessionIdIndex());

    char session_id_buf[SIZE_DEF::SESSION_ID_INDEX_SIZE + 1];
    strcpy(session_id_buf, session_val->sessionIdIndex());
    link->freeSession(session_val);

    response_data = this->generateFreeSessionResponse(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, link->linkIdIndex(), session_id_buf);
    return response_data;
}

char *DFabricClass::generateFreeSessionResponse (
    char const *result_val,
    char *ajax_id_val,
    char const *link_id_index_val,
    char const *session_id_index_val)
{
    phwangDebugS(false, "DFabricClass::generateFreeSessionResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE, MallocClass::generateFreeSessionResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::FE_FREE_SESSION_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;

    strcpy(current_ptr, session_id_index_val);

    return response_data;
}

/* put session data */

char *DFabricClass::processPutSessionDataRequest (
    SessionClass *session_val,
    char *ajax_id_val,
    char *data_val)
{
    char *response_data;
    phwangDebugS(true, "DFabricClass::processPutSessionDataRequest", data_val);

    char *room_id = session_val->groupObject()->roomIdIndex();
    if (!room_id) {
        response_data = this->generatePutSessionDataResponse(RESULT_DEF::RESULT_NULL_ROOM, ajax_id_val, session_val->linkObject()->linkIdIndex(), session_val->sessionIdIndex());
        return response_data;
    }

    this->sendPutSessionDataRequestToThemeServer(room_id, data_val);

    response_data = this->generatePutSessionDataResponse(RESULT_DEF::RESULT_ALMOST_SUCCEED, ajax_id_val, session_val->linkObject()->linkIdIndex(), session_val->sessionIdIndex());
    return response_data;
}

char *DFabricClass::generatePutSessionDataResponse (
    char const *result_val,
    char *ajax_id_val,
    char const *link_id_index_val,
    char const *session_id_index_val)
{
    phwangDebugS(false, "DFabricClass::generatePutSessionDataResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE, MallocClass::generatePutSessionDataResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::FE_PUT_SESSION_DATA_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;

    memcpy(current_ptr, session_id_index_val, SIZE_DEF::SESSION_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::SESSION_ID_INDEX_SIZE;

    *current_ptr = 0;

    return response_data;
}

void DFabricClass::sendPutSessionDataRequestToThemeServer (
    char const *room_id_val,
    char const *data_val)
{
    char *current_ptr;
    char *uplink_data = current_ptr = (char *) phwangMalloc(FABRIC_DEF::FT_UL_BUF_WITH_ROOM_SIZE + strlen(data_val), MallocClass::PUT_SESSION_DATA0);

    *current_ptr++ = FT_DEF::FT_PUT_ROOM_DATA_COMMAND;

    memcpy(current_ptr, room_id_val, SIZE_DEF::ROOM_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::ROOM_ID_INDEX_SIZE;

    strcpy(current_ptr, data_val);

    this->fabricObject_->uFabricObject()->transmitFunction(uplink_data);
}

/* get session data */

char *DFabricClass::processGetSessionDataRequest (
    SessionClass *session_val,
    char *ajax_id_val,
    char *data_val)
{
    phwangDebugS(true, "DFabricClass::processGetSessionDataRequest", data_val);

    char *data = session_val->dequeuePendingData();
    if (data) {
        return this->generateGetSessionDataResponse(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, session_val->linkObject()->linkIdIndex(), session_val->sessionIdIndex(), data);
    }
    else {
        return this->generateGetSessionDataResponse(RESULT_DEF::RESULT_SESSION_DATA_NOT_AVAILABLE, ajax_id_val, session_val->linkObject()->linkIdIndex(), session_val->sessionIdIndex(), "");
    }
}

char *DFabricClass::generateGetSessionDataResponse (
    char const *result_val,
    char *ajax_id_val,
    char const *link_id_index_val,
    char const *session_id_index_val,
    char const *data_val)
{
    phwangDebugS(false, "DFabricClass::generateGetSessionDataResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE + strlen(data_val), MallocClass::generateGetSessionDataResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::FE_GET_SESSION_DATA_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;

    memcpy(current_ptr, session_id_index_val, SIZE_DEF::SESSION_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::SESSION_ID_INDEX_SIZE;

    strcpy(current_ptr, data_val);
    return response_data;
}
