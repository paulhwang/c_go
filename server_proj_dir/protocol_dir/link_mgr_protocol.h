/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_protocol.h
*/

#pragma once

#define LINK_MGR_PROTOCOL_COMMAND_IS_MALLOC_LINK 'L'
#define LINK_MGR_PROTOCOL_RESPOND_IS_MALLOC_LINK 'l'
#define LINK_MGR_PROTOCOL_COMMAND_IS_MALLOC_SESSION 'S'
#define LINK_MGR_PROTOCOL_RESPOND_IS_MALLOC_SESSION 's'
#define LINK_MGR_PROTOCOL_COMMAND_IS_PUT_SESSION_DATA 'P'
#define LINK_MGR_PROTOCOL_RESPOND_IS_PUT_SESSION_DATA 'p'
//#define LINK_MGR_PROTOCOL_COMMAND_IS_FREE_LINK 'F'
//#define LINK_MGR_PROTOCOL_RESPOND_IS_FREE_LINK 'f'
//#define LINK_MGR_PROTOCOL_COMMAND_IS_TRANSFER_DATA 'D'
//#define LINK_MGR_PROTOCOL_RESPOND_IS_TRANSFER_DATA 'd'

//#define LINK_MGR_PROTOCOL_GAME_NAME_IS_GO 'G'

#define LINK_MGR_DATA_BUFFER_SIZE 512

#define LINK_MGR_PROTOCOL_LINK_ID_SIZE 4
#define LINK_MGR_PROTOCOL_LINK_INDEX_SIZE 4
#define LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE (LINK_MGR_PROTOCOL_LINK_ID_SIZE + LINK_MGR_PROTOCOL_LINK_INDEX_SIZE)

#define LINK_MGR_PROTOCOL_SESSION_ID_SIZE 4
#define LINK_MGR_PROTOCOL_SESSION_INDEX_SIZE 4
#define LINK_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE (LINK_MGR_PROTOCOL_SESSION_ID_SIZE + LINK_MGR_PROTOCOL_SESSION_INDEX_SIZE)
