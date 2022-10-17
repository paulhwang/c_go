/*
  Copyrights reserved
  Written by Paul Hwang
  File name: theme_def.h
*/

#pragma once

#include "size_def.h"
#include "result_def.h"
#include "te_def.h"

class THEME_DEF {
public:
    /* downlink data buffer size */
    int const static FT_DL_HEADER_SIZE = FT_DEF::FT_COMMAND_SIZE + 1;
    int const static FT_DL_BUFFER_SIZE = FT_DL_HEADER_SIZE + RESULT_DEF::RESULT_SIZE;
    int const static FT_DL_BUF_WITH_GROUP_SIZE = FT_DL_BUFFER_SIZE + SIZE_DEF::GROUP_II_SIZE;
    int const static FT_DL_BUF_WITH_GROUP_ROOM_SIZE = FT_DL_BUF_WITH_GROUP_SIZE + SIZE_DEF::ROOM_II_SIZE;

    /* uplink data buffer size */
    int const static TE_UL_BUFFER_SIZE = TE_DEF::TE_COMMAND_SIZE + 1;
    int const static TE_UL_BUF_WITH_ROOM_SIZE  = TE_UL_BUFFER_SIZE + SIZE_DEF::ROOM_II_SIZE;
    int const static TE_UL_BUF_WITH_BASE_SIZE  = TE_UL_BUFFER_SIZE + SIZE_DEF::BASE_II_SIZE;
};
