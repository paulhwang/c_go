/*
  Copyrights reserved
  Written by Paul Hwang
  File name: theme_class.h
*/

#pragma once

#include <pthread.h>

class RoomMgrClass;
class RoomClass;
class UThemeClass;
class DThemeClass;

class ThemeClass {
#define GAME_SERVER_ROOM_ARRAY_SIZE 32
    char const* objectName(void) {return "ThemeClass";}
    int theDebugCode;

    UThemeClass *theUThemeObject;
    DThemeClass *theDThemeObject;
    void *theRoomListMgrObject;

    RoomMgrClass *theRoomMgrObject;
    RoomClass *theRoomTableArray[GAME_SERVER_ROOM_ARRAY_SIZE];

public:
    ThemeClass(int debug_code_val);
    ~ThemeClass(void);

    UThemeClass *uThemeObject(void) {return this->theUThemeObject;}
    DThemeClass *dThemeObject(void) {return this->theDThemeObject;}
    RoomMgrClass *roomMgrObject(void) {return this->theRoomMgrObject;}

    RoomClass *mallocRoom(char *group_id_index_val);
    void freeRoom(RoomClass *group_object_val);
    RoomClass *searchRoom(char *data_val) {return (RoomClass *) phwangListMgrSearchEntry(this->theRoomListMgrObject, data_val, 0);}
    void insertRoom(RoomClass *room_object_val);
    void removeRoom(RoomClass *room_object_val);

    /* exports */
    void receiveData(char* data_val);
    void transmitData(char *data_val);
};
