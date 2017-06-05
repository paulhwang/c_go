/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_connect.cpp
*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include "../../phwang_dir/phwang.h"
#include "tp_transfer_class.h"

TpTransferClass *tpConnectServiceFunction (unsigned long ip_addr_val, unsigned short port_val, void (*receive_callback_val)(void *, void *), void *receive_object_val)
{
    int s;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    phwangLogit("startClient", "start");

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        phwangLogit("startClient", "open socket error");
        return 0;
    }
 
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_val);
  
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported \n");
        return 0;
    }
  
    phwangLogit("startClient", "connecting");
    if (connect(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return 0;
    }

    phwangLogit("startClient", "connected");

    TpTransferClass *tp_transfer_object = new TpTransferClass(receive_callback_val, receive_object_val);
    tp_transfer_object->startThreads(s);
    return tp_transfer_object;
}
