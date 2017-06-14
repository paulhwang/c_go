/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_userver_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "game_userver_class.h"

void GameUServerClass::baseMgrTest (void)
{
    char *buf = (char *) malloc(BASE_MGR_DATA_BUFFER_SIZE + 4);
    buf[0] = BASE_MGR_PROTOCOL_COMMAND_IS_MALLOC_BASE;
    buf[1] = BASE_MGR_PROTOCOL_GAME_NAME_IS_GO;
    buf[2] = 0;
    phwangTpTransmit(this->theTpTransferObject, buf);
}

void gameUServerTpServerAcceptFunction (void *game_server_object_val, void *tp_transfer_object_val) {
    phwangLogit("Golbal::gameUServerTpServerAcceptFunction", "");
    ((GameUServerClass *) game_server_object_val)->exportAcceptConnectionFromBaseMgr(tp_transfer_object_val);
}

void GameUServerClass::exportAcceptConnectionFromBaseMgr (void *tp_transfer_object_val)
{
    this->theTpTransferObject = tp_transfer_object_val;
    sleep(1);
    baseMgrTest();
}

void gameUServerTpReceiveDataFunction (void *game_server_object_val, void *data_val) {
    phwangLogit("Golbal::gameUServerTpReceiveDataFunction", (char *) data_val);
    ((GameUServerClass *) game_server_object_val)->exportReceiveDataFromBaseMgr(data_val);
}

void GameUServerClass::exportReceiveDataFromBaseMgr(void *data_val)
{
    phwangEnqueue(this->theReceiveQueue, data_val);
}

GameUServerClass::GameUServerClass (GameServerClass *game_server_object_val)
{
    memset(this, 0, sizeof(GameUServerClass));
    this->theGameServerObject = game_server_object_val;
    this->theReceiveQueue = phwangMallocQueue(GAME_USERVER_RECEIVE_QUEUE_SIZE);
    this->theTpServerObject = phwangMallocTpServer(this, BASE_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, gameUServerTpServerAcceptFunction, this, gameUServerTpReceiveDataFunction, this);

    if (1) {
        this->logit("GameUServerClass", "init");
    }
}

GameUServerClass::~GameUServerClass (void)
{
}

void GameUServerClass::startThreads (void)
{
    this->startReceiveThread();
}

void GameUServerClass::debug (int on_off_val, char const* str0_val, char const* str1_val)
{
    if (on_off_val) {
        this->logit(str0_val, str1_val);
    }
}

void GameUServerClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void GameUServerClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
