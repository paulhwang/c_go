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

#define GO_PROTOCOL_MOVE_COMMAND 'M'
#define GO_PROTOCOL_PASS_COMMAND 'P'
#define GO_PROTOCOL_BACKWARD_COMMAND 'b'
#define GO_PROTOCOL_DOUBLE_BACKWARD_COMMAND 'B'
#define GO_PROTOCOL_FORWARD_COMMAND 'f'
#define GO_PROTOCOL_DOUBLE_FORWARD_COMMAND 'F'
#define GO_PROTOCOL_RESIGN_COMMAND 'R'
#define GO_PROTOCOL_CONFIRM_COMMAND 'C'
#define GO_PROTOCOL_CONTINUE_COMMAND 'c'

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
    this->debug(true, "receiveInputData", str_val);

    switch (*str_val) {
        case GO_PROTOCOL_MOVE_COMMAND:
            this->aMoveIsPlayed(str_val + 1);
            return;

        case GO_PROTOCOL_BACKWARD_COMMAND:
            this->theBaseObject->gameObject()->processBackwardMove();
            this->theBaseObject->portObject()->transmitBoardData();
            return;

        case GO_PROTOCOL_DOUBLE_BACKWARD_COMMAND:
            this->theBaseObject->gameObject()->processDoubleBackwardMove();
            this->theBaseObject->portObject()->transmitBoardData();
            return;

        case GO_PROTOCOL_FORWARD_COMMAND:
            this->theBaseObject->gameObject()->processForwardMove();
            this->theBaseObject->portObject()->transmitBoardData();
            return;

        case GO_PROTOCOL_DOUBLE_FORWARD_COMMAND:
            this->theBaseObject->gameObject()->processDoubleForwardMove();
            this->theBaseObject->portObject()->transmitBoardData();
            return;

        case GO_PROTOCOL_PASS_COMMAND:
        case GO_PROTOCOL_RESIGN_COMMAND:
        case GO_PROTOCOL_CONFIRM_COMMAND:
        case GO_PROTOCOL_CONTINUE_COMMAND:

        default:
            this->abend("receiveInputData", str_val);
    }
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
