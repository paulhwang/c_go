/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_server.cpp
*/

#include "root_dir/main_dir/main_class.h"

int main (int argc, char** argv) {
    MainClass *mainObject = new MainClass();
    mainObject->startThreads();
}

