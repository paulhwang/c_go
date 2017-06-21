# Copyrights reserved
# Written by Paul Hwang

include Makefile.inc

SERVER_PROJ_DIR = server_proj_dir
CLIENT_PROJ_DIR = client_proj_dir
PHWANG_DIR = phwang_dir
INCLUDE_DIR = include_dir
PROTOCOL_DIR = $(INCLUDE_DIR)/protocol_dir
JSON_DIR     = $(PHWANG_DIR)/json_dir
SUSPEND_DIR  = $(PHWANG_DIR)/suspend_dir
LIST_MGR_DIR = $(PHWANG_DIR)/list_mgr_dir
QUEUE_DIR    = $(PHWANG_DIR)/queue_dir
NET_DIR      = $(PHWANG_DIR)/net_dir
SERVER_DIR   = $(SERVER_PROJ_DIR)/server_dir
FABRIC_DIR   = $(SERVER_PROJ_DIR)/fabric_dir
BASE_MGR_DIR = $(SERVER_PROJ_DIR)/base_mgr_dir
THEME_DIR    = $(SERVER_PROJ_DIR)/theme_dir
D_FABRIC_DIR  = $(FABRIC_DIR)/d_fabric_dir
U_FABRIC_DIR  = $(FABRIC_DIR)/u_fabric_dir
LINK_MGR_DIR  = $(FABRIC_DIR)/link_mgr_dir
GROUP_MGR_DIR = $(FABRIC_DIR)/group_mgr_dir
D_THEME_DIR  = $(THEME_DIR)/d_theme_dir
U_THEME_DIR  = $(THEME_DIR)/u_theme_dir
ROOM_MGR_DIR = $(THEME_DIR)/room_mgr_dir
GO_BASE_DIR = $(BASE_MGR_DIR)/go_base_dir
CLIENT_DIR = $(CLIENT_PROJ_DIR)/client_dir

DIRS = $(PHWANG_DIR) $(SERVER_PROJ_DIR) $(CLIENT_PROJ_DIR)

JSON_OBJS = $(JSON_DIR)/json_class.o 
SUSPEND_OBJS = $(SUSPEND_DIR)/suspend_class.o 
LIST_MGR_OBJS = $(LIST_MGR_DIR)/list_mgr_class.o $(LIST_MGR_DIR)/list_entry_class.o
QUEUE_OBJS = $(QUEUE_DIR)/queue_entry_class.o $(QUEUE_DIR)/queue_class.o
NET_OBJS = $(NET_DIR)/tp_server_class.o $(NET_DIR)/tp_transfer_class.o $(NET_DIR)/tp_transfer_transmit.o $(NET_DIR)/tp_transfer_receive.o 
PHWANG_OBJS = $(PHWANG_DIR)/phwang.o $(PHWANG_DIR)/phwang_class.o $(JSON_OBJS) $(SUSPEND_OBJS) $(LIST_MGR_OBJS) $(QUEUE_OBJS) $(NET_OBJS) 

SERVER_OBJS = $(SERVER_DIR)/go_server.o $(SERVER_DIR)/main_class.o
LINK_MGR_OBJS = $(LINK_MGR_DIR)/link_mgr_class.o $(LINK_MGR_DIR)/link_class.o $(LINK_MGR_DIR)/session_mgr_class.o $(LINK_MGR_DIR)/session_class.o 
GROUP_MGR_OBJS = $(GROUP_MGR_DIR)/group_mgr_class.o $(GROUP_MGR_DIR)/group_class.o 
D_FABRIC_OBJS =  $(LINK_MGR_OBJS) $(D_FABRIC_DIR)/d_fabric_class.o $(D_FABRIC_DIR)/d_fabric_transmit.o $(D_FABRIC_DIR)/d_fabric_parse.o
U_FABRIC_OBJS = $(GROUP_MGR_OBJS) $(U_FABRIC_DIR)/u_fabric_class.o $(U_FABRIC_DIR)/u_fabric_transmit.o $(U_FABRIC_DIR)/u_fabric_parse.o 
FABRIC_OBJS = $(U_FABRIC_OBJS) $(D_FABRIC_OBJS) $(FABRIC_DIR)/fabric_class.o 
ROOM_MGR_OBJS = $(ROOM_MGR_DIR)/room_mgr_class.o $(ROOM_MGR_DIR)/room_class.o 
D_THEME_OBJS = $(ROOM_MGR_OBJS) $(D_THEME_DIR)/d_theme_class.o $(D_THEME_DIR)/d_theme_transmit.o $(D_THEME_DIR)/d_theme_parse.o 
U_THEME_OBJS = $(BASE_MGR_OBJS) $(U_THEME_DIR)/u_theme_class.o $(U_THEME_DIR)/u_theme_transmit.o $(U_THEME_DIR)/u_theme_export.o $(U_THEME_DIR)/u_theme_test.o 
GO_BASE_OBJS = $(GO_BASE_DIR)/go_base_class.o $(GO_BASE_DIR)/go_game_class.o $(GO_BASE_DIR)/go_engine_class.o $(GO_BASE_DIR)/go_board_class.o $(GO_BASE_DIR)/go_move_class.o $(GO_BASE_DIR)/go_port_class.o $(GO_BASE_DIR)/go_config_class.o $(GO_BASE_DIR)/go_group_class.o $(GO_BASE_DIR)/go_group_list_class.o
BASE_MGR_OBJS = $(BASE_MGR_DIR)/base_mgr_class.o $(BASE_MGR_DIR)/base_mgr_exports.o $(BASE_MGR_DIR)/base_mgr_parse.o $(BASE_MGR_DIR)/base_mgr_transmit.o $(BASE_MGR_DIR)/base_mgr_base.o $(GO_BASE_OBJS)
THEME_OBJS = $(U_THEME_OBJS)  $(D_THEME_OBJS) $(THEME_DIR)/theme_class.o 
SERVER_PROJ_OBJS = $(SERVER_OBJS) $(FABRIC_OBJS) $(THEME_OBJS)

CLIENT_OBJS = $(CLIENT_DIR)/go_client.o
CLIENT_PROJ_OBJS = $(CLIENT_OBJS)

SERVER = server
ALL_SERVER_OBJS	= $(PHWANG_OBJS) $(SERVER_PROJ_OBJS)

CLIENT = client 
ALL_CLIENT_OBJS	= $(PHWANG_OBJS) $(CLIENT_PROJ_OBJS) 

UTILS_OBJLIBS = lib_utils.a
GO_ROOT_OBJLIBS	= lib_root.a lib_go_base.a lib_base_mgr.a

all:	$(SERVER) $(CLIENT)

$(SERVER): $(ALL_SERVER_OBJS) 
	$(CC) -o $(SERVER) $(ALL_SERVER_OBJS) -lstdc++ -pthread

$(CLIENT): $(ALL_CLIENT_OBJS) 
	$(CC) -o $(CLIENT) $(ALL_CLIENT_OBJS) -lstdc++ -pthread

##lib_utils.a:	force_look
##	$(ECHO) looking into utils_dir : $(MAKE) $(MFLAGS)
##	cd utils_dir; $(MAKE) $(MFLAGS)

##lib_root.a lib_base_mgr.a lib_go_base.a:	force_look
##	$(ECHO) looking into root_dir : $(MAKE) $(MFLAGS)
##	cd root_dir; $(MAKE) $(MFLAGS)

clean:
	$(ECHO) cleaning up in .
	- $(RM) $(SERVER) $(CLIENT) $(ALL_SERVER_OBJS) $(ALL_CLIENT_OBJS) $(UTILS_OBJLIBS) $(GO_ROOT_OBJLIBS)
#	-for d in $(DIRS); do (cd $$d; $(MAKE) clean); done

force_look:
	true

