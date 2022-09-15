/*
  Copyrights reserved
  Written by Paul Hwang
  File name: ft_command_define.h
*/

#pragma once

#include "te_command_define.h"

class FT_CommandClass {
public:
    int const static FT_DL_DATA_BUF_SIZE = 512;

    int const static FT_DL_COMMAND_SIZE = 1;
    char const static SETUP_ROOM_COMMAND  = 'R';
    char const static SETUP_ROOM_RESPONSE = 'r';
    char const static PUT_ROOM_DATA_COMMAND  = 'D';
    char const static PUT_ROOM_DATA_RESPONSE = 'd';

    int const static ROOM_ID_INITIAL_VALUE = 700;
    int const static ROOM_ID_SIZE = 4;
    int const static ROOM_INDEX_SIZE = 4;
    int const static ROOM_ID_INDEX_SIZE = ROOM_ID_SIZE + ROOM_INDEX_SIZE;

    int const static GROUP_ID_INITIAL_VALUE = 500;
    int const static GROUP_ID_SIZE = 4;
    int const static GROUP_INDEX_SIZE = 4;
    int const static GROUP_ID_INDEX_SIZE = GROUP_ID_SIZE + GROUP_INDEX_SIZE;

    /* downlink data buffer size */
    int const static FT_DL_HEADER_SIZE = FT_DL_COMMAND_SIZE + 1;
    int const static FT_DL_BUFFER_SIZE = FT_DL_HEADER_SIZE + 2; ///////////////// TBD FE_CommandClass::FE_RESULT_SIZE;

    /* uplink data buffer size */
    int const static FT_UL_BUFFER_SIZE = 1 + 1;
    int const static FT_UL_BUF_WITH_ROOM_SIZE  = FT_UL_BUFFER_SIZE + FT_CommandClass::ROOM_ID_INDEX_SIZE;
    int const static FT_UL_BUF_WITH_BASE_SIZE  = FT_UL_BUFFER_SIZE + TE_CommandClass::BASE_ID_INDEX_SIZE;

};
