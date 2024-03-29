/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_parse.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../define_dir/ft_def.h"
#include "../../define_dir/te_def.h"
#include "../../define_dir/fe_def.h"
#include "../../define_dir/theme_def.h"
#include "d_theme_class.h"
#include "../theme_class.h"
#include "../u_theme_dir/u_theme_class.h"
#include "../room_class.h"

void DThemeClass::parseData (char *data_val)
{
    if (true && this->debugOn_) {
        printf("DThemeClass::parseData() %s\n", data_val);
    }

    switch (*data_val) {
        case FT_DEF::FT_SETUP_ROOM_COMMAND:
            this->processSetupRoom(data_val + 1);
            return;

        case FT_DEF::FT_PUT_ROOM_DATA_COMMAND:
            this->processPutRoomData(data_val + 1);
            return;

        default:
            phwangAbendS("DThemeClass::parseData", data_val);
            return;
    }
}

void DThemeClass::processSetupRoom (char *data_val)
{
    if (true && this->debugOn_) {
        printf("DThemeClass::processSetupRoom() %s\n", data_val);
    }

    char *group_id_ptr = data_val;
    char *rest_data_ptr = data_val + SIZE_DEF::GROUP_II_SIZE;

    RoomClass *room = this->themeObj_->mallocRoom(group_id_ptr);
    if (!room) {
        phwangAbendS("DThemeClass::processSetupRoom", "null_room");

        /* downlink */
        char *dl_current_ptr;
        char *downlink_data = dl_current_ptr = (char *) phwangMalloc(THEME_DEF::DL_CR_BUF_SIZE, MallocClass::DTHEME_SETUP_ROOM1);

        *dl_current_ptr++ = FT_DEF::FT_SETUP_ROOM_RESPONSE;

        strcpy(dl_current_ptr, RESULT_DEF::RESULT_MALLOC_ROOM_FAIL);

        this->xmtData(downlink_data);
        return;
    }

    /* uplink */
    char *ul_current_ptr;
    char *uplink_data = ul_current_ptr = (char *) phwangMalloc(THEME_DEF::UL_CR_BUF_SIZE + strlen(rest_data_ptr), MallocClass::DTHEME_SETUP_ROOM2);
    *ul_current_ptr++ = TE_DEF::TE_SETUP_BASE_COMMAND;

    memcpy(ul_current_ptr, room->roomIdIndex(), SIZE_DEF::ROOM_II_SIZE);
    ul_current_ptr += SIZE_DEF::ROOM_II_SIZE;

    strcpy(ul_current_ptr, rest_data_ptr);
    this->themeObj_->uThemeObject()->xmtData(uplink_data);
}

void DThemeClass::processPutRoomData (char *data_val)
{
    if (true && this->debugOn_) {
        printf("DThemeClass::processPutRoomData() %s\n", data_val);
    }

    char *room_id_ptr = data_val;
    char *rest_data_ptr = data_val + SIZE_DEF::ROOM_II_SIZE;

    RoomClass *room = this->themeObj_->searchRoom(room_id_ptr);
    if (!room) {
        phwangAbendS("DThemeClass::processPutRoomData", "null room");

        /* downlink */
        char *dl_current_ptr;
        char *downlink_data = dl_current_ptr = (char *) phwangMalloc(THEME_DEF::DL_CR_BUF_SIZE, MallocClass::DTHEME_PUT_ROOM_DATA1);

        *dl_current_ptr++ = FT_DEF::FT_PUT_ROOM_DATA_RESPONSE;

        strcpy(dl_current_ptr, RESULT_DEF::RESULT_NULL_ROOM);

        this->xmtData(downlink_data);
        return;
    }

    /* uplink */
    char *ul_current_ptr;
    char *uplink_data = ul_current_ptr = (char *) phwangMalloc(THEME_DEF::UL_CB_BUF_SIZE + strlen(rest_data_ptr), MallocClass::DTHEME_PUT_ROOM_DATA2);

    *ul_current_ptr++ = TE_DEF::TE_PUT_BASE_DATA_COMMAND;

    memcpy(ul_current_ptr, room->baseIdIndex(), SIZE_DEF::BASE_II_SIZE);
    ul_current_ptr += SIZE_DEF::BASE_II_SIZE;

    strcpy(ul_current_ptr, rest_data_ptr);

    this->themeObj_->uThemeObject()->xmtData(uplink_data);
}
