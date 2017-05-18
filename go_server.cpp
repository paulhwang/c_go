/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "./utils/socket_class.h"

int main (int argc, char** argv) {
  socket_class *socket_object = new socket_class();
  socket_object->start_server(8001);
  socket_object->start_client();
}

