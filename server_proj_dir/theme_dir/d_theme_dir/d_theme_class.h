/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_class.h
*/

#pragma once

#include <pthread.h>
#include "../theme_class.h"

#define GAME_DSERVER_RECEIVE_QUEUE_SIZE 100
#define GAME_DSERVER_GROUP_ARRAY_SIZE 32

class ThemeClass;

class DThemeClass {
    int debugOn_;
    ThemeClass *themeObj_;
    void *thePortObject;

    void startNetConnect(void);
    void processSetupRoom(char *data_al);
    void processPutRoomData(char *data_val);

public:
    DThemeClass(int debug_on_val, ThemeClass *theme_object_val);
    ~DThemeClass(void);
    char const* objectName(void) {return "DThemeClass";}

    void *portObject(void) {return this->thePortObject;}
    void xmtData(char *data_val);

    /* exports */
    void parseData(char *data_val);
};
