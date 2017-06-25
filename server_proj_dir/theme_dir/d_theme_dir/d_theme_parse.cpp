/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_parse.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/fabric_theme_protocol.h"
#include "../../protocol_dir/theme_engine_protocol.h"
#include "../../protocol_dir/room_mgr_protocol.h"
#include "d_theme_class.h"
#include "../theme_class.h"
#include "../u_theme_dir/u_theme_class.h"
#include "../room_mgr_dir/room_mgr_class.h"
#include "../room_mgr_dir/room_class.h"

void DThemeClass::exportedparseFunction (char *data_val)
{
    this->debug(true, "exportedparseFunction", data_val);

    if (*data_val == FABRIC_THEME_PROTOCOL_COMMAND_IS_MALLOC_ROOM) {
        this->processMallocRoom(data_val + 1);
        return;
    }

    if (*data_val == FABRIC_THEME_PROTOCOL_COMMAND_IS_TRANSFER_DATA) {
        this->processTransferData(data_val + 1);
        return;
    }

    this->abend("exportedparseFunction", data_val);
}

void DThemeClass::processMallocRoom (char *data_val)
{
    char *downlink_data;
    char *uplink_data;
    char *data_ptr;

    this->debug(true, "processMallocRoom", data_val);

    RoomClass *room = this->theThemeObject->mallocRoom(data_val);
    if (!room) {
        this->abend("processMallocRoom", "null room");
        downlink_data = data_ptr = (char *) malloc(ROOM_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = FABRIC_THEME_PROTOCOL_RESPOND_IS_MALLOC_ROOM;
        strcpy(data_ptr, "null room");
        this->transmitFunction(downlink_data);
        return;
    }

    uplink_data = data_ptr = (char *) malloc(ROOM_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = THEME_ENGINE_PROTOCOL_COMMAND_IS_MALLOC_BASE;
    memcpy(data_ptr, room->theRoomIdIndex, ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    data_ptr += ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE;
    *data_ptr = 0;
    this->theThemeObject->uThemeObject()->transmitFunction(uplink_data);
}

void DThemeClass::processTransferData (char *data_val)
{
    char *downlink_data;
    char *uplink_data;
    char *data_ptr;

    this->debug(true, "processTransferData", data_val);

    RoomClass *room = this->theThemeObject->searchRoom(data_val);
    if (!room) {
        this->abend("processTransferData", "null room");
        downlink_data = data_ptr = (char *) malloc(ROOM_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = FABRIC_THEME_PROTOCOL_RESPOND_IS_TRANSFER_DATA;
        strcpy(data_ptr, "null room");
        this->transmitFunction(downlink_data);
        return;
    }

    uplink_data = data_ptr = (char *) malloc(ROOM_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = THEME_ENGINE_PROTOCOL_COMMAND_IS_TRANSFER_DATA;
    memcpy(data_ptr, room->theBaseIdIndex, BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE);
    data_ptr += BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE;
    strcpy(data_ptr, data_val + ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    this->theThemeObject->uThemeObject()->transmitFunction(uplink_data);
}
