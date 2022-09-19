# Copyrights reserved
# Written by Paul Hwang

include Makefile.inc

###########################################################################################
########## PHWANG DIRS
PHWANG_DIR        = phwang_dir
JSON_DIR          = $(PHWANG_DIR)/json_dir
SUSPEND_DIR       = $(PHWANG_DIR)/suspend_dir
LIST_MGR_DIR      = $(PHWANG_DIR)/list_mgr_dir
ARRAY_MGR_DIR     = $(PHWANG_DIR)/array_mgr_dir
ID_INDEX_LIST_DIR = $(PHWANG_DIR)/id_index_list_dir
QUEUE_DIR         = $(PHWANG_DIR)/queue_dir
SQL_DIR           = $(PHWANG_DIR)/sql_dir
ABEND_DIR         = $(PHWANG_DIR)/abend_dir
ATOMIC_DIR        = $(PHWANG_DIR)/atomic_dir
MALLOC_DIR        = $(PHWANG_DIR)/malloc_dir
ENCODE_DIR        = $(PHWANG_DIR)/encode_dir
THREAD_DIR        = $(PHWANG_DIR)/thread_dir
NET_DIR           = $(PHWANG_DIR)/net_dir
TCP_DIR           = $(NET_DIR)/tcp_dir
PORT_DIR          = $(NET_DIR)/port_dir

########## PHWANG OBJS
JSON_OBJS = $(JSON_DIR)/json_class.o 
SUSPEND_OBJS = $(SUSPEND_DIR)/suspend_class.o 
LIST_MGR_OBJS = $(LIST_MGR_DIR)/list_mgr_root_class.o $(LIST_MGR_DIR)/list_mgr_class.o $(LIST_MGR_DIR)/list_entry_class.o
ARRAY_MGR_OBJS = $(ARRAY_MGR_DIR)/array_mgr_root_class.o $(ARRAY_MGR_DIR)/array_mgr_class.o
ID_INDEX_LIST_OBJS = $(ID_INDEX_LIST_DIR)/id_index_list_class.o 
QUEUE_OBJS = $(QUEUE_DIR)/queue_root_class.o $(QUEUE_DIR)/queue_class.o $(QUEUE_DIR)/queue_entry_class.o
TCP_OBJS = $(TCP_DIR)/tcp_server_class.o $(TCP_DIR)/tcp_connect_class.o
PORT_OBJS = $(PORT_DIR)/port_class.o $(PORT_DIR)/port_class_transmit.o $(PORT_DIR)/port_class_receive.o $(PORT_DIR)/port_class_receive2.o
NET_OBJS = $(TCP_OBJS) $(PORT_OBJS) $(NET_DIR)/net_root_class.o
ABEND_OBJS = $(ABEND_DIR)/abend.o
ATOMIC_OBJS = $(ATOMIC_DIR)/atomic.o
MALLOC_OBJS = $(MALLOC_DIR)/malloc_class.o
ENCODE_OBJS = $(ENCODE_DIR)/encode.o
THREAD_OBJS = $(THREAD_DIR)/thread_root_class.o 
OBJECT_OBJS = $(OBJECT_DIR)/object_class.o
PHWANG_OBJS = $(PHWANG_DIR)/phwang.o $(PHWANG_DIR)/phwang1.o $(PHWANG_DIR)/phwang_class.o $(JSON_OBJS) $(SUSPEND_OBJS) $(LIST_MGR_OBJS) $(ARRAY_MGR_OBJS) $(ID_INDEX_LIST_OBJS) $(QUEUE_OBJS) $(NET_OBJS) $(MALLOC_OBJS) $(ENCODE_OBJS) $(THREAD_OBJS) $(ABEND_OBJS) $(ATOMIC_OBJS)
SQL_OBJS = $(SQL_DIR)/sql_class.o

###########################################################################################
########## SERVER DIRS
SERVER_PROJ_DIR   = server_proj_dir
SERVER_DIR        = $(SERVER_PROJ_DIR)/server_dir
DB_DIR            = $(SERVER_PROJ_DIR)/db_dir
DEFINE_DIR        = $(SERVER_PROJ_DIR)/define_dir
FABRIC_DIR        = $(SERVER_PROJ_DIR)/fabric_dir
THEME_DIR         = $(SERVER_PROJ_DIR)/theme_dir
ENGINE_DIR        = $(SERVER_PROJ_DIR)/engine_dir
TEST_DIR          = $(SERVER_PROJ_DIR)/test_dir
MESSENGER_DIR     = $(FABRIC_DIR)/messenger_dir
D_FABRIC_DIR      = $(FABRIC_DIR)/d_fabric_dir
U_FABRIC_DIR      = $(FABRIC_DIR)/u_fabric_dir
MMW_DIR           = $(MESSENGER_DIR)/mmw_dir
D_THEME_DIR       = $(THEME_DIR)/d_theme_dir
U_THEME_DIR       = $(THEME_DIR)/u_theme_dir
D_ENGINE_DIR      = $(ENGINE_DIR)/d_engine_dir
BASE_MGR_DIR      = $(ENGINE_DIR)/base_mgr_dir
GO_BASE_DIR       = $(ENGINE_DIR)/go_base_dir

########## SERVER OBJS
SERVER_OBJS = $(SERVER_DIR)/server_main.o $(SERVER_DIR)/server_root_class.o
DEFINE_OBJS = $(DEFINE_DIR)/result_def.o $(DEFINE_DIR)/size_def.o
DB_OBJS = $(DB_DIR)/db_class.o $(DB_DIR)/db_account_class.o $(DB_DIR)/db_account_default.o $(DB_DIR)/db_account_entry_class.o $(DB_DIR)/db_test_class.o
MMW_OBJS = $(MMW_DIR)/mmw_frame_class.o $(MMW_DIR)/mmw_input_class.o $(MMW_DIR)/mmw_thread_class.o $(MMW_DIR)/mmw_class.o
MESSENGER_OBJS = $(MMW_OBJS) $(MESSENGER_DIR)/messenger_class.o
D_FABRIC_OBJS = $(D_FABRIC_DIR)/d_fabric_class.o $(D_FABRIC_DIR)/d_fabric_transmit.o $(D_FABRIC_DIR)/d_fabric_parse.o
U_FABRIC_OBJS = $(U_FABRIC_DIR)/u_fabric_class.o $(U_FABRIC_DIR)/u_fabric_transmit.o $(U_FABRIC_DIR)/u_fabric_parse.o 
FABRIC_OBJS = $(MESSENGER_OBJS) $(U_FABRIC_OBJS) $(D_FABRIC_OBJS) $(FABRIC_DIR)/fabric_class.o $(FABRIC_DIR)/fabric_thread.o $(FABRIC_DIR)/link_class.o $(FABRIC_DIR)/session_class.o $(FABRIC_DIR)/group_class.o $(FABRIC_DIR)/name_list_class.o 
D_THEME_OBJS = $(D_THEME_DIR)/d_theme_class.o $(D_THEME_DIR)/d_theme_transmit.o $(D_THEME_DIR)/d_theme_parse.o 
U_THEME_OBJS = $(U_THEME_DIR)/u_theme_class.o $(U_THEME_DIR)/u_theme_transmit.o $(U_THEME_DIR)/u_theme_parse.o 
THEME_OBJS = $(U_THEME_OBJS)  $(D_THEME_OBJS) $(THEME_DIR)/theme_class.o $(THEME_DIR)/room_class.o 
GO_BASE_OBJS = $(GO_BASE_DIR)/go_base_class.o $(GO_BASE_DIR)/go_game_class.o $(GO_BASE_DIR)/go_fight_class.o $(GO_BASE_DIR)/go_board_class.o $(GO_BASE_DIR)/go_move_class.o $(GO_BASE_DIR)/go_port_class.o $(GO_BASE_DIR)/go_config_class.o $(GO_BASE_DIR)/go_group_class.o $(GO_BASE_DIR)/go_group_list_class.o
D_ENGINE_OBJS = $(D_ENGINE_DIR)/d_engine_class.o $(D_ENGINE_DIR)/d_engine_transmit.o $(D_ENGINE_DIR)/d_engine_parse.o 
ENGINE_OBJS = $(D_ENGINE_OBJS) $(GO_BASE_OBJS) $(ENGINE_DIR)/engine_class.o 
TEST_OBJS = $(TEST_DIR)/test_class.o $(TEST_DIR)/test_thread.o $(TEST_DIR)/test_transmit.o $(TEST_DIR)/test_parse.o $(TEST_DIR)/test_case1.o 
SERVER_PROJ_OBJS = $(SERVER_OBJS) $(DB_OBJS) $(FABRIC_OBJS) $(THEME_OBJS) $(ENGINE_OBJS) $(TEST_OBJS) $(DEFINE_OBJS)
ALL_SERVER_OBJS	= $(PHWANG_OBJS) $(SERVER_PROJ_OBJS) $(SQL_OBJS)

###########################################################################################
########## CLIENT DIRS
CLIENT_PROJ_DIR   = client_proj_dir
CLIENT_DIR        = $(CLIENT_PROJ_DIR)/client_dir

########## CLIENT OBJS
CLIENT_OBJS = $(CLIENT_DIR)/go_client.o
CLIENT_PROJ_OBJS = $(CLIENT_OBJS)
ALL_CLIENT_OBJS	= $(PHWANG_OBJS) $(CLIENT_PROJ_OBJS) 

###########################################################################################
########## ROBUST DIRS
ROBUST_PROJ_DIR     = robust_proj_dir
ROBUST_DIR          = $(ROBUST_PROJ_DIR)/robust_dir

########## ROBUST OBJS
ROBUST_OBJS = $(ROBUST_DIR)/robust_main.o $(ROBUST_DIR)/robust_root_class.o
ROBUST_PROJ_OBJS = $(ROBUST_OBJS)
ALL_ROBUST_OBJS	= $(PHWANG_OBJS) $(ROBUST_PROJ_OBJS) 

###########################################################################################
DIRS = $(PHWANG_DIR) $(SERVER_PROJ_DIR) $(CLIENT_PROJ_DIR) $(ROBUST_PROJ_DIR)

SERVER = server
CLIENT = client 
ROBUST = robust 

all:	$(SERVER) $(ROBUST)

$(SERVER): $(ALL_SERVER_OBJS) 
	$(CC) -o $(SERVER) $(ALL_SERVER_OBJS) -lstdc++ -pthread -L/usr/lib/postgresql/12/lib -lpq

$(CLIENT): $(ALL_CLIENT_OBJS) 
	$(CC) -o $(CLIENT) $(ALL_CLIENT_OBJS) -lstdc++ -pthread

$(ROBUST): $(ALL_ROBUST_OBJS) 
	$(CC) -o $(ROBUST) $(ALL_ROBUST_OBJS) -lstdc++ -pthread

##lib_utils.a:	force_look
##	$(ECHO) looking into utils_dir : $(MAKE) $(MFLAGS)
##	cd utils_dir; $(MAKE) $(MFLAGS)

##lib_root.a lib_base_mgr.a lib_go_base.a:	force_look
##	$(ECHO) looking into root_dir : $(MAKE) $(MFLAGS)
##	cd root_dir; $(MAKE) $(MFLAGS)

UTILS_OBJLIBS = lib_utils.a
GO_ROOT_OBJLIBS	= lib_root.a lib_go_base.a lib_base_mgr.a

clean:
	$(ECHO) cleaning up in .
	- $(RM) $(SERVER) $(CLIENT) $(ROBUST) $(ALL_SERVER_OBJS) $(ALL_CLIENT_OBJS) $(ALL_ROBUST_OBJS) $(UTILS_OBJLIBS) $(GO_ROOT_OBJLIBS)
#	-for d in $(DIRS); do (cd $$d; $(MAKE) clean); done

force_look:
	true

