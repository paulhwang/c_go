/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_theme_protocol.h
*/

#pragma once

class FT_Command_Class {
public:
    int const static FT_DATA_BUFFER_SIZE = 512;

    char const static SETUP_ROOM_COMMAND  = 'R';
    char const static SETUP_ROOM_RESPONSE = 'r';
    char const static PUT_ROOM_DATA_COMMAND  = 'D';
    char const static PUT_ROOM_DATA_RESPONSE = 'd';

    int const static ROOM_ID_SIZE = 4;
    int const static ROOM_INDEX_SIZE = 4;
    int const static ROOM_ID_INDEX_SIZE = ROOM_ID_SIZE + ROOM_INDEX_SIZE;
};
