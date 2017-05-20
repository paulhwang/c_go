/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "./utils/transport_class.h"

int main (int argc, char** argv) {
  TransportClass *transport_object = new TransportClass(null);
  transport_object->startClient(0, 8001);
}



