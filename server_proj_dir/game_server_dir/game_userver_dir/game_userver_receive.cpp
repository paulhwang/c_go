/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_userver_receive.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "game_userver_class.h"

void GameUServerClass::receiveThreadFunction (void)
{
    if (1) {
        this->logit("receiveThreadFunction", "starts");
    }
    this->receiveThreadLoop();
}

void GameUServerClass::receiveThreadLoop (void)
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

void *gameUServerReceiveThreadFunction (void *this_val)
{
    ((GameUServerClass *)this_val)->receiveThreadFunction();
}

void GameUServerClass::startReceiveThread (void)
{
    int r;

    if (0) {
        this->logit("startReceiveThread", "create receiveThread");
    }
    r = pthread_create(&this->theReceiveThread, NULL, gameUServerReceiveThreadFunction, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }
}
