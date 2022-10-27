/*
  Copyrights reserved
  Written by Paul Hwang
  File name: robust_main.cpp
*/

#include <unistd.h>
#include "../../phwang_dir/phwang.h"
#include "../../server_proj_dir/define_dir/tcp_port_define.h"
#include "robust_root_class.h"

int main (int argc, char** argv) {
    int debug_code = 255;

    printf("%s start running\n", argv[0]);

    RobustRootClass* robustRootObject = new RobustRootClass(1, 1);

    sleep(10);

    while (1) {
        sleep(10);
    }
    return 0;
}

