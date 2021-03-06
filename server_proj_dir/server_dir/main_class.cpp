/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../fabric_dir/fabric_class.h"
#include "../engine_dir/engine_class.h"
#include "../theme_dir/theme_class.h"
#include "main_class.h"

MainClass::MainClass(void)
{
    this->theFabricObject = new FabricClass();
    this->theGoThemeObject = new ThemeClass();
    this->theEngineObject = new EngineClass();
}

MainClass::~MainClass(void)
{
    this->theEngineObject->~EngineClass();
    this->theGoThemeObject->~ThemeClass();
    this->theFabricObject->~FabricClass();
    this->debug(true, "~MainClass", "exit");
}

void MainClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void MainClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
