/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_server.cpp
*/

#include "engine_class.h"

int main (int argc, char** argv) {
    EngineClass *mainObject = new EngineClass();
    mainObject->startEngineThreads();
}

