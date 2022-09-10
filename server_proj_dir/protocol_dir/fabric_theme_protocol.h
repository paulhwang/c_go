/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_theme_protocol.h
*/

#pragma once

class FT_Command_Class {
public:
    char const static SETUP_ROOM_COMMAND  = 'R';
    char const static SETUP_ROOM_RESPONSE = 'r';
    char const static PUT_ROOM_DATA_COMMAND  = 'D';
    char const static PUT_ROOM_DATA_RESPONSE = 'd';
};
