/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_class.h
*/

#pragma once

class LinkMgrClass;

class LinkClass {
    LinkMgrClass *theLinkMgrObject;
    int theLinkId;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    LinkClass(LinkMgrClass *link_mgr_object_val, int link_id_val);
    ~LinkClass(void);
    char const* objectName(void) {return "LinkClass";}
};
