/*
  Copyrights reserved
  Written by Paul Hwang
  File name: theme_engine_protocol.h
*/

#pragma once

class TE_Command_Class {
public:
    char const static SETUP_BASE_COMMAND  = 'B';
    char const static SETUP_BASE_RESPONSE = 'b';
    char const static PUT_BASE_DATA_COMMAND  = 'D';
    char const static PUT_BASE_DATA_RESPONSE = 'd';
};
