/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_server_class.h
*/

#pragma once

#include <pthread.h>
#include "../../define_dir/size_def.h"
#include "../fabric_class.h"

class FabricClass;
class DbAccountClass;

class DFabricClass {
    char const *objectName(void) {return "DFabricClass";}

    FabricClass *fabricObj_;
    void *tcpServerObj_;
    void *portObj_;
    char timeStampString_[SIZE_DEF::FABRIC_TIME_STAMP_SIZE + 1];

    FileMgrClass *fileMgrObj(void) {return fabricObj_->fileMgrObj();}
    DbClass *dbObject(void) {return fabricObj_->dbObject();}
    DbAccountClass *dbAccountObject(void);
    MessengerClass *messengerObject(void) {return this->fabricObj_->messengerObject();}

    char *timeStampString(void) {return this->timeStampString_;}
    void setTimeStampString(void);
    void startNetServer(void);

    void sendSearchLinkFailResponse (
        char const command_val,
        void *tp_transfer_object_val,
        char const *ajax_id_val,
        char *data_val);

    void sendSearchLinkSessionFailResponse (
        char const command_val,
        void *tp_transfer_object_val,
        char const *ajax_id_val,
        char *data_val);

    char *processRegisterRequest (
        char *ajax_id_val,
        char *data_val);

    char *generateRegisterResponse (
        char const *result_val,
        char *ajax_id_val,
        char const *account_name_val);

    char *processLoginRequest (
        char *ajax_id_val,
        char *data_val,
        char device_type_val,
        void *port_object_val);

    char *generateLoginResponse (
        char const *result_val,
        char *ajax_id_val,
        char const *link_id_index_val,
        char const *encoded_my_name_val);

    char *processLogoutRequest (
        LinkClass *link_val,
        char *ajax_id_val,
        char *data_val);

    char *generateLogoutResponse (
        char const *result_val,
        char *ajax_id_val,
        char const *link_id_index_val);

    char *processGetLinkDataRequest (
        LinkClass *link_val,
        char *ajax_id_val);

    char *processGetNameListRequest (
        LinkClass *link_val,
        char *ajax_id_val,
        char *data_val);

    char *generateGetNameListResponse (
        char const *result_val,
        char *ajax_id_val,
        char const *link_id_index_val,
        char const *data_val);

    char *processSetupSessionRequest (
        LinkClass *link_val,
        char *ajax_id_val,
        char *data_val);

    char *generateSetupSessionResponse (
        char const *result_val,
        char *ajax_id_val,
        char const *link_id_index_val,
        char const *session_id_index_val,
        char const *theme_info_val);

    char *processSetupSession2Request (
        SessionClass *session_val,
        char *ajax_id_val,
        char *data_val);

    char *generateSetupSession2Response (
        char const *result_val,
        char *ajax_id_val,
        char const *link_id_index_val,
        char const *session_id_index_val,
        char theme_type_val,
        char const *theme_data_val);

    char *processSetupSession3Request (
        SessionClass *session_val,
        char *ajax_id_val,
        char *data_val);

    char *generateSetupSession3Response (
        char const *result_val,
        char *ajax_id_val,
        SessionClass *session_val);

    char *processFreeSessionRequest (
        SessionClass *session_val,
        char *ajax_id_val);

    char *generateFreeSessionResponse (
        char const *result_val,
        char *ajax_id_val,
        char const *link_id_index_val,
        char const *session_id_index_val);

    char *processPutSessionDataRequest (
        SessionClass *session_val,
        char *ajax_id_val,
        char *data_val);

    char *generatePutSessionDataResponse (
        char const *result_val,
        char *ajax_id_val,
        char const *link_id_index_val,
        char const *session_id_index_val);

    char *processGetSessionDataRequest (
        SessionClass *session_val,
        char *ajax_id_val,
        char *data_val);

    char *generateGetSessionDataResponse (
        char const *result_val,
        char *ajax_id_val,
        char const *link_id_index_val,
        char const *session_id_index_val,
        char const *data_val);

    char *processReadFileRequest (
        char *ajax_id_val,
        char *data_val);

    char *generateReadFileResponse (
        char const *result_val,
        char *ajax_id_val,
        char more_data_exist_val,
        int fd_val,
        char const *result_data_val);

    char *processReadMoreFileRequest (
        char *ajax_id_val,
        char *data_val);

    char *generateReadMoreFileResponse (
        char const *result_val,
        char *ajax_id_val);

    char *processWriteFileRequest (
        char *ajax_id_val,
        char *data_val);

    char *generateWriteFileResponse (
        char const *result_val,
        char *ajax_id_val);

    char *processWriteMoreFileRequest (
        char *ajax_id_val,
        char *data_val);

    char *generateWriteMoreFileResponse (
        char const *result_val,
        char *ajax_id_val);

    char *processDatagramRequest (
        char *ajax_id_val,
        char *data_val);

    char *generateDatagramResponse (
        char const *result_val,
        char *ajax_id_val,
        char const *data_val);

    void sendSetupRoomRequestToThemeServer (GroupClass *group_val);
    void sendPutSessionDataRequestToThemeServer (
        char const *room_id_index_val,
        char const *data_val);

    void transmitData(void *port_obj_val, char *data_val);

public:
    DFabricClass(FabricClass *port_obj_val);
    ~DFabricClass(void);

    void tcpAccept(void *port_obj_val);
    void parseInput(void *port_obj_val, char *data_val);
};
