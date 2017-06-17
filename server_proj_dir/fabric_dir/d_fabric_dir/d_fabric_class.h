/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_server_class.h
*/

#pragma once

#include <pthread.h>
#include "../../protocol_dir/link_mgr_protocol.h"

#define D_FABRIC_RECEIVE_QUEUE_SIZE 100

class FabricClass;

class DFabricClass {
    FabricClass *theFabricObject;
    void *theTpServerObject;
    void *theTpTransferObject;

    void startNetServer(void);

    void debug(int on_off_val, char const* str0_val, char const* str1_val);
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class LinkMgrClass;
    friend class SessionMgrClass;
    friend class GroupMgrClass;
    friend class UFabricClass;
    friend class DFabricClass;

    char const* objectName(void) {return "DFabricClass";}
    void transmitFunction(char *data_val);
   
public:
    DFabricClass(FabricClass *fabric_object_val);
    ~DFabricClass(void);

    /* exports */
    void exportedNetReceiveFunction(char *data_val);
    void exportedNetAcceptFunction(void *tp_transfer_object_val);
};
