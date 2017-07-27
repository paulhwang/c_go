/*
  Copyrights reserved
  Written by Paul Hwang
  File name: web_fabric_protocol.h
*/

#pragma once

#define WEB_FABRIC_PROTOCOL_COMMAND_IS_MALLOC_LINK 'L'
#define WEB_FABRIC_PROTOCOL_RESPOND_IS_MALLOC_LINK 'l'
#define WEB_FABRIC_PROTOCOL_COMMAND_IS_GET_LINK_DATA 'D'
#define WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA 'd'
#define WEB_FABRIC_PROTOCOL_COMMAND_IS_GET_NAME_LIST 'N'
#define WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_NAME_LIST 'n'
#define WEB_FABRIC_PROTOCOL_COMMAND_IS_MALLOC_SESSION 'S'
#define WEB_FABRIC_PROTOCOL_RESPOND_IS_MALLOC_SESSION 's'
#define WEB_FABRIC_PROTOCOL_COMMAND_IS_MALLOC_SESSION_REPLY 'R'
#define WEB_FABRIC_PROTOCOL_RESPOND_IS_MALLOC_SESSION_REPLY 'r'
#define WEB_FABRIC_PROTOCOL_COMMAND_IS_PUT_SESSION_DATA 'P'
#define WEB_FABRIC_PROTOCOL_RESPOND_IS_PUT_SESSION_DATA 'p'
#define WEB_FABRIC_PROTOCOL_COMMAND_IS_GET_SESSION_DATA 'G'
#define WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_SESSION_DATA 'g'

#define WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA_PENDING_SESSION 'S'
#define WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA_PENDING_SESSION_3 'T'
#define WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA_PENDING_DATA 'D'
#define WEB_FABRIC_PROTOCOL_RESPOND_IS_GET_LINK_DATA_NAME_LIST 'N'

#define WEB_FABRIC_PROTOCOL_NAME_LIST_TAG_SIZE 3
#define WEB_FABRIC_PROTOCOL_AJAX_ID_SIZE 3

#define WEB_FABRIC_PROTOCOL_LINK_ID_SIZE LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE
#define WEB_FABRIC_PROTOCOL_SESSION_ID_SIZE LINK_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE
