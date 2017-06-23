/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_class.h
*/

#pragma once

#include <pthread.h>
#include "../../protocol_dir/room_mgr_protocol.h"
#include "../../protocol_dir/base_mgr_protocol.h"
#include "../go_base_dir/go_base_class.h"

class EngineClass;
class BaseClass;
class GoBaseClass;

#define BASE_MGR_RECEIVE_QUEUE_SIZE 100

class BaseMgrClass {
#define BASE_MGR_BASE_ARRAY_SIZE 1000
#define BASE_MGR_MAX_GLOBAL_BASE_ID 9999

    EngineClass *theEngineObject;
    int theGlobalBaseId;
    GoBaseClass *theBaseTableArray[BASE_MGR_BASE_ARRAY_SIZE + 4];

    void *theTpTransferObject;

    void parseReceiveData(char *data_val);

    void startNetConnect(void);

    int allocBaseId(void);
    int allocBaseIndex(void);
    GoBaseClass *mallocGoBase(void);

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class GoPortClass;
    friend class DEngineClass;

    EngineClass *engineObject(void) {return this->theEngineObject;}

public:
    BaseMgrClass(EngineClass *engine_object_val);
    ~BaseMgrClass();
    char const* objectName(void) {return "BaseMgrClass";}

    GoBaseClass *searchBase(char *data_val);
    GoBaseClass *getBaseByIdIndex(int base_id_val, int base_index_val);

    void baseMgrLogit(char const* str0_val, char const* str1_val);
    void baseMgrAbend(char const* str0_val, char const* str1_val);
};
