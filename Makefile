go_server.o: go_server.cpp
	gcc -c go_server.cpp

go_client.o: go_client.cpp
	gcc -c go_client.cpp

server: go_server.o ./utils/transport_class.cpp ./utils/logit.cpp ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp
	gcc go_server.o ./utils/transport_class.cpp  ./utils/logit.cpp  ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp -lstdc++ -o server

client: go_client.o ./utils/transport_class.cpp ./utils/logit.cpp ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp
	gcc go_client.o ./utils/transport_class.cpp  ./utils/logit.cpp ./go_root/go_root_class.cpp ./go_root/go_base/go_base_class.cpp ./go_root/go_base/go_move_class.cpp -lstdc++ -o client

all:
	make server;
	make client;

clear:
	rm server;
	rm client;

