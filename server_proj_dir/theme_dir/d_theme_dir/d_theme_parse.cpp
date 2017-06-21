/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/fabric_theme_protocol.h"
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
        this->processMallocRoom(++data_val);
    }
    else {
    	this->theThemeObject->uThemeObject()->transmitFunction(data_val);
    }
}

void DThemeClass::processMallocRoom (char *data_val)
{
    char *output_data = (char *) malloc(ROOM_MGR_DATA_BUFFER_SIZE + 4);
    output_data[0] = FABRIC_THEME_PROTOCOL_RESPOND_IS_MALLOC_ROOM;

    RoomClass *room = this->theThemeObject->roomMgrObject()->mallocRoom(data_val);
    if (!room) {
        this->abend("processMallocRoom", "null room");
        strcpy(output_data + 1, "null room");
        this->transmitFunction(output_data);
        return;
    }

    memcpy(output_data + 1, room->groupIdIndex, GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE);
    phwangEncodeIdIndex(output_data + 1 + GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE, room->roomId(), ROOM_MGR_PROTOCOL_ROOM_ID_SIZE, room->roomIndex(), ROOM_MGR_PROTOCOL_ROOM_INDEX_SIZE);
    this->transmitFunction(output_data);
}
