/*
  Copyrights reserved
  Written by Paul Hwang
  File name: web_fabric_protocol.h
*/

#pragma once

class FECommandClass {
public:
    int const static NAME_LIST_TAG_SIZE = 3;
    int const static AJAX_ID_SIZE = 3;

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
    char const static GET_SESSION_DATA_RESPONSE = 'G';
    char const static MMW_READ_DATA_COMMAND  = 'M';
    char const static MMW_READ_DATA_RESPONSE = 'm';

    char const static RESPOND_IS_GET_LINK_DATA_PENDING_SESSION = 'S';
    char const static RESPOND_IS_GET_LINK_DATA_PENDING_SESSION3 = 'T';
    char const static RESPOND_IS_GET_LINK_DATA_PENDING_DATA = 'D';
    char const static RESPOND_IS_GET_LINK_DATA_NAME_LIST = 'N';
};
