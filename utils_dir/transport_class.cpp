/*
  Copyrights reserved
  Written by Paul Hwang
  File name: transport_class.cpp
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
#include "transport_class.h"
#include "./logit.h"

#define MAXHOSTNAME 32
#define BACKLOG 5

void receiveDataFromTransportFunc (void *main_object_val, void *data_val);

TransportClass::TransportClass (void *main_object_val) {
  this->mainObject = main_object_val;

  if (1) {
    this->logit("TransportClass", "init");
  }
}

TransportClass::~TransportClass () {
}

void TransportClass::serverThreadFunction (ushort port_val) {
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

  char const* data = "from server";
  send(data_socket , data , strlen(data) , 0);

  int valread = read(data_socket , buffer, 1024);
  printf("valread=%i data=%s\n", valread, buffer);
  //this->rootObject()->baseObject()->portObject()->receiveStringData(buffer);

    receiveDataFromTransportFunc(this->mainObject, (void *) "Move   03031001");
}

void TransportClass::startClient (ulong ip_addr_val, ushort port_val) {
  int s;
  struct sockaddr_in serv_addr;
  char buffer[1024] = {0};
  this->logit("startClient", "start");

  if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    this->logit("startClient", "open socket error");
    return;
  }
 
  memset(&serv_addr, '0', sizeof(serv_addr));
  
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port_val);
  
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    printf("Invalid address/ Address not supported \n");
    return ;
  }
  
  this->logit("startClient", "connecting");
  if (connect(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("\nConnection Failed \n");
    return;
  }

  this->logit("startClient", "connected");

  char const* data1 = "Move   10302001";
  send(s , data1 , strlen(data1) , 0);

  int valread = read(s, buffer, 1024);
  printf("valread=%i data=%s\n", valread, buffer);

  char const* data2 = "SpecialBACKWORD";
  send(s , data2 , strlen(data2) , 0);
}

void TransportClass::logit (char const* str0_val, char const* str1_val) {
  LOGIT(str0_val, str1_val);
}

void TransportClass::abend (char const* str0_val, char const* str1_val) {
  ABEND(str0_val, str1_val);
}

