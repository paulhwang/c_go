/*
  Copyrights reserved
  Written by Paul Hwang
  File name: result_def.h
*/

#pragma once

class RESULT_DEF {
public:
    char const static ANSWER_YES = 'Y';
    char const static ANSWER_NO  = 'N';

    int const static RESULT_SIZE = 2;

    char const static *RESULT_SUCCEED;
    char const static *RESULT_ACCOUNT_NAME_NOT_EXIST;
    char const static *RESULT_ACCOUNT_NAME_ALREADY_EXIST;
    char const static *RESULT_PASSWORD_MATCH;
    char const static *RESULT_PASSWORD_NOT_MATCH;

    char const static *RESULT_DB_SELECT_FAIL;
    char const static *RESULT_DB_EMPTY_TABLE;
    char const static *RESULT_DB_ERROR;

    char const static *RESULT_TIME_STAMP_NOT_MATCH;
    char const static *RESULT_LINK_NOT_EXIST;
    char const static *RESULT_SESSION_NOT_EXIST;
    char const static *RESULT_NULL_LINK;
    char const static *RESULT_NULL_SESSION;
    char const static *RESULT_NULL_ROOM;
    char const static *RESULT_MALLOC_SESSION_FAIL;
    char const static *RESULT_MALLOC_GROUP_FAIL;
    char const static *RESULT_SECOND_LINK_NOT_EXIST;
    char const static *RESULT_NULL_SECOND_SESSION;
    char const static *RESULT_SESSION_DATA_NOT_AVAILABLE;
    char const static *RESULT_MALLOC_SECOND_SESSION_FAIL;
    char const static *RESULT_ALMOST_SUCCEED;
    char const static *RESULT_WAITING_FOR_ANSWER;

    char const static *RESULT_MALLOC_ROOM_FAIL;
};
