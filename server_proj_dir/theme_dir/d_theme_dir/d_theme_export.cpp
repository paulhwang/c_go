/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "d_theme_class.h"
#include "../theme_class.h"
#include "../u_theme_dir/u_theme_class.h"

void DThemeClass::exportedparseFunction(char *data_val)
{
    this->debug(true, "exportedparseFunction", data_val);
    this->theThemeObject->uThemeObject()->transmitFunction(data_val);
}
