/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "./utils/transport_class.h"

int main (int argc, char** argv) {
  transport_class *transport_object = new transport_class();
  transport_object->start_client(0, 8001);
}



