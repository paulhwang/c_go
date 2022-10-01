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
        this->sendSetupSessioResponse(session, group, RESULT_DEF::RESULT_SUCCEED);

        session->linkObject()->setPendingSessionSetup3(session->sessionIdIndex(), "");
    }
}

char *UFabricClass::sendSetupSessioResponse (
        SessionClass *session_val,
        GroupClass *group_val,
        char const *result_val)
{
    phwangDebugSS(false, "DFabricClass::generateSetupSessioResponse", "result=", result_val);
    LinkClass *link = session_val->linkObject();

    char *encoded_theme_info     = phwangEncodeStringMalloc(group_val->themeInfo());
    char *encoded_initiator_name = phwangEncodeStringMalloc(group_val->initiatorName());
    char *encoded_peer_name      = phwangEncodeStringMalloc(group_val->peerName());

    char *response_data = (char *) phwangMalloc(
        FABRIC_DEF::FE_DL_BUF_WITH_LINK_SESSION_SIZE + 5 + strlen(encoded_theme_info) + strlen(encoded_initiator_name) + strlen(encoded_peer_name),
        MallocClass::generateSetupSessionSucceedResponse);
    char *current_ptr = &response_data[FABRIC_DEF::FE_DL_COMMAND_AJAX_SIZE];

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

    memcpy(current_ptr, encoded_initiator_name, strlen(encoded_initiator_name));
    current_ptr += strlen(encoded_initiator_name);

    memcpy(current_ptr, encoded_peer_name, strlen(encoded_peer_name));
    current_ptr += strlen(encoded_peer_name);

    *current_ptr = 0;

    phwangFree(encoded_theme_info);
    phwangFree(encoded_initiator_name);
    phwangFree(encoded_peer_name);

    return response_data;
    switch (link->deviceType()) {
        case 'N':
            memcpy(&response_data[1], "000" /*ajax_id_val*/, SIZE_DEF::AJAX_ID_SIZE);
            break;

        case 'A':
            memcpy(&response_data[1], "***", SIZE_DEF::AJAX_ID_SIZE);
            break;
        default:
            break;
    }
    //this->fabricObject()->dFabricObject()->transmitFunction(0 /*port_object_val*/, response_data);
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
