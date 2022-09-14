/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fe_command_define.h
*/

#pragma once

class FE_CommandClass {
public:
    int const static FE_DL_DATA_BUF_SIZE = 512;
    int const static FE_UL_DATA_BUF_SIZE = 512;

    int const static FE_COMMAND_SIZE = 1;

    char const static SIGN_UP_COMMAND  = 'U';
    char const static SIGN_UP_RESPONSE = 'u';
    char const static SETUP_LINK_COMMAND  = 'L';
    char const static SETUP_LINK_RESPONSE = 'l';
    char const static FREE_LINK_COMMAND  = 'F';
    char const static FREE_LINK_RESPONSE = 'f';
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

    /* response results */
    int const static FE_RESULT_SIZE = 2;

    char const static *FE_RESULT_SUCCEED;
    char const static *FE_RESULT_ACCOUNT_NAME_NOT_EXIST;
    char const static *FE_RESULT_ACCOUNT_NAME_ALREADY_EXIST;
    char const static *FE_RESULT_PASSWORD_NOT_MATCH;

    char const static *FE_RESULT_DB_SELECT_FAIL;

    char const static *FE_RESULT_LINK_NOT_EXIST;
    char const static *FE_RESULT_SESSION_NOT_EXIST;
    char const static *FE_RESULT_NULL_LINK;
    char const static *FE_RESULT_NULL_SESSION;
    char const static *FE_RESULT_NULL_ROOM;

    /* sizes */
    char const static *FAKE_LINK_ID_INDEX;
    int const static LINK_ID_SIZE = 4;
    int const static LINK_INDEX_SIZE = 4;
    int const static LINK_ID_INDEX_SIZE = LINK_ID_SIZE + LINK_INDEX_SIZE;

    char const static *FAKE_SESSION_ID_INDEX;
    int const static SESSION_ID_SIZE = 4;
    int const static SESSION_INDEX_SIZE = 4;
    int const static SESSION_ID_INDEX_SIZE = SESSION_ID_SIZE + SESSION_INDEX_SIZE;

    int const static NAME_LIST_TAG_SIZE = 3;

    int const static AJAX_ID_SIZE = 3;
    int const static FE_RESPONSE_HEADER_SIZE = FE_COMMAND_SIZE + AJAX_ID_SIZE;
    int const static FE_RESPONSE_BUFFER_SIZE = FE_RESPONSE_HEADER_SIZE + FE_RESULT_SIZE + 1;
    int const static FE_RESPONSE_BUF_WITH_LINK_SIZE = FE_RESPONSE_BUFFER_SIZE + LINK_ID_INDEX_SIZE;
    int const static FE_RESPONSE_BUF_WITH_LINK_SESSION_SIZE = FE_RESPONSE_BUF_WITH_LINK_SIZE + SESSION_ID_INDEX_SIZE;
};
