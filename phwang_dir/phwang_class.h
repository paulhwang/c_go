/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang_class.h
*/

#pragma once

#define LOGIT_BUF_SIZE 512

class MallocClass;
class QueueRootClass;
class NetRootClass;
class ThreadRootClass;
class ListMgrRootClass;
class ArrayMgrRootClass;

class PhwangClass {
    char const *objectName(void) {return "PhwangClass";}
    int theDebugCode;

    MallocClass *theMallocObject;
    QueueRootClass *theQueueRootObject;
    NetRootClass *theNetRootObject;
    ThreadRootClass *theThreadRootObject;
    ListMgrRootClass *theListMgrRootObject;
    ArrayMgrRootClass *theArrayMgrRootObject;

public:
    PhwangClass(int debug_code_val);
    ~PhwangClass(void);

    void initObjects (void);
    int debugCode(void) {return this->theDebugCode;}

    MallocClass *mallocObject(void) {return this->theMallocObject;}
    QueueRootClass *queueRootObject(void) {return this->theQueueRootObject;}
    NetRootClass *netRootObject(void) {return this->theNetRootObject;}
    ThreadRootClass *threadRootObject(void) {return this->theThreadRootObject;}
    ListMgrRootClass *listMgrRootObject(void) {return this->theListMgrRootObject;}
    ArrayMgrRootClass *arrayMgrRootObject(void) {return this->theArrayMgrRootObject;}

    /* register */
    void registerProgramProcess(int *register_tag_ptr_val, char *program_name_val, unsigned short port_val);
};
