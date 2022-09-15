/*
  Copyrights reserved
  Written by Paul Hwang
  File name: te_command_define.h
*/

#pragma once

#include "size_def.h"
#include "result_def.h"

class TE_CommandClass {
public:
    int const static TE_DL_COMMAND_SIZE = 1;
    char const static SETUP_BASE_COMMAND  = 'B';
    char const static SETUP_BASE_RESPONSE = 'b';
    char const static PUT_BASE_DATA_COMMAND  = 'D';
    char const static PUT_BASE_DATA_RESPONSE = 'd';

    /* downlink data buffer size */
    int const static TE_DL_HEADER_SIZE = TE_DL_COMMAND_SIZE + 1;
    int const static TE_DL_BUFFER_SIZE = TE_DL_HEADER_SIZE + RESULT_DEF::RESULT_SIZE;
    int const static FT_DL_BUF_WITH_ROOM_SIZE = TE_DL_BUFFER_SIZE + SIZE_DEF::ROOM_ID_INDEX_SIZE;
    int const static FT_DL_BUF_WITH_ROOM_BASE_SIZE = FT_DL_BUF_WITH_ROOM_SIZE + SIZE_DEF::BASE_ID_INDEX_SIZE;
};
