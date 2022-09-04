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

class PhwangClass {
    inline static char *ObjectName = "PhwangClass";
    inline static int ObjectCount = 0;

    ObjectClass *theObjectObject;
    AbendClass *theAbendObject;
    EncodeClass *theEncodeObject;
    MallocClass *theMallocObject;
    QueueRootClass *theQueueRootObject;
    NetRootClass *theNetRootObject;

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

    /* tbd */
    void printBoard(char const *data_val, int board_size_val);

    /* list_mgr */
    void *listMgrMalloc(char const *caller_name_val, int id_size_val, int index_size_val, int global_entry_id_val);
    void  listMgrFree(void *list_mgr_val);
    void  listMgrRemoveEntry(void *list_mgr_val, void *entry_val);
    void *listMgrSearchEntry(void *list_mgr_val, char const *data_val, void *extra_data_val);
    int   listMgrGetMaxIndex(void *list_mgr_val, char const *who_val);
    void *listMgrGetEntryTableArray(void *list_mgr_val);

    /* array_mgr */
    void *arrayMgrMalloc(char const *caller_name_val, char array_type_val, int max_array_size_val);
    void  arrayMgrFree(void *array_mgr_val);
    void  arrayMgrInsertElement(void *array_mgr_val, void *element_val);
    void  arrayMgrRemoveElement(void *array_mgr_val, void *element_val);
    void *arrayMgrGetArrayTable(void *array_mgr_val, int *array_size_ptr);

    /* register */
    void registerProgramProcess(int *register_tag_ptr_val, char *program_name_val, unsigned short port_val);
};
