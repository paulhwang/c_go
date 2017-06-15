/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_parse.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "base_mgr_class.h"

void BaseMgrClass::parseReceiveData (char *data_val)
{
    this->logit("receiveFunction", data_val);

    if (*data_val == BASE_MGR_PROTOCOL_COMMAND_IS_MALLOC_BASE) {
        data_val++;
        if (*data_val == BASE_MGR_PROTOCOL_GAME_NAME_IS_GO) {
            this->mallocGoBase();
        }
    }
    else if (*data_val == BASE_MGR_PROTOCOL_COMMAND_IS_TRANSFER_DATA) {
        data_val++;
        this->receiveData(data_val);
    }
    else {
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
