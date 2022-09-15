/*
  Copyrights reserved
  Written by Paul Hwang
  File name: ft_command_define.h
*/

#pragma once

#include "size_def.h"
#include "result_def.h"

class FT_CommandClass {
public:
    int const static FT_DL_COMMAND_SIZE = 1;
    char const static SETUP_ROOM_COMMAND  = 'R';
    char const static SETUP_ROOM_RESPONSE = 'r';
    char const static PUT_ROOM_DATA_COMMAND  = 'D';
    char const static PUT_ROOM_DATA_RESPONSE = 'd';
};
