/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_engine_parse.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../define_dir/result_def.h"
#include "../../define_dir/te_def.h"
#include "../../define_dir/fe_def.h"
#include "../../define_dir/engine_def.h"
#include "d_engine_class.h"
#include "../engine_class.h"

void DEngineClass::exportedParseFunction (char *data_val)
{
    phwangDebugS(true, "DEngineClass::exportedParseFunction", data_val);

    switch (*data_val) {
        case TE_DEF::TE_SETUP_BASE_COMMAND:
            this->processSetupBase(data_val + 1);
            return;

        case TE_DEF::TE_PUT_BASE_DATA_COMMAND:
            this->processPutBaseData(data_val + 1);
            return;

        default:
            phwangAbendS("DEngineClass::exportedParseFunction", data_val);
            return;
    }
}

void DEngineClass::processSetupBase (char *data_val)
{
    phwangDebugS(true, "DEngineClass::processSetupBase", data_val);

    char *room_id_ptr = data_val;
    char *base_id_ptr = room_id_ptr + SIZE_DEF::ROOM_ID_INDEX_SIZE;

    GoBaseClass *go_base_object = this->theEngineObject->mallocGoBase(base_id_ptr);
    if (!go_base_object) {
        phwangAbendS("DEngineClass::processSetupBase", "null go_base");
        return;
    }
    go_base_object->setRoomIdIndex(room_id_ptr);

    /* downlink */
    char *current_ptr;
    char *downlink_data = current_ptr = (char *) phwangMalloc(ENGINE_DEF::TE_DL_BUF_WITH_ROOM_BASE_SIZE, MallocClass::DENGINE_SETUP_BASE);
    *current_ptr++ = TE_DEF::TE_SETUP_BASE_RESPONSE;

    memcpy(current_ptr, RESULT_DEF::RESULT_SUCCEED, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, room_id_ptr, SIZE_DEF::ROOM_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::ROOM_ID_INDEX_SIZE;

    memcpy(current_ptr, go_base_object->goBaseIdIndex(), SIZE_DEF::BASE_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::BASE_ID_INDEX_SIZE;
    *current_ptr = 0;

    this->transmitFunction(downlink_data);
}

void DEngineClass::processPutBaseData (char *data_val)
{
    phwangDebugS(true, "DEngineClass::processPutBaseData", data_val);

    GoBaseClass *base_object = this->theEngineObject->searchGoBase(data_val);
    if (!base_object) {
        phwangAbendS("DEngineClass::processPutBaseData", "null base_object");
        /* TBD */
        return;
    }

    //this->debug(true, "processPutBaseData", base_object->goBaseIdIndex());

    base_object->portObject()->receiveInputData(data_val + SIZE_DEF::ROOM_ID_INDEX_SIZE);
}

void DEngineClass::processPutBaseDataResponse (GoBaseClass *base_object_val, char const *data_val)
{
    char *current_ptr;
    char *downlink_data = current_ptr = (char *) phwangMalloc(ENGINE_DEF::TE_DL_BUF_WITH_ROOM_SIZE + strlen(data_val), MallocClass::DENGINE_PUT_BASE_DATA);

    *current_ptr++ = TE_DEF::TE_PUT_BASE_DATA_RESPONSE;

    memcpy(current_ptr, RESULT_DEF::RESULT_SUCCEED, RESULT_DEF::RESULT_SIZE);
    current_ptr += RESULT_DEF::RESULT_SIZE;

    memcpy(current_ptr, base_object_val->roomIdIndex(), SIZE_DEF::ROOM_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::ROOM_ID_INDEX_SIZE;

    strcpy(current_ptr, data_val);

    this->transmitFunction(downlink_data);
}
