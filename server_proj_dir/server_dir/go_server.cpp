/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_server.cpp
*/

#include <unistd.h>
#include "../../phwang_dir/extern_dir/phwang_class.h"
#include "main_class.h"

main (int argc, char** argv) {
    MainClass *mainObject = new MainClass();
    mainObject->startThreads();
    sleep(1000);
}

