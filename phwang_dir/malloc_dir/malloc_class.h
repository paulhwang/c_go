/*
  Copyrights reserved
  Written by Paul Hwang
  File name: malloc_class.h
*/

#pragma once

#define MALLOC_CLASS_USER_TABLE_SIZE 20

class MallocClass
{
    char const *objectName(void) {return "MallocClass";}
    int theDebugCode;
    int theUserTable[MALLOC_CLASS_USER_TABLE_SIZE];

    void checkWhoTable(void);
    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    MallocClass(int debug_code_val);
    ~MallocClass(void);
    
    int const static receiveThreadFunction = 0;
    int const static tpTranferReceiveThreadFunction = 1;
    int const static receiveThreadFunction2 = 2;
    int const static startTransmitThread  = 3;
    int const static UTHEME_BASE = 4;
    int const static UTHEME_BASE_PUT_BASE_DATA = 4;
    int const static DTHEME_PUT_ROOM_DATA1 = 4;
    int const static DTHEME_PUT_ROOM_DATA2 = 4;
    int const static DTHEME_SETUP_ROOM1 = 4;
    int const static DTHEME_SETUP_ROOM2 = 4;
    int const static DENGINE_SETUP_BASE = 4;
    int const static DENGINE_PUT_BASE_DATA = 4;
    int const static BAD_LINK = 5;
    int const static BAD_SESSION = 5;
    int const static SIGN_UP = 5;
    int const static SIGN_IN = 5;
    int const static DATAGRAM = 5;
    int const static FREE_LINK = 5;
    int const static FREE_LINK_ERROR = 5;
    int const static GET_LINK_DATA = 5;
    int const static GET_LINK_DATA_ERROR = 5;
    int const static GET_NAME_LIST = 5;
    int const static GET_NAME_LIST_ERROR = 5;
    int const static SETUP_SESSION = 5;
    int const static SETUP_SESSION_ERROR = 5;
    int const static SETUP_SESSION2 = 5;
    int const static SETUP_SESSION2_ERROR = 5;
    int const static SETUP_SESSION3 = 5;
    int const static PUT_SESSION_DATA0 = 5;
    int const static PUT_SESSION_DATA1 = 5;
    int const static PUT_SESSION_DATA_ERROR = 5;
    int const static GET_SESSION_DATA = 5;
    int const static GET_SESSION_DATA_ERROR = 5;
    int const static MALLOC_ROOM = 5;
    int const static ENCODE_STRING1111111111111111111 = 6;
    int const static encodeNumberMalloc = 7;
    int const static encodeStringMalloc = 8;
    int const static decodeStringMalloc = 9;
    int const static TEST_SETUP_LINK = 10;
    int const static DB_ACCOUNT_DEFAULT_NAME = 11;
    int const static MAX_INDEX = 11;

    void *phwangMalloc(int size_val, int who_val);
    void phwangFree(void *data_val);
};
