/*
  Copyrights reserved
  Written by Paul Hwang
  File name: te_command_define.h
*/

#pragma once

#include "ft_command_define.h"

class TE_CommandClass {
public:
    int const static TE_DL_COMMAND_SIZE = 1;
    char const static SETUP_BASE_COMMAND  = 'B';
    char const static SETUP_BASE_RESPONSE = 'b';
    char const static PUT_BASE_DATA_COMMAND  = 'D';
    char const static PUT_BASE_DATA_RESPONSE = 'd';

    int const static BASE_ID_SIZE = 4;
    int const static BASE_INDEX_SIZE = 4;
    int const static BASE_ID_INDEX_SIZE = BASE_ID_SIZE + BASE_INDEX_SIZE;

    /* downlink data buffer size */
    int const static TE_DL_HEADER_SIZE = TE_DL_COMMAND_SIZE + 1;
    int const static TE_DL_BUFFER_SIZE = TE_DL_HEADER_SIZE + 2; ///////////////// TBD FE_CommandClass::FE_RESULT_SIZE;
    int const static FT_DL_BUF_WITH_ROOM_SIZE = TE_DL_BUFFER_SIZE + 8;///////////////////TBD FT_CommandClass::ROOM_ID_INDEX_SIZE;
    int const static FT_DL_BUF_WITH_ROOM_BASE_SIZE = FT_DL_BUF_WITH_ROOM_SIZE + BASE_ID_INDEX_SIZE;
};
