/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang_class.cpp
*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include "phwang.h"
#include "phwang_class.h"
#include "abend_dir/abend_class.h"
#include "encode_dir/encode_class.h"
#include "malloc_dir/malloc_class.h"
#include "object_dir/object_class.h"
#include "queue_dir/queue_root_class.h"
#include "net_dir/net_root_class.h"
#include "list_mgr_dir/list_mgr_root_class.h"
#include "array_mgr_dir/array_mgr_root_class.h"

PhwangClass::PhwangClass (void)
{
    memset(this, 0, sizeof(*this));
    this->theObjectObject = new ObjectClass();
    this->theAbendObject = new AbendClass();
    this->theMallocObject = new MallocClass();
    this->theEncodeObject = new EncodeClass();
    this->theQueueRootObject = new QueueRootClass();
    this->theNetRootObject = new NetRootClass();
    this->theListMgrRootObject = new ListMgrRootClass();
    this->theArrayMgrRootObject = new ArrayMgrRootClass();
}

PhwangClass::~PhwangClass (void)
{
}

/*************************************************************/

void PhwangClass::logit (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", ObjectName, str0_val);
    this->abendObject()->phwangLogit(s, str1_val);
}

void PhwangClass::abend (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", ObjectName, str0_val);
    this->abendObject()->phwangAbend(s, str1_val);
}

void PhwangClass::abend3 (char const *str0_val, char const *str1_val, char const *str2_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", ObjectName, str0_val);
    this->abendObject()->phwangAbend3(s, str1_val, str2_val);
}

void PhwangClass::printBoard (char const* data_val, int board_size_val)
{
    int i = strlen(data_val);
    while (i) {
        if (*data_val == '0') {
            printf(" +");
        }
        else if (*data_val == '1') {
            printf(" *");
        }
        else if (*data_val == '2') {
            printf(" O");
        }
        data_val++;
        i--;
        if (i % board_size_val == 0) {
            printf("\n");
        }
    }
}

/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/

void PhwangClass::registerProgramProcess(int *register_tag_ptr_val, char *program_name_val, unsigned short port_val)
{
    *register_tag_ptr_val = 1;
    while (*register_tag_ptr_val) {
        sleep(10);
    }
}
