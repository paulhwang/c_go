/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../define_dir/fe_def.h"
#include "../../define_dir/ft_def.h"
#include "../../define_dir/fabric_def.h"
#include "../../define_dir/result_def.h"
#include "u_fabric_class.h"
#include "../fabric_class.h"
#include "../d_fabric_dir/d_fabric_class.h"
#include "../link_class.h"
#include "../session_class.h"
#include "../group_class.h"

void UFabricClass::exportedParseFunction (char *data_val)
{
    phwangDebugS(true, "UFabricClass::exportedParseFunction", data_val);

    switch (*data_val) {
        case FT_DEF::FT_SETUP_ROOM_RESPONSE:
            this->processSetupRoomResponse(data_val + 1);
            return;

        case FT_DEF::FT_PUT_ROOM_DATA_RESPONSE:
            this->processPutRoomDataResponse(data_val + 1);
            return;

        default:
            phwangAbendS("UFabricClass::exportedParseFunction", data_val);
            return;
    }
}

void UFabricClass::processSetupRoomResponse (char *data_val)
{
    phwangDebugS(true, "UFabricClass::processSetupRoomResponse", data_val);

    char *current_ptr;
    char result_buf[RESULT_DEF::RESULT_SIZE + 1];
    memcpy(result_buf, data_val, RESULT_DEF::RESULT_SIZE);
    result_buf[RESULT_DEF::RESULT_SIZE] = 0;
    current_ptr = data_val + RESULT_DEF::RESULT_SIZE;

    char *group_id_index = current_ptr;
    char group_id_buf[SIZE_DEF::GROUP_ID_INDEX_SIZE + 1];
    memcpy(group_id_buf, data_val, SIZE_DEF::GROUP_ID_INDEX_SIZE);
    group_id_buf[SIZE_DEF::GROUP_ID_INDEX_SIZE] = 0;
    current_ptr += SIZE_DEF::GROUP_ID_INDEX_SIZE;

    char *room_id_ptr = current_ptr;

    GroupClass *group = this->theFabricObject->searchGroup(group_id_index);
    if (!group) {
        phwangAbendS("UFabricClass::processSetupRoomResponse", "null_group");
        return;
    }
    group->setRoomStatusToReady();

    int session_array_size;
    group->setRoomIdIndex(room_id_ptr);
    group->setSessionTableArray((SessionClass **) phwangArrayMgrGetArrayTable(group->sessionArrayMgr(), &session_array_size));
    for (int i = 0; i < session_array_size; i++) {
        SessionClass *session = group->sessionTableArray(0);
        if ( (group->mode() == FE_DEF::FE_GROUP_MODE_SOLO) ||
            ((group->mode() == FE_DEF::FE_GROUP_MODE_DUET) && (!strcmp(group->firstFiddle(), group->secondFiddle()))) ||
             (group->mode() == FE_DEF::FE_GROUP_MODE_ENSEMBLE)) {
            phwangDebugS(true, "UFabricClass::processSetupRoomResponse", "match");
            this->sendSetupSessioResponse(session, group, result_buf);
        }

        session->linkObject()->setPendingSessionSetup3(session->sessionIdIndex(), "");
    }
}

void UFabricClass::sendSetupSessioResponse (
    SessionClass *session_val,
    GroupClass *group_val,
    char const *result_val)
{
    phwangDebugSS(false, "UFabricClass::sendSetupSessioResponse", "result=", result_val);
    LinkClass *link = session_val->linkObject();

    char *encoded_theme_info    = phwangEncodeStringMalloc(group_val->themeInfo());
    char *encoded_first_fiddle  = phwangEncodeStringMalloc(group_val->firstFiddle());
    char *encoded_second_fiddle = "";
    if (group_val->mode() == FE_DEF::FE_GROUP_MODE_DUET) {
        encoded_second_fiddle = phwangEncodeStringMalloc(group_val->secondFiddle());
    }

    char *response_data = (char *) phwangMalloc(
        FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE + 5 + strlen(encoded_theme_info) + strlen(encoded_first_fiddle) + strlen(encoded_second_fiddle),
        MallocClass::generateSetupSessionSucceedResponse);
    char *current_ptr = &response_data[FE_DEF::FE_COMMAND_SIZE];

    switch (link->deviceType()) {
        case 'N':
            memcpy(current_ptr, "+++" /*ajax_id_val*/, SIZE_DEF::AJAX_ID_SIZE);
            break;

        case 'A':
            memcpy(current_ptr, "***", SIZE_DEF::AJAX_ID_SIZE);
            break;
        default:
            break;
    }
    current_ptr += SIZE_DEF::AJAX_ID_SIZE;

    memcpy(current_ptr, result_val, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, link->linkIdIndex(), SIZE_DEF::LINK_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::LINK_ID_INDEX_SIZE;

    memcpy(current_ptr, session_val->sessionIdIndex(), SIZE_DEF::SESSION_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::SESSION_ID_INDEX_SIZE;

    *current_ptr++ = group_val->roomStatus();
    *current_ptr++ = group_val->mode();

    memcpy(current_ptr, encoded_theme_info, strlen(encoded_theme_info));
    current_ptr += strlen(encoded_theme_info);

    memcpy(current_ptr, encoded_first_fiddle, strlen(encoded_first_fiddle));
    current_ptr += strlen(encoded_first_fiddle);

    if (group_val->mode() == FE_DEF::FE_GROUP_MODE_DUET) {
        memcpy(current_ptr, encoded_second_fiddle, strlen(encoded_second_fiddle));
        current_ptr += strlen(encoded_second_fiddle);
    }

    *current_ptr = 0;

    phwangFree(encoded_theme_info);
    phwangFree(encoded_first_fiddle);
    if (strlen(encoded_second_fiddle)) {
        phwangFree(encoded_second_fiddle);
    }

    phwangDebugSS(true, "UFabricClass::sendSetupSessioResponse", "response_data=", response_data);

    //this->fabricObject()->dFabricObject()->transmitFunction(link->portObject(), response_data);
}

void UFabricClass::processPutRoomDataResponse (char *data_val)
{
    phwangDebugS(true, "UFabricClass::processPutRoomDataResponse", data_val);

    char result_buf[RESULT_DEF::RESULT_SIZE + 1];
    memcpy(result_buf, data_val, RESULT_DEF::RESULT_SIZE);
    result_buf[RESULT_DEF::RESULT_SIZE] = 0;
    char *current_ptr = data_val + RESULT_DEF::RESULT_SIZE;

    char *group_id_ptr = current_ptr;
    current_ptr += SIZE_DEF::GROUP_ID_INDEX_SIZE;

    char *rest_data = current_ptr;

    GroupClass *group = this->theFabricObject->searchGroup(group_id_ptr);
    if (!group) {
        phwangAbendS("UFabricClass::processPutRoomDataResponse", "null_group");
        return;
    }

    int session_array_size;
    group->setSessionTableArray((SessionClass **) phwangArrayMgrGetArrayTable(group->sessionArrayMgr(), &session_array_size));
    for (int i = 0; i < session_array_size; i++) {
        SessionClass *session = group->sessionTableArray(i);
        if (session) {
            session->enqueuePendingDownLinkData(rest_data);
        }
    }
}
