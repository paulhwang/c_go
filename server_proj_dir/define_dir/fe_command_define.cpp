/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fe_command_define.cpp
*/

#include "fe_command_define.h"

char const *FE_CommandClass::FE_RESULT_SUCCEED                    = "00";
char const *FE_CommandClass::FE_RESULT_ACCOUNT_NAME_NOT_EXIST     = "01";
char const *FE_CommandClass::FE_RESULT_ACCOUNT_NAME_ALREADY_EXIST = "02";
char const *FE_CommandClass::FE_RESULT_PASSWORD_NOT_MATCH         = "05";

char const *FE_CommandClass::FE_RESULT_DB_SELECT_FAIL             = "21";

char const *FE_CommandClass::FE_RESULT_LINK_NOT_EXIST             = "51";
char const *FE_CommandClass::FE_RESULT_SESSION_NOT_EXIST          = "52";
char const *FE_CommandClass::FE_RESULT_NULL_LINK                  = "53";
char const *FE_CommandClass::FE_RESULT_NULL_SESSION               = "54";
char const *FE_CommandClass::FE_RESULT_NULL_ROOM                  = "56";
char const *FE_CommandClass::FE_RESULT_MALLOC_SESSION_FAIL        = "57";
char const *FE_CommandClass::FE_RESULT_MALLOC_GROUP_FAIL          = "58";
char const *FE_CommandClass::FE_RESULT_HIS_LINK_NOT_EXIST         = "59";
char const *FE_CommandClass::FE_RESULT_NULL_HIS_SESSION           = "60";

char const *FE_CommandClass::FE_RESULT_MALLOC_ROOM_FAIL           = "71";


char const *FE_CommandClass::FAKE_LINK_ID_INDEX    = "99990000";
char const *FE_CommandClass::FAKE_SESSION_ID_INDEX = "99980000";
