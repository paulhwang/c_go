server: go_server.cpp ./utils/transport_class.cpp ./utils/logit.cpp
	gcc go_server.cpp ./utils/transport_class.cpp  ./utils/logit.cpp -lstdc++ -o server

client: go_client.cpp ./utils/transport_class.cpp ./utils/logit.cpp
	gcc go_client.cpp ./utils/transport_class.cpp  ./utils/logit.cpp -lstdc++ -o client

all:
	make server;
	make client;

clear:
	rm server;
	rm client;

