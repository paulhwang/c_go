/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_class.cpp
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <pwd.h>
#include <arpa/inet.h>
#include "../../utils_dir/queue_mgr_class.h"
#include "tp_class.h"
#include "tp_transfer_class.h"
#include "../../utils_dir/logit.h"

TpClass::TpClass (void *main_object_val)
{
    this->theMainObject = main_object_val;

    if (1) {
        this->logit("TpClass", "init");
    }
}

TpClass::~TpClass (void)
{
}

TpTransferClass *TpClass::clientThreadFunction (unsigned long ip_addr_val, ushort port_val, void (*receive_callback_val)(void *, void *))
{
  int s;
  struct sockaddr_in serv_addr;
  char buffer[1024] = {0};
  this->logit("startClient", "start");

  if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    this->logit("startClient", "open socket error");
    return 0;
  }
 
  memset(&serv_addr, '0', sizeof(serv_addr));
  
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port_val);
  
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    printf("Invalid address/ Address not supported \n");
    return 0;
  }
  
  this->logit("startClient", "connecting");
  if (connect(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("\nConnection Failed \n");
    return 0;
  }

  this->logit("startClient", "connected");

    TpTransferClass *tp_transfer_object = new TpTransferClass(this, receive_callback_val, 0);
    tp_transfer_object->startThreads(s);
    return tp_transfer_object;
}

void TpClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    LOGIT(s, str1_val);
}

void TpClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    ABEND(s, str1_val);
}

