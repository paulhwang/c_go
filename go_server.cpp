/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "./root_dir/go_root_class.h"
#include "./utils_dir/transport_class.h"

int main (int argc, char** argv) {
  GoRootClass* root_object = new GoRootClass();
  
  root_object->transportObject()->startServer(8001);
}



