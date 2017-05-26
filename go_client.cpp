/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include <unistd.h>
#include "./utils_dir/transport_class.h"

void receiveDataFromTransportFunc (void* engine_object_val, void *data_val) {
    printf("%s\n", (char *) data_val);
}

int main (int argc, char** argv) {
  	TransportClass *transport_object = new TransportClass(null);
  	transport_object->clientThreadFunction(0, TRANSPORT_PORT_NUMBER_FOR_ME);
  	sleep(2);
  	transport_object->transmitData((void *)  "Move   10302001");
  	sleep(1000);
}
