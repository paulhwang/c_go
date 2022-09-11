/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_theme_protocol.h
*/

#pragma once

class FT_CommandClass {
public:
    int const static FT_DL_DATA_BUF_SIZE = 512;
    int const static FT_UL_DATA_BUF_SIZE = 512;

    char const static SETUP_ROOM_COMMAND  = 'R';
    char const static SETUP_ROOM_RESPONSE = 'r';
    char const static PUT_ROOM_DATA_COMMAND  = 'D';
    char const static PUT_ROOM_DATA_RESPONSE = 'd';

    int const static ROOM_ID_SIZE = 4;
    int const static ROOM_INDEX_SIZE = 4;
    int const static ROOM_ID_INDEX_SIZE = ROOM_ID_SIZE + ROOM_INDEX_SIZE;

    int const static GROUP_ID_SIZE = 4;
    int const static GROUP_INDEX_SIZE = 4;
    int const static GROUP_ID_INDEX_SIZE = GROUP_ID_SIZE + GROUP_INDEX_SIZE;
};
