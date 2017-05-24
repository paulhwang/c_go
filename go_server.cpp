/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_server.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include "engine_class.h"

#include "root_dir/go_base_dir/go_base_class.h"

int main (int argc, char** argv) {
    EngineClass* engine_object = new EngineClass();
    if (!engine_object) {
    	  fprintf(stderr, "Fail to start engine_object");
        exit(EXIT_FAILURE);
    }

    engine_object->startEngine();
    exit(EXIT_SUCCESS);
}

