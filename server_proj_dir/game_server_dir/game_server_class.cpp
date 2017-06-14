/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_server_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "game_server_class.h"
#include "group_mgr_class.h"

void GameServerClass::baseMgrTest (void)
{
    char *buf = (char *) malloc(BASE_MGR_DATA_BUFFER_SIZE + 4);
    buf[0] = BASE_MGR_PROTOCOL_COMMAND_IS_MALLOC_BASE;
    buf[1] = BASE_MGR_PROTOCOL_GAME_NAME_IS_GO;
    buf[2] = 0;
    phwangTpTransmit(this->theTpTransferObject, buf);
}

void gameServerTpServerAcceptFunction (void *game_server_object_val, void *tp_transfer_object_val) {
    phwangLogit("Golbal::gameServerTpServerAcceptFunction", "");
    ((GameServerClass *) game_server_object_val)->exportAcceptConnectionFromBaseMgr(tp_transfer_object_val);
}

void GameServerClass::exportAcceptConnectionFromBaseMgr (void *tp_transfer_object_val)
{
    this->theTpTransferObject = tp_transfer_object_val;
    sleep(1);
    baseMgrTest();
}

void gameServerTpReceiveDataFunction (void *game_server_object_val, void *data_val) {
    phwangLogit("Golbal::gameServerTpReceiveDataFunction", (char *) data_val);
    ((GameServerClass *) game_server_object_val)->exportReceiveDataFromBaseMgr(data_val);
}

void GameServerClass::exportReceiveDataFromBaseMgr(void *data_val)
{
    phwangEnqueue(this->theReceiveQueue, data_val);
}

GameServerClass::GameServerClass (void *main_object_val)
{
    memset(this, 0, sizeof(GameServerClass));
    this->theMainObject = main_object_val;
    this->theGroupMgrObject = new GroupMgrClass(this);
    this->theReceiveQueue = phwangMallocQueue(GAME_SERVER_RECEIVE_QUEUE_SIZE);
    this->theTpServerObject = phwangMallocTpServer(this, BASE_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, gameServerTpServerAcceptFunction, this, gameServerTpReceiveDataFunction, this);

    if (1) {
        this->logit("GameServerClass", "init");
    }
}

GameServerClass::~GameServerClass (void)
{
}

void GameServerClass::insertGroup (GroupClass *group_object_val)
{
    int i = 0;
    while (i < GAME_SERVER_GROUP_ARRAY_SIZE) {
        if (!this->theGroupTableArray[i]) {
            this->theGroupTableArray[i] = group_object_val;
            return;
        }
        i++;
    }
    this->abend("insertGroup", "table is full");
}

void GameServerClass::removeGroup (GroupClass *group_object_val)
{
    int i = 0;
    while (i < GAME_SERVER_GROUP_ARRAY_SIZE) {
        if (this->theGroupTableArray[i] == group_object_val) {
            this->theGroupTableArray[i] = 0;
            return;
        }
        i++;
    }
    this->abend("removeGroup", "not found");
}

void GameServerClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void GameServerClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
