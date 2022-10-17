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

    char result_buf[RESULT_DEF::RESULT_SIZE + 1];
    memcpy(result_buf, data_val, RESULT_DEF::RESULT_SIZE);
    result_buf[RESULT_DEF::RESULT_SIZE] = 0;
    char *current_ptr = data_val + RESULT_DEF::RESULT_SIZE;

    char *group_id_index = current_ptr;
    char group_id_buf[SIZE_DEF::GROUP_II_SIZE + 1];
    memcpy(group_id_buf, data_val, SIZE_DEF::GROUP_II_SIZE);
    group_id_buf[SIZE_DEF::GROUP_II_SIZE] = 0;
    current_ptr += SIZE_DEF::GROUP_II_SIZE;

    char *room_id_ptr = current_ptr;

    GroupClass *group = this->fabricObject_->searchGroup(group_id_index);
    if (!group) {
        phwangAbendS("UFabricClass::processSetupRoomResponse", "null_group");
        return;
    }
    group->setRoomStatusToReady();

    int session_array_size;
    group->setRoomIdIndex(room_id_ptr);
    group->setSessionTableArray((SessionClass **) phwangArrayMgrGetArrayTable(group->sessionArrayMgr(), &session_array_size));
    for (int i = 0; i < session_array_size; i++) {
        SessionClass *session = group->sessionTableArray(i);
        session->linkObject()->setPendingSessionSetup3(session->sessionIdIndex());
    }
}

void UFabricClass::processPutRoomDataResponse (char *data_val)
{
    phwangDebugS(true, "UFabricClass::processPutRoomDataResponse", data_val);

    char result_buf[RESULT_DEF::RESULT_SIZE + 1];
    memcpy(result_buf, data_val, RESULT_DEF::RESULT_SIZE);
    result_buf[RESULT_DEF::RESULT_SIZE] = 0;
    char *current_ptr = data_val + RESULT_DEF::RESULT_SIZE;

    char *group_id_ptr = current_ptr;
    current_ptr += SIZE_DEF::GROUP_II_SIZE;

    char *rest_data = current_ptr;

    GroupClass *group = this->fabricObject_->searchGroup(group_id_ptr);
    if (!group) {
        phwangAbendS("UFabricClass::processPutRoomDataResponse", "null_group");
        return;
    }

    int session_array_size;
    group->setSessionTableArray((SessionClass **) phwangArrayMgrGetArrayTable(group->sessionArrayMgr(), &session_array_size));
    for (int i = 0; i < session_array_size; i++) {
        SessionClass *session = group->sessionTableArray(i);
        if (session) {
            session->enqueuePendingData(rest_data);
        }
    }
}
