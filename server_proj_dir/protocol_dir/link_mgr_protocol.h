/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_protocol.h
*/

#pragma once

#define LINK_MGR_DATA_BUFFER_SIZE1 512

class ListMgrProtocolClass {
public:
    int const static LINK_MGR_DATA_BUFFER_SIZE = 512;

    int const static LINK_ID_SIZE = 4;
    int const static LINK_INDEX_SIZE = 4;
    int const static LINK_ID_INDEX_SIZE = LINK_ID_SIZE + LINK_INDEX_SIZE;

    int const static SESSION_ID_SIZE = 4;
    int const static SESSION_INDEX_SIZE = 4;
    int const static SESSION_ID_INDEX_SIZE = SESSION_ID_SIZE + SESSION_INDEX_SIZE;
};
