/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_protocol.h
*/

#pragma once

#define LINK_MGR_DATA_BUFFER_SIZE 512

#define LINK_MGR_PROTOCOL_SESSION_ID_SIZE 4
#define LINK_MGR_PROTOCOL_SESSION_INDEX_SIZE 4
#define LINK_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE (LINK_MGR_PROTOCOL_SESSION_ID_SIZE + LINK_MGR_PROTOCOL_SESSION_INDEX_SIZE)

class ListMgrProtocolClass {
public:
    int const static LINK_ID_SIZE = 4;
    int const static LINK_INDEX_SIZE = 4;
    int const static LINK_ID_INDEX_SIZE = LINK_ID_SIZE + LINK_INDEX_SIZE;
};
