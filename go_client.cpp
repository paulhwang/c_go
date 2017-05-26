/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "./utils_dir/transport_class.h"

void receiveDataFromTransportFunc (void* engine_object_val, void *data_val) {
    printf("%s\n", (char *) data_val);
}

int main (int argc, char** argv) {
  TransportClass *transport_object = new TransportClass(null);
  transport_object->startClient(0, 8002);
}



