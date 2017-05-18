go:     go_server.cpp ./utils/transport_class.cpp ./utils/logit.cpp
	gcc go_server.cpp ./utils/transport_class.cpp  ./utils/logit.cpp -lstdc++ -o go

