/*
  Copyrights reserved
  Written by Paul Hwang
  File name: size_def.h
*/

#pragma once

#include "../../phwang_dir/net_dir/port_dir/port_class.h"

class SIZE_DEF {
public:
    int const static FABRIC_TIME_STAMP_SIZE = 10;

    int const static AJAX_ID_SIZE = 3;

    int const static NAME_LIST_TAG_SIZE = 3;
    int const static NAME_LIST_TAG_MAX_VALUE = 999;
    int const static NAME_LIST_BUFFER_SIZE = PortClass::RECEIVE_BUFFER_SIZE;

    char const static *FAKE_LINK_II;
    int const static LINK_ID_INITIAL_VALUE = 1000;
    int const static LINK_ID_SIZE = 4;
    int const static LINK_INDEX_SIZE = 4;
    int const static LINK_II_SIZE = LINK_ID_SIZE + LINK_INDEX_SIZE;

    char const static *FAKE_SESSION_ID_INDEX;
    int const static SESSION_ID_INITIAL_VALUE = 3000;
    int const static SESSION_ID_SIZE = 4;
    int const static SESSION_INDEX_SIZE = 4;
    int const static SESSION_II_SIZE = SESSION_ID_SIZE + SESSION_INDEX_SIZE;

    int const static GROUP_ID_INITIAL_VALUE = 5000;
    int const static GROUP_ID_SIZE = 4;
    int const static GROUP_INDEX_SIZE = 4;
    int const static GROUP_II_SIZE = GROUP_ID_SIZE + GROUP_INDEX_SIZE;

    int const static ROOM_ID_INITIAL_VALUE = 7000;
    int const static ROOM_ID_SIZE = 4;
    int const static ROOM_INDEX_SIZE = 4;
    int const static ROOM_II_SIZE = ROOM_ID_SIZE + ROOM_INDEX_SIZE;

    int const static BASE_ID_INITIAL_VALUE = 9000;
    int const static BASE_ID_SIZE = 4;
    int const static BASE_INDEX_SIZE = 4;
    int const static BASE_II_SIZE = BASE_ID_SIZE + BASE_INDEX_SIZE;
};
