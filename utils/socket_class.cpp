/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "stdio.h"
#include "./logit.h"
#include "socket_class.h"

void logit1 (char * func_name, char *param) {
  printf("%s() %s\n", func_name, param);
}

socket_class::socket_class () {

}

socket_class::~socket_class () {

}

void socket_class::start_server () {
  this->logit("start_server", "start");

}

void socket_class::start_client () {
  this->logit("start_client", "start");
}

void debug (int debug_val, char* str0_val, char* str1_val) {
  if (debug_val) {
    LOGIT(str0_val, str1_val);
  }
}

void socket_class::logit (char* str0_val, char* str1_val) {
	LOGIT(str0_val, str1_val);
}

