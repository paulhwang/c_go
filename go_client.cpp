/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_client.cpp
*/

#include <unistd.h>
#include "./utils_dir/transport_class.h"
#include "./utils_dir/logit.h"

void mainReceiveDataFromTransport (void* engine_object_val, void *data_val) {
    //printf("mainReceiveDataFromTransport() %s\n", (char *) data_val);
    char *data = (char *) data_val;

    if (*data == 'm') {

    }
    else if (*data == 'd') {
        PRINT_BOARD((char *) data + 1, 19);
    }
}

int main (int argc, char** argv) {
  	TransportClass *transport_object = new TransportClass(null);
  	transport_object->clientThreadFunction(0, TRANSPORT_PORT_NUMBER_FOR_ME);
  	transport_object->exportTransmitData((void *)  "dMove   03021001");
  	sleep(1000);
}