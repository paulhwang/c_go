/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tcp_ip_def.h
*/

#pragma once

class TCP_IP_DEF {
public:
    int const static ETHERNET_MTU_SIZE = 1500;

    int const static     TCP_HEADER_SIZE = 20;
    int const static MAX_TCP_HEADER_SIZE = 60;

    int const static     IP_HEADER_SIZE = 20;
    int const static MAX_IP_HEADER_SIZE = 24;

    int const static     TCP_IP_HEADER_SIZE =     TCP_HEADER_SIZE +     IP_HEADER_SIZE;
    int const static MAX_TCP_IP_HEADER_SIZE = MAX_TCP_HEADER_SIZE + MAX_IP_HEADER_SIZE;

    int const static MAX_TCP_DATA_SIZE = ETHERNET_MTU_SIZE - MAX_TCP_IP_HEADER_SIZE;
    int const static MAX_TCP_DATA_LEN_SIZE = 4;
};
