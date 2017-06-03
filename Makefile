# Copyrights reserved
# Written by Paul Hwang

include Makefile.inc

ROOT_DIR = root_dir
UTILS_DIR = utils_dir
TP_DIR = $(ROOT_DIR)/tp_dir
MAIN_DIR = $(ROOT_DIR)/main_dir
LINK_MGR_DIR = $(ROOT_DIR)/link_mgr_dir
BASE_MGR_DIR = $(ROOT_DIR)/base_mgr_dir
GO_BASE_DIR = $(ROOT_DIR)/go_base_dir

DIRS	= utils_dir root_dir

MAIN_OBJS = $(MAIN_DIR)/main_class.o $(MAIN_DIR)/main_exports.o
LINK_MGR_OBJS = $(LINK_MGR_DIR)/link_mgr_class.o $(LINK_MGR_DIR)/link_class.o $(LINK_MGR_DIR)/session_mgr_class.o $(LINK_MGR_DIR)/session_class.o $(LINK_MGR_DIR)/link_mgr_thread.o $(LINK_MGR_DIR)/link_mgr_exports.o 
BASE_MGR_OBJS = $(BASE_MGR_DIR)/base_mgr_class.o $(BASE_MGR_DIR)/base_mgr_exports.o $(BASE_MGR_DIR)/base_mgr_thread.o 
TP_OBJS = $(TP_DIR)/tp_class.o $(TP_DIR)/tp_server.o $(TP_DIR)/tp_transfer_class.o $(TP_DIR)/tp_transfer_thread.o $(TP_DIR)/tp_transfer_receive.o 
QUEUE_OBJS = $(UTILS_DIR)/queue_entry_class.o $(UTILS_DIR)/queue_mgr_class.o
UTILS_OBJS = $(TP_OBJS) $(QUEUE_OBJS) $(UTILS_DIR)/logit.o $(UTILS_DIR)/encode.o $(UTILS_DIR)/suspend_class.o 
GO_BASE_OBJS = $(GO_BASE_DIR)/go_base_class.o $(GO_BASE_DIR)/go_game_class.o $(GO_BASE_DIR)/go_engine_class.o $(GO_BASE_DIR)/go_board_class.o $(GO_BASE_DIR)/go_move_class.o $(GO_BASE_DIR)/go_port_class.o $(GO_BASE_DIR)/go_config_class.o $(GO_BASE_DIR)/go_group_class.o $(GO_BASE_DIR)/go_group_list_class.o

SERVER = server
SERVER_OBJS	= go_server.o $(UTILS_OBJS) $(MAIN_OBJS) $(LINK_MGR_OBJS) $(BASE_MGR_OBJS) $(GO_BASE_OBJS)

CLIENT = client 
CLIENT_OBJS	= go_client.o $(UTILS_OBJS)

UTILS_OBJLIBS = lib_utils.a
GO_ROOT_OBJLIBS	= lib_root.a lib_go_base.a lib_base_mgr.a

all:	$(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS) 
	$(CC) -o $(SERVER) $(SERVER_OBJS) -lstdc++ -pthread

$(CLIENT): $(CLIENT_OBJS) 
	$(CC) -o $(CLIENT) $(CLIENT_OBJS) -lstdc++ -pthread

##lib_utils.a:	force_look
##	$(ECHO) looking into utils_dir : $(MAKE) $(MFLAGS)
##	cd utils_dir; $(MAKE) $(MFLAGS)

##lib_root.a lib_base_mgr.a lib_go_base.a:	force_look
##	$(ECHO) looking into root_dir : $(MAKE) $(MFLAGS)
##	cd root_dir; $(MAKE) $(MFLAGS)

clean:
	$(ECHO) cleaning up in .
	- $(RM) $(SERVER) $(CLIENT) $(SERVER_OBJS) $(CLIENT_OBJS) $(UTILS_OBJLIBS) $(GO_ROOT_OBJLIBS)
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean); done

force_look:
	true

