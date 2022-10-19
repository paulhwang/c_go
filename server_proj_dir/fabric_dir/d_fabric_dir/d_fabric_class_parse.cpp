/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_export.cpp
*/

#include <errno.h>
#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../../phwang_dir/file_dir/file_read_class.h"
#include "../../define_dir/result_def.h"
#include "../../define_dir/file_def.h"
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
    return fabricObj_->dbObject()->dbAccountObject();
}

void DFabricClass::parseInput (
    void *port_obj_val,
    char *data_val)
{
    char ajax_id[SIZE_DEF::AJAX_ID_SIZE + 1];
    memcpy(ajax_id, data_val, SIZE_DEF::AJAX_ID_SIZE);
    ajax_id[SIZE_DEF::AJAX_ID_SIZE] = 0;
    char *current_ptr = data_val + SIZE_DEF::AJAX_ID_SIZE;

    if (*current_ptr == '{') {
        if (memcmp(current_ptr, this->timeStampString_, SIZE_DEF::FABRIC_TIME_STAMP_SIZE)) {
            phwangDebugSS(true, "DFabricClass::parseInput", " ***time_stamp not match: data=", data_val);
            phwangAbendSS("DFabricClass::parseInput", " ***time_stamp not match: data=", data_val);
            return;
        }
        current_ptr += SIZE_DEF::FABRIC_TIME_STAMP_SIZE;
    }

    char depth = current_ptr[0];
    char command = current_ptr[1];
    current_ptr += 2;

    if (command != FE_DEF::GET_LINK_DATA_COMMAND) {
        phwangDebugSS(true, "DFabricClass::parseInput", "data_val=", data_val);
        phwangDebugSS(true, "DFabricClass::parseInput", "current_ptr=", current_ptr);
    }

    LinkClass *link;
    SessionClass *session;
    char *response_data;
    switch (depth) {
        case '0':
            switch (command) {
                case FE_DEF::REGISTER_COMMAND:
                    response_data = this->processRegisterRequest(ajax_id, current_ptr);
                    break;

                case FE_DEF::LOGIN_COMMAND:
                    response_data = this->processLoginRequest(ajax_id, current_ptr, 'N', port_obj_val);
                    break;

                case FE_DEF::OPEN_FILE_COMMAND:
                    response_data = this->processOpenFileRequest(ajax_id, current_ptr);
                    break;

                case FE_DEF::CLOSE_FILE_COMMAND:
                    response_data = this->processCloseFileRequest(ajax_id, current_ptr);
                    break;

                case FE_DEF::READ_FILE_COMMAND:
                    response_data = this->processReadFileRequest(ajax_id, current_ptr);
                    break;

                case FE_DEF::MESSAGE_COMMAND:
                    response_data = this->processDatagramRequest(ajax_id, current_ptr);
                    break;

                default:
                    printf("comand=%c\n", command);
                    phwangAbendS("DFabricClass::parseInput_0", current_ptr);
                    return;
            }
            break;

        case '1':
            link = this->fabricObj_->searchLink(current_ptr, data_val);
            if (!link) {
                this->sendSearchLinkFailResponse(command, port_obj_val, ajax_id, current_ptr);
                return;
            }
            current_ptr += SIZE_DEF::LINK_II_SIZE;

            switch (command) {
                case FE_DEF::LOGOUT_COMMAND:
                    response_data = this->processLogoutRequest(link, ajax_id, current_ptr);
                    break;

                case FE_DEF::GET_LINK_DATA_COMMAND:
                    response_data = this->processGetLinkDataRequest(link, ajax_id);
                    break;

                case FE_DEF::GET_NAME_LIST_COMMAND:
                    response_data = this->processGetNameListRequest(link, ajax_id, current_ptr);
                    break;

                case FE_DEF::SETUP_SESSION_COMMAND:
                    response_data = this->processSetupSessionRequest(link, ajax_id, current_ptr);
                    break;

                case FE_DEF::WRITE_FILE_COMMAND:
                    response_data = this->processWriteFileRequest(ajax_id, current_ptr);
                    break;

                default:
                    phwangAbendS("DFabricClass::parseInput_1", data_val);
                    return;
            }
            break;

        case '2':
            session = this->fabricObj_->serachLinkAndSession(current_ptr);
            if (!session) {
                this->sendSearchLinkSessionFailResponse(command, port_obj_val, ajax_id, current_ptr);
                return;
            }
            current_ptr += SIZE_DEF::LINK_II_SIZE + SIZE_DEF::SESSION_II_SIZE;

            switch (command) {
                case FE_DEF::SETUP_SESSION2_COMMAND:
                    response_data = this->processSetupSession2Request(session, ajax_id, current_ptr);
                    break;

                case FE_DEF::SETUP_SESSION3_COMMAND:
                    response_data = this->processSetupSession3Request(session, ajax_id, current_ptr);
                    break;

                case FE_DEF::FREE_SESSION_COMMAND:
                    response_data = this->processFreeSessionRequest(session, ajax_id);
                    break;

                case FE_DEF::PUT_SESSION_DATA_COMMAND:
                    response_data = this->processPutSessionDataRequest(session, ajax_id, current_ptr);
                    break;

                case FE_DEF::GET_SESSION_DATA_COMMAND:
                    response_data = this->processGetSessionDataRequest(session, ajax_id, current_ptr);
                    break;

                default:
                    phwangAbendS("DFabricClass::parseInput_2", data_val);
                    return;
            }
            break;

        default:
            phwangAbendS("DFabricClass::parseInput", "bad type");
            return;
    }

    this->transmitData(port_obj_val, response_data);
}

void DFabricClass::sendSearchLinkFailResponse (
    char const command_val,
    void *port_object_val,
    char const *ajax_id_val,
    char *data_val)
{
    phwangDebugS(true, "DFabricClass::sendSearchLinkFailResponse", data_val);
    phwangAbendS("DFabricClass::sendSearchLinkFailResponse", data_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACR_BUF_SIZE, MallocClass::BAD_LINK);
    char *current_ptr = response_data;

    strcpy(current_ptr, ajax_id_val);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = command_val + 32;

    strcpy(current_ptr, RESULT_DEF::RESULT_LINK_NOT_EXIST);

    this->transmitData(port_object_val, response_data);
}

void DFabricClass::sendSearchLinkSessionFailResponse (
    char const command_val,
    void *port_object_val,
    char const *ajax_id_val,
    char *data_val)
{
    phwangDebugS(true, "DFabricClass::sendSearchLinkSessionFailResponse", data_val);
    phwangAbendS("DFabricClass::sendSearchLinkSessionFailResponse", data_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACR_BUF_SIZE, MallocClass::BAD_SESSION);
    char *current_ptr = response_data;

    strcpy(current_ptr, ajax_id_val);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = command_val + 32;

    strcpy(current_ptr, RESULT_DEF::RESULT_SESSION_NOT_EXIST);

    this->transmitData(port_object_val, response_data);
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

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACR_BUF_SIZE + strlen(account_name_val), MallocClass::generateRegisterResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::REGISTER_RESPONSE;

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
        LinkClass *link = this->fabricObj_->mallocLink(my_name, device_type_val, port_object_val);
        if (!link) {
            phwangAbendS("DFabricClass::processLoginRequest", "null_link");
            phwangFree(my_name);
            response_data = generateLoginResponse(RESULT_DEF::RESULT_NULL_LINK, ajax_id_val, SIZE_DEF::FAKE_LINK_II, encoded_my_name_buf);
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
        response_data = generateLoginResponse(result_buf, ajax_id_val, SIZE_DEF::FAKE_LINK_II, encoded_my_name_buf);
        return response_data;
    }

    else {
        phwangAbendSS("DFabricClass::processLoginRequest", "unsupported_result", result_buf);
        phwangFree(my_name);
        response_data = generateLoginResponse(RESULT_DEF::RESULT_DB_ERROR, ajax_id_val, SIZE_DEF::FAKE_LINK_II, encoded_my_name_buf);
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
    char const *encoded_my_name_val)
{
    phwangDebugS(false, "DFabricClass::generateLoginResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACRL_BUF_SIZE + SIZE_DEF::FABRIC_TIME_STAMP_SIZE + strlen(encoded_my_name_val), MallocClass::generateLoginResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::LOGIN_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_II_SIZE);
    current_ptr += SIZE_DEF::LINK_II_SIZE;

    memcpy(current_ptr, this->timeStampString_, SIZE_DEF::FABRIC_TIME_STAMP_SIZE);
    current_ptr += SIZE_DEF::FABRIC_TIME_STAMP_SIZE;

    strcpy(current_ptr, encoded_my_name_val);
    return response_data;
}

char *DFabricClass::processLogoutRequest (
    LinkClass *link_val,
    char *ajax_id_val,
    char *data_val)
{
    char *response_data;
    phwangDebugSS(false, "DFabricClass::processLogoutRequest", "link_id=", link_val->linkIdIndex());

    char link_id_index_buf[SIZE_DEF::LINK_II_SIZE + 1];
    strcpy(link_id_index_buf, link_val->linkIdIndex());

    this->fabricObj_->freeLink(link_val);
    link_val = 0;

    response_data = generateLogoutResponse(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, link_id_index_buf);
    return response_data;
}

char *DFabricClass::generateLogoutResponse (
    char const *result_val,
    char *ajax_id_val,
    char const *link_id_index_val)
{
    phwangDebugS(false, "DFabricClass::generateLogoutResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACRL_BUF_SIZE, MallocClass::generateLogoutResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::LOGOUT_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_II_SIZE);
    current_ptr += SIZE_DEF::LINK_II_SIZE;

    *current_ptr = 0;
    return response_data;
}

char *DFabricClass::processGetLinkDataRequest (
    LinkClass *link_val,
    char *ajax_id_val)
{
    phwangDebugS(false, "DFabricClass::processGetLinkDataRequest", "");
    if (!link_val) {
        phwangAbendS("DFabricClass::processGetLinkDataRequest", "null link");
    }

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

    int response_data_size = FABRIC_DEF::DL_AJAX_COMMAND_SIZE + 
                             RESULT_DEF::RESULT_SIZE +
                             SIZE_DEF::LINK_II_SIZE + 
                             1 + SIZE_DEF::NAME_LIST_TAG_SIZE +
                             1 + FE_DEF::FE_GET_LINK_DATA_LENGTH_SIZE + pending_session_info2_length +
                             1 + FE_DEF::FE_GET_LINK_DATA_LENGTH_SIZE + pending_session_info3_length +
                             1 + SIZE_DEF::SESSION_II_SIZE + 1;

    char *response_data = (char *) phwangMalloc(response_data_size, MallocClass::GET_LINK_DATA);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::GET_LINK_DATA_RESPONSE;

    memcpy(current_ptr, RESULT_DEF::RESULT_SUCCEED, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_val->linkIdIndex(), SIZE_DEF::LINK_II_SIZE);
    current_ptr += SIZE_DEF::LINK_II_SIZE;

    *current_ptr++ = FE_DEF::FE_GET_LINK_DATA_TYPE_NAME_LIST;
    phwangEncodeNumber(current_ptr, this->fabricObj_->nameListObject()->nameListTag(), SIZE_DEF::NAME_LIST_TAG_SIZE);
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
                current_ptr += SIZE_DEF::SESSION_II_SIZE;

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
    char *name_list = this->fabricObj_->nameListObject()->getNameList(name_list_tag);

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

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACRL_BUF_SIZE + strlen(data_val), MallocClass::generateGetNameListResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::GET_NAME_LIST_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_II_SIZE);
    current_ptr += SIZE_DEF::LINK_II_SIZE;

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
        response_data = this->generateSetupSessionResponse(RESULT_DEF::RESULT_MALLOC_SESSION_FAIL, ajax_id_val, link_val->linkIdIndex(), SIZE_DEF::FAKE_SESSION_II, data_val);
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

    GroupClass *group = this->fabricObj_->mallocGroup(group_mode, theme_type, theme_info, first_fiddle, second_fiddle);
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

    LinkClass *second_link = this->fabricObj_->searchLinkByName(group->secondFiddle());
    if (!second_link) {
        response_data = this->generateSetupSessionResponse(RESULT_DEF::RESULT_SECOND_LINK_NOT_EXIST, ajax_id_val, link_val->linkIdIndex(), SIZE_DEF::FAKE_SESSION_II, data_val);
        return response_data;
    }

    SessionClass *second_session = second_link->mallocSession();
    if (!second_session) {
        response_data = this->generateSetupSessionResponse(RESULT_DEF::RESULT_MALLOC_SECOND_SESSION_FAIL, ajax_id_val, link_val->linkIdIndex(), SIZE_DEF::FAKE_SESSION_II, data_val);
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

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACRLS_BUF_SIZE + strlen(data_val), MallocClass::generateSetupDuet3Response);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::SETUP_SESSION_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_II_SIZE);
    current_ptr += SIZE_DEF::LINK_II_SIZE;

    memcpy(current_ptr, session_id_index_val, SIZE_DEF::SESSION_II_SIZE);
    current_ptr += SIZE_DEF::SESSION_II_SIZE;

    strcpy(current_ptr, data_val);
    return response_data;
}

void DFabricClass::sendSetupRoomRequestToThemeServer (GroupClass *group_val)
{
    char *current_ptr;
    char *uplink_data = current_ptr = (char *) phwangMalloc(FABRIC_DEF::UL_CG_BUF_SIZE + 1 + strlen(group_val->themeInfo()), MallocClass::sendSetupRoomRequestToThemeServer);

    *current_ptr++ = FT_DEF::FT_SETUP_ROOM_COMMAND;

    memcpy(current_ptr, group_val->groupIdIndex(), SIZE_DEF::GROUP_II_SIZE);
    current_ptr += SIZE_DEF::GROUP_II_SIZE;

    *current_ptr++ = group_val->themeType();

    strcpy(current_ptr, group_val->themeInfo());

    this->fabricObj_->uFabricObject()->transmitFunction(uplink_data);
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

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACRLS_BUF_SIZE + 1 + strlen(theme_info_val), MallocClass::generateSetupDuet2Response);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::SETUP_SESSION2_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_II_SIZE);
    current_ptr += SIZE_DEF::LINK_II_SIZE;

    memcpy(current_ptr, session_id_index_val, SIZE_DEF::SESSION_II_SIZE);
    current_ptr += SIZE_DEF::SESSION_II_SIZE;

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
        FABRIC_DEF::DL_ACRLS_BUF_SIZE + 4 + strlen(encoded_theme_info) + strlen(encoded_first_fiddle) + strlen(encoded_second_fiddle),
        MallocClass::sendSetupSessionResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::SETUP_SESSION3_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link->linkIdIndex(), SIZE_DEF::LINK_II_SIZE);
    current_ptr += SIZE_DEF::LINK_II_SIZE;

    memcpy(current_ptr, session_val->sessionIdIndex(), SIZE_DEF::SESSION_II_SIZE);
    current_ptr += SIZE_DEF::SESSION_II_SIZE;

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

    char session_id_buf[SIZE_DEF::SESSION_II_SIZE + 1];
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

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACRLS_BUF_SIZE, MallocClass::generateFreeSessionResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::FREE_SESSION_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_II_SIZE);
    current_ptr += SIZE_DEF::LINK_II_SIZE;

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

    response_data = this->generatePutSessionDataResponse(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, session_val->linkObject()->linkIdIndex(), session_val->sessionIdIndex());
    return response_data;
}

char *DFabricClass::generatePutSessionDataResponse (
    char const *result_val,
    char *ajax_id_val,
    char const *link_id_index_val,
    char const *session_id_index_val)
{
    phwangDebugS(false, "DFabricClass::generatePutSessionDataResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACRLS_BUF_SIZE, MallocClass::generatePutSessionDataResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::PUT_SESSION_DATA_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_II_SIZE);
    current_ptr += SIZE_DEF::LINK_II_SIZE;

    memcpy(current_ptr, session_id_index_val, SIZE_DEF::SESSION_II_SIZE);
    current_ptr += SIZE_DEF::SESSION_II_SIZE;

    *current_ptr = 0;

    return response_data;
}

void DFabricClass::sendPutSessionDataRequestToThemeServer (
    char const *room_id_val,
    char const *data_val)
{
    char *current_ptr;
    char *uplink_data = current_ptr = (char *) phwangMalloc(FABRIC_DEF::UL_CR_BUF_SIZE + strlen(data_val), MallocClass::PUT_SESSION_DATA0);

    *current_ptr++ = FT_DEF::FT_PUT_ROOM_DATA_COMMAND;

    memcpy(current_ptr, room_id_val, SIZE_DEF::ROOM_II_SIZE);
    current_ptr += SIZE_DEF::ROOM_II_SIZE;

    strcpy(current_ptr, data_val);

    this->fabricObj_->uFabricObject()->transmitFunction(uplink_data);
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

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACRLS_BUF_SIZE + strlen(data_val), MallocClass::generateGetSessionDataResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::GET_SESSION_DATA_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link_id_index_val, SIZE_DEF::LINK_II_SIZE);
    current_ptr += SIZE_DEF::LINK_II_SIZE;

    memcpy(current_ptr, session_id_index_val, SIZE_DEF::SESSION_II_SIZE);
    current_ptr += SIZE_DEF::SESSION_II_SIZE;

    strcpy(current_ptr, data_val);
    return response_data;
}

char *DFabricClass::processOpenFileRequest (
        char *ajax_id_val,
        char *data_val)
{
    char *response_data;
    phwangDebugS(true, "DFabricClass::processOpenFileRequest", data_val);

    char mode = data_val[0];

    char *encoded_file_name = &data_val[1];
    int file_name_size;
    char *file_name = phwangDecodeStringMalloc(encoded_file_name, &file_name_size);

    response_data = this->generateOpenFileResponse(RESULT_DEF::RESULT_SUCCEED, ajax_id_val);
    return response_data;
}

char *DFabricClass::generateOpenFileResponse (
    char const *result_val,
    char *ajax_id_val)
{
    phwangDebugS(false, "DFabricClass::generateOpenFileResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACRLS_BUF_SIZE, MallocClass::generateOpenFileResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::OPEN_FILE_RESPONSE;

    strcpy(current_ptr, result_val);

    return response_data;
}

char *DFabricClass::processCloseFileRequest (
        char *ajax_id_val,
        char *data_val)
{
    phwangDebugS(true, "DFabricClass::processCloseFileRequest", data_val);

}

char *DFabricClass::generateCloseFileResponse (
    char const *result_val,
    char *ajax_id_val)
{
}

char *DFabricClass::processReadFileRequest (
        char *ajax_id_val,
        char *data_val)
{
    char *response_data;
    phwangDebugS(true, "DFabricClass::processReadFileRequest", data_val);

    char *current_ptr = data_val;
    int file_name_size;
    char *file_name = phwangDecodeStringMalloc(current_ptr, &file_name_size);
    //current_ptr += file_name_size;
    phwangDebugSS(true, "DFabricClass::processReadFileRequest", "file_name=", file_name);

    char file_name_[100];
    //strcpy(file_name_, "../data_dir/customer_data_dir/dtf_dir/");
    strcpy(file_name_, FILE_DEF::DTF_DIR);
    strcat(file_name_, file_name);
    phwangDebugSS(true, "DFabricClass::processReadFileRequest", "file_name_=", file_name_);

    FileReadClass *file_class = new FileReadClass();
    int open_result = file_class->openFile(file_name_, "r");
    if (open_result == -1) {
        phwangLogitS("DFabricClass::processReadFileRequest", "cannot open file");
        phwangAbendS("DFabricClass::processReadFileRequest", "cannot open file");
    }

    char data_buf[1000];
    int eof;
    file_class->readLine(data_buf, &eof);
    phwangDebugSS(true, "DFabricClass::processReadFileRequest", "data_buf=", data_buf);

    char more;
    if (eof) {
        more = 'N';
        delete file_class;

    }
    else {
        more = 'Y';
        /////tbd;
    }

    char *result_data = data_buf;
    response_data = this->generateReadFileResponse(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, more, result_data);
    return response_data;
}

char *DFabricClass::generateReadFileResponse (
    char const *result_val,
    char *ajax_id_val,
    char more_data_exist_val,
    char const *result_data_val)
{
    phwangDebugS(false, "DFabricClass::generateReadFileResponse", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACRLS_BUF_SIZE, MallocClass::generateReadFileResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::READ_FILE_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    *current_ptr++ = more_data_exist_val;

    strcpy(current_ptr, result_data_val);

    return response_data;
}

char *DFabricClass::processWriteFileRequest (
        char *ajax_id_val,
        char *data_val)
{
    char *response_data;
    phwangDebugS(true, "DFabricClass::processWriteFileRequest", data_val);

    char *current_ptr = data_val;
    int file_name_size;
    char *file_name = phwangDecodeStringMalloc(current_ptr, &file_name_size);
    current_ptr += file_name_size;
    phwangDebugSS(true, "DFabricClass::processWriteFileRequest", "file_name=", file_name);

    char *data = current_ptr;
    phwangDebugSS(true, "DFabricClass::processWriteFileRequest", "data=", data);

    response_data = this->generateWriteFileResponse(RESULT_DEF::RESULT_SUCCEED, ajax_id_val);
    return response_data;
}

char *DFabricClass::generateWriteFileResponse (
    char const *result_val,
    char *ajax_id_val)
{
    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACRLS_BUF_SIZE, MallocClass::generateWriteFileResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::WRITE_FILE_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    *current_ptr = 0;

    return response_data;
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
    phwangDebugSS(true, "DFabricClass::generateDatagramResponse", "data_val=", data_val);

    char *encoded_data = phwangEncodeStringMalloc(data_val);
    int encoded_data_length = strlen(encoded_data);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACRL_BUF_SIZE + strlen(encoded_data), MallocClass::generateDatagramResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::MESSAGE_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    strcpy(current_ptr, encoded_data);
    //current_ptr += encoded_data_length;

    phwangFree(encoded_data);

    return response_data;
}
