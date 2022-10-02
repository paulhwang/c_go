/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_theme_transmit.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "u_theme_class.h"

void UThemeClass::transmitFunction (char *data_val)
{
    phwangLogitS("UThemeClass::transmitFunction", data_val);

    if (!this->portObject()) {
        phwangAbendS("UThemeClass::transmitFunction", "null portObject()! The reason could be the connection from ThemeServer has not been accepted");
        return;
    }

    phwangPortTransmit(this->portObject(), data_val);
}
