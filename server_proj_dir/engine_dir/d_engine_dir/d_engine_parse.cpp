/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_engine_parse.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/theme_engine_protocol.h"
#include "d_engine_class.h"
#include "../engine_class.h"
#include "../base_mgr_dir/base_mgr_class.h"

void DEngineClass::exportedparseFunction (char *data_val)
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

void DEngineClass::processMallocBase(char *data_val)
{
    char *downlink_data;
    char *data_ptr;

    this->debug(true, "processMallocBase", data_val);

    GoBaseClass *go_base_object = this->theEngineObject->mallocGoBase();
    if (!go_base_object) {
        this->abend("processMallocBase", "null go_base");
        return;
    }
    go_base_object->setRoomIdIndex(data_val);

    downlink_data = data_ptr = (char *) malloc(BASE_MGR_DATA_BUFFER_SIZE + 4);
    *data_ptr++ = THEME_ENGINE_PROTOCOL_RESPOND_IS_MALLOC_BASE;
    memcpy(data_ptr, data_val, ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    data_ptr += ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE;
    memcpy(data_ptr, go_base_object->goBaseIdIndex(), BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE);
    data_ptr += BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE;
    *data_ptr = 0;
    this->transmitFunction(downlink_data);
}

void DEngineClass::processTransferData(char *data_val)
{
    this->debug(true, "processTransferData", data_val);

    GoBaseClass *base_object = this->theEngineObject->searchGoBase(data_val);
    if (!base_object) {
        this->abend("processTransferData", "null base_object");
        /* TBD */
        return;
    }

    if (1) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "baseId=%d baseIndex=%d", base_object->goBaseId(), base_object->goBaseIndex());
        this->logit("processTransferData", s);
    }

    base_object->portObject()->receiveStringData(data_val + ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
}

void DEngineClass::processTransferDataResponse(GoBaseClass *base_object_val, char *data_val)
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
