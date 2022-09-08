/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang_class.h
*/

#pragma once

#define LOGIT_BUF_SIZE 512

class AbendClass;
class EncodeClass;
class MallocClass;
class QueueRootClass;
class NetRootClass;
class ThreadRootClass;
class ListMgrRootClass;
class ArrayMgrRootClass;

class PhwangClass {
    char const *objectName(void) {return "PhwangClass";}
    int theDebugCode;

    AbendClass *theAbendObject;
    EncodeClass *theEncodeObject;
    MallocClass *theMallocObject;
    QueueRootClass *theQueueRootObject;
    NetRootClass *theNetRootObject;
    ThreadRootClass *theThreadRootObject;
    ListMgrRootClass *theListMgrRootObject;
    ArrayMgrRootClass *theArrayMgrRootObject;

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
    PhwangClass(int debug_code_val);
    ~PhwangClass(void);

    void initObjects (void);
    int debugCode(void) {return this->theDebugCode;}

    AbendClass *abendObject(void) {return this->theAbendObject;}
    EncodeClass *encodeObject(void) {return this->theEncodeObject;}
    MallocClass *mallocObject(void) {return this->theMallocObject;}
    QueueRootClass *queueRootObject(void) {return this->theQueueRootObject;}
    NetRootClass *netRootObject(void) {return this->theNetRootObject;}
    ThreadRootClass *threadRootObject(void) {return this->theThreadRootObject;}
    ListMgrRootClass *listMgrRootObject(void) {return this->theListMgrRootObject;}
    ArrayMgrRootClass *arrayMgrRootObject(void) {return this->theArrayMgrRootObject;}

    /* register */
    void registerProgramProcess(int *register_tag_ptr_val, char *program_name_val, unsigned short port_val);
};
