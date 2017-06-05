/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_class.cpp
*/

#include <unistd.h>
#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/queue_dir/queue_class.h"
#include "../../phwang_dir/tp_dir/tp_server_class.h"
#include "../../phwang_dir/tp_dir/tp_transfer_class.h"
#include "base_mgr_class.h"
#include "../go_base_dir/go_base_class.h"

BaseMgrClass::BaseMgrClass (MainClass *main_object_val)
{
    memset(this, 0, sizeof(BaseMgrClass));
    this->theMainObject = main_object_val;
    this->theTpServerObject = new TpServerClass(this->theMainObject);
    this->theGlobalBaseId = 0;

    this->theReceiveQueue = phwangMallocQueue(BASE_MGR_RECEIVE_QUEUE_SIZE);

    if (1) {
        this->logit("BaseMgrClass", "init");
    }
}

BaseMgrClass::~BaseMgrClass (void)
{
    this->theTpTransferObject->~TpTransferClass(); 
    phwangFreeQueue(this->theReceiveQueue);
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

void BaseMgrClass::mallocGoBase (void)
{
    int base_id = this->allocBaseId();
    int base_index = this->allocBaseIndex();
    if (base_index != -1) {
        this->theBaseTableArray[base_index] = new GoBaseClass(this, base_id);

        char *data_buf = (char *) malloc(BASE_MGR_DATA_BUFFER_SIZE + 4);
        data_buf[0] = BASE_MGR_PROTOCOL_RESPOND_IS_MALLOC_BASE;
        data_buf[1] = BASE_MGR_PROTOCOL_GAME_NAME_IS_GO;
        phwangEncodeIdIndex(data_buf + 2, base_id, BASE_MGR_PROTOCOL_BASE_ID_SIZE, base_index, BASE_MGR_PROTOCOL_BASE_INDEX_SIZE);

        this->transmitData(data_buf);
    }
    else {
        /* TBD */
    }
}

void BaseMgrClass::transmitData(char *data_val)
{
    if (1) {
        this->logit("transmitData", data_val);
        this->theTpTransferObject->exportTransmitData(data_val);
    }
}

void BaseMgrClass::receiveData (char* data_val) {
    this->logit("receiveData", data_val);

    char game = *data_val++;

    int base_id;
    int base_index;
    phwangDecodeIdIndex(data_val, &base_id, BASE_MGR_PROTOCOL_BASE_ID_SIZE, &base_index, BASE_MGR_PROTOCOL_BASE_INDEX_SIZE);
    data_val += BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE;
    void *base = this->theBaseTableArray[base_index];
    if (!base) {
        return;
    }

    if (game == BASE_MGR_PROTOCOL_GAME_NAME_IS_GO) {
        GoBaseClass *go_base = (GoBaseClass *) base;
        if (go_base->baseId() != base_id) {
            return;
        }
        go_base->portObject()->receiveStringData(data_val);
    }
    else {
        /* TBD: other games */
    }
}

void BaseMgrClass::baseMgrLogit (char const* str0_val, char const* str1_val) {
    phwangLogit(str0_val, str1_val);
}

void BaseMgrClass::baseMgrAbend (char const* str0_val, char const* str1_val) {
    phwangAbend(str0_val, str1_val);
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

