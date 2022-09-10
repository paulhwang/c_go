/*
  Copyrights reserved
  Written by Paul Hwang
  File name: engine_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../protocol_dir/base_mgr_protocol.h"
#include "engine_class.h"
#include "go_base_dir/go_base_class.h"
#include "d_engine_dir/d_engine_class.h"

EngineClass::EngineClass (int debug_code_val)
{
    memset(this, 0, sizeof(EngineClass));
    this->theDebugCode = debug_code_val;
    
    this->theDEngineObject = new DEngineClass(this);
    this->theGoBaseListMgrObject = phwangListMgrMalloc("GO_BASE", BASE_MGR_PROTOCOL_BASE_ID_SIZE, BASE_MGR_PROTOCOL_BASE_INDEX_SIZE, 900);

    phwangDebugS(false, "EngineClass::EngineClass", "init");
}

EngineClass::~EngineClass (void)
{
    this->theDEngineObject->~DEngineClass();
    phwangDebugS(true, "EngineClass::~EngineClass", "exit");
}

GoBaseClass *EngineClass::mallocGoBase (char const *config_info_val)
{
    phwangDebugS(true, "EngineClass::mallocGoBase", "");
    GoBaseClass *base_object = new GoBaseClass(this->theGoBaseListMgrObject, this, config_info_val);
    if (!base_object) {
        phwangAbendS("EngineClass::mallocGoBase", "fail_to_malloc_base_object");
        return 0;
    }
    return base_object;
}
