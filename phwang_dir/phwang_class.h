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
class ListMgrRootClass;
class ArrayMgrRootClass;

class PhwangClass {
    inline static char *ObjectName = "PhwangClass";

    ObjectClass *theObjectObject;
    AbendClass *theAbendObject;
    EncodeClass *theEncodeObject;
    MallocClass *theMallocObject;
    QueueRootClass *theQueueRootObject;
    NetRootClass *theNetRootObject;
    ListMgrRootClass *theListMgrRootObject;
    ArrayMgrRootClass *theArrayMgrRootObject;

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void logit3(char const *str0_val, char const *str1_val, char const *str2_val);
    void abend(char const *str0_val, char const *str1_val);
    void abend3(char const *str0_val, char const *str1_val, char const *str2_val);

public:
    PhwangClass(void);
    ~PhwangClass(void);

    AbendClass *abendObject(void) {return this->theAbendObject;}
    ObjectClass *objectObject(void) {return this->theObjectObject;}
    EncodeClass *encodeObject(void) {return this->theEncodeObject;}
    MallocClass *mallocObject(void) {return this->theMallocObject;}
    QueueRootClass *queueRootObject(void) {return this->theQueueRootObject;}
    NetRootClass *netRootObject(void) {return this->theNetRootObject;}
    ListMgrRootClass *listMgrRootObject(void) {return this->theListMgrRootObject;}
    ArrayMgrRootClass *arrayMgrRootObject(void) {return this->theArrayMgrRootObject;}

    /* tbd */
    void printBoard(char const *data_val, int board_size_val);

    /* register */
    void registerProgramProcess(int *register_tag_ptr_val, char *program_name_val, unsigned short port_val);
};
