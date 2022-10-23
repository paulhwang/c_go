/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_theme_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../define_dir/result_def.h"
#include "../../define_dir/fe_def.h"
#include "../../define_dir/te_def.h"
#include "../../define_dir/ft_def.h"
#include "../../define_dir/theme_def.h"
#include "u_theme_class.h"
#include "../theme_class.h"
#include "../d_theme_dir/d_theme_class.h"
#include "../room_class.h"

void UThemeClass::exportedParseFunction (char *data_val)
{
    phwangDebugS(true, "UThemeClass::exportedParseFunction", data_val);

    switch (*data_val) {
        case TE_DEF::TE_SETUP_BASE_RESPONSE:
            this->processSetupBaseResponse(data_val + 1);
            return;

        case TE_DEF::TE_PUT_BASE_DATA_RESPONSE:
            this->processPutBaseDataResponse(data_val + 1);
            return;

        default:
            phwangAbendS("UThemeClass::exportedParseFunction", data_val);
            return;
    }
}

void UThemeClass::processSetupBaseResponse (char *data_val)
{
    phwangDebugS(true, "UThemeClass::processSetupBaseResponse", data_val);

    char *result_ptr = data_val;
    char *room_id_ptr = result_ptr + RESULT_DEF::RESULT_SIZE;
    char *base_id_ptr = room_id_ptr + SIZE_DEF::ROOM_II_SIZE;

    RoomClass *room = this->theThemeObject->searchRoom(room_id_ptr);
    if (!room) {
        phwangAbendS("UThemeClass::processSetupBaseResponse", "null_room");
        return;
    }

    /* downlink */
    int group_array_size;
    char *current_ptr;
    room->setBaseIdIndex(base_id_ptr);
    room->setGroupTableArray((char **) phwangArrayMgrGetArrayTable(room->groupArrayMgr(), &group_array_size));

    char *downlink_data = current_ptr = (char *) phwangMalloc(THEME_DEF::DL_CRGM_BUF_SIZE, MallocClass::UTHEME_BASE);

    *current_ptr++ = FT_DEF::FT_SETUP_ROOM_RESPONSE;

    memcpy(current_ptr, result_ptr, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, room->groupTableArray(0), SIZE_DEF::GROUP_II_SIZE);
    current_ptr += SIZE_DEF::GROUP_II_SIZE;

    memcpy(current_ptr, room->roomIdIndex(), SIZE_DEF::ROOM_II_SIZE);
    current_ptr += SIZE_DEF::ROOM_II_SIZE;

    *current_ptr = 0;

    this->theThemeObject->dThemeObject()->xmtData(downlink_data);
}

void UThemeClass::processPutBaseDataResponse (char *data_val)
{
    phwangDebugS(false, "UThemeClass::processPutBaseDataResponse", data_val);

    char *result_ptr = data_val;
    char *room_id_ptr = result_ptr + RESULT_DEF::RESULT_SIZE;
    char *rest_data_ptr = room_id_ptr + SIZE_DEF::ROOM_II_SIZE;

    RoomClass *room = this->theThemeObject->searchRoom(room_id_ptr);

    if (!room) {
        phwangAbendS("UThemeClass::processPutBaseDataResponse", "null room");
        return;
    }

    /* downlink */
    int group_array_size;
    room->setGroupTableArray((char **) phwangArrayMgrGetArrayTable(room->groupArrayMgr(), &group_array_size));
    for (int i = 0; i < group_array_size; i++) {
        if (room->groupTableArray(i)) {
            char *current_ptr;
            char *downlink_data = current_ptr = (char *) phwangMalloc(THEME_DEF::DL_CRG_BUF_SIZE + strlen(rest_data_ptr), MallocClass::UTHEME_BASE_PUT_BASE_DATA);

            *current_ptr++ = FT_DEF::FT_PUT_ROOM_DATA_RESPONSE;

            memcpy(current_ptr, result_ptr, RESULT_DEF::RESULT_SIZE);
            current_ptr += RESULT_DEF::RESULT_SIZE;

            memcpy(current_ptr, room->groupTableArray(i), SIZE_DEF::GROUP_II_SIZE);
            current_ptr += SIZE_DEF::GROUP_II_SIZE;

            strcpy(current_ptr, rest_data_ptr);

            this->theThemeObject->dThemeObject()->xmtData(downlink_data);
        }
    }
}
