/*
  Copyrights reserved
  Written by Paul Hwang
  File name: server_root_class.cpp
*/

#include "../../include_dir/phwang.h"
#include "../fabric_dir/fabric_class.h"
#include "../engine_dir/engine_class.h"
#include "../theme_dir/theme_class.h"
#include "server_root_class.h"

ServerRootClass::ServerRootClass (int debug_on_val)
{
    phwangPhwangPhwang(debug_on_val);
    this->theFabricObject = new FabricClass(debug_on_val);
    sleep(1);
    this->theGoThemeObject = new ThemeClass(debug_on_val);
    sleep(1);
    this->theEngineObject = new EngineClass(debug_on_val);
}

ServerRootClass::~ServerRootClass (void)
{
    this->theEngineObject->~EngineClass();
    this->theGoThemeObject->~ThemeClass();
    this->theFabricObject->~FabricClass();
    phwangDebugS(true, "ServerRootClass::~ServerRootClass", "exit");
}
