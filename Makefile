include Makefile.inc

DIRS	= utils root_dir

SERVER = server
SERVER_OBJS	= go_server.o

CLIENT = client
CLIENT_OBJS	= go_client.o

UTILS_OBJLIBS	= lib_utils.a
GO_ROOT_OBJLIBS	= lib_go_root.a lib_go_base.a

all:	$(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS) $(UTILS_OBJLIBS) $(GO_ROOT_OBJLIBS)
	$(CC) -o $(SERVER) $(SERVER_OBJS) $(UTILS_OBJLIBS) $(GO_ROOT_OBJLIBS) -lstdc++

$(CLIENT): $(CLIENT_OBJS) $(UTILS_OBJLIBS) $(GO_ROOT_OBJLIBS)
	$(CC) -o $(CLIENT) $(CLIENT_OBJS) $(UTILS_OBJLIBS) $(GO_ROOT_OBJLIBS) -lstdc++

lib_utils.a:	force_look
	$(ECHO) looking into utils : $(MAKE) $(MFLAGS)
	cd utils; $(MAKE) $(MFLAGS)

lib_go_root.a lib_go_base.a:	force_look
	$(ECHO) looking into root_dir : $(MAKE) $(MFLAGS)
	cd root_dir; $(MAKE) $(MFLAGS)

clean:
	$(ECHO) cleaning up in .
	- $(RM) $(SERVER) $(CLIENT) $(SERVER_OBJS) $(CLIENT_OBJS) $(UTILS_OBJLIBS) $(GO_ROOT_OBJLIBS)
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean); done

force_look:
	true

