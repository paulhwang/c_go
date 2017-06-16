/*
  Copyrights reserved
  Written by Paul Hwang
  File name: group_room_protocol.h
*/

#pragma once

#define GROUP_ROOM_PROTOCOL_TRANSPORT_PORT_NUMBER 8009

#define GROUP_MGR_DATA_BUFFER_SIZE 512

#define GROUP_MGR_PROTOCOL_GROUP_ID_SIZE 4
#define GROUP_MGR_PROTOCOL_GROUP_INDEX_SIZE 4
#define GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE (GROUP_MGR_PROTOCOL_GROUP_ID_SIZE + GROUP_MGR_PROTOCOL_GROUP_INDEX_SIZE)

#define ROOM_MGR_DATA_BUFFER_SIZE 512

#define ROOM_MGR_PROTOCOL_ROOM_ID_SIZE 4
#define ROOM_MGR_PROTOCOL_ROOM_INDEX_SIZE 4
#define ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE (ROOM_MGR_PROTOCOL_ROOM_ID_SIZE + ROOM_MGR_PROTOCOL_ROOM_INDEX_SIZE)
