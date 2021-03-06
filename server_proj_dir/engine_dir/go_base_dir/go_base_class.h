/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_base_class.h
*/

#pragma once

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/room_mgr_protocol.h"
#include "../../../phwang_dir/list_mgr_dir/list_entry_class.h"
#include "go_define.h"
#include "go_board_class.h"
#include "go_fight_class.h"
#include "go_port_class.h"
#include "go_config_class.h"
#include "go_game_class.h"
#include "go_group_class.h"
#include "go_group_list_class.h"
#include "go_move_class.h"

class EngineClass;

class GoBaseClass : public ListEntryClass {
    EngineClass *theEngineObject;
    char theRoomIdIndex[ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE + 4];

    GoFightClass *theFightObject;
    GoBoardClass *theBoardObject;
    GoPortClass *thePortObject;
    GoConfigClass *theConfigObject;
    GoGameClass *theGameObject;

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    GoBaseClass(void *list_mgr_object_val, EngineClass *engine_object_val, char const *config_info_val);
    ~GoBaseClass(void);
    char const *objectName(void) {return "GoBaseClass";}

    EngineClass *engineObject(void) {return this->theEngineObject;}
    GoFightClass *fightObject(void) {return this->theFightObject;}
    GoBoardClass *boardObject(void) {return this->theBoardObject;}
    GoPortClass *portObject(void) {return this->thePortObject;}
    GoConfigClass *configObject(void) {return this->theConfigObject;}
    GoGameClass *gameObject(void) {return this->theGameObject;}
    char *roomIdIndex(void) {return this->theRoomIdIndex;}
    char *goBaseIdIndex(void) {return this->entryIdIndex();}
    void setRoomIdIndex(char const *room_id_index_val) {memcpy(this->theRoomIdIndex, room_id_index_val, ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE); this->theRoomIdIndex[ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE] = 0;}

    void goBaseLogit(char const *str0_val, char const *str1_val) {phwangLogit(str0_val, str1_val);}
    void goBaseAbend(char const *str0_val, char const *str1_val) {phwangAbend(str0_val, str1_val);}
};
