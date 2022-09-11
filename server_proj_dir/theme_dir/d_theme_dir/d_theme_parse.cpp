/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_parse.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../protocol_dir/ft_command_class.h"
#include "../../protocol_dir/te_command_class.h"
#include "d_theme_class.h"
#include "../theme_class.h"
#include "../u_theme_dir/u_theme_class.h"
#include "../room_class.h"

void DThemeClass::exportedParseFunction (char *data_val)
{
    phwangDebugS(true, "DThemeClass::exportedParseFunction", data_val);

    switch (*data_val) {
        case FT_CommandClass::SETUP_ROOM_COMMAND:
            this->processSetupRoom(data_val + 1);
            return;

        case FT_CommandClass::PUT_ROOM_DATA_COMMAND:
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

        /* downlink */
        downlink_data = data_ptr = (char *) phwangMalloc(FT_CommandClass::FT_DL_DATA_BUF_SIZE + 4, MallocClass::DTHEME_SETUP_ROOM1);
        *data_ptr++ = FT_CommandClass::SETUP_ROOM_RESPONSE;
        strcpy(data_ptr, "null room");
        this->transmitFunction(downlink_data);
        return;
    }

    /* uplink */
    if (strlen(data_val) > TE_CommandClass::TE_UL_DATA_BUF_SIZE) {
        phwangAbendSI("DThemeClass::processSetupRoom", "buf_size", strlen(data_val));
    }

    data_val += FT_CommandClass::GROUP_ID_INDEX_SIZE;

    uplink_data = data_ptr = (char *) phwangMalloc(TE_CommandClass::TE_UL_DATA_BUF_SIZE + 4, MallocClass::DTHEME_SETUP_ROOM2);
    *data_ptr++ = TE_CommandClass::SETUP_BASE_COMMAND;

    memcpy(data_ptr, room->roomIdIndex(), FT_CommandClass::ROOM_ID_INDEX_SIZE);
    data_ptr += FT_CommandClass::ROOM_ID_INDEX_SIZE;

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

        /* downlink */
        downlink_data = data_ptr = (char *) phwangMalloc(FT_CommandClass::FT_DL_DATA_BUF_SIZE + 4, MallocClass::DTHEME_PUT_ROOM_DATA1);
        *data_ptr++ = FT_CommandClass::PUT_ROOM_DATA_RESPONSE;
        strcpy(data_ptr, "null room");
        this->transmitFunction(downlink_data);
        return;
    }

    /* uplink */
    if (strlen(data_val) > TE_CommandClass::TE_UL_DATA_BUF_SIZE) {
        phwangAbendSI("DThemeClass::processPutRoomData", "buf_size", strlen(data_val));
    }

    uplink_data = data_ptr = (char *) phwangMalloc(TE_CommandClass::TE_UL_DATA_BUF_SIZE + 4, MallocClass::DTHEME_PUT_ROOM_DATA2);
    *data_ptr++ = TE_CommandClass::PUT_BASE_DATA_COMMAND;
    memcpy(data_ptr, room->baseIdIndex(), TE_CommandClass::BASE_ID_INDEX_SIZE);
    data_ptr += TE_CommandClass::BASE_ID_INDEX_SIZE;
    strcpy(data_ptr, data_val + FT_CommandClass::ROOM_ID_INDEX_SIZE);
    this->theThemeObject->uThemeObject()->transmitFunction(uplink_data);
}
