/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_def.h
*/

#include "size_def.h"

#pragma once

class FABRIC_DEF {
public:
    /* uplink data buffer size */
    int const static FE_UL_BUFFER_SIZE = 1 + 1;
    int const static FE_UL_BUF_WITH_GROUP_SIZE = FE_UL_BUFFER_SIZE + SIZE_DEF::GROUP_ID_INDEX_SIZE;
    int const static FE_UL_BUF_WITH_ROOM_SIZE  = FE_UL_BUFFER_SIZE + SIZE_DEF::ROOM_ID_INDEX_SIZE;
};
