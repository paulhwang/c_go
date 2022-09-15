/*
  Copyrights reserved
  Written by Paul Hwang
  File name: ft_def.h
*/

#pragma once

class FT_DEF {
public:
    int  const static FT_COMMAND_SIZE = 1;
    char const static FT_SETUP_ROOM_COMMAND     = 'R';
    char const static FT_SETUP_ROOM_RESPONSE    = 'r';
    char const static FT_PUT_ROOM_DATA_COMMAND  = 'D';
    char const static FT_PUT_ROOM_DATA_RESPONSE = 'd';
};
