/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "stdio.h"
#include "./utils/socket_server.h"
#include "./utils/socket_client.h"
#include "./utils/socket_service_class.h"

int main (int argc, char** argv) {
  printf("hello world\n");
  //start_socket_server();
  //start_socket_client();
  socket_service_class *socket_object = new socket_service_class();
}

