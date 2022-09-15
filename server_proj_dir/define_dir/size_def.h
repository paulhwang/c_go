/*
  Copyrights reserved
  Written by Paul Hwang
  File name: size_def.h
*/

#pragma once

class SIZE_DEF {
public:
    char const static *FAKE_LINK_ID_INDEX;
    int const static LINK_ID_INITIAL_VALUE = 100;
    int const static LINK_ID_SIZE = 4;
    int const static LINK_INDEX_SIZE = 4;
    int const static LINK_ID_INDEX_SIZE = LINK_ID_SIZE + LINK_INDEX_SIZE;

    char const static *FAKE_SESSION_ID_INDEX;
    int const static SESSION_ID_INITIAL_VALUE = 300;
    int const static SESSION_ID_SIZE = 4;
    int const static SESSION_INDEX_SIZE = 4;
    int const static SESSION_ID_INDEX_SIZE = SESSION_ID_SIZE + SESSION_INDEX_SIZE;

    int const static GROUP_ID_INITIAL_VALUE = 500;
    int const static GROUP_ID_SIZE = 4;
    int const static GROUP_INDEX_SIZE = 4;
    int const static GROUP_ID_INDEX_SIZE = GROUP_ID_SIZE + GROUP_INDEX_SIZE;

    int const static ROOM_ID_INITIAL_VALUE = 700;
    int const static ROOM_ID_SIZE = 4;
    int const static ROOM_INDEX_SIZE = 4;
    int const static ROOM_ID_INDEX_SIZE = ROOM_ID_SIZE + ROOM_INDEX_SIZE;

    int const static BASE_ID_INITIAL_VALUE = 900;
    int const static BASE_ID_SIZE = 4;
    int const static BASE_INDEX_SIZE = 4;
    int const static BASE_ID_INDEX_SIZE = BASE_ID_SIZE + BASE_INDEX_SIZE;

    int const static NAME_LIST_TAG_SIZE = 3;

    int const static AJAX_ID_SIZE = 3;
};