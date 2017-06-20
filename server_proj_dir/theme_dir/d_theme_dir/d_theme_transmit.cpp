/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_d_server_receive.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "d_theme_class.h"

void GameDServerClass::transmitFunction (char *data_val)
{
    this->logit("transmitFunction", data_val);

    if (!this->theTpTransferObject) {
        this->abend("transmitFunction", "null theTpTransferObject");
        return;
    }

    phwangTpTransmit(this->theTpTransferObject, data_val);
}
