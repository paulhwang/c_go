/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_theme_class.h
*/

#pragma once

#include <pthread.h>
#include "../../protocol_dir/base_mgr_protocol.h"

class ThemeClass;

#define GAME_USERVER_RECEIVE_QUEUE_SIZE 100

class UThemeClass {
    ThemeClass *theThemeObject;
    void *theTpServerObject;
    void *theTpTransferObject;

    void startNetServer(void);
    void processSetupBaseResponse(char *data_al);
    void processPutBaseDataResponse(char *data_val);

    void debug(int debug_on_val, char const *func_name_val, char const *str1_val);
    void debug2(int debug_on_val, char const *func_name_val, char const *str1_val, char const *str2_val);
    void debugInt(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val);
    void debugInt2(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);
    void logit(char const *func_name_val, char const *str1_val);
    void logit2(char const *func_name_val, char const *str1_val, char const *str2_val);
    void logitInt(char const *func_name_val, char const *str1_val, int int1_val);
    void logitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);
    void abend(char const *func_name_val, char const *str1_val);
    void abend2(char const *func_name_val, char const *str1_val, char const *str2_val);

protected:
    friend class DThemeClass;
    friend class RoomMgrClass;

    void transmitFunction(char *data_val);

public:
    UThemeClass(ThemeClass *theme_object_val);
    ~UThemeClass(void);
    char const* objectName(void) {return "UThemeClass";}

    /* exports */
    void exportedNetAcceptFunction(void *tp_transfer_object_val);
    void exportedParseFunction(char *data_val);
};
