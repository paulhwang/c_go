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
    int const static DL_CR_BUF_SIZE = FT_DL_HEADER_SIZE + RESULT_DEF::RESULT_SIZE;
    int const static DL_CRG_BUF_SIZE = DL_CR_BUF_SIZE + SIZE_DEF::GROUP_II_SIZE;
    int const static DL_CRGM_BUF_SIZE = DL_CRG_BUF_SIZE + SIZE_DEF::ROOM_II_SIZE;

    /* uplink data buffer size */
    int const static UL_C_BUF_SIZE = TE_DEF::TE_COMMAND_SIZE + 1;
    int const static UL_CR_BUF_SIZE  = UL_C_BUF_SIZE + SIZE_DEF::ROOM_II_SIZE;
    int const static UL_CB_BUF_SIZE  = UL_C_BUF_SIZE + SIZE_DEF::BASE_II_SIZE;
};
