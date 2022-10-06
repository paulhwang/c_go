/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_server_class.h
*/

#pragma once

#include <pthread.h>

#define U_FABRIC_RECEIVE_QUEUE_SIZE 100

class FabricClass;
class SessionClass;
class GroupClass;

class UFabricClass {
    FabricClass *fabricObject_;
    void *tcpServerObject_;
    void *portObject_;

    void startNetServer(void);
    void processSetupRoomResponse(char *data_val);
    void processPutRoomDataResponse(char *data_val);

public:
    UFabricClass(FabricClass *fabric_object_val);
    ~UFabricClass(void);
    char const* objectName(void) {return "UFabricClass";}

    void *portObject(void) {return this->portObject_;}
    void transmitFunction(char *data_val);

    /* exports */
    FabricClass *fabricObject(void) {return this->fabricObject_;}
    void exportedParseFunction(char *data_val);
    void exportedNetAcceptFunction(void *tp_transfer_object_val);
};
