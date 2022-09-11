/*
  Copyrights reserved
  Written by Paul Hwang
  File name: theme_engine_protocol.h
*/

#pragma once

class TE_CommandClass {
public:
    int const static DL_DATA_BUF_SIZE = 512;
    //int const static UL_DATA_BUF_SIZE = 512;

    char const static SETUP_BASE_COMMAND  = 'B';
    char const static SETUP_BASE_RESPONSE = 'b';
    char const static PUT_BASE_DATA_COMMAND  = 'D';
    char const static PUT_BASE_DATA_RESPONSE = 'd';

    int const static BASE_ID_SIZE = 4;
    int const static BASE_INDEX_SIZE = 4;
    int const static BASE_ID_INDEX_SIZE = BASE_ID_SIZE + BASE_INDEX_SIZE;
};
