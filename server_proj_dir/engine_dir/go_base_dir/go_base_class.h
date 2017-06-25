/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_base_class.h
*/

#pragma once

#include "../../../phwang_dir/list_mgr_dir/list_entry_class.h"
#include "../../../phwang_dir/phwang.h"
#include "../base_mgr_dir/base_mgr_class.h"
#include "go_define.h"
#include "go_board_class.h"
#include "go_engine_class.h"
#include "go_port_class.h"
#include "go_config_class.h"
#include "go_game_class.h"
#include "go_group_class.h"
#include "go_group_list_class.h"
#include "go_move_class.h"
class BaseMgrClass;
class EngineClass;

class GoBaseClass : public ListEntryClass {
    EngineClass *theEngineObject___;
    char theRoomIdIndex[ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE + 4];

    GoEngineClass* theEngineObject;
    GoBoardClass* theBoardObject;
    GoPortClass* thePortObject;
    GoConfigClass* theConfigObject;
    GoGameClass* theGameObject;

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class DEngineClass;
    friend class BaseMgrClass;

    void setRoomIdIndex(char *room_id_index_val) {memcpy(this->theRoomIdIndex, room_id_index_val, ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE); this->theRoomIdIndex[ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE] = 0;}

  public:
    GoBaseClass(void *list_mgr_object_val, EngineClass *engine_object_val);
    ~GoBaseClass(void);

    char const* objectName(void) {return "GoBaseClass";}
    int goBaseId(void) {return this->theEntryId;}
    int goBaseIndex(void) {return this->theEntryIndex;}
    char *goBaseIdIndex(void) {return this->theEntryIdIndex;}
    GoEngineClass* engineObject(void) {return this->theEngineObject;}
    GoBoardClass* boardObject(void) {return this->theBoardObject;}
    GoPortClass* portObject(void) {return this->thePortObject;}
    GoConfigClass* configObject(void) {return this->theConfigObject;}
    GoGameClass* gameObject(void) {return this->theGameObject;}

    EngineClass *engineObject___(void) {return this->theEngineObject___;}

    void goBaseLogit(char const* str0_val, char const* str1_val) {phwangLogit(str0_val, str1_val);}
    void goBaseAbend(char const* str0_val, char const* str1_val) {phwangAbend(str0_val, str1_val);}
};
