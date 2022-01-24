/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_port_class.cpp
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "go_protocol_define.h"
#include "go_base_class.h"
#include "go_port_class.h"
#include "../engine_class.h"
#include "../d_engine_dir/d_engine_class.h"
#include "../../protocol_dir/base_mgr_protocol.h"

GoPortClass::GoPortClass (GoBaseClass *base_object_val):
    theBaseObject(base_object_val)
{
    if (1) { /* debug */
        this->logit("GoPortClass", "init");
    }
}

void GoPortClass::transmitBoardData (void) {
    this->theBaseObject->boardObject()->encodeBoard();

    if (0) { /* debug */
        this->logit("transmitBoardData", this->theBaseObject->boardObject()->boardOutputBuffer());
    }

    this->transmitOutputData(this->theBaseObject->boardObject()->boardOutputBuffer());
}

void GoPortClass::transmitOutputData (char const *data_val) {
    this->theBaseObject->engineObject()->dEngineObject()->processPutBaseDataResponse(this->theBaseObject, data_val);
}

void GoPortClass::receiveInputData (char const *str_val) {
    if (1) { /* debug */
        this->logit("receiveInputData", str_val);
    }

    switch (*str_val) {
        case GO_PROTOCOL_GAME_INFO:
            this->parseGameData(str_val + 1);
            return;

        case GO_PROTOCOL_TIME_INFO:
        case GO_PROTOCOL_CHAT_INFO:
        default:
            this->abend("receiveInputData", str_val);
            return;
    }
}

void GoPortClass::parseGameData (char const *str_val) {
    GoMoveClass *move;
    switch (*str_val) {
        case GO_PROTOCOL_MOVE_COMMAND:
            move = new GoMoveClass(this->theBaseObject, str_val + 1);
            this->theBaseObject->gameObject()->addNewMoveAndFight(move);
            this->transmitBoardData();
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
            this->abend("parseGameData", str_val);
            return;
    }
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
