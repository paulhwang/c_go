/*
  Copyrights reserved
  Written by Paul Hwang
  File name: te_def.h
*/

#pragma once

class TE_DEF {
public:
    int  const static TE_COMMAND_SIZE = 1;
    char const static TE_SETUP_BASE_COMMAND  = 'B';
    char const static TE_SETUP_BASE_RESPONSE = 'b';
    char const static TE_PUT_BASE_DATA_COMMAND  = 'D';
    char const static TE_PUT_BASE_DATA_RESPONSE = 'd';
};
