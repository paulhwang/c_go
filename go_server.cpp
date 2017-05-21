/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "./root_dir/root_class.h"
#include "./utils_dir/transport_class.h"

int main (int argc, char** argv) {
  RootClass* root_object = new RootClass();
  
  root_object->transportObject()->startServer(8001);
}



