# Copyrights reserved
# Written by Paul Hwang

include Makefile.inc

SERVER_PROJ_DIR = server_proj_dir
CLIENT_PROJ_DIR = client_proj_dir
UTILS_DIR = utils_dir
INCLUDE_DIR = include_dir
PROTOCOL_DIR = $(INCLUDE_DIR)/protocol_dir
LOGIT_DIR   = $(UTILS_DIR)/logit_dir
ENCODE_DIR  = $(UTILS_DIR)/encode_dir
JSON_DIR    = $(UTILS_DIR)/json_dir
SUSPEND_DIR = $(UTILS_DIR)/suspend_dir
QUEUE_DIR   = $(UTILS_DIR)/queue_dir
TP_DIR      = $(UTILS_DIR)/tp_dir
MAIN_DIR        = $(SERVER_PROJ_DIR)/main_dir
LINK_MGR_DIR    = $(SERVER_PROJ_DIR)/link_mgr_dir
BASE_MGR_DIR    = $(SERVER_PROJ_DIR)/base_mgr_dir
GO_BASE_DIR     = $(SERVER_PROJ_DIR)/go_base_dir
SERVER_MAIN_DIR = $(SERVER_PROJ_DIR)/main_dir
CLIENT_MAIN_DIR = $(CLIENT_PROJ_DIR)/main_dir

DIRS = $(UTILS_DIR) $(SERVER_PROJ_DIR) $(CLIENT_PROJ_DIR)

MAIN_OBJS = $(MAIN_DIR)/main_class.o
LINK_MGR_OBJS = $(LINK_MGR_DIR)/link_mgr_class.o $(LINK_MGR_DIR)/link_class.o $(LINK_MGR_DIR)/session_mgr_class.o $(LINK_MGR_DIR)/session_class.o $(LINK_MGR_DIR)/link_mgr_thread.o $(LINK_MGR_DIR)/link_mgr_exports.o 
BASE_MGR_OBJS = $(BASE_MGR_DIR)/base_mgr_class.o $(BASE_MGR_DIR)/base_mgr_exports.o $(BASE_MGR_DIR)/base_mgr_thread.o 
TP_OBJS = $(TP_DIR)/tp_class.o $(TP_DIR)/tp_server.o $(TP_DIR)/tp_transfer_class.o $(TP_DIR)/tp_transfer_transmit.o $(TP_DIR)/tp_transfer_receive.o 
LOGIT_OBJS = $(LOGIT_DIR)/logit.o 
ENCODE_OBJS = $(ENCODE_DIR)/encode.o 
JSON_OBJS = $(JSON_DIR)/json_class.o 
SUSPEND_OBJS = $(SUSPEND_DIR)/suspend_class.o 
QUEUE_OBJS = $(QUEUE_DIR)/queue_entry_class.o $(QUEUE_DIR)/queue_class.o
UTILS_OBJS = $(LOGIT_OBJS) $(ENCODE_OBJS) $(JSON_OBJS) $(SUSPEND_OBJS) $(QUEUE_OBJS) $(TP_OBJS) 
GO_BASE_OBJS = $(GO_BASE_DIR)/go_base_class.o $(GO_BASE_DIR)/go_game_class.o $(GO_BASE_DIR)/go_engine_class.o $(GO_BASE_DIR)/go_board_class.o $(GO_BASE_DIR)/go_move_class.o $(GO_BASE_DIR)/go_port_class.o $(GO_BASE_DIR)/go_config_class.o $(GO_BASE_DIR)/go_group_class.o $(GO_BASE_DIR)/go_group_list_class.o
SERVER_MAIN_OBJS = $(SERVER_MAIN_DIR)/go_server.o 
SERVER_OBJS = $(SERVER_MAIN_OBJS) $(MAIN_OBJS) $(LINK_MGR_OBJS) $(BASE_MGR_OBJS) $(GO_BASE_OBJS)
CLIENT_MAIN_OBJS = $(CLIENT_MAIN_DIR)/go_client.o
CLIENT_OBJS = $(CLIENT_MAIN_OBJS)

SERVER = server
ALL_SERVER_OBJS	= $(UTILS_OBJS) $(SERVER_OBJS)

CLIENT = client 
ALL_CLIENT_OBJS	= $(UTILS_OBJS) $(CLIENT_OBJS) 

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
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean); done

force_look:
	true

