/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_class.cpp
*/

#include <stdio.h>
#include "../../utils_dir/logit.h"
#include "../../utils_dir/queue_mgr_class.h"
#include "../tp_dir/tp_class.h"
#include "../tp_dir/tp_transfer_class.h"
#include "../link_mgr_dir/link_mgr_class.h"
#include "../base_mgr_dir/base_mgr_class.h"
#include "main_class.h"
#include "../main_dir/main_exports.h"

MainClass::MainClass(void)
{
    this->theLinkMgrObject = new LinkMgrClass(this);
    this->theGoBaseMgrObject = new BaseMgrClass(this);
    this->theTransportObject = new TpClass(this);
}

MainClass::~MainClass(void)
{
    this->theBaseMgrTpTransferObject->~TpTransferClass(); 

    this->theLinkMgrTpTransferObject->~TpTransferClass(); 
}

void MainClass::startThreads (void)
{
    this->theGoBaseMgrObject->startThreads();
    this->theLinkMgrObject->startThreads();

    StartServerOutputStruct start_server_output;

    this->theTransportObject->startServer(TRANSPORT_PORT_NUMBER_FOR_BASE_MGR, mainBaseMgrReceiveDataFromTransport, this->theGoBaseMgrObject, &start_server_output);
    this->theBaseMgrTpTransferObject = start_server_output.tp_transfer_object;
    this->theBaseMgrTpServerThread = start_server_output.server_thread;

    this->theTransportObject->startServer(TRANSPORT_PORT_NUMBER_FOR_LINK_MGR, mainLinkMgrReceiveDataFromTransport, this->theLinkMgrObject, &start_server_output);
    this->theLinkMgrTpTransferObject = start_server_output.tp_transfer_object;
    this->theLinkMgrTpServerThread = start_server_output.server_thread;

    this->theGoBaseMgrObject->startThreads();
    this->theLinkMgrObject->startThreads();

    //pthread_join(this->theGoBaseMgrObject->receiveThread(), NULL);
    //pthread_join(this->theLinkMgrObject->receiveThread(), NULL);
}

void MainClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    LOGIT(s, str1_val);
}

void MainClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    ABEND(s, str1_val);
}

