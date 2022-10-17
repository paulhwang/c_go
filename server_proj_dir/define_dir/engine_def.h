/*
  Copyrights reserved
  Written by Paul Hwang
  File name: engine_def.h
*/

#pragma once

#include "size_def.h"

class ENGINE_DEF {
public:
    /* downlink data buffer size */
    int const static TE_DL_HEADER_SIZE = TE_DEF::TE_COMMAND_SIZE + 1;
    int const static TE_DL_BUFFER_SIZE = TE_DL_HEADER_SIZE + RESULT_DEF::RESULT_SIZE;
    int const static TE_DL_BUF_WITH_ROOM_SIZE = TE_DL_BUFFER_SIZE + SIZE_DEF::ROOM_II_SIZE;
    int const static TE_DL_BUF_WITH_ROOM_BASE_SIZE = TE_DL_BUF_WITH_ROOM_SIZE + SIZE_DEF::BASE_II_SIZE;
};
