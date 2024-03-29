/*
  Copyrights reserved
  Written by Paul Hwang
  File name: engine_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../define_dir/te_def.h"
#include "engine_class.h"
#include "go_base_dir/go_base_class.h"
#include "d_engine_dir/d_engine_class.h"

EngineClass::EngineClass (int debug_on_val)
{
    memset(this, 0, sizeof(EngineClass));
    this->debugOn_ = true && debug_on_val;
    this->theDebugCode = debug_on_val;
    
    this->theDEngineObject = new DEngineClass(this->debugOn_, this);
    this->theGoBaseListMgrObject = phwangListMgrMalloc(this->debugOn_, "GO_BASE", SIZE_DEF::BASE_ID_SIZE, SIZE_DEF::BASE_INDEX_SIZE, SIZE_DEF::BASE_ID_INITIAL_VALUE);

    phwangDebugS(false, "EngineClass::EngineClass", "init");
}

EngineClass::~EngineClass (void)
{
    this->theDEngineObject->~DEngineClass();
    phwangDebugS(true, "EngineClass::~EngineClass", "exit");
}

GoBaseClass *EngineClass::mallocGoBase (char *config_info_val)
{
    GoBaseClass *base_object = new GoBaseClass(this->debugOn_, this->theGoBaseListMgrObject, this, config_info_val);
    if (!base_object) {
        phwangAbendS("EngineClass::mallocGoBase", "fail_to_malloc_base_object");
        return 0;
    }
    return base_object;
}
