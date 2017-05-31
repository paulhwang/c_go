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
#include "../main_exports.h"
#include "queue_mgr_class.h"
#include "transport_class.h"
#include "./logit.h"

#define MAXHOSTNAME 32
#define BACKLOG 5

TransportClass::TransportClass (void *main_object_val)
{
    this->mainObject = main_object_val;
    this->transmitQueue = new QueueMgrClass();
    this->transmitQueue->initQueue(TRANSPORT_TRANSMIT_QUEUE_SIZE);

    if (1) {
        this->logit("TransportClass", "init");
    }
}

TransportClass::~TransportClass (void)
{
}

void TransportClass::serverThreadFunction (ushort port_val)
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

    this->startReceiveThread(data_socket);
    this->startTransmitThread(data_socket);
}

void TransportClass::clientThreadFunction (unsigned long ip_addr_val, ushort port_val)
{
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

    this->startReceiveThread(s);
    this->startTransmitThread(s);
}

#define TRANSPORT_RECEIVE_BUFFER_SIZE 1024

void TransportClass::receiveThreadFunction(int socket_val)
{
    while (1) {
        char *buffer = (char *) malloc(TRANSPORT_RECEIVE_BUFFER_SIZE);

        int length = read(socket_val, buffer, TRANSPORT_RECEIVE_BUFFER_SIZE);
        this->logit("receiveThreadFunction", buffer);

        mainReceiveDataFromTransport(this->mainObject, buffer);
    }
}

void TransportClass::exportTransmitData (void *data_val)
{
    this->transmitQueue->enqueueData(data_val);
}

void TransportClass::transmitThreadFunction(int socket_val)
{
    while (1) {
        void *data = this->transmitQueue->dequeueData();
        if (data) {
            char *str_data = (char *) data;
            this->logit("transmitThreadFunction", (char *) str_data);
            send(socket_val, str_data , strlen(str_data) , 0);
        }
    }
}

void TransportClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    LOGIT(s, str1_val);
}

void TransportClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    ABEND(s, str1_val);
}

