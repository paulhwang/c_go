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
class ObjectClass;
class QueueRootClass;
class NetRootClass;
class ThreadRootClass;
class ListMgrRootClass;
class ArrayMgrRootClass;

class PhwangClass {
    char const *objectName(void) {return "PhwangClass";}

    ObjectClass *theObjectObject;
    AbendClass *theAbendObject;
    EncodeClass *theEncodeObject;
    MallocClass *theMallocObject;
    QueueRootClass *theQueueRootObject;
    NetRootClass *theNetRootObject;
    ThreadRootClass *theThreadRootObject;
    ListMgrRootClass *theListMgrRootObject;
    ArrayMgrRootClass *theArrayMgrRootObject;

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    PhwangClass(int debug_code_val);
    ~PhwangClass(void);

    AbendClass *abendObject(void) {return this->theAbendObject;}
    ObjectClass *objectObject(void) {return this->theObjectObject;}
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
