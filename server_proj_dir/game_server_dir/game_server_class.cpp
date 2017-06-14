/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_server_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "game_server_class.h"
#include "group_mgr_class.h"

void gameServerTpServerAcceptFunction (void *base_mgr_object_val, void *tp_transfer_object_val) {
    phwangLogit("Golbal::gameServerTpServerAcceptFunction", "");
    phwangAbend("Golbal::gameServerTpServerAcceptFunction", "");
    //((BaseMgrClass *) base_mgr_object_val)->exportAcceptConnection(tp_transfer_object_val);
}

void gameServerTpReceiveDataFunction (void *base_mgr_object_val, void *data_val) {
    phwangLogit("Golbal::gameServerTpReceiveDataFunction", (char *) data_val);
    phwangAbend("Golbal::gameServerTpReceiveDataFunction", (char *) data_val);
    //((BaseMgrClass *) base_mgr_object_val)->exportReceiveData(data_val);
}

GameServerClass::GameServerClass (void *main_object_val)
{
    memset(this, 0, sizeof(GameServerClass));
    this->theMainObject = main_object_val;
    this->theGroupMgrObject = new GroupMgrClass(this);
    this->theTpServerObject = phwangMallocTpServer(this, BASE_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, gameServerTpServerAcceptFunction, this, gameServerTpReceiveDataFunction, this);

    if (1) {
        this->logit("GameServerClass", "init");
    }
}

GameServerClass::~GameServerClass (void)
{
}

void GameServerClass::startThreads (void)
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
