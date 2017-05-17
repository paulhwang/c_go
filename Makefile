go:     go_server.c ./utils/logit.c ./utils/socket_server.c ./utils/socket_client.c
	gcc go_server.c ./utils/logit.c ./utils/socket_server.c ./utils/socket_client.c -o go


