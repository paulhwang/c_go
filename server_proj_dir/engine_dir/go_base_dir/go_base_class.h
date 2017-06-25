/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_base_class.h
*/

#pragma once

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

class GoBaseClass {
    EngineClass *thetheEngineObject;
    int theBaseId;
    int theBaseIndex;
    char theBaseIdIndex[BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE + 4];
    char theRoomIdIndex[ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE + 4];

    BaseMgrClass* theBaseMgrObject;
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

    char *baseIdIndex(void) {return this->theBaseIdIndex;}
    void setRoomIdIndex(char *room_id_index_val) {memcpy(this->theRoomIdIndex, room_id_index_val, ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE); this->theRoomIdIndex[ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE] = 0;}

  public:
    GoBaseClass(BaseMgrClass* base_mgr_object_val, EngineClass *engine_object_val, int base_id_val, int base_index_val);
    ~GoBaseClass(void);

    char const* objectName(void) {return "GoBaseClass";}
    int baseId(void) {return this->theBaseId;}
    int baseIndex(void) {return this->theBaseIndex;}
    BaseMgrClass* baseMgrObject(void) {return this->theBaseMgrObject;}
    GoEngineClass* engineObject(void) {return this->theEngineObject;}
    GoBoardClass* boardObject(void) {return this->theBoardObject;}
    GoPortClass* portObject(void) {return this->thePortObject;}
    GoConfigClass* configObject(void) {return this->theConfigObject;}
    GoGameClass* gameObject(void) {return this->theGameObject;}

    void goBaseLogit(char const* str0_val, char const* str1_val) {phwangLogit(str0_val, str1_val);}
    void goBaseAbend(char const* str0_val, char const* str1_val) {phwangAbend(str0_val, str1_val);}
};
