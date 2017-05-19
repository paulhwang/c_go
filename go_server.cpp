/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "./go_root/go_root_class.h"
#include "./utils/transport_class.h"

int main (int argc, char** argv) {
  goRootClass* root_object = new goRootClass();
  
  transport_class *transport_object = new transport_class();
  transport_object->start_server(8001);
}



