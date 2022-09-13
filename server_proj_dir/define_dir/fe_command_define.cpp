/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fe_command_define.cpp
*/

#include "fe_command_define.h"

char const *FE_CommandClass::FE_RESULT_SUCCEED                = "00";
char const *FE_CommandClass::FE_RESULT_ACCOUNT_NAME_NOT_EXIST = "01";
char const *FE_CommandClass::FE_RESULT_PASSWORD_NOT_MATCH     = "02";
char const *FE_CommandClass::FE_RESULT_LINK_NOT_EXIST         = "11";
char const *FE_CommandClass::FE_RESULT_SESSION_NOT_EXIST      = "12";


char const *FE_CommandClass::FAKE_LINK_ID_INDEX    = "99990000";
char const *FE_CommandClass::FAKE_SESSION_ID_INDEX = "99980000";
