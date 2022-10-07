/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fe_def.h
*/

#pragma once

class FE_DEF {
public:
    int  const static FE_COMMAND_SIZE = 1;

    char const static FE_REGISTER_COMMAND                  = 'R';
    char const static FE_REGISTER_RESPONSE                 = 'r';
    char const static FE_LOGIN_COMMAND                     = 'I';
    char const static FE_LOGIN_RESPONSE                    = 'i';
    char const static FE_LOGOUT_COMMAND                    = 'O';
    char const static FE_LOGOUT_RESPONSE                   = 'o';
    char const static FE_GET_LINK_DATA_COMMAND             = 'D';
    char const static FE_GET_LINK_DATA_RESPONSE            = 'd';
    char const static FE_GET_NAME_LIST_COMMAND             = 'N';
    char const static FE_GET_NAME_LIST_RESPONSE            = 'n';
    char const static FE_SETUP_SESSION_COMMAND             = 'S';
    char const static FE_SETUP_SESSION_RESPONSE            = 's';
    char const static FE_SETUP_SESSION2_COMMAND            = 'Y';
    char const static FE_SETUP_SESSION2_RESPONSE           = 'y';
    char const static FE_SETUP_SESSION3_COMMAND            = 'Z';
    char const static FE_SETUP_SESSION3_RESPONSE           = 'z';
    char const static FE_FREE_SESSION_COMMAND              = 'V';
    char const static FE_FREE_SESSION_RESPONSE             = 'v';
    char const static FE_PUT_SESSION_DATA_COMMAND          = 'P';
    char const static FE_PUT_SESSION_DATA_RESPONSE         = 'p';
    char const static FE_GET_SESSION_DATA_COMMAND          = 'G';
    char const static FE_GET_SESSION_DATA_RESPONSE         = 'g';
    char const static FE_MESSAGE_COMMAND                   = 'M';
    char const static FE_MESSAGE_RESPONSE                  = 'm';

    char const static FE_DEVICE_TYPE_NODEJS     = 'N';
    char const static FE_DEVICE_TYPE_IPHONE     = 'I';
    char const static FE_DEVICE_TYPE_ANDROID    = 'A';

    char const static FE_GET_LINK_DATA_RESPONSE_YES = 'Y';
    char const static FE_GET_LINK_DATA_RESPONSE_NO  = 'N';

    char const static FE_GROUP_MODE_SOLO     = 'S';
    char const static FE_GROUP_MODE_DUET     = 'D';
    char const static FE_GROUP_MODE_ENSEMBLE = 'E';

    char const static FE_ROOM_STATUS_PREPARING = 'P';
    char const static FE_ROOM_STATUS_READY     = 'R';

    char const static FE_APP_IS_GO_GAME     = 'G';

    char const static FE_GET_LINK_DATA_TYPE_PENDING_SESSION  = 'S';
    char const static FE_GET_LINK_DATA_TYPE_PENDING_SESSION3 = 'T';
    char const static FE_GET_LINK_DATA_TYPE_PENDING_DATA     = 'D';
    char const static FE_GET_LINK_DATA_TYPE_NAME_LIST        = 'N';
};
