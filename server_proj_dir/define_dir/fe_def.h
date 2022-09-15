/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fe_def.h
*/

#include "result_def.h"
#include "size_def.h"

#pragma once

class FE_DEF {
public:
    int const static FE_COMMAND_SIZE = 1;

    char const static SIGN_UP_COMMAND  = 'U';
    char const static SIGN_UP_RESPONSE = 'u';
    char const static SETUP_LINK_COMMAND  = 'L';
    char const static SETUP_LINK_RESPONSE = 'l';
    char const static SIGN_OFF_COMMAND  = 'F';
    char const static SIGN_OFF_RESPONSE = 'f';
    char const static GET_LINK_DATA_COMMAND  = 'D';
    char const static GET_LINK_DATA_RESPONSE = 'd';
    char const static GET_NAME_LIST_COMMAND  = 'N';
    char const static GET_NAME_LIST_RESPONSE = 'n';
    char const static SETUP_SESSION_COMMAND  = 'S';
    char const static SETUP_SESSION_RESPONSE = 's';
    char const static SETUP_SESSION2_COMMAND  = 'R';
    char const static SETUP_SESSION2_RESPONSE = 'r';
    char const static SETUP_SESSION3_COMMAND  = 'T';
    char const static SETUP_SESSION3_RESPONSE = 't';
    char const static FREE_SESSION_COMMAND  = 'Y';
    char const static FREE_SESSION_RESPONSE = 'y';
    char const static PUT_SESSION_DATA_COMMAND  = 'P';
    char const static PUT_SESSION_DATA_RESPONSE = 'p';
    char const static GET_SESSION_DATA_COMMAND  = 'G';
    char const static GET_SESSION_DATA_RESPONSE = 'g';
    char const static MESSAGE_COMMAND  = 'M';
    char const static MESSAGE_RESPONSE = 'm';

    char const static RESPOND_IS_GET_LINK_DATA_PENDING_SESSION = 'S';
    char const static RESPOND_IS_GET_LINK_DATA_PENDING_SESSION3 = 'T';
    char const static RESPOND_IS_GET_LINK_DATA_PENDING_DATA = 'D';
    char const static RESPOND_IS_GET_LINK_DATA_NAME_LIST = 'N';

    int const static FE_RESPONSE_HEADER_SIZE = FE_COMMAND_SIZE + SIZE_DEF::AJAX_ID_SIZE;
    int const static FE_RESPONSE_BUFFER_SIZE = FE_RESPONSE_HEADER_SIZE + RESULT_DEF::RESULT_SIZE + 1;
    int const static FE_RESPONSE_BUF_WITH_LINK_SIZE = FE_RESPONSE_BUFFER_SIZE + SIZE_DEF::LINK_ID_INDEX_SIZE;
    int const static FE_RESPONSE_BUF_WITH_LINK_SESSION_SIZE = FE_RESPONSE_BUF_WITH_LINK_SIZE + SIZE_DEF::SESSION_ID_INDEX_SIZE;

    int const static FE_PENDING_SESSIONS_SIZE = 512;/********TBD*******************/
    int const static FE_GET_LINK_DATA_BUF_SIZE = FE_RESPONSE_BUF_WITH_LINK_SIZE + 1024;/********TBD*******************/
};
