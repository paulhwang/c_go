/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_server.cpp
*/

#include <unistd.h>
#include "main_class.h"

int main (int argc, char** argv) {
    MainClass *mainObject = new MainClass();
    mainObject->startThreads();
    sleep(1000);
}

