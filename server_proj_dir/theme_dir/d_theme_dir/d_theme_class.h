/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_class.h
*/

#pragma once

#include <pthread.h>
#include "../../protocol_dir/base_mgr_protocol.h"

#define GAME_DSERVER_RECEIVE_QUEUE_SIZE 100
#define GAME_DSERVER_GROUP_ARRAY_SIZE 32

class ThemeClass;

class DThemeClass {
    ThemeClass *theThemeObject;
    void *theTpTransferObject;

    void startNetConnect(void);
    void processSetupRoom(char *data_al);
    void processPutRoomData(char *data_val);

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

public:
    DThemeClass(ThemeClass *theme_object_val);
    ~DThemeClass(void);
    char const* objectName(void) {return "DThemeClass";}

    void transmitFunction(char *data_val);

    /* exports */
    void exportedParseFunction(char *data_val);
};
