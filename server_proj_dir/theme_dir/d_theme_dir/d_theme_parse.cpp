/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_parse.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../define_dir/ft_command_define.h"
#include "../../define_dir/te_command_define.h"
#include "../../define_dir/fe_command_define.h"
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

    char *group_id_ptr = data_val;
    char *rest_data_ptr = data_val + FT_CommandClass::GROUP_ID_INDEX_SIZE;

    RoomClass *room = this->theThemeObject->mallocRoom(group_id_ptr);
    if (!room) {
        phwangAbendS("DThemeClass::processSetupRoom", "null_room");

        /* downlink */
        char *dl_current_ptr;
        char *downlink_data = dl_current_ptr = (char *) phwangMalloc(FT_CommandClass::FT_DL_DATA_BUF_SIZE + 4, MallocClass::DTHEME_SETUP_ROOM1);
        *dl_current_ptr++ = FT_CommandClass::SETUP_ROOM_RESPONSE;

        strcpy(dl_current_ptr, FE_CommandClass::FE_RESULT_MALLOC_ROOM_FAIL);

        this->transmitFunction(downlink_data);
        return;
    }

    /* uplink */
    char *ul_current_ptr;
    char *uplink_data = ul_current_ptr = (char *) phwangMalloc(TE_CommandClass::TE_UL_DATA_BUF_SIZE + 4, MallocClass::DTHEME_SETUP_ROOM2);
    *ul_current_ptr++ = TE_CommandClass::SETUP_BASE_COMMAND;

    memcpy(ul_current_ptr, room->roomIdIndex(), FT_CommandClass::ROOM_ID_INDEX_SIZE);
    ul_current_ptr += FT_CommandClass::ROOM_ID_INDEX_SIZE;

    strcpy(ul_current_ptr, rest_data_ptr);
    this->theThemeObject->uThemeObject()->transmitFunction(uplink_data);
}

void DThemeClass::processPutRoomData (char *data_val)
{
    phwangDebugS(true, "DThemeClass::processPutRoomData", data_val);

    char *room_id_ptr = data_val;
    char *rest_data_ptr = data_val + FT_CommandClass::ROOM_ID_INDEX_SIZE;

    RoomClass *room = this->theThemeObject->searchRoom(room_id_ptr);
    if (!room) {
        phwangAbendS("DThemeClass::processPutRoomData", "null room");

        /* downlink */
        char *dl_current_ptr;
        char *downlink_data = dl_current_ptr = (char *) phwangMalloc(FT_CommandClass::FT_DL_DATA_BUF_SIZE + 4, MallocClass::DTHEME_PUT_ROOM_DATA1);
        *dl_current_ptr++ = FT_CommandClass::PUT_ROOM_DATA_RESPONSE;

        strcpy(dl_current_ptr, FE_CommandClass::FE_RESULT_NULL_ROOM);

        this->transmitFunction(downlink_data);
        return;
    }

    /* uplink */
    if (strlen(data_val) > TE_CommandClass::TE_UL_DATA_BUF_SIZE) {
        phwangAbendSI("DThemeClass::processPutRoomData", "buf_size", strlen(data_val));
    }

    char *ul_current_ptr;
    char *uplink_data = ul_current_ptr = (char *) phwangMalloc(TE_CommandClass::TE_UL_DATA_BUF_SIZE + 4, MallocClass::DTHEME_PUT_ROOM_DATA2);

    *ul_current_ptr++ = TE_CommandClass::PUT_BASE_DATA_COMMAND;

    memcpy(ul_current_ptr, room->baseIdIndex(), TE_CommandClass::BASE_ID_INDEX_SIZE);
    ul_current_ptr += TE_CommandClass::BASE_ID_INDEX_SIZE;

    strcpy(ul_current_ptr, rest_data_ptr);

    this->theThemeObject->uThemeObject()->transmitFunction(uplink_data);
}
