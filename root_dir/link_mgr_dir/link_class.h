/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_class.h
*/

#pragma once

#define  LINK_CLASS_LINK_NAME_BUF_SIZE 32

class LinkMgrClass;

class LinkClass {
    LinkMgrClass *theLinkMgrObject;
    int theLinkId;
    char theLinkName[LINK_CLASS_LINK_NAME_BUF_SIZE + 4];

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    LinkClass(LinkMgrClass *link_mgr_object_val, int link_id_val, char const* link_name_val);
    ~LinkClass(void);
    char const* objectName(void) {return "LinkClass";}
};
