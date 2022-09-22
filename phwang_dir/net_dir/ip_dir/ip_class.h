/*
  Copyrights reserved
  Written by Paul Hwang
  File name: ip_class.h
*/

#pragma once

class IpClass {
    char const *objectName(void) {return "IpClass";}
    char const *theWho;

public:
    IpClass(void);
    ~IpClass(void);

    void getIpAddr(unsigned long *ip_addr_ptr_val);
};
