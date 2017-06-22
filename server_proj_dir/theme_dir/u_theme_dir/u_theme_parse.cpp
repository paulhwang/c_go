/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_theme_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/theme_engine_protocol.h"
#include "u_theme_class.h"
#include "../theme_class.h"
#include "../d_theme_dir/d_theme_class.h"

void UThemeClass::exportedparseFunction(char *data_val)
{
    this->debug(true, "exportedparseFunction", data_val);

    if (*data_val == THEME_ENGINE_PROTOCOL_RESPOND_IS_MALLOC_BASE) {
        this->processMallocBaseResponse(++data_val);
    }
    else if (*data_val == THEME_ENGINE_PROTOCOL_RESPOND_IS_GET_SESSION_DATA) {
        this->processGetSessionDataResponse(++data_val);
    }
    else if (*data_val == THEME_ENGINE_PROTOCOL_RESPOND_IS_PUT_SESSION_DATA) {
        this->processPutSessionDataResponse(++data_val);
    }
    else {
        this->abend("exportedparseFunction", data_val);
    }
}

void UThemeClass::processMallocBaseResponse(char *data_al)
{

}

void UThemeClass::processGetSessionDataResponse(char *data_val)
{

}

void UThemeClass::processPutSessionDataResponse(char *data_val)
{

}
