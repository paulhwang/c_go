include Makefile.inc

SERVER = server
CLIENT = client

all:	$(SERVER) $(CLIENT)

go_server.o: go_server.cpp
	$(CC) -c go_server.cpp

go_client.o: go_client.cpp
	$(CC) -c go_client.cpp

$(SERVER): go_server.o ./utils/transport_class.cpp ./utils/logit.cpp ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp
	$(CC) go_server.o ./utils/transport_class.cpp  ./utils/logit.cpp  ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp -lstdc++ -o server

$(CLIENT): go_client.o ./utils/transport_class.cpp ./utils/logit.cpp ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp
	$(CC) go_client.o ./utils/transport_class.cpp  ./utils/logit.cpp ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp -lstdc++ -o client

clean:
	$(ECHO) cleaning up in .
	rm server;
	rm client;

