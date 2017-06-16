/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_server_class.h
*/

#pragma once

#include <pthread.h>
#include "../../protocol_dir/game_server_protocol.h"

#define U_FABRIC_RECEIVE_QUEUE_SIZE 100

class FabricClass;
class GroupMgrClass;

class UFabricClass {
    FabricClass *theFabricObject;
    GroupMgrClass *theGroupMgrObject;
    void *theReceiveQueue;
    pthread_t theReceiveThread;
    void *theTpServerObject;
    void *theTpTransferObject;

    void startReceiveThread(void);
    void receiveFunction(char *data_val);

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    UFabricClass(FabricClass *fabric_object_val);
    ~UFabricClass(void);
    char const* objectName(void) {return "UFabricClass";}

    /* exports */
    void exportedNetReceiveFunction(void *data_val);
    void exportedNetAcceptFunction(void *tp_transfer_object_val);

    void startThreads(void);
    void startNetServer(void);
    void receiveThreadFunction(void);
    void transmitFunction(char *data_val);
};
