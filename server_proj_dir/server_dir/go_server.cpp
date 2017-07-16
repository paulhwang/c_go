/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_server.cpp
*/

#include <unistd.h>
#include "../../phwang_dir/phwang.h"
#include "../protocol_dir/net_port_protocol.h"
#include "main_class.h"

main (int argc, char **argv) {
    MainClass *mainObject = new MainClass();
    int register_tag;
    phwangRegisterProgramProcess(&register_tag, argv[0], LINK_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER);
}

