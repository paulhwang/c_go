/*
  Copyrights reserved
  Written by Paul Hwang
  File name: server_main.cpp
*/

#include <unistd.h>
#include "../../include_dir/phwang.h"
#include "server_root_class.h"
#include "../test_dir/test_class.h"

int main (int argc, char** argv) {
    int debug_code = 255;

    //printf("%s start running\n", argv[0]);

    ServerRootClass* serverRootObject = new ServerRootClass(debug_code);

    sleep(10);
    //TestClass *testObject = new TestClass();
    //testObject->startTestThreads();

    while (1) {
        sleep(10);
    }
    return 0;
}

