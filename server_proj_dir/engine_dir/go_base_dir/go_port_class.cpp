/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_port_class.cpp
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "go_base_class.h"
#include "go_port_class.h"
#include "../engine_class.h"
#include "../d_engine_dir/d_engine_class.h"
#include "../../protocol_dir/base_mgr_protocol.h"

#define GO_PROTOCOL_CODE_SIZE 7
#define GO_PROTOCOL_CODE_PROPOSE      "Propose"
#define GO_PROTOCOL_CODE_ACCEPT       "Accept "
#define GO_PROTOCOL_CODE_CONFIRM      "Confirm"
#define GO_PROTOCOL_CODE_MOVE_DATA    "Move   "
#define GO_PROTOCOL_CODE_SPECIAL_MOVE "Special"
#define GO_PROTOCOL_CODE_BOARD_DATA   "Board  "

GoPortClass::GoPortClass (GoBaseClass *base_object_val):
    theBaseObject(base_object_val)
{
    this->debug(true, "GoPortClass", "init");
}

void GoPortClass::transmitBoardData (void) {
    this->debug(true, "transmitBoardData", this->theBaseObject->boardObject()->encodeBoard());
    this->theBaseObject->engineObject()->dEngineObject()->processPutBaseDataResponse(this->theBaseObject, this->theBaseObject->boardObject()->encodeBoard());
}

void GoPortClass::receiveInputData (char const *str_val) {
    char code[GO_PROTOCOL_CODE_SIZE + 4];
    char data[32];

    this->debug(true, "receiveInputData", str_val);

    if (!str_val) {
        this->abend("receiveInputData", "null input");
        return;
    }

    memcpy(code, str_val, GO_PROTOCOL_CODE_SIZE);
    code[GO_PROTOCOL_CODE_SIZE] = 0;
    strcpy(data, str_val + GO_PROTOCOL_CODE_SIZE);

    this->debug(true, "receiveInputData", code);
    this->debug(true, "receiveInputData", data);

    if (!strcmp(code, GO_PROTOCOL_CODE_MOVE_DATA)) {
        this->aMoveIsPlayed(data);
        return;
    }
    else if (!strcmp(code, GO_PROTOCOL_CODE_SPECIAL_MOVE)) {
        this->aSpecialMoveIsPlayed(data);
        return;
    }
    this->abend("receiveInputData", code);
};

void GoPortClass::aMoveIsPlayed (char const *str_val) {
    this->debug(true, "aMoveIsPlayed", str_val);

    GoMoveClass *move = new GoMoveClass(this->theBaseObject, str_val);
    this->theBaseObject->gameObject()->addNewMoveAndFight(move);
    this->transmitBoardData();
}

void GoPortClass::aSpecialMoveIsPlayed (char const *str_val) {
    this->debug(true, "aSpecialMoveIsPlayed", str_val);
    this->theBaseObject->gameObject()->receiveSpecialMoveFromOpponent(str_val);
}

void GoPortClass::logit (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theBaseObject->goBaseLogit(s, str1_val);
}

void GoPortClass::abend (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theBaseObject->goBaseAbend(s, str1_val);
}
