/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "./go_root/go_root_class.h"
#include "./utils/transport_class.h"

int main (int argc, char** argv) {
  goRootClass* root_object = new goRootClass();
  
  TransportClass *transport_object = new TransportClass();
  transport_object->startServer(8001);
}



