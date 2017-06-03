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

#define MAXHOSTNAME 32
#define BACKLOG 5

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

void TpClass::serverThreadFunction (ushort port_val, TpTransferClass *tp_transfer_object_val)
{
  char localhost[MAXHOSTNAME + 1];
  struct servent *sp;
  int s, data_socket;
  struct hostent *hp;
  int opt = 1;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  char buffer[1024] = {0};

  this->logit("startServer", "start");
/*
  if ((sp = getservbyname("whois", "tcp")) == NULL) {
    this->logit("start_server", "No whois service on this host");
    return;
  }
  printf("port=%d\n", sp->s_port);
S
  //gethostname(localhost, MAXHOSTNAME);
  this->logit("start_server", localhost);

  hp = gethostbyname("")
*/

  if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
  	this->logit("startServer", "open socket error");
  	return;
  }

  if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
  	this->logit("startServer", "setsockopt error");
    return;
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port_val);

  if (bind(s, (struct sockaddr *)&address, sizeof(address)) < 0) {
  	this->logit("startServer", "bind error");
    return;
  }

  this->logit("startServer", "listening");
  listen(s, BACKLOG);

  this->logit("startServer", "accepting");
  if ((data_socket = accept(s, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
    this->logit("startServer", "accept error");
    return;
  }

    this->logit("startServer", "accepted");

    tp_transfer_object_val->startThreads(data_socket);
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

    TpTransferClass *tp_transfer_object = new TpTransferClass(this, receive_callback_val);
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

