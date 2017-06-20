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

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class UThemeClass;
    friend class RoomMgrClass;

    void transmitFunction(char *data_val);

public:
    DThemeClass(ThemeClass *theme_object_val);
    ~DThemeClass(void);
    char const* objectName(void) {return "DThemeClass";}

    /* exports */
    void exportedNetReceiveFunction(char *data_val);
};
