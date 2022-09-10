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
    this->theMallocObject = new MallocClass(this->debugCode());
    this->theEncodeObject = new EncodeClass(this->debugCode());
    this->theQueueRootObject = new QueueRootClass(this->debugCode());
    this->theNetRootObject = new NetRootClass(this->debugCode());
    this->theThreadRootObject = new ThreadRootClass(this->debugCode());
    this->theListMgrRootObject = new ListMgrRootClass(this->debugCode());
    this->theArrayMgrRootObject = new ArrayMgrRootClass(this->debugCode());

    phwangDebugSI(false, "PhwangClass::initObjects", "debugCode=", this->debugCode());
}

void PhwangClass::registerProgramProcess (int *register_tag_ptr_val, char *program_name_val, unsigned short port_val)
{
    *register_tag_ptr_val = 1;
    while (*register_tag_ptr_val) {
        sleep(10);
    }
}
