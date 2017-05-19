include Makefile.inc

SERVER = server
SERVER_OBJS	= go_server.o

CLIENT = client
CLIENT_OBJS	= go_client.o

OBJLIBS	= lib_go_root

all:	$(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS) $(OBJLIBS) ./utils/transport_class.cpp ./utils/logit.cpp ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp
	$(CC) -o $(SERVER) $(SERVER_OBJS) ./utils/transport_class.cpp  ./utils/logit.cpp  ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp -lstdc++

$(CLIENT): $(CLIENT_OBJS) $(OBJLIBS) ./utils/transport_class.cpp ./utils/logit.cpp ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp
	$(CC) -o $(CLIENT) $(CLIENT_OBJS) ./utils/transport_class.cpp  ./utils/logit.cpp ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp -lstdc++

lib_go_root:	force_look

clean:
	$(ECHO) cleaning up in .
	- $(RM) $(SERVER) $(CLIENT) $(SERVER_OBJS) $(CLIENT_OBJS)

force_look:
	true

