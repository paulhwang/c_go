/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_server_thread.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "game_server_class.h"

void *gameServerReceiveThreadFunction (void *this_val)
{
    ((GameServerClass *)this_val)->receiveThreadFunction();
}

void GameServerClass::receiveThreadFunction (void)
{
    if (1) {
        this->logit("receiveThreadFunction", "starts");
    }
    this->receiveThreadLoop();
}

void GameServerClass::receiveThreadLoop (void)
{
    while (1) {
        char *data = (char *) phwangDequeue(this->theReceiveQueue);
        //this->logit("receiveThreadLoop", data);
        if (data) {
            /*
            if (*data == BASE_MGR_PROTOCOL_COMMAND_IS_MALLOC_BASE) {
                data++;
                if (*data == BASE_MGR_PROTOCOL_GAME_NAME_IS_GO) {
                    this->mallocGoBase();
                }
            }
            else if (*data == BASE_MGR_PROTOCOL_COMMAND_IS_TRANSFER_DATA) {
                data++;
                this->receiveData(data);
            }
            else {
            }
            */
        }
    }
}

void GameServerClass::startReceiveThread (void)
{
    int r;

    if (0) {
        this->logit("startReceiveThread", "create receiveThread");
    }
    r = pthread_create(&this->theReceiveThread, NULL, gameServerReceiveThreadFunction, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }
}
void GameServerClass::startThreads (void)
{
    this->startReceiveThread();
}
