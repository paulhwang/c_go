/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_parse.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../protocol_dir/ft_command_class.h"
#include "../../protocol_dir/te_command_class.h"
#include "../../protocol_dir/room_mgr_protocol.h"
#include "d_theme_class.h"
#include "../theme_class.h"
#include "../u_theme_dir/u_theme_class.h"
#include "../room_class.h"

void DThemeClass::exportedParseFunction (char *data_val)
{
    phwangDebugS(true, "DThemeClass::exportedParseFunction", data_val);

    switch (*data_val) {
        case FT_Command_Class::SETUP_ROOM_COMMAND:
            this->processSetupRoom(data_val + 1);
            return;

        case FT_Command_Class::PUT_ROOM_DATA_COMMAND:
            this->processPutRoomData(data_val + 1);
            return;

        default:
            phwangAbendS("DThemeClass::exportedParseFunction", data_val);
            return;
    }
}

void DThemeClass::processSetupRoom (char *data_val)
{
    phwangDebugS(true, "DThemeClass::processSetupRoom", data_val);

    char *group_id_index_val = data_val;

    char *downlink_data;
    char *uplink_data;
    char *data_ptr;

    RoomClass *room = this->theThemeObject->mallocRoom(group_id_index_val);
    if (!room) {
        phwangAbendS("DThemeClass::processSetupRoom", "null room");
        downlink_data = data_ptr = (char *) phwangMalloc(ROOM_MGR_DATA_BUFFER_SIZE + 4, MallocClass::DTHEME_SETUP_ROOM1);
        *data_ptr++ = FT_Command_Class::SETUP_ROOM_RESPONSE;
        strcpy(data_ptr, "null room");
        this->transmitFunction(downlink_data);
        return;
    }
    data_val += GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE;

    uplink_data = data_ptr = (char *) phwangMalloc(ROOM_MGR_DATA_BUFFER_SIZE + 4, MallocClass::DTHEME_SETUP_ROOM2);
    *data_ptr++ = TE_Command_Class::SETUP_BASE_COMMAND;

    memcpy(data_ptr, room->roomIdIndex(), ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    data_ptr += ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE;

    strcpy(data_ptr, data_val);
    this->theThemeObject->uThemeObject()->transmitFunction(uplink_data);
}

void DThemeClass::processPutRoomData (char *data_val)
{
    char *downlink_data;
    char *uplink_data;
    char *data_ptr;

    phwangDebugS(true, "DThemeClass::processPutRoomData", data_val);

    RoomClass *room = this->theThemeObject->searchRoom(data_val);
    if (!room) {
        phwangAbendS("DThemeClass::processPutRoomData", "null room");
        downlink_data = data_ptr = (char *) phwangMalloc(ROOM_MGR_DATA_BUFFER_SIZE + 4, MallocClass::DTHEME_PUT_ROOM_DATA1);
        *data_ptr++ = FT_Command_Class::PUT_ROOM_DATA_RESPONSE;
        strcpy(data_ptr, "null room");
        this->transmitFunction(downlink_data);
        return;
    }

    uplink_data = data_ptr = (char *) phwangMalloc(ROOM_MGR_DATA_BUFFER_SIZE + 4, MallocClass::DTHEME_PUT_ROOM_DATA2);
    *data_ptr++ = TE_Command_Class::PUT_BASE_DATA_COMMAND;
    memcpy(data_ptr, room->baseIdIndex(), BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE);
    data_ptr += BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE;
    strcpy(data_ptr, data_val + ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    this->theThemeObject->uThemeObject()->transmitFunction(uplink_data);
}
