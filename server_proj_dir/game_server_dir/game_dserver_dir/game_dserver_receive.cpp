/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_dserver_receive.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "game_dserver_class.h"

void GameDServerClass::transmitFunction (char *data_val)
{
    this->logit("transmitFunction", data_val);
    phwangTpTransmit(this->theTpTransferObject, data_val);
}

void GameDServerClass::receiveFunction (char *data_val)
{
    this->logit("receiveFunction", data_val);
}

void GameDServerClass::receiveThreadFunction (void)
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

void *gameDServerReceiveThreadFunction (void *this_val)
{
    ((GameDServerClass *)this_val)->receiveThreadFunction();
}

void GameDServerClass::startReceiveThread (void)
{
    int r;

    if (0) {
        this->logit("startReceiveThread", "create receiveThread");
    }
    r = pthread_create(&this->theReceiveThread, NULL, gameDServerReceiveThreadFunction, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }
}
