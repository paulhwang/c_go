include Makefile.inc

SERVER = server
SERVER_OBJS	= go_server.o

CLIENT = client
CLIENT_OBJS	= go_client.o

GO_ROOT_OBJLIBS	= lib_go_root.a lib_go_base.a
UTILS_OBJLIBS	= lib_utils.a

all:	$(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS) $(UTILS_OBJLIBS) $(GO_ROOT_OBJLIBS) ./utils/transport_class.cpp ./utils/logit.cpp ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp
	$(CC) -o $(SERVER) $(SERVER_OBJS) ./utils/transport_class.cpp  ./utils/logit.cpp  ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp -lstdc++

$(CLIENT): $(CLIENT_OBJS) $(UTILS_OBJLIBS) $(GO_ROOT_OBJLIBS) ./utils/transport_class.cpp ./utils/logit.cpp ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp
	$(CC) -o $(CLIENT) $(CLIENT_OBJS) ./utils/transport_class.cpp  ./utils/logit.cpp ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp -lstdc++

lib_utils.a:	force_look
	$(ECHO) looking into utils : 
	cd utils;

lib_go_root.a:	force_look
	$(ECHO) looking into go_root : 
	cd go_root;

clean:
	$(ECHO) cleaning up in .
	- $(RM) $(SERVER) $(CLIENT) $(SERVER_OBJS) $(CLIENT_OBJS) $(UTILS_OBJLIBS) $(GO_ROOT_OBJLIBS)

force_look:
	true

