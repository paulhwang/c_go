/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_u_server_receive.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "game_u_server_class.h"
#include "../game_server_class.h"
#include "../game_d_server_dir/game_d_server_class.h"

void GameUServerClass::receiveFunction (char *data_val)
{
    this->logit("receiveFunction", data_val);
    this->theGameServerObject->gameDServerObject()->transmitFunction(data_val);
}

void GameUServerClass::receiveThreadFunction (void)
{
    if (1) {
        this->logit("receiveThreadFunction", "starts");
    }

    while (1) {
        void *data = phwangDequeue(this->theReceiveQueue);
        if (data) {
            this->receiveFunction((char *) data);
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
