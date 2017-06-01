/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_class.cpp
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include "../../utils_dir/logit.h"
#include "../../utils_dir/queue_mgr_class.h"
#include "base_mgr_class.h"
#include "base_class.h"
#include "../../main_exports.h"
#include "../go_base_dir/go_base_class.h"

BaseMgrClass::BaseMgrClass (void *main_object_val)
{
    memset(this, 0, sizeof(BaseMgrClass));
    this->theMainObject = main_object_val;
    this->theGlobalBaseId = 0;

    this->theReceiveQueue = new QueueMgrClass();
    this->theReceiveQueue->initQueue(BASE_MGR_RECEIVE_QUEUE_SIZE);

    if (1) {
        this->logit("BaseMgrClass", "init");
    }
}

BaseMgrClass::~BaseMgrClass (void)
{
    delete this->theReceiveQueue;
}

void *BaseMgrClass::getBaseByBaseId (int base_id_val) {
    int index = 0;
    while (index < BASE_MGR_BASE_ARRAY_SIZE) {
        if (this->theBaseIndexArray[index] == base_id_val) {
            return this->theBaseTableArray[index];
        }
        index++;
    }
    return 0;
}

int BaseMgrClass::allocBaseId (void)
{
    if (this->theGlobalBaseId >= BASE_MGR_MAX_GLOBAL_BASE_ID) {
        this->theGlobalBaseId = 0;
    }
    this->theGlobalBaseId++;
    return this->theGlobalBaseId;
}

int BaseMgrClass::allocBaseIndex (void)
{
    int index = 0;
    while (index < BASE_MGR_BASE_ARRAY_SIZE) {
        if (!this->theBaseTableArray[index]) {
            return index;
        }
        index++;
    }
    return -1;
}

void BaseMgrClass::mallocBase (void)
{
    int base_id = this->allocBaseId();
    int base_index = this->allocBaseIndex();
    if (base_index != -1) {
        this->theBaseIndexArray[base_index] = base_id;
        this->theBaseTableArray[base_index] = new GoBaseClass(this);

        char *data_buf = (char *) malloc(BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE + 4);
        data_buf[0] = 'm';
        this->encodeBaseId(base_id, base_index, data_buf + 1);

        this->transmitData(data_buf);
    }
    else {
        /* TBD */
    }
}

void BaseMgrClass::encodeBaseId (int base_id_val, int base_index_val, char *buf_val)
{
    if (0) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "base_id_val=%d base_index_val=%d", base_id_val, base_index_val);
        this->logit("encodeBaseId", s);
    }

    buf_val[8] = 0;

    buf_val[7] = '0' + base_index_val % 10;
    base_index_val /= 10;
    buf_val[6] = '0' + base_index_val % 10;
    base_index_val /= 10;
    buf_val[5] = '0' + base_index_val % 10;
    base_index_val /= 10;
    buf_val[4] = '0' + base_index_val;

    buf_val[3] = '0' + base_id_val % 10;
    base_id_val /= 10;
    buf_val[2] = '0' + base_id_val % 10;
    base_id_val /= 10;
    buf_val[1] = '0' + base_id_val % 10;
    base_id_val /= 10;
    buf_val[0] = '0' + base_id_val;

    if (1) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "base_id_index=%s", buf_val);
        this->logit("encodeBaseId", s);
    }
}

int BaseMgrClass::decodeBaseId (char *data_val, int *base_id_ptr_val, int *base_index_ptr_val)
{
    int base_id;
    int base_index;
    base_id =  (*data_val++ - '0') * 1000;
    base_id += (*data_val++ - '0') * 100;
    base_id += (*data_val++ - '0') * 10;
    base_id += (*data_val++ - '0');
    base_index =  (*data_val++ - '0') * 1000;
    base_index += (*data_val++ - '0') * 100;
    base_index += (*data_val++ - '0') * 10;
    base_index += (*data_val - '0');

    if (1) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "base_id=%d base_index=%d", base_id, base_index);
        this->logit("decodeBaseId", s);
    }

    *base_id_ptr_val = base_id;
    *base_index_ptr_val = base_index;
    return 1;
}

void BaseMgrClass::createBase (void)
{
    BaseClass *base = new BaseClass(this);
    this->theGoBaseObject = new GoBaseClass(this);
}

void BaseMgrClass::transmitData(char *data_val)
{
    if (1) {
        this->logit("transmitData", data_val);
        mainTransmitDataToTransport(this->theMainObject, data_val);
    }
}

void BaseMgrClass::receiveData (char* data_val) {
    this->logit("receiveData", data_val);

    int base_id;
    int base_index;
    this->decodeBaseId(data_val, &base_id, &base_index);
    void *base = this->getBaseByBaseId(base_id);
    if (!base) {
        return;
    }

    char const *game = "go";
    if (!strcmp(game, "go")) {
        GoBaseClass *go_base = (GoBaseClass *) base;
        go_base->portObject()->receiveStringData(data_val + BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE);
    }
    else {
        /* TBD: other games */
    }
}

void BaseMgrClass::baseMgrLogit (char const* str0_val, char const* str1_val) {
    LOGIT(str0_val, str1_val);
}

void BaseMgrClass::baseMgrAbend (char const* str0_val, char const* str1_val) {
    LOGIT(str0_val, str1_val);
}

void BaseMgrClass::logit (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->baseMgrLogit(s, str1_val);
}

void BaseMgrClass::abend (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->baseMgrAbend(s, str1_val);
}

