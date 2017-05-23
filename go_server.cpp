/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_server.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "engine_class.h"
#include "./root_dir/root_class.h"
#include "./utils_dir/transport_class.h"

void* createGoRoot (void* ptr_val) {
    RootClass* root_object = new RootClass();
  	root_object->transportObject()->startServer(8001);
}

void* createTransport (void* ptr_val) {
    printf("***************createTransport starts\n");
}

int main (int argc, char** argv) {
    EngineClass* engine_object = new EngineClass();
    if (!engine_object) {
        exit(EXIT_FAILURE);
    }
    engine_object->startEngine();

    pthread_t  go_thread, transport_thread;
    int r;

    r = pthread_create(&go_thread, NULL, createGoRoot, 0);
    if (r) {
        fprintf(stderr,"Error - pthread_create() return code: %d\n", r);
        exit(EXIT_FAILURE);
    }

    r = pthread_create(&transport_thread, NULL, createTransport, 0);
    if (r) {
        fprintf(stderr,"Error - pthread_create() return code: %d\n", r);
        exit(EXIT_FAILURE);
    }

    pthread_join(go_thread, NULL);
    pthread_join(transport_thread, NULL);

    exit(EXIT_SUCCESS);
}

