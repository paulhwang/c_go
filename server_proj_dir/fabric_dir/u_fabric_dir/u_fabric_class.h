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
    FabricClass *theFabricObject;
    void *theTpServerObject;
    void *thePortObject;

    void startNetServer(void);
    void processSetupRoomResponse(char *data_val);
    void processPutRoomDataResponse(char *data_val);

public:
    UFabricClass(FabricClass *fabric_object_val);
    ~UFabricClass(void);
    char const* objectName(void) {return "UFabricClass";}

    void *portObject(void) {return this->thePortObject;}
    void transmitFunction(char *data_val);

    /* exports */
    FabricClass *fabricObject(void) {return this->theFabricObject;}
    void exportedParseFunction(char *data_val);
    void exportedNetAcceptFunction(void *tp_transfer_object_val);

    void sendSetupSessioResponse (
        SessionClass *session_val,
        GroupClass *group_val,
        char const *result_val);
};
