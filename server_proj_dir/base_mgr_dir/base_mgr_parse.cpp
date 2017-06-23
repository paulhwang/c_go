/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_parse.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../protocol_dir/theme_engine_protocol.h"
#include "../protocol_dir/room_mgr_protocol.h"
#include "base_mgr_class.h"

void BaseMgrClass::parseReceiveData (char *data_val)
{
    this->debug(true, "exportedparseFunction", data_val);

    if (*data_val == THEME_ENGINE_PROTOCOL_COMMAND_IS_MALLOC_BASE) {
        this->processMallocBase(data_val + 1);
        return;
    }

    if (*data_val == THEME_ENGINE_PROTOCOL_COMMAND_IS_TRANSFER_DATA) {
        this->processTransferData(data_val + 1);
        return;
    }

    this->abend("exportedparseFunction", data_val);
}

void BaseMgrClass::processMallocBase(char *data_val)
{
    char *downlink_data;
    char *data_ptr;

    this->debug(true, "processMallocBase", data_val);

    GoBaseClass *go_base_object = this->mallocGoBase();
    if (!go_base_object) {
        this->abend("processMallocBase", "null go_base");
        return;
    }
    go_base_object->setRoomIdIndex(data_val);

    downlink_data = data_ptr = (char *) malloc(BASE_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = THEME_ENGINE_PROTOCOL_RESPOND_IS_MALLOC_BASE;
    memcpy(data_ptr, data_val, ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    data_ptr += ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE;
    memcpy(data_ptr, go_base_object->baseIdIndex(), BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE);
    data_ptr += BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE;
    *data_ptr = 0;
    this->transmitFunction(downlink_data);
}

void BaseMgrClass::processTransferData(char *data_val)
{
    this->debug(true, "processTransferData", data_val);

    GoBaseClass *base_object = this->searchBase(data_val);
    if (!base_object) {
        this->abend("processTransferData", "null base_object");
        /* TBD */
        return;
    }

    if (1) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "baseId=%d baseIndex=%d", base_object->baseId(), base_object->baseIndex());
        this->logit("processTransferData", s);
    }

    base_object->portObject()->receiveStringData(data_val + ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
}

void BaseMgrClass::processTransferDataResponse(GoBaseClass *base_object_val, char *data_val)
{
    char *downlink_data;
    char *data_ptr;

    downlink_data = data_ptr = (char *) malloc(BASE_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = THEME_ENGINE_PROTOCOL_RESPOND_IS_TRANSFER_DATA;
    memcpy(data_ptr, base_object_val->theRoomIdIndex, ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    data_ptr += ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE;
    strcpy(data_ptr, data_val);
    this->transmitFunction(downlink_data);
}

void BaseMgrClass::receiveData (char* data_val) {
    this->logit("receiveData", data_val);

    char game = *data_val++;

    int base_id;
    int base_index;
    phwangDecodeIdIndex(data_val, &base_id, BASE_MGR_PROTOCOL_BASE_ID_SIZE, &base_index, BASE_MGR_PROTOCOL_BASE_INDEX_SIZE);
    data_val += BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE;
    void *base = this->theBaseTableArray[base_index];
    if (!base) {
        return;
    }

    if (game == BASE_MGR_PROTOCOL_GAME_NAME_IS_GO) {
        GoBaseClass *go_base = (GoBaseClass *) base;
        if (go_base->baseId() != base_id) {
            return;
        }
        go_base->portObject()->receiveStringData(data_val);
    }
    else {
        /* TBD: other games */
    }
}
