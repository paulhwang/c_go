/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_server.cpp
*/

#include <unistd.h>
#include "../../phwang_dir/extern_dir/phwang_class.h"
#include "main_class.h"

PhwangClass *thePhwangObject;

int main (int argc, char** argv) {
    thePhwangObject = new PhwangClass();
    MainClass *mainObject = new MainClass();
    mainObject->startThreads();
    sleep(1000);
}

