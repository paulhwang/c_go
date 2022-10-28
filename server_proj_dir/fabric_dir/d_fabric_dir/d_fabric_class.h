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
    int debugOn_;
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

    char *parseRegister (
        char *ajax_id_val,
        char *data_val);

    char *parseRegister_ (
        char const *result_val,
        char *ajax_id_val,
        char const *account_name_val);

    char *parseLogin (
        char *ajax_id_val,
        char *data_val,
        char device_type_val,
        void *port_object_val);

    char *parseLogin_ (
        char const *result_val,
        char *ajax_id_val,
        char const *link_id_index_val,
        char const *encoded_my_name_val);

    char *parseLogout (
        LinkClass *link_val,
        char *ajax_id_val,
        char *data_val);

    char *parseLogout_ (
        char const *result_val,
        char *ajax_id_val,
        char const *link_id_index_val);

    char *parseGetLinkData (
        LinkClass *link_val,
        char *ajax_id_val);

    char *parseGetNameList (
        LinkClass *link_val,
        char *ajax_id_val,
        char *data_val);

    char *parseGetNameList_ (
        char const *result_val,
        char *ajax_id_val,
        char const *link_id_index_val,
        char const *data_val);

    char *parseSetupSession (
        LinkClass *link_val,
        char *ajax_id_val,
        char *data_val);

    char *parseSetupSession_ (
        char const *result_val,
        char *ajax_id_val,
        char const *link_id_index_val,
        char const *session_id_index_val,
        char const *theme_info_val);

    char *parseSetupSession2 (
        SessionClass *session_val,
        char *ajax_id_val,
        char *data_val);

    char *parseSetupSession2_ (
        char const *result_val,
        char *ajax_id_val,
        char const *link_id_index_val,
        char const *session_id_index_val,
        char theme_type_val,
        char const *theme_data_val);

    char *parseSetupSession3 (
        SessionClass *session_val,
        char *ajax_id_val,
        char *data_val);

    char *parseSetupSession3_ (
        char const *result_val,
        char *ajax_id_val,
        SessionClass *session_val);

    char *parseFreeSession (
        SessionClass *session_val,
        char *ajax_id_val);

    char *parseFreeSession_ (
        char const *result_val,
        char *ajax_id_val,
        char const *link_id_index_val,
        char const *session_id_index_val);

    char *parsePutSessionData (
        SessionClass *session_val,
        char *ajax_id_val,
        char *data_val);

    char *parsePutSessionData_ (
        char const *result_val,
        char *ajax_id_val,
        char const *link_id_index_val,
        char const *session_id_index_val);

    char *parseGetSessionData (
        SessionClass *session_val,
        char *ajax_id_val,
        char *data_val);

    char *parseGetSessionData_ (
        char const *result_val,
        char *ajax_id_val,
        char const *link_id_index_val,
        char const *session_id_index_val,
        char const *data_val);

    char *parseReadFile (
        char *ajax_id_val,
        char *data_val);

    char *parseReadFile_ (
        char const *result_val,
        char *ajax_id_val,
        char more_data_exist_val,
        int fd_val,
        char const *result_data_val);

    char *parseReadMoreFile (
        char *ajax_id_val,
        char *data_val);

    char *parseReadMoreFile_ (
        char const *result_val,
        char *ajax_id_val,
        char more_data_exist_val,
        int fd_val,
        char const *result_data_val);

    char *parseWriteFile (
        char *ajax_id_val,
        char *data_val);

    char *parseWriteFile_ (
        char const *result_val,
        char *ajax_id_val,
        int fd_val);

    char *parseWriteMoreFile (
        char *ajax_id_val,
        char *data_val);

    char *parseWriteMoreFile_ (
        char const *result_val,
        char *ajax_id_val,
        int fd_val);

    char *parseDatagram (
        char *ajax_id_val,
        char *data_val);

    char *parseDatagram_ (
        char const *result_val,
        char *ajax_id_val,
        char const *data_val);

    void sendSetupRoomRequestToThemeServer (GroupClass *group_val);
    void sendPutSessionDataRequestToThemeServer (
        char const *room_id_index_val,
        char const *data_val);

    void xmtData(void *port_obj_val, char *data_val);

public:
    DFabricClass(int debug_on_val, FabricClass *port_obj_val);
    ~DFabricClass(void);

    void tcpAccept(void *port_obj_val);
    void parseData(void *port_obj_val, char *data_val);
};
