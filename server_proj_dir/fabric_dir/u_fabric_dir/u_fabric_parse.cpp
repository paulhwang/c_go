/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../define_dir/fe_command_define.h"
#include "../../define_dir/ft_command_define.h"
#include "u_fabric_class.h"
#include "../fabric_class.h"
#include "../link_class.h"
#include "../session_class.h"
#include "../group_class.h"

void UFabricClass::exportedParseFunction (char *data_val)
{
    phwangDebugS(true, "UFabricClass::exportedParseFunction", data_val);

    switch (*data_val) {
        case FT_CommandClass::SETUP_ROOM_RESPONSE:
            this->processSetupRoomResponse(data_val + 1);
            return;

        case FT_CommandClass::PUT_ROOM_DATA_RESPONSE:
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
    char result_buf[FE_CommandClass::FE_RESULT_SIZE + 1];
    memcpy(result_buf, data_val, FE_CommandClass::FE_RESULT_SIZE);
    result_buf[FE_CommandClass::FE_RESULT_SIZE] = 0;
    current_ptr = data_val + FE_CommandClass::FE_RESULT_SIZE;

    char *group_id_index = current_ptr;
    char group_id_buf[FT_CommandClass::GROUP_ID_INDEX_SIZE + 1];
    memcpy(group_id_buf, data_val, FT_CommandClass::GROUP_ID_INDEX_SIZE);
    group_id_buf[FT_CommandClass::GROUP_ID_INDEX_SIZE] = 0;
    current_ptr += FT_CommandClass::GROUP_ID_INDEX_SIZE;

    char *room_id_ptr = current_ptr;

    GroupClass *group = this->theFabricObject->searchGroup(group_id_index);
    if (!group) {
        phwangAbendS("UFabricClass::processSetupRoomResponse", "null_group");
        return;
    }

    int session_array_size;
    group->setRoomIdIndex(room_id_ptr);
    group->setSessionTableArray((SessionClass **) phwangArrayMgrGetArrayTable(group->sessionArrayMgr(), &session_array_size));
    for (int i = 0; i < session_array_size; i++) {
        SessionClass *session = group->sessionTableArray(0);
        session->linkObject()->setPendingSessionSetup3(session->sessionIdIndex(), "");
    }
}

void UFabricClass::processPutRoomDataResponse (char *data_val)
{
    phwangDebugS(true, "UFabricClass::processPutRoomDataResponse", data_val);

    char result_buf[FE_CommandClass::FE_RESULT_SIZE + 1];
    memcpy(result_buf, data_val, FE_CommandClass::FE_RESULT_SIZE);
    result_buf[FE_CommandClass::FE_RESULT_SIZE] = 0;
    char *current_ptr = data_val + FE_CommandClass::FE_RESULT_SIZE;
    current_ptr = data_val;//////////////////

    char *group_id_ptr = current_ptr;
    current_ptr += FT_CommandClass::GROUP_ID_INDEX_SIZE;

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
