/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_server_class.h
*/

#pragma once

#include <pthread.h>
#include "../fabric_class.h"

class FabricClass;
class DbAccountClass;

#define FABRIC_SERVER_TIME_STAMP_LENGTH_SIZE 8

class DFabricClass {
    char const *objectName(void) {return "DFabricClass";}

    FabricClass *theFabricObject;
    void *theTpServerObject;
    void *theTpTransferObject;
    char theTimeStampString[FABRIC_SERVER_TIME_STAMP_LENGTH_SIZE + 16];

    DbClass *dbObject(void) {return theFabricObject->dbObject();}
    DbAccountClass *dbAccountObject(void);
    MessengerClass *messengerObject(void) {return this->theFabricObject->messengerObject();}

    char *timeStampString(void) {return this->theTimeStampString;}
    void setTimeStampString(void);
    void startNetServer(void);

    void sendSearchLinkFailResponse (
        char const command_val,
        void *tp_transfer_object_val,
        char const *ajax_id_val);

    void sendSearchLinkSessionFailResponse (
        char const command_val,
        void *tp_transfer_object_val,
        char const *ajax_id_val);

    void processMessageRequest (
        void *tp_transfer_object_val,
        char *data_val,
        char const *ajax_id_val);

    void sendMessageResponce (
        void *tp_transfer_object_val,
        char const *ajax_id_val,
        char const *err_msg_val,
        char const *data_val);

    char *processSignUpRequest (char *data_val);
    char *generateSignUpResponse (char const *result_val);

    char *processSignInRequest (char *data_val);
    char *generateSignInResponse (
        char const *result_val,
        char const *link_id_index_val);

    char *processSignOffRequest (
        LinkClass *link_val);
    char *generateSignOffResponse (
        char const *result_val,
        char const *link_id_index_val);

    char *processGetLinkDataRequest (
        LinkClass *link_val,
        char *data_val);
    char *generateGetLinkDataResponse (
        char const *result_val,
        char const *link_id_index_val,
        char const *data_val);

    char *processGetNameListRequest (
        LinkClass *link_val,
        char *data_val);
    char *generateGetNameListResponse (
        char const *result_val,
        char const *link_id_index_val,
        char const *data_val);

    char *processSetupSessionRequest (
        void *tp_transfer_object_val,
        char *data_val,
        char const *ajax_id_val,
        LinkClass *link_val);
    char *generateSetupSessionResponse (
        char const *result_val,
        char const *link_id_index_val,
        char const *session_id_index_val);
    void sendSetupSessionResponce (
        void *tp_transfer_object_val,
        char const *ajax_id_val,
        char const *link_id_index_val,
        char const *session_id_index_val,
        char const *result_val);

    void processSetupSession2Request (
        void *tp_transfer_object_val,
        char *data_val,
        char const *ajax_id_val,
        LinkClass *link_val);
    void sendSetupSession2Responce (
        void *tp_transfer_object_val,
        char const *ajax_id_val,
        char const *link_id_index_val,
        char const *session_id_index_val,
        char const *result_val);
    void errorProcessSetupSession2(void *tp_transfer_object_val, char const *ajax_id_val, char const *err_msg_val);

    char *processSetupSession3Request (
        LinkClass *link_val,
        char *data_val);
    char *generateSetupSession3Response (
        char const *result_val,
        char const *link_id_index_val,
        char const *session_id_index_val);

    char *processFreeSessionRequest (
        LinkClass *link_val,
        SessionClass *session_val);
    char *generateFreeSessionResponse (
        char const *result_val,
        char const *link_id_index_val,
        char const *session_id_index_val);

    char *processPutSessionDataRequest (
        SessionClass *session_val,
        char *data_val);
    char *generatePutSessionDataResponse (
        char const *result_val,
        char const *link_id_index_val,
        char const *session_id_index_val);

    char *processGetSessionDataRequest (
        SessionClass *session_val,
        char *data_val);
    char *generateGetSessionDataResponse (
        char const *result_val,
        char const *link_id_index_val,
        char const *session_id_index_val,
        char const *data_val);

    void sendSetupRoomRequestToThemeServer (
        GroupClass *group_val,
        char *theme_info_val);

    void sendPutSessionDataRequestToThemeServer (
        char const *room_id_index_val,
        char const *data_val);
   
public:
    DFabricClass(FabricClass *fabric_object_val);
    ~DFabricClass(void);

    void transmitFunction(void *tp_transfer_object_val, char *data_val);

    /* exports */
    void exportedNetAcceptFunction(void *tp_transfer_object_val);
    void exportedParseFunction(void *tp_transfer_object_val, char *data_val);
};
