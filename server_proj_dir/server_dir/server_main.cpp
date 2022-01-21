/*
  Copyrights reserved
  Written by Paul Hwang
  File name: server_main.cpp
*/

#include <unistd.h>
#include "../../phwang_dir/phwang.h"
#include "../protocol_dir/net_port_protocol.h"
#include "server_root_class.h"
#include "../test_dir/test_class.h"

main (int argc, char** argv) {
    ServerRootClass* serverRootObject = new ServerRootClass();
    int register_tag;
    sleep(10);
    //TestClass *testObject = new TestClass();
    //testObject->startTestThreads();
    phwangRegisterProgramProcess(&register_tag, argv[0], HTTP_FABRIC_PROTOCOL_TRANSPORT_PORT_NUMBER);
}
