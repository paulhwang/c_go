# Copyrights reserved
# Written by Paul Hwang

include ../Makefile.inc

### libraries
PHWANG_DIR        = ../phwang_dir
PHWANG_STATIC_LIB = $(PHWANG_DIR)/libphwang.a
PHWANG_DYNAMIC_LIB = $(PHWANG_DIR)/libphwang.so

### Directories
SERVER_PROJ_DIR   = .
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
SQL_DIR           = $(PHWANG_DIR)/sql_dir

### Objects
SERVER_OBJS = $(SERVER_DIR)/server_main.o $(SERVER_DIR)/server_root_class.o
DEFINE_OBJS = $(DEFINE_DIR)/result_def.o $(DEFINE_DIR)/size_def.o $(DEFINE_DIR)/file_def.o
DB_OBJS = $(DB_DIR)/db_class.o $(DB_DIR)/db_account_class.o $(DB_DIR)/db_account_default.o $(DB_DIR)/db_account_entry_class.o $(DB_DIR)/db_test_class.o
MMW_OBJS = $(MMW_DIR)/mmw_frame_class.o $(MMW_DIR)/mmw_input_class.o $(MMW_DIR)/mmw_thread_class.o $(MMW_DIR)/mmw_class.o
MESSENGER_OBJS = $(MMW_OBJS) $(MESSENGER_DIR)/messenger_class.o
D_FABRIC_OBJS = $(D_FABRIC_DIR)/d_fabric_class.o $(D_FABRIC_DIR)/d_fabric_class_transmit.o $(D_FABRIC_DIR)/d_fabric_class_parse.o
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
SQL_OBJS = $(SQL_DIR)/sql_class.o
ALL_SERVER_OBJS	= $(SERVER_PROJ_OBJS) $(SQL_OBJS)

### Executable
SERVER = $(SERVER_PROJ_DIR)/server

all:	$(SERVER)

$(SERVER): $(ALL_SERVER_OBJS) $(PHWANG_STATIC_LIB)
	$(CC) -o $(SERVER) $(ALL_SERVER_OBJS) -lstdc++ -pthread -L$(PHWANG_DIR) -lphwang -L/usr/lib/postgresql/12/lib -lpq

$(D_FABRIC_DIR)/d_fabric_class.o: $(D_FABRIC_DIR)/d_fabric_class.cpp $(D_FABRIC_DIR)/d_fabric_class.h
	$(CC) -c $(D_FABRIC_DIR)/d_fabric_class.cpp -o $(D_FABRIC_DIR)/d_fabric_class.o

$(D_FABRIC_DIR)/d_fabric_class_parse.o: $(D_FABRIC_DIR)/d_fabric_class_parse.cpp $(D_FABRIC_DIR)/d_fabric_class.h
	$(CC) -c $(D_FABRIC_DIR)/d_fabric_class_parse.cpp -o $(D_FABRIC_DIR)/d_fabric_class_parse.o

$(D_FABRIC_DIR)/d_fabric_class_transmit.o: $(D_FABRIC_DIR)/d_fabric_class_transmit.cpp $(D_FABRIC_DIR)/d_fabric_class.h
	$(CC) -c $(D_FABRIC_DIR)/d_fabric_class_transmit.cpp -o $(D_FABRIC_DIR)/d_fabric_class_transmit.o

clean:
	- $(RM) $(SERVER) $(ALL_SERVER_OBJS)
#	-for d in $(DIRS); do (cd $$d; $(MAKE) clean); done

force_look:
	true










###########################################################################################
########## CLIENT DIRS
CLIENT_PROJ_DIR   = client_proj_dir
CLIENT_DIR        = $(CLIENT_PROJ_DIR)/client_dir

########## CLIENT OBJS
CLIENT_OBJS = $(CLIENT_DIR)/go_client.o
CLIENT_PROJ_OBJS = $(CLIENT_OBJS)
ALL_CLIENT_OBJS	= $(PHWANG_OBJS) $(CLIENT_PROJ_OBJS) 

CLIENT = client 

$(CLIENT): $(ALL_CLIENT_OBJS) 
	$(CC) -o $(CLIENT) $(ALL_CLIENT_OBJS) -lstdc++ -pthread




UTILS_OBJLIBS = lib_utils.a
GO_ROOT_OBJLIBS	= lib_root.a lib_go_base.a lib_base_mgr.a



##lib_utils.a:	force_look
##	$(ECHO) looking into utils_dir : $(MAKE) $(MFLAGS)
##	cd utils_dir; $(MAKE) $(MFLAGS)

##lib_root.a lib_base_mgr.a lib_go_base.a:	force_look
##	$(ECHO) looking into root_dir : $(MAKE) $(MFLAGS)
##	cd root_dir; $(MAKE) $(MFLAGS)

#$(PHWANG_DYNAMIC_LIB): $(PHWANG_OBJS)
#	$(CC) -shared -o $(PHWANG_DYNAMIC_LIB) -fPIC $(PHWANG_OBJS) 
