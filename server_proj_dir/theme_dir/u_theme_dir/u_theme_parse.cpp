/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_theme_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../protocol_dir/theme_engine_protocol.h"
#include "../../protocol_dir/fabric_theme_protocol.h"
#include "../../protocol_dir/room_mgr_protocol.h"
#include "../../protocol_dir/group_mgr_protocol.h"
#include "u_theme_class.h"
#include "../theme_class.h"
#include "../d_theme_dir/d_theme_class.h"
#include "../room_class.h"

void UThemeClass::exportedParseFunction (char *data_val)
{
    if (1) { /* debug */
        phwangLogitS("UThemeClass::exportedParseFunction", data_val);
    }

    if (*data_val == THEME_ENGINE_PROTOCOL_RESPOND_IS_SETUP_BASE) {
        this->processSetupBaseResponse(data_val + 1);
        return;
    }

    if (*data_val == THEME_ENGINE_PROTOCOL_RESPOND_IS_PUT_BASE_DATA) {
        this->processPutBaseDataResponse(data_val + 1);
        return;
    }

    phwangAbend("UThemeClass::exportedParseFunction", data_val);
}

void UThemeClass::processSetupBaseResponse (char *data_val)
{
    if (1) { /* debug */
        phwangLogitS("UThemeClass::processSetupBaseResponse", data_val);
    }

    char *room_id_index_val = data_val;

    char *downlink_data;
    char *data_ptr;
    int group_array_size;

    RoomClass *room = this->theThemeObject->searchRoom(room_id_index_val);
    if (!room) {
        phwangAbendS("UThemeClass::processSetupBaseResponse", "null room");
        return;
    }

    data_val += ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE;
    room->setBaseIdIndex(data_val);

    downlink_data = data_ptr = (char *) phwangMalloc(ROOM_MGR_DATA_BUFFER_SIZE + 4, MallocClass::UTHEME_BASE);
    *data_ptr++ = FABRIC_THEME_PROTOCOL_RESPOND_IS_SETUP_ROOM;

    room->setGroupTableArray((char **) phwangArrayMgrGetArrayTable(room->groupArrayMgr(), &group_array_size));
    memcpy(data_ptr, room->groupTableArray(0), GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE);
    data_ptr += GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE;

    memcpy(data_ptr, room->roomIdIndex(), ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    data_ptr += ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE;
    *data_ptr = 0;
    this->theThemeObject->dThemeObject()->transmitFunction(downlink_data);
}

void UThemeClass::processPutBaseDataResponse (char *data_val)
{
    char *downlink_data;
    char *data_ptr;
    int group_array_size;

    if (0) { /* debug */
        phwangLogitS("UThemeClass::processPutBaseDataResponse", data_val);
    }

    RoomClass *room = this->theThemeObject->searchRoom(data_val);
    if (!room) {
        phwangAbendS("UThemeClass::processPutBaseDataResponse", "null room");
        return;
    }
    data_val += ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE;

    room->setGroupTableArray((char **) phwangArrayMgrGetArrayTable(room->groupArrayMgr(), &group_array_size));
    for (int i = 0; i < group_array_size; i++) {
        if (room->groupTableArray(i)) {
            downlink_data = data_ptr = (char *) phwangMalloc(ROOM_MGR_DATA_BUFFER_SIZE + 4, MallocClass::UTHEME_BASE_PUT_BASE_DATA);
            *data_ptr++ = FABRIC_THEME_PROTOCOL_RESPOND_IS_PUT_ROOM_DATA;
            memcpy(data_ptr, room->groupTableArray(i), GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE);
            data_ptr += GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE;
            strcpy(data_ptr, data_val);
            this->theThemeObject->dThemeObject()->transmitFunction(downlink_data);
        }
    }
}
