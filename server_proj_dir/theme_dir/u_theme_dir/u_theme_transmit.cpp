/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_theme_transmit.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "u_theme_class.h"

void UThemeClass::xmtData (char *data_val)
{
    phwangLogitS("UThemeClass::xmtData", data_val);

    if (!this->portObject()) {
        phwangAbendS("UThemeClass::xmtData", "null portObject()! The reason could be the connection from ThemeServer has not been accepted");
        return;
    }

    phwangPortTransmit(this->portObject(), data_val);
}
