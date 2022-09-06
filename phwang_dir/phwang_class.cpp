/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang_class.cpp
*/

#include "phwang.h"
#include "phwang_class.h"
#include "abend_dir/abend_class.h"
#include "encode_dir/encode_class.h"
#include "malloc_dir/malloc_class.h"
#include "object_dir/object_class.h"
#include "queue_dir/queue_root_class.h"
#include "net_dir/net_root_class.h"
#include "thread_dir/thread_root_class.h"
#include "list_mgr_dir/list_mgr_root_class.h"
#include "array_mgr_dir/array_mgr_root_class.h"

PhwangClass::PhwangClass (int debug_code_val)
{
    memset(this, 0, sizeof(*this));
    this->theDebugCode = debug_code_val;
}

PhwangClass::~PhwangClass (void)
{
}

void PhwangClass::initObjects (void)
{
    this->theObjectObject = new ObjectClass(this->debugCode());
    this->theAbendObject = new AbendClass(this->debugCode());
    this->theMallocObject = new MallocClass(this->debugCode());
    this->theEncodeObject = new EncodeClass(this->debugCode());
    this->theQueueRootObject = new QueueRootClass(this->debugCode());
    this->theNetRootObject = new NetRootClass(this->debugCode());
    this->theThreadRootObject = new ThreadRootClass(this->debugCode());
    this->theListMgrRootObject = new ListMgrRootClass(this->debugCode());
    this->theArrayMgrRootObject = new ArrayMgrRootClass(this->debugCode());

    this->debugInt(false, "PhwangClass", "debugCode=", this->debugCode());
}

void PhwangClass::registerProgramProcess(int *register_tag_ptr_val, char *program_name_val, unsigned short port_val)
{
    *register_tag_ptr_val = 1;
    while (*register_tag_ptr_val) {
        sleep(10);
    }
}

void PhwangClass::debug (int debug_on_val, char const *func_name_val, char const *str1_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitBufSize];
        sprintf(s, "%s::%s", this->objectName(), func_name_val);
        phwangDebug(debug_on_val, s, str1_val);
    }
}

void PhwangClass::debug2 (int debug_on_val, char const *func_name_val, char const *str1_val, char const *str2_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitBufSize];
        sprintf(s, "%s::%s", this->objectName(), func_name_val);
        phwangDebug2(debug_on_val, s, str1_val, str2_val);
    }
}

void PhwangClass::debugInt(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitBufSize];
        sprintf(s, "%s::%s", this->objectName(), func_name_val);
        phwangDebugInt(debug_on_val, s, str1_val, int1_val);
    }
}

void PhwangClass::debugInt2(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitBufSize];
        sprintf(s, "%s::%s", this->objectName(), func_name_val);
        phwangDebugInt2(debug_on_val, s, str1_val, int1_val, str2_val, int2_val);
    }
}

void PhwangClass::logit (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitBufSize];
    sprintf(s, "%s::%s", this->objectName(), func_name_val);
    phwangLogit(s, str1_val);
}

void PhwangClass::logit2 (char const *func_name_val, char const *str1_val, char const *str2_val) {
    char s[AbendClass::LogitBufSize];
    sprintf(s, "%s::%s", this->objectName(), func_name_val);
    phwangLogit2(s, str1_val, str2_val);
}

void PhwangClass::logitInt(char const *func_name_val, char const *str1_val, int int1_val)
{
    char s[AbendClass::LogitBufSize];
    sprintf(s, "%s::%s", this->objectName(), func_name_val);
    phwangLogitInt(s, str1_val, int1_val);
}

void PhwangClass::logitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    char s[AbendClass::LogitBufSize];
    sprintf(s, "%s::%s", this->objectName(), func_name_val);
    phwangLogitInt2(s, str1_val, int1_val, str2_val, int2_val);
}

void PhwangClass::abend (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitBufSize];
    sprintf(s, "%s::%s", this->objectName(), func_name_val);
    phwangAbend(s, str1_val);
}

void PhwangClass::abend2 (char const *func_name_val, char const *str1_val, char const *str2_val) {
    char s[AbendClass::LogitBufSize];
    sprintf(s, "%s::%s", this->objectName(), func_name_val);
    phwangAbend2(s, str1_val, str2_val);
}
