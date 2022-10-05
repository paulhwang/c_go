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

DbAccountClass *DFabricClass::dbAccountObject(void) {return theFabricObject->dbObject()->dbAccountObject();}

void DFabricClass::exportedParseFunction (
    void *port_object_val,
    char *data_val)
{
    char device_type = data_val[0];
    char depth = data_val[1];
    char command = data_val[2];
    char *current_ptr = &data_val[3];

    char ajax_id[SIZE_DEF::AJAX_ID_SIZE + 1];
    switch (device_type) {
        case FE_DEF::FE_DEVICE_TYPE_NODEJS:
            memcpy(ajax_id, current_ptr, SIZE_DEF::AJAX_ID_SIZE);
            ajax_id[SIZE_DEF::AJAX_ID_SIZE] = 0;
            current_ptr += SIZE_DEF::AJAX_ID_SIZE;
            break;

        case FE_DEF::FE_DEVICE_TYPE_IPHONE:
        case FE_DEF::FE_DEVICE_TYPE_ANDROID:
            break;

        default:
            phwangAbendS("DFabricClass::exportedParseFunction", "bad_device");
            break;
    }

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
                    response_data = this->processRegisterRequest(current_ptr);
                    response_data[0] = FE_DEF::FE_REGISTER_RESPONSE;
                    break;

                case FE_DEF::FE_LOGIN_COMMAND:
                    response_data = this->processLoginRequest(current_ptr, device_type, port_object_val);
                    response_data[0] = FE_DEF::FE_LOGIN_RESPONSE;
                    break;

                case FE_DEF::FE_MESSAGE_COMMAND:
                    response_data = this->processDatagramRequest(current_ptr);
                    response_data[0] = FE_DEF::FE_MESSAGE_RESPONSE;
                    break;

                default:
                    phwangAbendS("DFabricClass::exportedParseFunction_0", current_ptr);
                    return;
            }
            break;

        case '1':
            link = this->theFabricObject->searchLink(current_ptr, data_val);
            if (!link) {
                this->sendSearchLinkFailResponse(command, port_object_val, ajax_id);
                return;
            }
            current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;

            switch (command) {
                case FE_DEF::FE_LOGOUT_COMMAND:
                    response_data = this->processLogoutRequest(link, current_ptr);
                    response_data[0] = FE_DEF::FE_LOGOUT_RESPONSE;
                    break;

                case FE_DEF::FE_GET_LINK_DATA_COMMAND:
                    response_data = this->processGetLinkDataRequest(link, current_ptr);
                    response_data[0] = FE_DEF::FE_GET_LINK_DATA_RESPONSE;
                    break;

                case FE_DEF::FE_GET_NAME_LIST_COMMAND:
                    response_data = this->processGetNameListRequest(link, current_ptr);
                    response_data[0] = FE_DEF::FE_GET_NAME_LIST_RESPONSE;
                    break;

                case FE_DEF::FE_SETUP_SESSION_COMMAND:
                    response_data = this->processSetupSessionRequest(link, current_ptr, ajax_id);
                    if (!response_data) {
                        return;
                    }
                    response_data[0] = FE_DEF::FE_SETUP_SESSION_RESPONSE;
                    break;

                case FE_DEF::FE_SETUP_SESSION3_COMMAND:
                    response_data = this->processSetupSession3Request(link, current_ptr);
                    response_data[0] = FE_DEF::FE_SETUP_SESSION3_RESPONSE;
                    break;

                default:
                    phwangAbendS("DFabricClass::exportedParseFunction_1", data_val);
                    return;
            }
            break;

        case '2':
            session = this->theFabricObject->serachLinkAndSession(current_ptr);
            if (!session) {
                this->sendSearchLinkSessionFailResponse(command, port_object_val, ajax_id);
                return;
            }
            current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE + SIZE_DEF::SESSION_ID_INDEX_SIZE;

            switch (command) {
                case FE_DEF::FE_SETUP_SESSION2_COMMAND:
                    response_data = this->processSetupSession2Request(session, current_ptr);
                    response_data[0] = FE_DEF::FE_SETUP_SESSION2_RESPONSE;
                    break;

                case FE_DEF::FE_FREE_SESSION_COMMAND:
                    this->processFreeSessionRequest(session);
                    response_data[0] = FE_DEF::FE_FREE_SESSION_RESPONSE;
                    break;

                case FE_DEF::FE_PUT_SESSION_DATA_COMMAND:
                    response_data = this->processPutSessionDataRequest(session, current_ptr, ajax_id);
                    if (!response_data) {
                        return;
                    }
                    response_data[0] = FE_DEF::FE_PUT_SESSION_DATA_RESPONSE;
                    break;

                case FE_DEF::FE_GET_SESSION_DATA_COMMAND:
                    response_data = this->processGetSessionDataRequest(session, current_ptr);
                    response_data[0] = FE_DEF::FE_GET_SESSION_DATA_RESPONSE;
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

    switch (device_type) {
        case FE_DEF::FE_DEVICE_TYPE_NODEJS:
            memcpy(&response_data[1], ajax_id, SIZE_DEF::AJAX_ID_SIZE);
            break;

        case FE_DEF::FE_DEVICE_TYPE_IPHONE:
        case FE_DEF::FE_DEVICE_TYPE_ANDROID:
            memcpy(&response_data[1], "***", SIZE_DEF::AJAX_ID_SIZE);
            break;
        default:
            break;
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

char *DFabricClass::processDatagramRequest (char *input_data_val)
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
    response_data = generateDatagramResponse(RESULT_DEF::RESULT_SUCCEED, output_data);
    return response_data;
}

char *DFabricClass::generateDatagramResponse (
    char const *result_val,
    char const *data_val)
{
    phwangDebugSS(false, "DFabricClass::generateDatagramResponse", "data_val=", data_val);

    char *encoded_data = phwangEncodeStringMalloc(data_val);
    int encoded_data_length = strlen(encoded_data);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SIZE + strlen(encoded_data), MallocClass::generateDatagramResponse);
    char *current_ptr = &response_data[FABRIC_DEF::FE_DL_COMMAND_AJAX_SIZE];

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    strcpy(current_ptr, encoded_data);
    //current_ptr += encoded_data_length;
    phwangFree(encoded_data);

    return response_data;
}

char *DFabricClass::processRegisterRequest (char *data_val)
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

        response_data = generateRegisterResponse(RESULT_DEF::RESULT_SUCCEED, account_name);

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
        response_data = generateRegisterResponse(result_buf, account_name);
        phwangFree(account_name);
        return response_data;
    }

    else if (!strcmp(result_buf, RESULT_DEF::RESULT_DB_SELECT_FAIL)) {
        response_data = generateRegisterResponse(result_buf, account_name);
        phwangFree(account_name);
        return response_data;
   }

    else {
        phwangAbendSS("DFabricClass::processRegisterRequest", "unsupported_result", result_buf);
        response_data = generateRegisterResponse(RESULT_DEF::RESULT_DB_ERROR, account_name);
        phwangFree(account_name);
        return response_data;
    }
}

char *DFabricClass::generateRegisterResponse (
    char const *result_val,
    char const *account_name_val)
{
    phwangDebugS(false, "DFabricClass::generateRegisterResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUFFER_SIZE + strlen(account_name_val), MallocClass::generateRegisterResponse);
    char *current_ptr = &response_data[FABRIC_DEF::FE_DL_COMMAND_AJAX_SIZE];
    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE );
    current_ptr += RESULT_DEF::RESULT_SIZE;

    strcpy(current_ptr, account_name_val);
    return response_data;
}

char *DFabricClass::processLoginRequest (
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
        LinkClass *link = this->theFabricObject->mallocLink(my_name, device_type_val, port_object_val);
        if (!link) {
            phwangAbendS("DFabricClass::processLoginRequest", "null_link");
            phwangFree(my_name);
            response_data = generateLoginResponse(RESULT_DEF::RESULT_NULL_LINK, SIZE_DEF::FAKE_LINK_ID_INDEX, encoded_my_name_buf);
            return response_data;
        }

        phwangFree(my_name);
        response_data = generateLoginResponse(RESULT_DEF::RESULT_SUCCEED, link->linkIdIndex(), encoded_my_name_buf);
        return response_data;
    }

    else if ((!strcmp(result_buf, RESULT_DEF::RESULT_PASSWORD_NOT_MATCH)) ||
             (!strcmp(result_buf, RESULT_DEF::RESULT_ACCOUNT_NAME_NOT_EXIST)) ||
             (!strcmp(result_buf, RESULT_DEF::RESULT_DB_SELECT_FAIL))) {
        phwangFree(my_name);
        response_data = generateLoginResponse(result_buf, SIZE_DEF::FAKE_LINK_ID_INDEX, encoded_my_name_buf);
        return response_data;
    }

    else {
        phwangAbendSS("DFabricClass::processLoginRequest", "unsupported_result", result_buf);
        phwangFree(my_name);
        response_data = generateLoginResponse(RESULT_DEF::RESULT_DB_ERROR, SIZE_DEF::FAKE_LINK_ID_INDEX, encoded_my_name_buf);
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
    char const *link_id_index_val,
    char const *account_name_val)
{
    phwangDebugS(false, "DFabricClass::generateLoginResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SIZE + strlen(account_name_val), MallocClass::generateLoginResponse);
    char *current_ptr = &response_data[FABRIC_DEF::FE_DL_COMMAND_AJAX_SIZE];
    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;

    strcpy(current_ptr, account_name_val);
    return response_data;
}

char *DFabricClass::processLogoutRequest (
    LinkClass *link_val,
    char *data_val)
{
    char *response_data;
    phwangDebugSS(false, "DFabricClass::processLogoutRequest", "link_id=", link_val->linkIdIndex());

    this->theFabricObject->freeLink(link_val);

    response_data = generateLogoutResponse(RESULT_DEF::RESULT_SUCCEED, link_val->linkIdIndex(), data_val);
    return response_data;
}

char *DFabricClass::generateLogoutResponse (
    char const *result_val,
    char const *link_id_index_val,
    char const *data_val)
{
    phwangDebugS(false, "DFabricClass::generateLogoutResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SIZE + strlen(data_val), MallocClass::generateLogoutResponse);
    char *current_ptr = &response_data[FABRIC_DEF::FE_DL_COMMAND_AJAX_SIZE];
    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;

    strcpy(current_ptr, data_val);
    return response_data;
}

char *DFabricClass::processGetLinkDataRequest (
    LinkClass *link_val,
    char *data_val)
{
    char *response_data;
    phwangDebugS(false, "DFabricClass::processGetLinkDataRequest", data_val);

    link_val->resetKeepAliveTime();

    char *downlink_data = (char *) phwangMalloc(FABRIC_DEF::FE_GET_LINK_DATA_BUF_SIZE, MallocClass::GET_LINK_DATA);
    char *current_ptr = &downlink_data[FABRIC_DEF::FE_DL_COMMAND_AJAX_SIZE];

    memcpy(current_ptr, RESULT_DEF::RESULT_SUCCEED, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_val->linkIdIndex(), SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;

    *current_ptr++ = FE_DEF::RESPOND_IS_GET_LINK_DATA_NAME_LIST;
    phwangEncodeNumber(current_ptr, this->theFabricObject->nameListObject()->nameListTag(), SIZE_DEF::NAME_LIST_TAG_SIZE);
    current_ptr += SIZE_DEF::NAME_LIST_TAG_SIZE;
    *current_ptr = 0;

    int max_session_table_array_index = phwnagListMgrGetMaxIndex(link_val->sessionListMgrObject(), "DFabricClass::processGetLinkData()");
    SessionClass **session_table_array = (SessionClass **) phwangListMgrGetEntryTableArray(link_val->sessionListMgrObject());
    for (int i = 0; i <= max_session_table_array_index; i++) {
        SessionClass *session = session_table_array[i];
        if (session) {
            char *pending_downlink_data = session->getPendingDownLinkData();
            if (pending_downlink_data) {
                *current_ptr++ = FE_DEF::RESPOND_IS_GET_LINK_DATA_PENDING_DATA;
                session->enqueuePendingDownLinkData(pending_downlink_data);
                strcpy(current_ptr, link_val->linkIdIndex());
                current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;
                strcpy(current_ptr, session->sessionIdIndex());
                current_ptr += SIZE_DEF::SESSION_ID_INDEX_SIZE;

                phwangDebugSS(true, "DFabricClass::processGetLinkDataRequest","Pending_data_exist:", downlink_data);
            }
        }
    }

    char *pending_session_info = link_val->getPendingSessionSetup();
    if (pending_session_info) {
        *current_ptr++ = FE_DEF::RESPOND_IS_GET_LINK_DATA_PENDING_SESSION;
        strcpy(current_ptr, pending_session_info);
        phwangDebugSS(true, "DFabricClass::processGetLinkDataRequest", "getPendingSessionSetup ", downlink_data);
        phwangFree(pending_session_info);
    }

    char *pending_session_info3 = link_val->getPendingSessionSetup3();
    if (pending_session_info3) {
        *current_ptr++ = FE_DEF::RESPOND_IS_GET_LINK_DATA_PENDING_SESSION3;
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

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE + strlen(data_val), MallocClass::generateGetLinkDataResponse);
    char *current_ptr = &response_data[FABRIC_DEF::FE_DL_COMMAND_AJAX_SIZE];
    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;
    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;
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

    int name_list_tag = phwangDecodeNumber(name_list_tag_val, SIZE_DEF::NAME_LIST_TAG_SIZE);
    char *name_list = this->theFabricObject->nameListObject()->getNameList(name_list_tag);

    if (!name_list) {
        /////////////////////////////////TBD
    }

    response_data = generateGetNameListResponse(RESULT_DEF::RESULT_SUCCEED, link_val->linkIdIndex(), name_list);
    return response_data;
}

char *DFabricClass::generateGetNameListResponse (
    char const *result_val,
    char const *link_id_index_val,
    char const *data_val)
{
    phwangDebugS(false, "DFabricClass::generateGetNameListResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE + strlen(data_val), MallocClass::generateGetNameListResponse);
    char *current_ptr = &response_data[FABRIC_DEF::FE_DL_COMMAND_AJAX_SIZE];
    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;
    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;
    strcpy(current_ptr, data_val);
    return response_data;
}

char *DFabricClass::processSetupSessionRequest (
    LinkClass *link_val,
    char *data_val,
    char *ajax_id_val)
{
    char *response_data = 0;
    phwangDebugSS(true, "DFabricClass::processSetupSessionRequest", "data_val=", data_val);

    SessionClass *session = link_val->mallocSession();
    if (!session) {
        response_data = this->generateSetupSessionResponse(RESULT_DEF::RESULT_MALLOC_SESSION_FAIL, link_val->linkIdIndex(), SIZE_DEF::FAKE_SESSION_ID_INDEX, data_val);
        return response_data;
    }
    session->setAjaxId(ajax_id_val);

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
        case 'G':
            break;

        default:
            phwangAbendS("DFabricClass::processSetupSessionRequest", "theme_type not supported");
    }

    GroupClass *group = this->theFabricObject->mallocGroup(group_mode, theme_type, theme_info, first_fiddle, second_fiddle);
    phwangFree(theme_info);
    phwangFree(first_fiddle);
    phwangFree(second_fiddle);
    if (!group) {
        response_data = this->generateSetupSessionResponse(RESULT_DEF::RESULT_MALLOC_GROUP_FAIL, link_val->linkIdIndex(), session->sessionIdIndex(), data_val);
        return response_data;
    }
    group->insertSession(session);
    session->bindGroup(group);

    if ( (group->mode() == FE_DEF::FE_GROUP_MODE_SOLO) ||
        ((group->mode() == FE_DEF::FE_GROUP_MODE_DUET) && (!strcmp(group->firstFiddle(), group->secondFiddle()))) ||
         (group->mode() == FE_DEF::FE_GROUP_MODE_ENSEMBLE)) {
        this->sendSetupRoomRequestToThemeServer(group);
        return 0;
    }

    LinkClass *second_link = this->theFabricObject->searchLinkByName(group->secondFiddle());
    if (!second_link) {
        response_data = this->generateSetupSessionResponse(RESULT_DEF::RESULT_SECOND_LINK_NOT_EXIST, link_val->linkIdIndex(), SIZE_DEF::FAKE_SESSION_ID_INDEX, data_val);
        return response_data;
    }

    SessionClass *second_session = second_link->mallocSession();
    if (!second_session) {
        response_data = this->generateSetupSessionResponse(RESULT_DEF::RESULT_MALLOC_SECOND_SESSION_FAIL, link_val->linkIdIndex(), SIZE_DEF::FAKE_SESSION_ID_INDEX, data_val);
        return response_data;
    }

    second_link->setPendingSessionSetup(second_session->sessionIdIndex(), group->themeType(), group->themeInfo());
    return 0;
    //response_data = this->generateSetupSoloResponse(RESULT_DEF::RESULT_SUCCEED, link_val->linkIdIndex(), session->sessionIdIndex(), data_val);
    //return response_data;
}

char *DFabricClass::generateSetupSessionResponse (
    char const *result_val,
    char const *link_id_index_val,
    char const *session_id_index_val,
    char const *data_val)
{
    phwangDebugS(false, "DFabricClass::generateSetupSessionResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE + strlen(data_val), MallocClass::generateSetupDuet3Response);
    char *current_ptr = &response_data[FABRIC_DEF::FE_DL_COMMAND_AJAX_SIZE];

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

    this->theFabricObject->uFabricObject()->transmitFunction(uplink_data);
}

char *DFabricClass::processSetupSession2Request (
    SessionClass *session_val,
    char *data_val)
{
    LinkClass *link = session_val->linkObject();
    char *response_data;
    phwangDebugS(false, "DFabricClass::processSetupSession2Request", data_val);
    phwangDebugSSS(false, "DFabricClass::processSetupSession2Request", "id=", link->linkIdIndex(), session_val->sessionIdIndex());

    char *theme_info_val = data_val;
    GroupClass *group = session_val->groupObject();
    this->sendSetupRoomRequestToThemeServer(group);//////////////do it twice ???

    response_data = this->generateSetupSession2Response(RESULT_DEF::RESULT_SUCCEED, link->linkIdIndex(), session_val->sessionIdIndex());
    return response_data;
}

char *DFabricClass::generateSetupSession2Response (
    char const *result_val,
    char const *link_id_index_val,
    char const *session_id_index_val)
{
    phwangDebugS(false, "DFabricClass::generateSetupSession2Response", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE, MallocClass::generateSetupDuet2Response);
    char *current_ptr = &response_data[FABRIC_DEF::FE_DL_COMMAND_AJAX_SIZE];
    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;
    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;
    strcpy(current_ptr, session_id_index_val);
    return response_data;
}

char *DFabricClass::processSetupSession3Request (
    LinkClass *link_val,
    char *data_val)
{
    char *response_data;
    phwangDebugSS(true, "DFabricClass::processSetupSession3Request", "data_val=", data_val);

    char session_id_buf[SIZE_DEF::SESSION_ID_INDEX_SIZE + 1];
    memcpy(session_id_buf, data_val, SIZE_DEF::SESSION_ID_INDEX_SIZE);
    session_id_buf[SIZE_DEF::SESSION_ID_INDEX_SIZE] = 0;
    phwangDebugSS(true, "DFabricClass::processSetupSession3Request", "session_id=", session_id_buf);

    response_data = this->generateSetupSession3Response(RESULT_DEF::RESULT_SUCCEED, link_val->linkIdIndex(), session_id_buf);
    return response_data;
}

char *DFabricClass::generateSetupSession3Response (
    char const *result_val,
    char const *link_id_index_val,
    char const *session_id_index_val)
{
    phwangDebugS(false, "DFabricClass::generateSetupSession3Response", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE, MallocClass::generateSetupDuet3Response);
    char *current_ptr = &response_data[FABRIC_DEF::FE_DL_COMMAND_AJAX_SIZE];
    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;
    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;
    strcpy(current_ptr, session_id_index_val);
    return response_data;
}

/* free session */

char *DFabricClass::processFreeSessionRequest (
    SessionClass *session_val)
{
    LinkClass *link = session_val->linkObject();
    char *response_data;
    phwangDebugSSS(true, "DFabricClass::processFreeSessionRequest", "id=", link->linkIdIndex(), session_val->sessionIdIndex());

    char session_id_buf[SIZE_DEF::SESSION_ID_INDEX_SIZE + 1];
    strcpy(session_id_buf, session_val->sessionIdIndex());
    link->freeSession(session_val);

    response_data = this->generateFreeSessionResponse(RESULT_DEF::RESULT_SUCCEED, link->linkIdIndex(), session_id_buf);
    return response_data;
}

char *DFabricClass::generateFreeSessionResponse (
    char const *result_val,
    char const *link_id_index_val,
    char const *session_id_index_val)
{
    phwangDebugS(false, "DFabricClass::generateFreeSessionResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE, MallocClass::generateFreeSessionResponse);
    char *current_ptr = &response_data[FABRIC_DEF::FE_DL_COMMAND_AJAX_SIZE];
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
    char *data_val,
    char *ajax_id_val)
{
    char *response_data;
    phwangDebugS(true, "DFabricClass::processPutSessionDataRequest", data_val);

    char *room_id = session_val->groupObject()->roomIdIndex();
    if (!room_id) {
        response_data = this->generatePutSessionDataResponse(RESULT_DEF::RESULT_NULL_ROOM, session_val->linkObject()->linkIdIndex(), session_val->sessionIdIndex());
        return response_data;
    }

    session_val->setAjaxId(ajax_id_val);
    this->sendPutSessionDataRequestToThemeServer(room_id, data_val);

    return 0;
    //response_data = this->generatePutSessionDataResponse(RESULT_DEF::RESULT_SUCCEED, session_val->linkObject()->linkIdIndex(), session_val->sessionIdIndex());
    //return response_data;
}

char *DFabricClass::generatePutSessionDataResponse (
    char const *result_val,
    char const *link_id_index_val,
    char const *session_id_index_val)
{
    phwangDebugS(false, "DFabricClass::generatePutSessionDataResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE, MallocClass::generatePutSessionDataResponse);
    char *current_ptr = &response_data[FABRIC_DEF::FE_DL_COMMAND_AJAX_SIZE];
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

    this->theFabricObject->uFabricObject()->transmitFunction(uplink_data);
}

/* get session data */

char *DFabricClass::processGetSessionDataRequest (
    SessionClass *session_val,
    char *data_val)
{
    phwangDebugS(true, "DFabricClass::processGetSessionDataRequest", data_val);

    char *data = session_val->getPendingDownLinkData();
    if (data) {
        return this->generateGetSessionDataResponse(RESULT_DEF::RESULT_SUCCEED, session_val->linkObject()->linkIdIndex(), session_val->sessionIdIndex(), data);
    }
    else {
        return this->generateGetSessionDataResponse(RESULT_DEF::RESULT_SESSION_DATA_NOT_AVAILABLE, session_val->linkObject()->linkIdIndex(), session_val->sessionIdIndex(), "");
    }
}

char *DFabricClass::generateGetSessionDataResponse (
    char const *result_val,
    char const *link_id_index_val,
    char const *session_id_index_val,
    char const *data_val)
{
    phwangDebugS(false, "DFabricClass::generateGetSessionDataResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE + strlen(data_val), MallocClass::generateGetSessionDataResponse);
    char *current_ptr = &response_data[FABRIC_DEF::FE_DL_COMMAND_AJAX_SIZE];
    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;
    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;
    memcpy(current_ptr, session_id_index_val, SIZE_DEF::SESSION_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::SESSION_ID_INDEX_SIZE;
    strcpy(current_ptr, data_val);
    return response_data;
}
