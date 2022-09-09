/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_server_class.h
*/

#pragma once

//#include <pthread.h>
//#include "../../protocol_dir/link_mgr_protocol.h"
//#include "../fabric_class.h"

class FabricClass;
class MmwClass;

class MessengerClass {
    char const *objectName(void) {return "MessengerClass";}

    FabricClass *theFabricObject;
    MmwClass *theMmwObject;

    void debug(int debug_on_val, char const *func_name_val, char const *str1_val);
    void debug2(int debug_on_val, char const *func_name_val, char const *str1_val, char const *str2_val);
    void debugInt(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val);
    void debugInt2(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);
    void logit(char const *func_name_val, char const *str1_val);
    void logit2(char const *func_name_val, char const *str1_val, char const *str2_val);
    void logitInt(char const *func_name_val, char const *str1_val, int int1_val);
    void logitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);
    void abend(char const *func_name_val, char const *str1_val);
    void abend2(char const *func_name_val, char const *str1_val, char const *str2_val);
   
public:
    MessengerClass(FabricClass *fabric_object_val);
    ~MessengerClass(void);

    FabricClass *fabricObject(void) {return this->theFabricObject;}

    void initMessenger(void);
    char *getMessage(void);
    void putMessage(char const *info_val);
};
