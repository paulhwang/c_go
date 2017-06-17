/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_class.h
*/

#pragma once

class ListMgrClass;

class ListEntryClass {
    ListMgrClass *theListMgrObject;
    int theEntryId;

    void debug(int on_off_val, char const* str0_val, char const* str1_val);
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    ListEntryClass(ListMgrClass *list_mgr_object, int entry_id_val);
    ~ListEntryClass(void);
    char const* objectName(void) {return "ListEntryClass";}
};
