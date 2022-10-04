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

    char *processDatagramRequest (char *data_val);
    char *generateDatagramResponse (
        char const *result_val,
        char const *data_val);

    char *processRegisterRequest (char *data_val);
    char *generateRegisterResponse (
        char const *result_val,
        char const *account_name_val);

    char *processLoginRequest (
        char *data_val,
        char device_type_val,
        void *port_object_val);
    char *generateLoginResponse (
        char const *result_val,
        char const *link_id_index_val,
        char const *account_name_val);

    char *processLogoutRequest (
        LinkClass *link_val,
        char *data_val);
    char *generateLogoutResponse (
        char const *result_val,
        char const *link_id_index_val,
        char const *data_val);

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

    char *processSetupSoloRequest (
        LinkClass *link_val,
        char *data_val,
        char *ajax_id_val);
    char *generateSetupSoloResponse (
        char const *result_val,
        char const *link_id_index_val,
        char const *session_id_index_val,
        char const *theme_info_val);

    char *processSetupDuet2Request (
        SessionClass *session_val,
        char *data_val);
    char *generateSetupDuet2Response (
        char const *result_val,
        char const *link_id_index_val,
        char const *session_id_index_val);

    char *processSetupDuet3Request (
        LinkClass *link_val,
        char *data_val);
    char *generateSetupDuet3Response (
        char const *result_val,
        char const *link_id_index_val,
        char const *session_id_index_val);

    char *processGetSessionSetupStatusRequest (
        SessionClass *session_val,
        char *data_val);
    char *generateGetSessionSetupStatusResponse (
        char const *result_val,
        char const *link_id_index_val,
        char const *session_id_index_val,
        char room_status_val,
        char session_type_val,
        char *theme_info_val,
        char *initiator_name_val,
        char *peer_name_val);

    char *processFreeSessionRequest (
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

    void sendSetupRoomRequestToThemeServer (GroupClass *group_val);
    void sendPutSessionDataRequestToThemeServer (
        char const *room_id_index_val,
        char const *data_val);
   
public:
    DFabricClass(FabricClass *fabric_object_val);
    ~DFabricClass(void);

    void transmitFunction(void *port_object_val, char *data_val);

    /* exports */
    void exportedNetAcceptFunction(void *port_object_val);
    void exportedParseFunction(void *port_object_val, char *data_val);
};
