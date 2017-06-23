/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_base.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "base_mgr_class.h"

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

int BaseMgrClass::allocBaseId (void)
{
    if (this->theGlobalBaseId >= BASE_MGR_MAX_GLOBAL_BASE_ID) {
        this->theGlobalBaseId = 0;
    }
    this->theGlobalBaseId++;
    return this->theGlobalBaseId;
}

GoBaseClass *BaseMgrClass::mallocGoBase (void)
{
    int base_id = this->allocBaseId();
    int base_index = this->allocBaseIndex();
    if (base_index == -1) {
        this->abend("mallocGoBase", "no space");
        return 0;
    }

    GoBaseClass *base_object = new GoBaseClass(this, base_id, base_index);
    this->theBaseTableArray[base_index] = base_object;

    char *data_buf = (char *) malloc(BASE_MGR_DATA_BUFFER_SIZE + 4);
    data_buf[0] = BASE_MGR_PROTOCOL_RESPOND_IS_MALLOC_BASE;
    data_buf[1] = BASE_MGR_PROTOCOL_GAME_NAME_IS_GO;
    phwangEncodeIdIndex(data_buf + 2, base_id, BASE_MGR_PROTOCOL_BASE_ID_SIZE, base_index, BASE_MGR_PROTOCOL_BASE_INDEX_SIZE);

    return base_object;
}

/*
GoBaseClass *BaseMgrClass::mallocGoBase (void)
{
    int base_id = this->allocBaseId();
    int base_index = this->allocBaseIndex();
    if (base_index == -1) {
        this->abend("mallocGoBase", "no space");
        return 0;
    }

    this->theBaseTableArray[base_index] = new GoBaseClass(this, base_id);

    char *data_buf = (char *) malloc(BASE_MGR_DATA_BUFFER_SIZE + 4);
    data_buf[0] = BASE_MGR_PROTOCOL_RESPOND_IS_MALLOC_BASE;
    data_buf[1] = BASE_MGR_PROTOCOL_GAME_NAME_IS_GO;
    phwangEncodeIdIndex(data_buf + 2, base_id, BASE_MGR_PROTOCOL_BASE_ID_SIZE, base_index, BASE_MGR_PROTOCOL_BASE_INDEX_SIZE);

    this->transmitFunction(data_buf);
}
*/