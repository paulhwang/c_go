/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_theme_class.h
*/

#pragma once

#include <pthread.h>
#include "../theme_class.h"

class ThemeClass;

#define GAME_USERVER_RECEIVE_QUEUE_SIZE 100

class UThemeClass {
    int debugOn_;
    ThemeClass *themeObj_;
    void *theTpServerObject;
    void *thePortObject;

    void startNetServer(void);
    void processSetupBaseResponse(char *data_al);
    void processPutBaseDataResponse(char *data_val);

protected:
    friend class DThemeClass;
    friend class RoomMgrClass;

    void *portObject(void) {return this->thePortObject;}
    void xmtData(char *data_val);

public:
    UThemeClass(int debug_on_val, ThemeClass *theme_object_val);
    ~UThemeClass(void);
    char const* objectName(void) {return "UThemeClass";}

    /* exports */
    void exportedNetAcceptFunction(void *tp_transfer_object_val);
    void parseData(char *data_val);
};
