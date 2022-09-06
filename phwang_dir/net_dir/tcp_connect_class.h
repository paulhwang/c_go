/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tcp_connect_class.h
*/

#pragma once

class TcpConnectClass {
    char const *objectName(void) {return "TcpConnectClass";}
    char const *theWho;

    void debug(int debug_on_val, char const *func_name_val, char const *str1_val);
    void debug2(int debug_on_val, char const *func_name_val, char const *str1_val, char const *str2_val);
    void debugInt(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val);
    void debugInt2(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);
    void logit(char const *func_name_val, char const *str1_val);
    void logit2(char const *func_name_val, char const *str1_val, char const *str2_val);
    void logitInt(char const *func_name_val, char const *str1_val, int int1_val);
    void logitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);
    void abend(char const *func_name_val, char const *str1_val);
    void abend2(char const *func_name_val, char const *str1_val, char const *str2_val);
    void composeFuncNameExtra(char *buf_val, char const *func_name_val) {phwangComposeFuncNameExtra(buf_val, this->objectName(), func_name_val, this->theWho);}

public:
    TcpConnectClass(char const *who_val);
    ~TcpConnectClass(void);

    void *tcpConnect(
                    unsigned long ip_addr_val, 
                    unsigned short port_val, 
                    void (*receive_callback_val)(void *, void *, void *), 
                    void *receive_object_val,
                    char const *who_val);
};
