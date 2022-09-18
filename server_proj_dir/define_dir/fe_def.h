/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fe_def.h
*/

#pragma once

class FE_DEF {
public:
    int  const static FE_COMMAND_SIZE              = 1;
    char const static FE_SIGN_UP_COMMAND           = 'U';
    char const static FE_SIGN_UP_RESPONSE          = 'u';
    char const static FE_SETUP_LINK_COMMAND        = 'L';
    char const static FE_SETUP_LINK_RESPONSE       = 'l';
    char const static FE_SIGN_OFF_COMMAND          = 'O';
    char const static FE_SIGN_OFF_RESPONSE         = 'o';
    char const static FE_GET_LINK_DATA_COMMAND     = 'D';
    char const static FE_GET_LINK_DATA_RESPONSE    = 'd';
    char const static FE_GET_NAME_LIST_COMMAND     = 'N';
    char const static FE_GET_NAME_LIST_RESPONSE    = 'n';
    char const static FE_SETUP_SESSION_COMMAND     = 'S';
    char const static FE_SETUP_SESSION_RESPONSE    = 's';
    char const static FE_SETUP_SESSION2_COMMAND    = 'R';
    char const static FE_SETUP_SESSION2_RESPONSE   = 'r';
    char const static FE_SETUP_SESSION3_COMMAND    = 'T';
    char const static FE_SETUP_SESSION3_RESPONSE   = 't';
    char const static FE_FREE_SESSION_COMMAND      = 'Y';
    char const static FE_FREE_SESSION_RESPONSE     = 'y';
    char const static FE_PUT_SESSION_DATA_COMMAND  = 'P';
    char const static FE_PUT_SESSION_DATA_RESPONSE = 'p';
    char const static FE_GET_SESSION_DATA_COMMAND  = 'G';
    char const static FE_GET_SESSION_DATA_RESPONSE = 'g';
    char const static FE_MESSAGE_COMMAND  = 'M';
    char const static FE_MESSAGE_RESPONSE = 'm';

    char const static RESPOND_IS_GET_LINK_DATA_PENDING_SESSION  = 'S';
    char const static RESPOND_IS_GET_LINK_DATA_PENDING_SESSION3 = 'T';
    char const static RESPOND_IS_GET_LINK_DATA_PENDING_DATA     = 'D';
    char const static RESPOND_IS_GET_LINK_DATA_NAME_LIST        = 'N';
};
