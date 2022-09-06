/*
  Copyrights reserved
  Written by Paul Hwang
  File name: server_root_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../fabric_dir/fabric_class.h"
#include "../engine_dir/engine_class.h"
#include "../theme_dir/theme_class.h"
#include "server_root_class.h"

ServerRootClass::ServerRootClass (int debug_code_val)
{
    phwangPhwangPhwang(debug_code_val);
    sleep(1);
    this->theFabricObject = new FabricClass(debug_code_val);
    sleep(3);
    this->theGoThemeObject = new ThemeClass(debug_code_val);
    sleep(3);
    this->theEngineObject = new EngineClass(debug_code_val);
}

ServerRootClass::~ServerRootClass (void)
{
    this->theEngineObject->~EngineClass();
    this->theGoThemeObject->~ThemeClass();
    this->theFabricObject->~FabricClass();
    this->debug(true, "~ServerRootClass", "exit");
}

void ServerRootClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void ServerRootClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
