/*
  Copyrights reserved
  Written by Paul Hwang
  File name: ip_class.cpp
*/

#include <arpa/inet.h>
#include <ifaddrs.h>
#include "../../../phwang_dir/phwang.h"
#include "ip_class.h"
#include <ifaddrs.h>

IpClass::IpClass (void)
{
    memset(this, 0, sizeof(*this));
    phwangDebugS(false, "IpClass::IpClass", "init");
}

IpClass::~IpClass (void)
{
    phwangDebugS(false, "~IpClass::IpClass", "exit");
}

void IpClass::getIpAddr(unsigned long *ip_addr_ptr_val)
{
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
        } else if (ifa->ifa_addr->sa_family == AF_INET6) { // check it is IP6
            // is a valid IP6 Address
            tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            printf("%s IPv6 Address() %s\n", ifa->ifa_name, addressBuffer); 
        } 
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
}
