/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "./go_root/go_root_class.h"
#include "./utils/transport_class.h"

int main (int argc, char** argv) {
  GoRootClass* root_object = new GoRootClass();
  
  root_object->transportObject()->startServer(8001);
}



