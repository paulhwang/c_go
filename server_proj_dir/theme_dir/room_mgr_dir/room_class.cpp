/*
  Copyrights reserved
  Written by Paul Hwang
  File name: room_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/id_index_list_dir/id_index_list_class.h"
#include "room_class.h"
#include "../theme_class.h"

RoomClass::RoomClass (void *list_mgr_object_val, ThemeClass *theme_object_val, char *group_id_index_val):
        ListEntryClass(list_mgr_object_val),
        theThemeObject(theme_object_val)
{
    //memset(this, 0, sizeof(RoomClass));
    //this->theRoomMgrObject = room_mgr_object_val;
    //this->theRoomId = room_id_val;
    //this->theRoomIndex = room_index_val;
    //phwangEncodeIdIndex(this->theRoomIdIndex, this->theRoomId, ROOM_MGR_PROTOCOL_ROOM_ID_SIZE, this->theRoomIndex, ROOM_MGR_PROTOCOL_ROOM_INDEX_SIZE);

    this->theMaxGroupTableArrayIndex = 0;
    this->insertGroup(group_id_index_val);

    this->debug(true, "RoomClass", this->roomIdIndex());
}

RoomClass::~RoomClass (void)
{
}

void RoomClass::insertGroup (char *group_id_index_val)
{
    char *buf = (char *) malloc(GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE + 4);
    memcpy(buf, group_id_index_val, GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE);
    buf[GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE] = 0;

    int i = 0;
    while (i < this->theMaxGroupTableArrayIndex) {
        if (!this->theGroupTableArray[i]) {
            this->theGroupTableArray[i] = buf;
            return;
        }
        i++;
    }

    if (this->theMaxGroupTableArrayIndex < ROOM_CLASS_GROUP_ARRAY_SIZE) {
        this->theGroupTableArray[this->theMaxGroupTableArrayIndex] = buf;
        this->theMaxGroupTableArrayIndex++;
        return;
    }

    free(buf);
    this->abend("insertGroup", "table is full");
}

void RoomClass::removeGroup (char *group_id_index_val)
{
    int i = 0;
    while (i < ROOM_CLASS_GROUP_ARRAY_SIZE) {
        if (!memcmp(this->theGroupTableArray[i], group_id_index_val, GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE)) {
            free(this->theGroupTableArray[i]);
            this->theGroupTableArray[i] = 0;
            return;
        }
        i++;
    }
    this->abend("removeGroup", "not found");
}

void RoomClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void RoomClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
