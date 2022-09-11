/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_theme_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../protocol_dir/te_command_class.h"
#include "../../protocol_dir/ft_command_class.h"
#include "u_theme_class.h"
#include "../theme_class.h"
#include "../d_theme_dir/d_theme_class.h"
#include "../room_class.h"

void UThemeClass::exportedParseFunction (char *data_val)
{
    phwangDebugS(true, "UThemeClass::exportedParseFunction", data_val);

    switch (*data_val) {
        case TE_CommandClass::SETUP_BASE_RESPONSE:
            this->processSetupBaseResponse(data_val + 1);
            return;

        case TE_CommandClass::PUT_BASE_DATA_RESPONSE:
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

    char *room_id_index_val = data_val;

    char *downlink_data;
    char *data_ptr;
    int group_array_size;

    RoomClass *room = this->theThemeObject->searchRoom(room_id_index_val);
    if (!room) {
        phwangAbendS("UThemeClass::processSetupBaseResponse", "null room");
        return;
    }

    /* downlink */
    data_val += FT_CommandClass::ROOM_ID_INDEX_SIZE;
    room->setBaseIdIndex(data_val);

    downlink_data = data_ptr = (char *) phwangMalloc(FT_CommandClass::FT_DL_DATA_BUF_SIZE + 4, MallocClass::UTHEME_BASE);
    *data_ptr++ = FT_CommandClass::SETUP_ROOM_RESPONSE;

    room->setGroupTableArray((char **) phwangArrayMgrGetArrayTable(room->groupArrayMgr(), &group_array_size));
    memcpy(data_ptr, room->groupTableArray(0), FT_CommandClass::GROUP_ID_INDEX_SIZE);
    data_ptr += FT_CommandClass::GROUP_ID_INDEX_SIZE;

    memcpy(data_ptr, room->roomIdIndex(), FT_CommandClass::ROOM_ID_INDEX_SIZE);
    data_ptr += FT_CommandClass::ROOM_ID_INDEX_SIZE;
    *data_ptr = 0;
    this->theThemeObject->dThemeObject()->transmitFunction(downlink_data);
}

void UThemeClass::processPutBaseDataResponse (char *data_val)
{
    char *downlink_data;
    char *data_ptr;
    int group_array_size;

    phwangDebugS(false, "UThemeClass::processPutBaseDataResponse", data_val);

    RoomClass *room = this->theThemeObject->searchRoom(data_val);
    if (!room) {
        phwangAbendS("UThemeClass::processPutBaseDataResponse", "null room");
        return;
    }
    data_val += FT_CommandClass::ROOM_ID_INDEX_SIZE;

    /* downlink */
    room->setGroupTableArray((char **) phwangArrayMgrGetArrayTable(room->groupArrayMgr(), &group_array_size));
    for (int i = 0; i < group_array_size; i++) {
        if (room->groupTableArray(i)) {
            downlink_data = data_ptr = (char *) phwangMalloc(FT_CommandClass::FT_DL_DATA_BUF_SIZE + 4, MallocClass::UTHEME_BASE_PUT_BASE_DATA);
            *data_ptr++ = FT_CommandClass::PUT_ROOM_DATA_RESPONSE;
            memcpy(data_ptr, room->groupTableArray(i), FT_CommandClass::GROUP_ID_INDEX_SIZE);
            data_ptr += FT_CommandClass::GROUP_ID_INDEX_SIZE;
            strcpy(data_ptr, data_val);
            this->theThemeObject->dThemeObject()->transmitFunction(downlink_data);
        }
    }
}
