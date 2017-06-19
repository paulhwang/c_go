/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "d_fabric_class.h"
#include "../fabric_class.h"
#include "../u_fabric_dir/u_fabric_class.h"
#include "../link_mgr_dir/link_mgr_class.h"
#include "../link_mgr_dir/link_class.h"
#include "../link_mgr_dir/session_class.h"

void DFabricClass::exportedparseFunction(char *data_val)
{
    this->logit("exportedparseFunction", data_val);

    if (*data_val == LINK_MGR_PROTOCOL_COMMAND_IS_MALLOC_LINK) {
        data_val++;
        this->processMallocLink(data_val);
    }
    else if (*data_val == LINK_MGR_PROTOCOL_COMMAND_IS_MALLOC_SESSION) {
        data_val++;
        this->processMallocSession(data_val);
    }
    else if (*data_val == LINK_MGR_PROTOCOL_COMMAND_IS_PUT_SESSION_DATA) {
        data_val++;
        this->processPutSessionData(data_val);
    }

    //this->theFabricObject->uFabricObject()->transmitFunction(data_val);
}

void DFabricClass::processMallocLink(char *data_val)
{
    char *data_buf = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    data_buf[0] = LINK_MGR_PROTOCOL_RESPOND_IS_MALLOC_LINK;

    LinkClass *link = this->theFabricObject->linkMgrObject()->mallocLink(data_val);
    if (link) {
        phwangEncodeIdIndex(data_buf + 1, link->linkId(), LINK_MGR_PROTOCOL_LINK_ID_SIZE, link->linkIndex(), LINK_MGR_PROTOCOL_LINK_INDEX_SIZE);
    }
    else {
        /* TBD */
    }
    this->theFabricObject->dFabricObject()->transmitFunction(data_buf);
}

void DFabricClass::processMallocSession(char *data_val)
{
    char *data_buf = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    data_buf[0] = LINK_MGR_PROTOCOL_RESPOND_IS_MALLOC_SESSION;

    SessionClass *session = this->theFabricObject->linkMgrObject()->mallocSession(data_val);
    if (session) {
        phwangEncodeIdIndex(data_buf + 1, session->sessionId(), LINK_MGR_PROTOCOL_SESSION_ID_SIZE, session->sessionIndex(), LINK_MGR_PROTOCOL_SESSION_INDEX_SIZE);
    }
    else {
        /* TBD */
    }
    this->theFabricObject->dFabricObject()->transmitFunction(data_buf);
}

void DFabricClass::processGetSessionData(char *data_val)
{
}

void DFabricClass::processPutSessionData(char *data_val)
{
    char *data_buf = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    data_buf[0] = LINK_MGR_PROTOCOL_RESPOND_IS_PUT_SESSION_DATA;

    this->theFabricObject->linkMgrObject()->putSessionData(data_val);

    //this->theFabricObject->dFabricObject()->transmitFunction(data_buf);
    this->theFabricObject->dFabricObject()->transmitFunction("put_session_data TBD");
}
