/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_engine_parse.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../protocol_dir/theme_engine_protocol.h"
#include "../../protocol_dir/base_mgr_protocol.h"
#include "d_engine_class.h"
#include "../engine_class.h"

void DEngineClass::exportedParseFunction (char *data_val)
{
    phwangDebugS(true, "DEngineClass::exportedParseFunction", data_val);

    switch (*data_val) {
        case TE_Command_Class::SETUP_BASE_COMMAND:
            this->processSetupBase(data_val + 1);
            return;

        case TE_Command_Class::PUT_BASE_DATA_COMMAND:
            this->processPutBaseData(data_val + 1);
            return;

        default:
            phwangAbendS("DEngineClass::exportedParseFunction", data_val);
            return;
    }
}

void DEngineClass::processSetupBase (char const *data_val)
{
    if (1) { /* debug */
        phwangLogitS("DEngineClass::processSetupBase", data_val);
    }

    char const *room_id_index_val = data_val;

    char *downlink_data;
    char *data_ptr;

    GoBaseClass *go_base_object = this->theEngineObject->mallocGoBase(room_id_index_val + ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    if (!go_base_object) {
        phwangAbendS("DEngineClass::processSetupBase", "null go_base");
        return;
    }
    go_base_object->setRoomIdIndex(room_id_index_val);

    downlink_data = data_ptr = (char *) phwangMalloc(BASE_MGR_DATA_BUFFER_SIZE + 4, MallocClass::DENGINE_SETUP_BASE);
    *data_ptr++ = TE_Command_Class::SETUP_BASE_RESPONSE;

    memcpy(data_ptr, room_id_index_val, ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    data_ptr += ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE;

    memcpy(data_ptr, go_base_object->goBaseIdIndex(), BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE);
    data_ptr += BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE;
    *data_ptr = 0;

    this->transmitFunction(downlink_data);
}

void DEngineClass::processPutBaseData (char const *data_val)
{
    if (1) { /* debug */
        phwangLogitS("DEngineClass::processPutBaseData", data_val);
    }

    GoBaseClass *base_object = this->theEngineObject->searchGoBase(data_val);
    if (!base_object) {
        phwangAbendS("DEngineClass::processPutBaseData", "null base_object");
        /* TBD */
        return;
    }

    //this->debug(true, "processPutBaseData", base_object->goBaseIdIndex());

    base_object->portObject()->receiveInputData(data_val + ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
}

void DEngineClass::processPutBaseDataResponse (GoBaseClass *base_object_val, char const *data_val)
{
    char *downlink_data;
    char *data_ptr;

    downlink_data = data_ptr = (char *) phwangMalloc(BASE_MGR_DATA_BUFFER_SIZE + 4, MallocClass::DENGINE_PUT_BASE_DATA);
    *data_ptr++ = TE_Command_Class::PUT_BASE_DATA_RESPONSE;
    memcpy(data_ptr, base_object_val->roomIdIndex(), ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    data_ptr += ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE;
    strcpy(data_ptr, data_val);
    this->transmitFunction(downlink_data);
}
