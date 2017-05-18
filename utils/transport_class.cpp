/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pwd.h>
#include "transport_class.h"
#include "./logit.h"

#define MAXHOSTNAME 32
#define BACKLOG 5

transport_class::transport_class () {

}

transport_class::~transport_class () {


}

void transport_class::start_server (ushort port_val) {
  char localhost[MAXHOSTNAME + 1];
  struct servent *sp;
  int s;
  struct hostent *hp;
  int opt = 1;
  struct sockaddr_in address;

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
  	this->logit("start_server", "open socket error");
  	return;
  }

  if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
  	this->logit("start_server", "setsockopt error");
    return;
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port_val);

  if (bind(s, (struct sockaddr *)&address, sizeof(address)) < 0) {
  	this->logit("start_server", "bind error");
    return;
  }

  this->debug(TRUE, "start_server", "listening");
  listen(s, BACKLOG);
}

void transport_class::start_client (unsigned long ip_addr_val, ushort port_val) {
  this->logit("start_client", "start");
}

void transport_class::debug (int debug_val, char const* str0_val, char const* str1_val) {
  if (debug_val) {
    LOGIT(str0_val, str1_val);
  }
}

void transport_class::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

