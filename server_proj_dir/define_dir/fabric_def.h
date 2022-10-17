/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_def.h
*/

#include "size_def.h"
#include "result_def.h"
#include "ft_def.h"

#pragma once

class FABRIC_DEF {
public:
    /* downlink data buffer size */
    int const static DL_AJAX_COMMAND_SIZE = SIZE_DEF::AJAX_ID_SIZE + FE_DEF::FE_COMMAND_SIZE;
    int const static DL_ACR_BUF_SIZE = DL_AJAX_COMMAND_SIZE + RESULT_DEF::RESULT_SIZE + 1;
    int const static DL_ACRL_BUF_SIZE = DL_ACR_BUF_SIZE + SIZE_DEF::LINK_II_SIZE;
    int const static DL_ACRLS_BUF_SIZE = DL_ACRL_BUF_SIZE + SIZE_DEF::SESSION_II_SIZE;

    /* uplink data buffer size */
    int const static UL_C_BUF_SIZE = FT_DEF::FT_COMMAND_SIZE + 1;
    int const static UL_CG_BUF_SIZE = UL_C_BUF_SIZE + SIZE_DEF::GROUP_ID_INDEX_SIZE;
    int const static UL_CR_BUF_SIZE = UL_C_BUF_SIZE + SIZE_DEF::ROOM_ID_INDEX_SIZE;
};
