/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_entry_class.h
*/

#pragma once

class ListMgrClass;

class ListEntryClass {
    ListMgrClass *theListMgrObject;

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    ListEntryClass(ListMgrClass *list_mgr_object);
    ~ListEntryClass(void);
    char const* objectName(void) {return "ListEntryClass";}

    int theEntryId;
    int theEntryIndex;
    char *theEntryIdIndex;
};
