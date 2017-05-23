/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_server.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include "root_dir/root_class.h"

int main (int argc, char** argv) {
    RootClass* root_object = new RootClass();
    if (!root_object) {
    	fprintf(stderr, "Fail to start root_object");
        exit(EXIT_FAILURE);
    }
    root_object->startEngine();
    exit(EXIT_SUCCESS);
}

