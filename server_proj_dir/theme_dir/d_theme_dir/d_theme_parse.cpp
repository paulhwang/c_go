/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_export.cpp
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
        this->processMallocRoom(++data_val);
    }
    else if (*data_val == FABRIC_THEME_PROTOCOL_COMMAND_IS_GET_SESSION_DATA) {
        this->processGetSessionData(++data_val);
    }
    else if (*data_val == FABRIC_THEME_PROTOCOL_COMMAND_IS_PUT_SESSION_DATA) {
        this->processPutSessionData(++data_val);
    }
    else {
    	this->theThemeObject->uThemeObject()->transmitFunction(data_val);
    }
}

void DThemeClass::processMallocRoom (char *data_val)
{
    char *downlink_data;
    char *uplink_data;
    char *data_ptr;

    RoomClass *room = this->theThemeObject->roomMgrObject()->mallocRoom(data_val);
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
    memcpy(data_ptr, room->theRoomIdIndex, room->theRoomIdIndexSize);
    data_ptr += room->theRoomIdIndexSize;
    *data_ptr = 0;
    this->debug(true, "processPutSessionData", uplink_data);
    this->theThemeObject->uThemeObject()->transmitFunction(uplink_data);
 
    downlink_data = data_ptr = (char *) malloc(ROOM_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = FABRIC_THEME_PROTOCOL_RESPOND_IS_MALLOC_ROOM;
    memcpy(data_ptr, room->groupIdIndex(), room->theGroupIdIndexSize);
    data_ptr += room->theGroupIdIndexSize;
    memcpy(data_ptr, room->roomIdIndex(), room->theRoomIdIndexSize);
    data_ptr += room->theRoomIdIndexSize;
    *data_ptr = 0;
    this->transmitFunction(downlink_data);
}

void DThemeClass::processGetSessionData (char *data_val)
{
    this->debug(true, "processGetSessionData", data_val);

}

void DThemeClass::processPutSessionData (char *data_val)
{
    char *downlink_data;
    char *uplink_data;
    char *data_ptr;

    this->debug(true, "processPutSessionData===", data_val);

    RoomClass *room = this->theThemeObject->roomMgrObject()->searchRoom(data_val);
    if (!room) {
        this->abend("processPutSessionData", "null room");
        downlink_data = data_ptr = (char *) malloc(ROOM_MGR_DATA_BUFFER_SIZE + 4);
        *data_ptr++ = FABRIC_THEME_PROTOCOL_RESPOND_IS_PUT_SESSION_DATA;
        strcpy(data_ptr, "null room");
        this->transmitFunction(downlink_data);
        return;
    }

    uplink_data = data_ptr = (char *) malloc(ROOM_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = THEME_ENGINE_PROTOCOL_COMMAND_IS_PUT_SESSION_DATA;
    memcpy(data_ptr, room->theRoomIdIndex, room->theRoomIdIndexSize);
    data_ptr += room->theRoomIdIndexSize;
    *data_ptr = 0;
    this->debug(true, "processPutSessionData", uplink_data);
    this->theThemeObject->uThemeObject()->transmitFunction(uplink_data);

    //////output_data[0] = FABRIC_THEME_PROTOCOL_RESPOND_IS_PUT_SESSION_DATA;
    ////strcpy(output_data + 1, (char *) data_val);
    //this->transmitFunction(output_data);
}
