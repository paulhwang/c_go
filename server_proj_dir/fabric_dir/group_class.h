/*
  Copyrights reserved
  Written by Paul Hwang
  File name: group_class.h
*/

#pragma once
#include "../../phwang_dir/list_mgr_dir/list_entry_class.h"
#include "../define_dir/size_def.h"

class SessionClass;
class FabricClass;

class GroupClass : public ListEntryClass {
#define GROUP_CLASS_SESSION_ARRAY_SIZE 32

    int debugOn_;
    FabricClass *theFabricObject;
    char theMode;
    char theThemeType;
    char *theThemeInfo;
    char *theFirstFiddle;
    char *theSecondFiddle;
    char theRoomStatus;
    char theRoomIdIndex[SIZE_DEF::ROOM_II_SIZE + 4];
    void *theSessionArrayMgr;
    SessionClass **theSessionTableArray;

public:
    GroupClass(
        int debug_on_val,
        void *list_mgr_object_val,
        FabricClass *fabric_object_val,
        char mode_val,
        char theme_type_val,
        char const *theme_info_val,
        char const *first_fiddle_val,
        char const *second_fiddle_val);
    ~GroupClass(void);
    char const* objectName(void) {return "GroupClass";}

    char mode(void) {return this->theMode;}
    char themeType(void) {return this->theThemeType;}
    char roomStatus(void) {return this->theRoomStatus;}
    void setRoomStatusToReady(void);
    char *themeInfo(void) {return this->theThemeInfo;}
    char *firstFiddle(void) {return this->theFirstFiddle;}
    char *secondFiddle(void) {return this->theSecondFiddle;}

    int isDominatedGroup(void);
    char *groupIdIndex(void) {return this->entryIdIndex();}
    char *roomIdIndex(void) {return this->theRoomIdIndex;}
    void *sessionArrayMgr(void) {return this->theSessionArrayMgr;}
    SessionClass *sessionTableArray(int index_val) {return this->theSessionTableArray[index_val];}
    void setSessionTableArray(SessionClass **val) {this->theSessionTableArray = val;}

    void setRoomIdIndex(char *val) {memcpy(this->theRoomIdIndex, val, SIZE_DEF::ROOM_II_SIZE);}
    void insertSession(SessionClass *session_object_val) {phwangArrayMgrInsertElement(this->theSessionArrayMgr, session_object_val);}
    void removeSession(SessionClass *session_object_val) {phwangArrayMgrRemoveElement(this->theSessionArrayMgr, session_object_val);}
};
