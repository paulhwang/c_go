/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_theme_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/theme_engine_protocol.h"
#include "../../protocol_dir/fabric_theme_protocol.h"
#include "../../protocol_dir/room_mgr_protocol.h"
#include "../../protocol_dir/group_mgr_protocol.h"
#include "u_theme_class.h"
#include "../theme_class.h"
#include "../d_theme_dir/d_theme_class.h"
#include "../room_mgr_dir/room_class.h"
#include "../room_mgr_dir/room_mgr_class.h"

void UThemeClass::exportedparseFunction(char *data_val)
{
    this->debug(true, "exportedparseFunction", data_val);

    if (*data_val == THEME_ENGINE_PROTOCOL_RESPOND_IS_MALLOC_BASE) {
        this->processMallocBaseResponse(data_val + 1);
        return;
    }

    if (*data_val == THEME_ENGINE_PROTOCOL_RESPOND_IS_TRANSFER_DATA) {
        this->processTransferDataResponse(data_val + 1);
        return;
    }

    this->abend("exportedparseFunction", data_val);
}

void UThemeClass::processMallocBaseResponse(char *data_val)
{
    char *downlink_data;
    char *data_ptr;

    this->debug(true, "processMallocBaseResponse", data_val);

    RoomClass *room = this->theThemeObject->roomMgrObject()->searchRoom(data_val);
    if (!room) {
        this->abend("processMallocBaseResponse", "null room");
        return;
    }

    data_val += ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE;
    room->insertBase(data_val);
    this->debug(true, "processMallocBaseResponse==1", "");

    downlink_data = data_ptr = (char *) malloc(ROOM_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = FABRIC_THEME_PROTOCOL_RESPOND_IS_MALLOC_ROOM;
    this->debug(true, "processMallocBaseResponse==2", "");
    memcpy(data_ptr, room->theGroupTableArray[0], GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE);
    data_ptr += GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE;
    this->debug(true, "processMallocBaseResponse==3", "");
    memcpy(data_ptr, room->roomIdIndex(), ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    this->debug(true, "processMallocBaseResponse==4", "");
    data_ptr += ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE;
    *data_ptr = 0;
    this->debug(true, "processMallocBaseResponse==", downlink_data);
    this->theThemeObject->dThemeObject()->transmitFunction(downlink_data);
}

void UThemeClass::processTransferDataResponse(char *data_val)
{
    this->debug(true, "processTransferDataResponse", data_val);

    RoomClass *room = this->theThemeObject->roomMgrObject()->searchRoom(data_val);
    if (!room) {
        this->abend("processTransferDataResponse", "null room");
        return;
    }

    int i = 0;
    while (i < room->maxGroupTableArrayIndex) {
        if (room->theGroupTableArray[i]) {

        }
        i++;
    }

}
