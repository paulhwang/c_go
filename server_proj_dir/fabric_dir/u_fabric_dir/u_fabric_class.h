/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_server_class.h
*/

#pragma once

#include <pthread.h>
#include "../fabric_class.h"

#define U_FABRIC_RECEIVE_QUEUE_SIZE 100

class FabricClass;
class SessionClass;
class GroupClass;

class UFabricClass {
    int debugOn_;
    FabricClass *fabricObj_;
    void *tcpServerObject_;
    void *portObject_;

    void startNetServer(void);
    void processSetupRoomResponse(char *data_val);
    void processPutRoomDataResponse(char *data_val);

public:
    UFabricClass(int debug_on_val, FabricClass *fabric_obj_val);
    ~UFabricClass(void);
    char const* objectName(void) {return "UFabricClass";}

    void *portObject(void) {return this->portObject_;}
    void xmtData(char *data_val);

    /* exports */
    void parseData(char *data_val);
    void exportedNetAcceptFunction(void *tp_transfer_object_val);
};
