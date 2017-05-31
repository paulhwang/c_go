/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_class.cpp
*/

#include <stdio.h>
#include <unistd.h>
#include "../../utils_dir/logit.h"
#include "../../utils_dir/queue_mgr_class.h"
#include "base_mgr_class.h"
#include "base_class.h"
#include "../../main_exports.h"
#include "../go_base_dir/go_base_class.h"

BaseMgrClass::BaseMgrClass (void *main_object_val)
{
    this->mainObject = main_object_val;

    this->theTestGoBase = new GoBaseClass(this);

    this->receiveQueue = new QueueMgrClass();
    this->receiveQueue->initQueue(BASE_MGR_RECEIVE_QUEUE_SIZE);

    if (1) {
        this->logit("init", "");
    }
}

BaseMgrClass::~BaseMgrClass (void)
{
}

GoBaseClass* BaseMgrClass::getBaseByBaseId (int base_id_val) {
    return this->theTestGoBase;
}

void BaseMgrClass::receiveThreadLoop (void)
{
    while (1) {
        char *data = (char *) this->receiveQueue->dequeueData();
        if (data) {
            if (*data == 'm') {
                this->mallocBase();
            }
            else if (*data == 'd') {
                this->receiveData(1, data + 1);
            }
            else {
            }
        }
    }
}

int BaseMgrClass::mallocBase (void)
{
    /*
        var base = this.importObject().importBase().malloc(this.rootObject(), this.allocBaseId());
        this.baseIndexArray().push(base.baseId());
        this.baseTableArray().push(base);
        return base.baseId();
    */
    return 1000;
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
        mainTransmitDataToTransport(this->mainObject, data_val);
    }
}

void BaseMgrClass::receiveData (int base_id_val, char* data_val) {
    this->logit("receiveData", data_val);
    GoBaseClass* go_base = this->getBaseByBaseId(base_id_val);
    if (!go_base) {
        return;
    }
    go_base->portObject()->receiveStringData(data_val);
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

