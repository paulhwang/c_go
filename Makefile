# Copyrights reserved
# Written by Paul Hwang

include Makefile.inc

SERVER_PROJ_DIR = server_proj_dir
CLIENT_PROJ_DIR = client_proj_dir
PHWANG_DIR = phwang_dir
INCLUDE_DIR = include_dir
PROTOCOL_DIR = $(INCLUDE_DIR)/protocol_dir
JSON_DIR          = $(PHWANG_DIR)/json_dir
SUSPEND_DIR       = $(PHWANG_DIR)/suspend_dir
LIST_MGR_DIR      = $(PHWANG_DIR)/list_mgr_dir
ARRAY_MGR_DIR     = $(PHWANG_DIR)/array_mgr_dir
ID_INDEX_LIST_DIR = $(PHWANG_DIR)/id_index_list_dir
QUEUE_DIR         = $(PHWANG_DIR)/queue_dir
NET_DIR      = $(PHWANG_DIR)/net_dir
SQL_DIR       = $(PHWANG_DIR)/sql_dir
SERVER_DIR   = $(SERVER_PROJ_DIR)/server_dir
DB_DIR       = $(SERVER_PROJ_DIR)/db_dir
FABRIC_DIR   = $(SERVER_PROJ_DIR)/fabric_dir
THEME_DIR    = $(SERVER_PROJ_DIR)/theme_dir
ENGINE_DIR   = $(SERVER_PROJ_DIR)/engine_dir
TEST_DIR     = $(SERVER_PROJ_DIR)/test_dir
D_FABRIC_DIR  = $(FABRIC_DIR)/d_fabric_dir
U_FABRIC_DIR  = $(FABRIC_DIR)/u_fabric_dir
D_THEME_DIR  = $(THEME_DIR)/d_theme_dir
U_THEME_DIR  = $(THEME_DIR)/u_theme_dir
D_ENGINE_DIR = $(ENGINE_DIR)/d_engine_dir
BASE_MGR_DIR = $(ENGINE_DIR)/base_mgr_dir
GO_BASE_DIR  = $(ENGINE_DIR)/go_base_dir
CLIENT_DIR = $(CLIENT_PROJ_DIR)/client_dir

DIRS = $(PHWANG_DIR) $(SERVER_PROJ_DIR) $(CLIENT_PROJ_DIR)

JSON_OBJS = $(JSON_DIR)/json_class.o 
SUSPEND_OBJS = $(SUSPEND_DIR)/suspend_class.o 
LIST_MGR_OBJS = $(LIST_MGR_DIR)/list_mgr_class.o $(LIST_MGR_DIR)/list_entry_class.o
ARRAY_MGR_OBJS = $(ARRAY_MGR_DIR)/array_mgr_class.o
ID_INDEX_LIST_OBJS = $(ID_INDEX_LIST_DIR)/id_index_list_class.o 
QUEUE_OBJS = $(QUEUE_DIR)/queue_entry_class.o $(QUEUE_DIR)/queue_class.o
NET_OBJS = $(NET_DIR)/tp_server_class.o $(NET_DIR)/tp_transfer_class.o $(NET_DIR)/tp_transfer_class_transmit.o $(NET_DIR)/tp_transfer_class_receive.o  $(NET_DIR)/tp_connect.o 
SQL_OBJS = $(SQL_DIR)/sql_class.o $(SQL_DIR)/sql_postgre.o
PHWANG_OBJS = $(PHWANG_DIR)/phwang.o $(PHWANG_DIR)/phwang_class.o $(JSON_OBJS) $(SUSPEND_OBJS) $(LIST_MGR_OBJS) $(ARRAY_MGR_OBJS) $(ID_INDEX_LIST_OBJS) $(QUEUE_OBJS) $(NET_OBJS) $(SQL_OBJS)

SERVER_OBJS = $(SERVER_DIR)/server_main.o $(SERVER_DIR)/server_root_class.o
DB_OBJS = $(DB_DIR)/db_class.o
D_FABRIC_OBJS = $(D_FABRIC_DIR)/d_fabric_class.o $(D_FABRIC_DIR)/d_fabric_transmit.o $(D_FABRIC_DIR)/d_fabric_parse.o
U_FABRIC_OBJS = $(U_FABRIC_DIR)/u_fabric_class.o $(U_FABRIC_DIR)/u_fabric_transmit.o $(U_FABRIC_DIR)/u_fabric_parse.o 
FABRIC_OBJS = $(U_FABRIC_OBJS) $(D_FABRIC_OBJS) $(FABRIC_DIR)/fabric_class.o $(FABRIC_DIR)/fabric_thread.o $(FABRIC_DIR)/link_class.o $(FABRIC_DIR)/session_class.o $(FABRIC_DIR)/group_class.o $(FABRIC_DIR)/name_list_class.o 
D_THEME_OBJS = $(D_THEME_DIR)/d_theme_class.o $(D_THEME_DIR)/d_theme_transmit.o $(D_THEME_DIR)/d_theme_parse.o 
U_THEME_OBJS = $(U_THEME_DIR)/u_theme_class.o $(U_THEME_DIR)/u_theme_transmit.o $(U_THEME_DIR)/u_theme_parse.o 
THEME_OBJS = $(U_THEME_OBJS)  $(D_THEME_OBJS) $(THEME_DIR)/theme_class.o $(THEME_DIR)/room_class.o 
GO_BASE_OBJS = $(GO_BASE_DIR)/go_base_class.o $(GO_BASE_DIR)/go_game_class.o $(GO_BASE_DIR)/go_fight_class.o $(GO_BASE_DIR)/go_board_class.o $(GO_BASE_DIR)/go_move_class.o $(GO_BASE_DIR)/go_port_class.o $(GO_BASE_DIR)/go_config_class.o $(GO_BASE_DIR)/go_group_class.o $(GO_BASE_DIR)/go_group_list_class.o
D_ENGINE_OBJS = $(D_ENGINE_DIR)/d_engine_class.o $(D_ENGINE_DIR)/d_engine_transmit.o $(D_ENGINE_DIR)/d_engine_parse.o 
ENGINE_OBJS = $(D_ENGINE_OBJS) $(GO_BASE_OBJS) $(ENGINE_DIR)/engine_class.o 
TEST_OBJS = $(TEST_DIR)/test_class.o $(TEST_DIR)/test_thread.o $(TEST_DIR)/test_transmit.o $(TEST_DIR)/test_parse.o $(TEST_DIR)/test_case1.o 
SERVER_PROJ_OBJS = $(SERVER_OBJS) $(DB_OBJS) $(FABRIC_OBJS) $(THEME_OBJS) $(ENGINE_OBJS) $(TEST_OBJS)

CLIENT_OBJS = $(CLIENT_DIR)/go_client.o
CLIENT_PROJ_OBJS = $(CLIENT_OBJS)

SERVER = server
ALL_SERVER_OBJS	= $(PHWANG_OBJS) $(SERVER_PROJ_OBJS)

CLIENT = client 
ALL_CLIENT_OBJS	= $(PHWANG_OBJS) $(CLIENT_PROJ_OBJS) 

UTILS_OBJLIBS = lib_utils.a
GO_ROOT_OBJLIBS	= lib_root.a lib_go_base.a lib_base_mgr.a

all:	$(SERVER) 

$(SERVER): $(ALL_SERVER_OBJS) 
	$(CC) -o $(SERVER) $(ALL_SERVER_OBJS) -lstdc++ -pthread -L/usr/lib/postgresql/12/lib -lpq

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

