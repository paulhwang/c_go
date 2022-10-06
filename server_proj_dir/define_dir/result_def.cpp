/*
  Copyrights reserved
  Written by Paul Hwang
  File name: result_def.cpp
*/

#include "result_def.h"

char const *RESULT_DEF::RESULT_SUCCEED                    = "00";
char const *RESULT_DEF::RESULT_ACCOUNT_NAME_NOT_EXIST     = "01";
char const *RESULT_DEF::RESULT_ACCOUNT_NAME_ALREADY_EXIST = "02";
char const *RESULT_DEF::RESULT_PASSWORD_MATCH             = "05";
char const *RESULT_DEF::RESULT_PASSWORD_NOT_MATCH         = "06";

char const *RESULT_DEF::RESULT_DB_SELECT_FAIL             = "21";
char const *RESULT_DEF::RESULT_DB_EMPTY_TABLE             = "22";
char const *RESULT_DEF::RESULT_DB_ERROR                   = "23";

char const *RESULT_DEF::RESULT_TIME_STAMP_NOT_MATCH       = "50";
char const *RESULT_DEF::RESULT_LINK_NOT_EXIST             = "51";
char const *RESULT_DEF::RESULT_SESSION_NOT_EXIST          = "52";
char const *RESULT_DEF::RESULT_NULL_LINK                  = "53";
char const *RESULT_DEF::RESULT_NULL_SESSION               = "54";
char const *RESULT_DEF::RESULT_NULL_ROOM                  = "56";
char const *RESULT_DEF::RESULT_MALLOC_SESSION_FAIL        = "57";
char const *RESULT_DEF::RESULT_MALLOC_GROUP_FAIL          = "58";
char const *RESULT_DEF::RESULT_SECOND_LINK_NOT_EXIST      = "59";
char const *RESULT_DEF::RESULT_NULL_SECOND_SESSION        = "60";
char const *RESULT_DEF::RESULT_SESSION_DATA_NOT_AVAILABLE = "61";
char const *RESULT_DEF::RESULT_MALLOC_SECOND_SESSION_FAIL = "62";
char const *RESULT_DEF::RESULT_ALMOST_SUCCEED             = "63";

char const *RESULT_DEF::RESULT_MALLOC_ROOM_FAIL           = "71";

