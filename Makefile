go:     go_server.cpp ./utils/socket_class.cpp ./utils/logit.cpp
	gcc go_server.cpp ./utils/socket_class.cpp  ./utils/logit.cpp -lstdc++ -o go

