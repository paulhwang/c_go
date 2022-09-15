/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fe_command_define.cpp
*/

#include "fe_command_define.h"

char const *RESULT_DEF::RESULT_SUCCEED                    = "00";
char const *RESULT_DEF::RESULT_ACCOUNT_NAME_NOT_EXIST     = "01";
char const *RESULT_DEF::RESULT_ACCOUNT_NAME_ALREADY_EXIST = "02";
char const *RESULT_DEF::RESULT_PASSWORD_NOT_MATCH         = "05";

char const *RESULT_DEF::RESULT_DB_SELECT_FAIL             = "21";

char const *RESULT_DEF::RESULT_LINK_NOT_EXIST             = "51";
char const *RESULT_DEF::RESULT_SESSION_NOT_EXIST          = "52";
char const *RESULT_DEF::RESULT_NULL_LINK                  = "53";
char const *RESULT_DEF::RESULT_NULL_SESSION               = "54";
char const *RESULT_DEF::RESULT_NULL_ROOM                  = "56";
char const *RESULT_DEF::RESULT_MALLOC_SESSION_FAIL        = "57";
char const *RESULT_DEF::RESULT_MALLOC_GROUP_FAIL          = "58";
char const *RESULT_DEF::RESULT_HIS_LINK_NOT_EXIST         = "59";
char const *RESULT_DEF::RESULT_NULL_HIS_SESSION           = "60";

char const *RESULT_DEF::RESULT_MALLOC_ROOM_FAIL           = "71";

