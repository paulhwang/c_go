/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "./go_game/go_root_class.h"
#include "./utils/transport_class.h"

int main (int argc, char** argv) {
  go_root_class* root_object = new go_root_class();

  transport_class *transport_object = new transport_class();
  transport_object->start_server(8001);
}



