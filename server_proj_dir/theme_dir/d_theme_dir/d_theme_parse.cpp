/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_parse.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../protocol_dir/fabric_theme_protocol.h"
#include "../../protocol_dir/theme_engine_protocol.h"
#include "../../protocol_dir/room_mgr_protocol.h"
#include "d_theme_class.h"
#include "../theme_class.h"
#include "../u_theme_dir/u_theme_class.h"
#include "../room_class.h"

void DThemeClass::exportedParseFunction (char *data_val)
{
    if (1) { /* debug */
        this->logit("exportedParseFunction", data_val);
    }

    if (*data_val == FABRIC_THEME_PROTOCOL_COMMAND_IS_SETUP_ROOM) {
        this->processSetupRoom(data_val + 1);
        return;
    }

    if (*data_val == FABRIC_THEME_PROTOCOL_COMMAND_IS_PUT_ROOM_DATA) {
        this->processPutRoomData(data_val + 1);
        return;
    }

    this->abend("exportedParseFunction", data_val);
}

void DThemeClass::processSetupRoom (char *data_val)
{
    this->debug(true, "processSetupRoom", data_val);

    char *group_id_index_val = data_val;

    char *downlink_data;
    char *uplink_data;
    char *data_ptr;

    RoomClass *room = this->theThemeObject->mallocRoom(group_id_index_val);
    if (!room) {
        this->abend("processSetupRoom", "null room");
        downlink_data = data_ptr = (char *) phwangMalloc1(ROOM_MGR_DATA_BUFFER_SIZE + 4, MallocClass::DTHEME_SETUP_ROOM1);
        *data_ptr++ = FABRIC_THEME_PROTOCOL_RESPOND_IS_SETUP_ROOM;
        strcpy(data_ptr, "null room");
        this->transmitFunction(downlink_data);
        return;
    }
    data_val += GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE;

    uplink_data = data_ptr = (char *) phwangMalloc1(ROOM_MGR_DATA_BUFFER_SIZE + 4, MallocClass::DTHEME_SETUP_ROOM2);
    *data_ptr++ = THEME_ENGINE_PROTOCOL_COMMAND_IS_SETUP_BASE;

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

    this->debug(true, "processPutRoomData", data_val);

    RoomClass *room = this->theThemeObject->searchRoom(data_val);
    if (!room) {
        this->abend("processPutRoomData", "null room");
        downlink_data = data_ptr = (char *) phwangMalloc1(ROOM_MGR_DATA_BUFFER_SIZE + 4, MallocClass::DTHEME_PUT_ROOM_DATA1);
        *data_ptr++ = FABRIC_THEME_PROTOCOL_RESPOND_IS_PUT_ROOM_DATA;
        strcpy(data_ptr, "null room");
        this->transmitFunction(downlink_data);
        return;
    }

    uplink_data = data_ptr = (char *) phwangMalloc1(ROOM_MGR_DATA_BUFFER_SIZE + 4, MallocClass::DTHEME_PUT_ROOM_DATA2);
    *data_ptr++ = THEME_ENGINE_PROTOCOL_COMMAND_IS_PUT_BASE_DATA;
    memcpy(data_ptr, room->baseIdIndex(), BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE);
    data_ptr += BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE;
    strcpy(data_ptr, data_val + ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    this->theThemeObject->uThemeObject()->transmitFunction(uplink_data);
}
