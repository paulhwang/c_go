include Makefile.inc

SERVER = server
SERVER_OBJS	= go_server.o

CLIENT = client
CLIENT_OBJS	= go_client.o

UTILS_OBJLIBS	= lib_utils.a
GO_ROOT_OBJLIBS	= lib_go_root.a lib_go_base.a

all:	$(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS) $(UTILS_OBJLIBS) $(GO_ROOT_OBJLIBS) ./utils/transport_class.cpp ./utils/logit.cpp ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp
	$(CC) -o $(SERVER) $(SERVER_OBJS) ./utils/transport_class.cpp  ./utils/logit.cpp  ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp -lstdc++

$(CLIENT): $(CLIENT_OBJS) $(UTILS_OBJLIBS) $(GO_ROOT_OBJLIBS) ./utils/transport_class.cpp ./utils/logit.cpp ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp
	$(CC) -o $(CLIENT) $(CLIENT_OBJS) ./utils/transport_class.cpp  ./utils/logit.cpp ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp -lstdc++

lib_utils.a:	force_look
	$(ECHO) looking into utils : $(MAKE) $(MFLAGS)
	cd utils; $(MAKE) $(MFLAGS)

lib_go_root.a lib_go_base.a:	force_look
	$(ECHO) looking into go_root : $(MAKE) $(MFLAGS)
	cd go_root; $(MAKE) $(MFLAGS)

clean:
	$(ECHO) cleaning up in .
	- $(RM) $(SERVER) $(CLIENT) $(SERVER_OBJS) $(CLIENT_OBJS) $(UTILS_OBJLIBS) $(GO_ROOT_OBJLIBS)

force_look:
	true

