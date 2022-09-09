/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_server_class.h
*/

#pragma once

#include <pthread.h>
#include "../../protocol_dir/link_mgr_protocol.h"
#include "../fabric_class.h"

class FabricClass;
class DbAccountClass;

#define FABRIC_SERVER_TIME_STAMP_LENGTH_SIZE 8

class DFabricClass {
    char const *objectName(void) {return "DFabricClass";}

    FabricClass *theFabricObject;
    void *theTpServerObject;
    char theTimeStampString[FABRIC_SERVER_TIME_STAMP_LENGTH_SIZE + 16];

    DbClass *dbObject(void) {return theFabricObject->dbObject();}
    DbAccountClass *dbAccountObject(void);
    MessengerClass *messengerObject(void) {return this->theFabricObject->messengerObject();}

    void setTimeStampString(void);
    void startNetServer(void);
    void sendMessageResponce(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val, char const *data_val);
    void processSignUpRequest(void *tp_transfer_object_val, char *data_val, char const *ajax_id_val);
    void processSetupLinkRequest(void *tp_transfer_object_val, char *data_val, char const *ajax_id_val);
    void processFreeLinkRequest(void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, LinkClass *link_val);
    void processGetLinkDataRequest(void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, LinkClass *link_val);
    void processGetNameListRequest(void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, LinkClass *link_val);
    void processSetupSessionRequest(void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, LinkClass *link_val);
    void processSetupSession2Request(void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, LinkClass *link_val);
    void processSetupSession3Request(void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, LinkClass *link_val);
    void processFreeSessionRequest(void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, SessionClass *session_val);
    void processPutSessionDataRequest(void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, SessionClass *session_val);
    void processGetSessionDataRequest(void *tp_transfer_object_val, char *data_val, char const *ajax_id_val, SessionClass *session_val);
    void processMessageRequest(void *tp_transfer_object_val, char *data_val, char const *ajax_id_val);
    void sendSignUpResponce(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);
    void sendSetupLinkResponce(void *tp_transfer_object_val, char const *ajax_id_val, char const *link_id_index_val, char const *err_msg_val);
    void errorProcessFreeLink(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);
    void errorProcessGetLinkData(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);
    void errorProcessGetNameList(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);
    void errorProcessSetupSession(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);
    void errorProcessSetupSession2(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);
    void errorProcessFreeSession(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);
    void errorProcessPutSessionData(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);
    void errorProcessGetSessionData(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);
    void mallocRoom(GroupClass *group_val, char *theme_info_val);
    void sendSearchLinkFailResponse (char const command_val, void *tp_transfer_object_val, char const *ajax_id_val);
    void sendSearchLinkSessionFailResponse (char const command_val, void *tp_transfer_object_val, char const *ajax_id_val);

    char *timeStampString(void) {return this->theTimeStampString;}

    void debug111(int debug_on_val, char const *func_name_val, char const *str1_val);
    void debug2(int debug_on_val, char const *func_name_val, char const *str1_val, char const *str2_val);
    void debugInt(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val);
    void debugInt2(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);
    void logit(char const *func_name_val, char const *str1_val);
    void logit2(char const *func_name_val, char const *str1_val, char const *str2_val);
    void logitInt(char const *func_name_val, char const *str1_val, int int1_val);
    void logitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);
    void abend(char const *func_name_val, char const *str1_val);
    void abend2(char const *func_name_val, char const *str1_val, char const *str2_val);
   
public:
    DFabricClass(FabricClass *fabric_object_val);
    ~DFabricClass(void);

    void transmitFunction(void *tp_transfer_object_val, char *data_val);

    /* exports */
    void exportedNetAcceptFunction(void *tp_transfer_object_val);
    void exportedParseFunction(void *tp_transfer_object_val, char *data_val);
};
