/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_export.cpp
*/

#include <errno.h>
#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../../phwang_dir/file_dir/file_mgr_class.h"
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

void DFabricClass::parseData (
    void *port_obj_val,
    char *data_val)
{
    char ajax_id[SIZE_DEF::AJAX_ID_SIZE + 1];
    memcpy(ajax_id, data_val, SIZE_DEF::AJAX_ID_SIZE);
    ajax_id[SIZE_DEF::AJAX_ID_SIZE] = 0;
    char *current_ptr = data_val + SIZE_DEF::AJAX_ID_SIZE;

    if (*current_ptr == '{') {
        if (memcmp(current_ptr, this->timeStampString_, SIZE_DEF::FABRIC_TIME_STAMP_SIZE)) {
            phwangDebugSS(true, "DFabricClass::parseData", " ***time_stamp not match: data=", data_val);
            phwangAbendSS("DFabricClass::parseData", " ***time_stamp not match: data=", data_val);
            return;
        }
        current_ptr += SIZE_DEF::FABRIC_TIME_STAMP_SIZE;
    }

    char depth = current_ptr[0];
    char command = current_ptr[1];
    current_ptr += 2;

    if (command != FE_DEF::GET_LINK_DATA_COMMAND) {
        if (true && this->debugOn()) {
            int len = 50;
            if (strlen(data_val) <= len) {
                printf("DFabricClass::parseData(*) %s\n", data_val);
            }
            else {
                char data_buf[len + 1];
                memcpy(data_buf, data_val, len);
                data_buf[len] = 0;
                printf("DFabricClass::parseData(*) %s\n", data_buf);
            }
        }
    }

    LinkClass *link;
    SessionClass *session;
    char *response_data;
    switch (depth) {
        case '0':
            switch (command) {
                case FE_DEF::REGISTER_COMMAND:
                    response_data = this->parseRegister(ajax_id, current_ptr);
                    break;

                case FE_DEF::LOGIN_COMMAND:
                    response_data = this->parseLogin(ajax_id, current_ptr, 'N', port_obj_val);
                    break;

                case FE_DEF::READ_FILE_COMMAND:
                    response_data = this->parseReadFile(ajax_id, current_ptr);
                    break;

                case FE_DEF::READ_MORE_FILE_COMMAND:
                    response_data = this->parseReadMoreFile(ajax_id, current_ptr);
                    break;

                case FE_DEF::MESSAGE_COMMAND:
                    response_data = this->parseDatagram(ajax_id, current_ptr);
                    break;

                default:
                    printf("comand=%c\n", command);
                    phwangAbendS("DFabricClass::parseData_0", current_ptr);
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
                    response_data = this->parseLogout(link, ajax_id, current_ptr);
                    break;

                case FE_DEF::GET_LINK_DATA_COMMAND:
                    response_data = this->parseGetLinkData(link, ajax_id);
                    break;

                case FE_DEF::GET_NAME_LIST_COMMAND:
                    response_data = this->parseGetNameList(link, ajax_id, current_ptr);
                    break;

                case FE_DEF::SETUP_SESSION_COMMAND:
                    response_data = this->parseSetupSession(link, ajax_id, current_ptr);
                    break;

                case FE_DEF::WRITE_FILE_COMMAND:
                    response_data = this->parseWriteFile(ajax_id, current_ptr);
                    break;

                case FE_DEF::WRITE_MORE_FILE_COMMAND:
                    response_data = this->parseWriteMoreFile(ajax_id, current_ptr);
                    break;

                default:
                    phwangAbendS("DFabricClass::parseData_1", data_val);
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
                    response_data = this->parseSetupSession2(session, ajax_id, current_ptr);
                    break;

                case FE_DEF::SETUP_SESSION3_COMMAND:
                    response_data = this->parseSetupSession3(session, ajax_id, current_ptr);
                    break;

                case FE_DEF::FREE_SESSION_COMMAND:
                    response_data = this->parseFreeSession(session, ajax_id);
                    break;

                case FE_DEF::PUT_SESSION_DATA_COMMAND:
                    response_data = this->parsePutSessionData(session, ajax_id, current_ptr);
                    break;

                case FE_DEF::GET_SESSION_DATA_COMMAND:
                    response_data = this->parseGetSessionData(session, ajax_id, current_ptr);
                    break;

                default:
                    phwangAbendS("DFabricClass::parseData_2", data_val);
                    return;
            }
            break;

        default:
            phwangAbendS("DFabricClass::parseData", "bad type");
            return;
    }

    this->xmtData(port_obj_val, response_data);
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

    this->xmtData(port_object_val, response_data);
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

    this->xmtData(port_object_val, response_data);
}

char *DFabricClass::parseRegister (
    char *ajax_id_val,
    char *data_val)
{
    char *response_data;
    phwangDebugS(false, "DFabricClass::parseRegister", data_val);

    char *encoded_account_name = data_val;
    int account_name_size;
    char *account_name = phwangDecodeStringMalloc(encoded_account_name, &account_name_size);

    phwangDebugS(true, "DFabricClass::parseRegister", account_name);

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

        response_data = parseRegister_(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, account_name);

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
        response_data = parseRegister_(result_buf, ajax_id_val, account_name);
        phwangFree(account_name);
        return response_data;
    }

    else if (!strcmp(result_buf, RESULT_DEF::RESULT_DB_SELECT_FAIL)) {
        response_data = parseRegister_(result_buf, ajax_id_val, account_name);
        phwangFree(account_name);
        return response_data;
   }

    else {
        phwangAbendSS("DFabricClass::parseRegister", "unsupported_result", result_buf);
        response_data = parseRegister_(RESULT_DEF::RESULT_DB_ERROR, ajax_id_val, account_name);
        phwangFree(account_name);
        return response_data;
    }
}

char *DFabricClass::parseRegister_ (
    char const *result_val,
    char *ajax_id_val,
    char const *account_name_val)
{
    phwangDebugS(false, "DFabricClass::parseRegister_", result_val);

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

char *DFabricClass::parseLogin (
    char *ajax_id_val,
    char *data_val,
    char device_type_val,
    void *port_object_val)
{
    char *response_data;
    phwangDebugS(false, "DFabricClass::parseLogin", data_val);

    char *encoded_my_name = data_val;
    int my_name_size;
    char *my_name = phwangDecodeStringMalloc(encoded_my_name, &my_name_size);

    char encoded_my_name_buf[128];
    memcpy(encoded_my_name_buf, encoded_my_name, my_name_size);
    encoded_my_name_buf[my_name_size] = 0;
    phwangDebugSS(false, "DFabricClass::parseLogin", "my_name=", encoded_my_name_buf);

    char *encoded_password = encoded_my_name + my_name_size;
    int password_size;
    char *password = phwangDecodeStringMalloc(encoded_password, &password_size);

    phwangDebugSS(false, "DFabricClass::parseLogin", my_name, password);

    char result_buf[RESULT_DEF::RESULT_SIZE + 1];
    this->dbObject()->dbAccountObject()->checkPassword(my_name, password, result_buf);
    phwangFree(password);

    if (!strcmp(result_buf, RESULT_DEF::RESULT_PASSWORD_MATCH)) {
        LinkClass *link = this->fabricObj_->mallocLink(my_name, device_type_val, port_object_val);
        if (!link) {
            phwangAbendS("DFabricClass::parseLogin", "null_link");
            phwangFree(my_name);
            response_data = parseLogin_(RESULT_DEF::RESULT_NULL_LINK, ajax_id_val, SIZE_DEF::FAKE_LINK_II, encoded_my_name_buf);
            return response_data;
        }

        phwangFree(my_name);
        response_data = parseLogin_(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, link->linkIdIndex(), encoded_my_name_buf);
        return response_data;
    }

    else if ((!strcmp(result_buf, RESULT_DEF::RESULT_PASSWORD_NOT_MATCH)) ||
             (!strcmp(result_buf, RESULT_DEF::RESULT_ACCOUNT_NAME_NOT_EXIST)) ||
             (!strcmp(result_buf, RESULT_DEF::RESULT_DB_SELECT_FAIL))) {
        phwangFree(my_name);
        response_data = parseLogin_(result_buf, ajax_id_val, SIZE_DEF::FAKE_LINK_II, encoded_my_name_buf);
        return response_data;
    }

    else {
        phwangAbendSS("DFabricClass::parseLogin", "unsupported_result", result_buf);
        phwangFree(my_name);
        response_data = parseLogin_(RESULT_DEF::RESULT_DB_ERROR, ajax_id_val, SIZE_DEF::FAKE_LINK_II, encoded_my_name_buf);
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

char *DFabricClass::parseLogin_ (
    char const *result_val,
    char *ajax_id_val,
    char const *link_id_index_val,
    char const *encoded_my_name_val)
{
    phwangDebugS(false, "DFabricClass::parseLogin_", result_val);

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

char *DFabricClass::parseLogout (
    LinkClass *link_val,
    char *ajax_id_val,
    char *data_val)
{
    char *response_data;
    phwangDebugSS(false, "DFabricClass::parseLogout", "link_id=", link_val->linkIdIndex());

    char link_id_index_buf[SIZE_DEF::LINK_II_SIZE + 1];
    strcpy(link_id_index_buf, link_val->linkIdIndex());

    this->fabricObj_->freeLink(link_val);
    link_val = 0;

    response_data = parseLogout_(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, link_id_index_buf);
    return response_data;
}

char *DFabricClass::parseLogout_ (
    char const *result_val,
    char *ajax_id_val,
    char const *link_id_index_val)
{
    phwangDebugS(false, "DFabricClass::parseLogout_", result_val);

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

char *DFabricClass::parseGetLinkData (
    LinkClass *link_val,
    char *ajax_id_val)
{
    phwangDebugS(false, "DFabricClass::parseGetLinkData", "");
    if (!link_val) {
        phwangAbendS("DFabricClass::parseGetLinkData", "null link");
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

                phwangDebugSS(true, "DFabricClass::parseGetLinkData","p_data=", response_data);
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

        phwangDebugSS(true, "DFabricClass::parseGetLinkData", "p_session3=", response_data);

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

        phwangDebugSS(true, "DFabricClass::parseGetLinkData", "p_session3=", response_data);

        phwangFree(pending_session_info3);
    }

    return response_data;
}

char *DFabricClass::parseGetNameList (
    LinkClass *link_val,
    char *ajax_id_val,
    char *data_val)
{
    char *response_data;
    phwangDebugS(true, "DFabricClass::parseGetNameList", data_val);

    char *name_list_tag_val = data_val;
    char *end_val = name_list_tag_val + 3;

    int name_list_tag = phwangDecodeNumber(name_list_tag_val, SIZE_DEF::NAME_LIST_TAG_SIZE);
    char *name_list = this->fabricObj_->nameListObject()->getNameList(name_list_tag);

    if (!name_list) {
        phwangAbendS("DFabricClass::parseGetNameList", data_val);
    }

    response_data = parseGetNameList_(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, link_val->linkIdIndex(), name_list);
    return response_data;
}

char *DFabricClass::parseGetNameList_ (
    char const *result_val,
    char *ajax_id_val,
    char const *link_id_index_val,
    char const *data_val)
{
    phwangDebugS(false, "DFabricClass::parseGetNameList_", result_val);

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

char *DFabricClass::parseSetupSession (
    LinkClass *link_val,
    char *ajax_id_val,
    char *data_val)
{
    char *response_data = 0;
    phwangDebugSS(true, "DFabricClass::parseSetupSession", "data_val=", data_val);

    SessionClass *session = link_val->mallocSession();
    if (!session) {
        response_data = this->parseSetupSession_(RESULT_DEF::RESULT_MALLOC_SESSION_FAIL, ajax_id_val, link_val->linkIdIndex(), SIZE_DEF::FAKE_SESSION_II, data_val);
        return response_data;
    }

    char group_mode = *data_val;
    char theme_type = *(data_val + 1);

    char *encoded_theme_info = data_val + 2;
    int theme_info_size;
    char *theme_info = phwangDecodeStringMalloc(encoded_theme_info, &theme_info_size);
    phwangDebugSS(true, "DFabricClass::parseSetupSession", "theme_info=", theme_info);

    char *encoded_first_fiddle = encoded_theme_info + theme_info_size;
    int first_fiddle_size;
    char *first_fiddle = phwangDecodeStringMalloc(encoded_first_fiddle, &first_fiddle_size);
    phwangDebugSS(true, "DFabricClass::parseSetupSession", "first_fiddle=", first_fiddle);

    char *encoded_second_fiddle = encoded_first_fiddle + first_fiddle_size;
    int second_fiddle_size;
    char *second_fiddle = phwangDecodeStringMalloc(encoded_second_fiddle, &second_fiddle_size);
    phwangDebugSS(true, "DFabricClass::parseSetupSession", "second_fiddle=", second_fiddle);

    switch (theme_type) {
        case FE_DEF::FE_APP_IS_GO_GAME:
            break;

        default:
            phwangAbendS("DFabricClass::parseSetupSession", "theme_type not supported");
    }

    GroupClass *group = this->fabricObj_->mallocGroup(group_mode, theme_type, theme_info, first_fiddle, second_fiddle);
    phwangFree(theme_info);
    phwangFree(first_fiddle);
    phwangFree(second_fiddle);
    if (!group) {
        response_data = this->parseSetupSession_(RESULT_DEF::RESULT_MALLOC_GROUP_FAIL, ajax_id_val, link_val->linkIdIndex(), session->sessionIdIndex(), data_val);
        return response_data;
    }
    group->insertSession(session);
    session->bindGroup(group);

    if (group->isDominatedGroup()) {
        this->sendSetupRoomRequestToThemeServer(group);

        response_data = this->parseSetupSession_(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, link_val->linkIdIndex(), session->sessionIdIndex(), data_val);
        return response_data;
    }

    LinkClass *second_link = this->fabricObj_->searchLinkByName(group->secondFiddle());
    if (!second_link) {
        response_data = this->parseSetupSession_(RESULT_DEF::RESULT_SECOND_LINK_NOT_EXIST, ajax_id_val, link_val->linkIdIndex(), SIZE_DEF::FAKE_SESSION_II, data_val);
        return response_data;
    }

    SessionClass *second_session = second_link->mallocSession();
    if (!second_session) {
        response_data = this->parseSetupSession_(RESULT_DEF::RESULT_MALLOC_SECOND_SESSION_FAIL, ajax_id_val, link_val->linkIdIndex(), SIZE_DEF::FAKE_SESSION_II, data_val);
        return response_data;
    }

    group->insertSession(second_session);
    second_session->bindGroup(group);

    second_link->setPendingSessionSetup2(second_session->sessionIdIndex(), group->themeType(), group->themeInfo());

    response_data = this->parseSetupSession_(RESULT_DEF::RESULT_WAITING_FOR_ANSWER, ajax_id_val, link_val->linkIdIndex(), session->sessionIdIndex(), data_val);
    return response_data;
}

char *DFabricClass::parseSetupSession_ (
    char const *result_val,
    char *ajax_id_val,
    char const *link_id_index_val,
    char const *session_id_index_val,
    char const *data_val)
{
    phwangDebugS(false, "DFabricClass::parseSetupSession_", result_val);

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

    this->fabricObj_->uFabricObject()->xmtData(uplink_data);
}

char *DFabricClass::parseSetupSession2 (
    SessionClass *session_val,
    char *ajax_id_val,
    char *data_val)
{
    LinkClass *link = session_val->linkObject();
    char *response_data;
    phwangDebugSS(true, "DFabricClass::parseSetupSession2", "data_val=", data_val);
    phwangDebugSSS(true, "DFabricClass::parseSetupSession2", "id=", link->linkIdIndex(), session_val->sessionIdIndex());

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

    response_data = this->parseSetupSession2_(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, link->linkIdIndex(), session_val->sessionIdIndex(), group->themeType(), group->themeInfo());
    return response_data;
}

char *DFabricClass::parseSetupSession2_ (
    char const *result_val,
    char *ajax_id_val,
    char const *link_id_index_val,
    char const *session_id_index_val,
    char theme_type_val,
    char const *theme_info_val)
{
    phwangDebugS(false, "DFabricClass::parseSetupSession2_", result_val);

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

char *DFabricClass::parseSetupSession3 (
    SessionClass *session_val,
    char *ajax_id_val,
    char *data_val)
{
    char *response_data;

    phwangDebugSS(true, "DFabricClass::parseSetupSession3", "session_id=", session_val->sessionIdIndex());
    phwangDebugSS(true, "DFabricClass::parseSetupSession3", "data_val=", data_val);

    response_data = this->parseSetupSession3_(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, session_val);
    return response_data;
}

char *DFabricClass::parseSetupSession3_ (
    char const *result_val,
    char *ajax_id_val,
    SessionClass *session_val)
{
    phwangDebugSS(false, "DFabricClass::parseSetupSession3_", "result=", result_val);
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

    phwangDebugSS(true, "DFabricClass::parseSetupSession3_", "response_data=", response_data);

    return response_data;
}

/* free session */

char *DFabricClass::parseFreeSession (
    SessionClass *session_val,
    char *ajax_id_val)
{
    LinkClass *link = session_val->linkObject();
    char *response_data;
    phwangDebugSSS(true, "DFabricClass::parseFreeSession", "id=", link->linkIdIndex(), session_val->sessionIdIndex());

    char session_id_buf[SIZE_DEF::SESSION_II_SIZE + 1];
    strcpy(session_id_buf, session_val->sessionIdIndex());
    link->freeSession(session_val);

    response_data = this->parseFreeSession_(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, link->linkIdIndex(), session_id_buf);
    return response_data;
}

char *DFabricClass::parseFreeSession_ (
    char const *result_val,
    char *ajax_id_val,
    char const *link_id_index_val,
    char const *session_id_index_val)
{
    phwangDebugS(false, "DFabricClass::parseFreeSession_", result_val);

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

char *DFabricClass::parsePutSessionData (
    SessionClass *session_val,
    char *ajax_id_val,
    char *data_val)
{
    char *response_data;
    phwangDebugS(true, "DFabricClass::parsePutSessionData", data_val);

    char *room_id = session_val->groupObject()->roomIdIndex();
    if (!room_id) {
        response_data = this->parsePutSessionData_(RESULT_DEF::RESULT_NULL_ROOM, ajax_id_val, session_val->linkObject()->linkIdIndex(), session_val->sessionIdIndex());
        return response_data;
    }

    this->sendPutSessionDataRequestToThemeServer(room_id, data_val);

    response_data = this->parsePutSessionData_(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, session_val->linkObject()->linkIdIndex(), session_val->sessionIdIndex());
    return response_data;
}

char *DFabricClass::parsePutSessionData_ (
    char const *result_val,
    char *ajax_id_val,
    char const *link_id_index_val,
    char const *session_id_index_val)
{
    phwangDebugS(false, "DFabricClass::parsePutSessionData_", result_val);

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

    this->fabricObj_->uFabricObject()->xmtData(uplink_data);
}

/* get session data */

char *DFabricClass::parseGetSessionData (
    SessionClass *session_val,
    char *ajax_id_val,
    char *data_val)
{
    char *data = session_val->dequeuePendingData();
    if (data) {
        return this->parseGetSessionData_(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, session_val->linkObject()->linkIdIndex(), session_val->sessionIdIndex(), data);
    }
    else {
        return this->parseGetSessionData_(RESULT_DEF::RESULT_SESSION_DATA_NOT_AVAILABLE, ajax_id_val, session_val->linkObject()->linkIdIndex(), session_val->sessionIdIndex(), "");
    }
}

char *DFabricClass::parseGetSessionData_ (
    char const *result_val,
    char *ajax_id_val,
    char const *link_id_index_val,
    char const *session_id_index_val,
    char const *data_val)
{
    phwangDebugS(false, "DFabricClass::parseGetSessionData_", result_val);

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

char *DFabricClass::parseReadFile (
        char *ajax_id_val,
        char *data_val)
{
    char *response_data;

    if (false && this->debugOn()) {
        printf("DFabricClass::parseReadFile() data=%s\n", data_val);
    }

    char *current_ptr = data_val;
    int file_name_size;
    char *file_name = phwangDecodeStringMalloc(current_ptr, &file_name_size);
    //current_ptr += file_name_size;
    phwangDebugSS(true, "DFabricClass::parseReadFile", "file_name=", file_name);

    char file_name_buf[FileMgrClass::MAX_FILE_NAME_SIZE + 1];
    if (strlen(FILE_DEF::DTF_DIR) + strlen(file_name) <= FileMgrClass::MAX_FILE_NAME_SIZE) {
        strcpy(file_name_buf, FILE_DEF::DTF_DIR);
        strcat(file_name_buf, file_name);
        //phwangDebugSS(true, "DFabricClass::parseReadFile", "file_name_buf=", file_name_buf);
    }
    else {
        phwangAbendSS("DFabricClass::parseReadFile", "file_name too long", file_name);
    }
    phwangFree(file_name);

    char data_buf[FileMgrClass::MAX_FILE_IO_BUF_SIZE + 1];
    int eof;
    int fd;
    int length = this->fileMgrObj()->readBytesOpen(file_name_buf, data_buf, FileMgrClass::MAX_FILE_IO_BUF_SIZE, &eof, &fd);

    if (false && this->debugOn()) {
        printf("DFabricClass::parseReadFile() length=%d %d data=%s\n", length, strlen(data_buf), data_buf);
    }

    char *result_data = data_buf;
    response_data = this->parseReadFile_(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, eof ? 'N' : 'Y', fd, result_data);
    return response_data;
}

char *DFabricClass::parseReadFile_ (
    char const *result_val,
    char *ajax_id_val,
    char more_data_exist_val,
    int fd_val,
    char const *result_data_val)
{
    phwangDebugS(false, "DFabricClass::parseReadFile_", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACR_BUF_SIZE + 1 + FileMgrClass::FD_LEN_SIZE + strlen(result_data_val), MallocClass::generateReadFileResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::READ_FILE_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    *current_ptr++ = more_data_exist_val;

    if (more_data_exist_val == 'Y') {
        phwangEncodeNumber(current_ptr, fd_val, FileMgrClass::FD_LEN_SIZE);
        current_ptr += FileMgrClass::FD_LEN_SIZE;
    }

    strcpy(current_ptr, result_data_val);

    return response_data;
}

char *DFabricClass::parseReadMoreFile (
        char *ajax_id_val,
        char *data_val)
{
    char *response_data;
    phwangDebugS(true, "DFabricClass::parseReadMoreFile", data_val);

    char *current_ptr = data_val;

    int fd = phwangDecodeNumber(current_ptr, FileMgrClass::FD_LEN_SIZE);
    current_ptr += FileMgrClass::FD_LEN_SIZE;

    printf("DFabricClass::parseReadMoreFile() fd=%d\n", fd);

    char data_buf[FileMgrClass::MAX_FILE_IO_BUF_SIZE + 1];
    int eof;
    int length = this->fileMgrObj()->readBytesMore(fd, data_buf, FileMgrClass::MAX_FILE_IO_BUF_SIZE, &eof);

    char *result_data = data_buf;
    response_data = this->parseReadMoreFile_(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, eof ? 'N' : 'Y', fd, result_data);
    return response_data;
}

char *DFabricClass::parseReadMoreFile_ (
    char const *result_val,
    char *ajax_id_val,
    char more_data_exist_val,
    int fd_val,
    char const *result_data_val)
{
    phwangDebugS(false, "DFabricClass::parseReadMoreFile_", result_val);

    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACR_BUF_SIZE + 1 + FileMgrClass::FD_LEN_SIZE + strlen(result_data_val), MallocClass::generateReadMoreFileResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::READ_MORE_FILE_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    *current_ptr++ = more_data_exist_val;

    if (more_data_exist_val == 'Y') {
        phwangEncodeNumber(current_ptr, fd_val, FileMgrClass::FD_LEN_SIZE);
        current_ptr += FileMgrClass::FD_LEN_SIZE;
    }

    strcpy(current_ptr, result_data_val);

    phwangDebugSS(false, "DFabricClass::parseReadMoreFile_", "response_data=", response_data);

    return response_data;
}

char *DFabricClass::parseWriteFile (
        char *ajax_id_val,
        char *data_val)
{
    char *response_data;
    if (false && this->debugOn()) {
        printf("DFabricClass::parseWriteFile() data=%s\n", data_val);
    }

    char *current_ptr = data_val;
    int file_name_size;
    char *file_name = phwangDecodeStringMalloc(current_ptr, &file_name_size);
    current_ptr += file_name_size;
    phwangDebugSS(true, "DFabricClass::parseWriteFile", "file_name=", file_name);

    char file_name_buf[FileMgrClass::MAX_FILE_NAME_SIZE + 1];
    if (strlen(FILE_DEF::DTF_DIR) + strlen(file_name) <= FileMgrClass::MAX_FILE_NAME_SIZE) {
        strcpy(file_name_buf, FILE_DEF::DTF_DIR);
        strcat(file_name_buf, file_name);
        //phwangDebugSS(true, "DFabricClass::parseWriteFile", "file_name_buf=", file_name_buf);
    }
    else {
        phwangAbendSS("DFabricClass::parseWriteFile", "file_name too long", file_name);
    }
    phwangFree(file_name);

    char eof = *current_ptr++;

    char *data = current_ptr;

    if (false && this->debugOn()) {
        printf("DFabricClass::parseWriteFile() eof=%c data=%s\n", eof, data);
    }

    int fd;
    this->fileMgrObj()->writeBytesOpen(file_name_buf, eof, data, &fd);

    response_data = this->parseWriteFile_(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, fd);
    return response_data;
}

char *DFabricClass::parseWriteFile_ (
    char const *result_val,
    char *ajax_id_val,
    int fd_val)
{
    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACRLS_BUF_SIZE, MallocClass::generateWriteFileResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::WRITE_FILE_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    phwangEncodeNumber(current_ptr, fd_val, FileMgrClass::FD_LEN_SIZE);
    current_ptr += FileMgrClass::FD_LEN_SIZE;

    *current_ptr = 0;

    return response_data;
}

char *DFabricClass::parseWriteMoreFile (
        char *ajax_id_val,
        char *data_val)
{
    char *response_data;
    if (false && this->debugOn()) {
        printf("DFabricClass::parseWriteMoreFile() data=%s\n", data_val);
    }

    char *current_ptr = data_val;

    int fd = phwangDecodeNumber(current_ptr, FileMgrClass::FD_LEN_SIZE);
    current_ptr += FileMgrClass::FD_LEN_SIZE;

    char eof = *current_ptr++;

    char *data = current_ptr;

    if (true && this->debugOn()) {
        printf("DFabricClass::parseWriteMoreFile() fd=%d eof=%c\n", fd, eof);
    }

    this->fileMgrObj()->writeBytesMore(fd, eof, data);

    response_data = this->parseWriteMoreFile_(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, fd);
    return response_data;
}

char *DFabricClass::parseWriteMoreFile_ (
    char const *result_val,
    char *ajax_id_val,
    int fd_val)
{
    char *response_data = (char *) phwangMalloc(FABRIC_DEF::DL_ACRLS_BUF_SIZE, MallocClass::generateWriteMoreFileResponse);
    char *current_ptr = response_data;

    memcpy(current_ptr, ajax_id_val, SIZE_DEF::AJAX_ID_SIZE);
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    *current_ptr++ = FE_DEF::WRITE_MORE_FILE_RESPONSE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    phwangEncodeNumber(current_ptr, fd_val, FileMgrClass::FD_LEN_SIZE);
    current_ptr += FileMgrClass::FD_LEN_SIZE;

    *current_ptr = 0;

    return response_data;
}

char *DFabricClass::parseDatagram (
    char *ajax_id_val,
    char *input_data_val)
{
    char *response_data;
    phwangDebugS(true, "DFabricClass::parseDatagram", input_data_val);

    char act = *input_data_val++;

    char *encoded_data = input_data_val;
    int data_size;
    char *data = phwangDecodeStringMalloc(encoded_data, &data_size);
    char const *output_data;

    if (1) { /* debug */
        char buf[256];
        sprintf(buf, "act=%c data=%s\n", act, data);
        phwangDebugS(true, "DFabricClass::parseDatagram", buf);
    }


    switch (act) {
        case 'I':
            this->messengerObject()->initMessenger();
            output_data = "I_data";
            break;

        case 'R':
            output_data = this->messengerObject()->getMessage();
            phwangDebugS(true, "DFabricClass::parseDatagram", output_data);
            break;

        case 'W':
            output_data = "W_data";
            this->messengerObject()->putMessage(0);
            break;

        default:
            break;
    }
    response_data = parseDatagram_(RESULT_DEF::RESULT_SUCCEED, ajax_id_val, output_data);
    return response_data;
}

char *DFabricClass::parseDatagram_ (
    char const *result_val,
    char *ajax_id_val,
    char const *data_val)
{
    phwangDebugSS(true, "DFabricClass::parseDatagram_", "data_val=", data_val);

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
