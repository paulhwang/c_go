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
    int const static FE_DL_COMMAND_AJAX_SIZE = FE_DEF::FE_COMMAND_SIZE + SIZE_DEF::AJAX_ID_SIZE;
    int const static FE_DL_BUFFER_SIZE = FE_DL_COMMAND_AJAX_SIZE + RESULT_DEF::RESULT_SIZE + 1;
    int const static FE_DL_BUF_WITH_LINK_SIZE = FE_DL_BUFFER_SIZE + SIZE_DEF::LINK_ID_INDEX_SIZE;
    int const static FE_DL_BUF_WITH_LINK_SESSION_SIZE = FE_DL_BUF_WITH_LINK_SIZE + SIZE_DEF::SESSION_ID_INDEX_SIZE;

    /* uplink data buffer size */
    int const static FT_UL_BUFFER_SIZE = FT_DEF::FT_COMMAND_SIZE + 1;
    int const static FT_UL_BUF_WITH_GROUP_SIZE = FT_UL_BUFFER_SIZE + SIZE_DEF::GROUP_ID_INDEX_SIZE;
    int const static FT_UL_BUF_WITH_ROOM_SIZE  = FT_UL_BUFFER_SIZE + SIZE_DEF::ROOM_ID_INDEX_SIZE;
};
