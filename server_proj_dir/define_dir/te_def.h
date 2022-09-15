/*
  Copyrights reserved
  Written by Paul Hwang
  File name: te_command_define.h
*/

#pragma once

class TE_CommandClass {
public:
    int const static TE_DL_COMMAND_SIZE = 1;
    char const static SETUP_BASE_COMMAND  = 'B';
    char const static SETUP_BASE_RESPONSE = 'b';
    char const static PUT_BASE_DATA_COMMAND  = 'D';
    char const static PUT_BASE_DATA_RESPONSE = 'd';
};
