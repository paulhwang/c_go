/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fe_def.h
*/

#pragma once

class FE_DEF {
public:
    int  const static FE_COMMAND_SIZE = 1;

    char const static REGISTER_COMMAND                  = 'U';
    char const static REGISTER_RESPONSE                 = 'u';
    char const static LOGIN_COMMAND                     = 'I';
    char const static LOGIN_RESPONSE                    = 'i';
    char const static LOGOUT_COMMAND                    = 'O';
    char const static LOGOUT_RESPONSE                   = 'o';
    char const static GET_LINK_DATA_COMMAND             = 'D';
    char const static GET_LINK_DATA_RESPONSE            = 'd';
    char const static GET_NAME_LIST_COMMAND             = 'N';
    char const static GET_NAME_LIST_RESPONSE            = 'n';
    char const static SETUP_SESSION_COMMAND             = 'S';
    char const static SETUP_SESSION_RESPONSE            = 's';
    char const static SETUP_SESSION2_COMMAND            = 'Y';
    char const static SETUP_SESSION2_RESPONSE           = 'y';
    char const static SETUP_SESSION3_COMMAND            = 'Z';
    char const static SETUP_SESSION3_RESPONSE           = 'z';
    char const static FREE_SESSION_COMMAND              = 'V';
    char const static FREE_SESSION_RESPONSE             = 'v';
    char const static PUT_SESSION_DATA_COMMAND          = 'P';
    char const static PUT_SESSION_DATA_RESPONSE         = 'p';
    char const static GET_SESSION_DATA_COMMAND          = 'G';
    char const static GET_SESSION_DATA_RESPONSE         = 'g';
    char const static READ_FILE_COMMAND                 = 'R';
    char const static READ_FILE_RESPONSE                = 'r';
    char const static READ_MORE_FILE_COMMAND            = 'B';
    char const static READ_MORE_FILE_RESPONSE           = 'b';
    char const static WRITE_FILE_COMMAND                = 'W';
    char const static WRITE_FILE_RESPONSE               = 'w';
    char const static WRITE_MORE_FILE_COMMAND           = 'C';
    char const static WRITE_MORE_FILE_RESPONSE          = 'c';
    char const static MESSAGE_COMMAND                   = 'M';
    char const static MESSAGE_RESPONSE                  = 'm';

    char const static FE_DEVICE_TYPE_NODEJS     = 'N';
    char const static FE_DEVICE_TYPE_IPHONE     = 'I';
    char const static FE_DEVICE_TYPE_ANDROID    = 'A';

    char const static FE_GROUP_MODE_SOLO     = 'S';
    char const static FE_GROUP_MODE_DUET     = 'D';
    char const static FE_GROUP_MODE_ENSEMBLE = 'E';

    char const static FE_ROOM_STATUS_PREPARING = 'P';
    char const static FE_ROOM_STATUS_READY     = 'R';

    char const static FE_APP_IS_GO_GAME     = 'G';

    char const static FE_GET_LINK_DATA_LENGTH_SIZE = 2;
    char const static FE_GET_LINK_DATA_TYPE_PENDING_SESSION2 = 'Y';
    char const static FE_GET_LINK_DATA_TYPE_PENDING_SESSION3 = 'Z';
    char const static FE_GET_LINK_DATA_TYPE_PENDING_DATA     = 'D';
    char const static FE_GET_LINK_DATA_TYPE_NAME_LIST        = 'N';
};
