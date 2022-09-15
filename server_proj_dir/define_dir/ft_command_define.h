/*
  Copyrights reserved
  Written by Paul Hwang
  File name: ft_command_define.h
*/

#pragma once

#include "size_def.h"
#include "result_def.h"

class FT_CommandClass {
public:
    int const static FT_DL_COMMAND_SIZE = 1;
    char const static SETUP_ROOM_COMMAND  = 'R';
    char const static SETUP_ROOM_RESPONSE = 'r';
    char const static PUT_ROOM_DATA_COMMAND  = 'D';
    char const static PUT_ROOM_DATA_RESPONSE = 'd';

    /* downlink data buffer size */
    int const static FT_DL_HEADER_SIZE = FT_DL_COMMAND_SIZE + 1;
    int const static FT_DL_BUFFER_SIZE = FT_DL_HEADER_SIZE + RESULT_DEF::RESULT_SIZE;
    int const static FT_DL_BUF_WITH_GROUP_SIZE = FT_DL_BUFFER_SIZE + SIZE_DEF::GROUP_ID_INDEX_SIZE;
    int const static FT_DL_BUF_WITH_GROUP_ROOM_SIZE = FT_DL_BUF_WITH_GROUP_SIZE + SIZE_DEF::ROOM_ID_INDEX_SIZE;

    /* uplink data buffer size */
    int const static FT_UL_BUFFER_SIZE = 1 + 1;
    int const static FT_UL_BUF_WITH_ROOM_SIZE  = FT_UL_BUFFER_SIZE + SIZE_DEF::ROOM_ID_INDEX_SIZE;
    int const static FT_UL_BUF_WITH_BASE_SIZE  = FT_UL_BUFFER_SIZE + SIZE_DEF::BASE_ID_INDEX_SIZE;

};
