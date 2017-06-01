/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_class.h
*/

#pragma once

class TpTransferClass {
    void *tp_object;
    int theSocket;

public:
    TpTransferClass(void *tp_object_val, int socket_val);
    ~TpTransferClass(void);

    char const *objectName(void) {return "TpTransferClass";}

    int socket(void) {return this->theSocket;}
};
