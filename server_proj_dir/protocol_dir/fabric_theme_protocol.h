/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_theme_protocol.h
*/

#pragma once

#define FABRIC_THEME_PROTOCOL_COMMAND_IS_SETUP_ROOM 'R'
#define FABRIC_THEME_PROTOCOL_RESPOND_IS_SETUP_ROOM 'r'
#define FABRIC_THEME_PROTOCOL_COMMAND_IS_PUT_ROOM_DATA 'D'
#define FABRIC_THEME_PROTOCOL_RESPOND_IS_PUT_ROOM_DATA 'd'

class FT_Command_Class {
public:
    char const static SETUP_ROOM_COMMAND  = 'R';
    char const static SETUP_ROOM_RESPONSE = 'r';
    char const static PUT_ROOM_DATA_COMMAND  = 'D';
    char const static PUT_ROOM_DATA_RESPONSE = 'd';
};
