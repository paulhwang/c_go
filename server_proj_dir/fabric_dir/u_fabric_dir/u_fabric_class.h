/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_server_class.h
*/

#pragma once

#include <pthread.h>

#define U_FABRIC_RECEIVE_QUEUE_SIZE 100

class FabricClass;

class UFabricClass {
    FabricClass *theFabricObject;
    void *theTpServerObject;
    void *theTpTransferObject;

    void startNetServer(void);
    void processSetupRoomResponse(char *data_val);
    void processPutRoomDataResponse(char *data_val);

public:
    UFabricClass(FabricClass *fabric_object_val);
    ~UFabricClass(void);
    char const* objectName(void) {return "UFabricClass";}

    void transmitFunction(char *data_val);

    /* exports */
    void exportedParseFunction(char *data_val);
    void exportedNetAcceptFunction(void *tp_transfer_object_val);
};
