/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "../../protocol_dir/fabric_theme_protocol.h"
#include "../../protocol_dir/session_mgr_protocol.h"
#include "../../protocol_dir/group_mgr_protocol.h"
#include "../../protocol_dir/room_mgr_protocol.h"
#include "../../protocol_dir/web_fabric_protocol.h"
#include "d_fabric_class.h"
#include "../fabric_class.h"
#include "../u_fabric_dir/u_fabric_class.h"
#include "../link_mgr_dir/link_mgr_class.h"
#include "../link_mgr_dir/link_class.h"
#include "../link_mgr_dir/session_class.h"
#include "../group_mgr_dir/group_mgr_class.h"
#include "../group_mgr_dir/group_class.h"

void DFabricClass::exportedparseFunction (char *data_val)
{
    this->logit("exportedparseFunction", data_val);

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_MALLOC_LINK) {
        this->processMallocLink(data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_MALLOC_SESSION) {
        this->processMallocSession(data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_GET_SESSION_DATA) {
        this->processGetSessionData(data_val + 1);
        return;
    }

    if (*data_val == WEB_FABRIC_PROTOCOL_COMMAND_IS_PUT_SESSION_DATA) {
        this->processPutSessionData(data_val + 1);
        return;
    }

    this->abend("exportedparseFunction", data_val);
}

void DFabricClass::processMallocLink (char *data_val)
{
    this->logit("processMallocLink", data_val);

    char *data_buf = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    data_buf[0] = WEB_FABRIC_PROTOCOL_RESPOND_IS_MALLOC_LINK;

    LinkClass *link = this->theFabricObject->linkMgrObject()->mallocLink(data_val);
    if (!link) {
        this->abend("processMallocLink", "null link");
        strcpy(data_buf + 1, "null link");
        this->transmitFunction(data_buf);
        return;
    }

    phwangEncodeIdIndex(data_buf + 1, link->linkId(), LINK_MGR_PROTOCOL_LINK_ID_SIZE, link->linkIndex(), LINK_MGR_PROTOCOL_LINK_INDEX_SIZE);
    this->transmitFunction(data_buf);
}

void DFabricClass::processMallocSession (char *data_val)
{
    this->logit("processMallocSession", data_val);

    char *data_buf = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);

    GroupClass *group = this->groupMgrObject()->mallocGroup();
    if (!group) {
        this->abend("processMallocSession", "null group");
        data_buf[0] = WEB_FABRIC_PROTOCOL_RESPOND_IS_MALLOC_SESSION;
        strcpy(data_buf + 1, "null group");
        this->transmitFunction(data_buf);
        return;
    }

    SessionClass *session = this->linkMgrObject()->mallocSession(data_val);
    if (!session) {
        this->abend("processMallocSession", "null session");
        data_buf[0] = WEB_FABRIC_PROTOCOL_RESPOND_IS_MALLOC_SESSION;
        strcpy(data_buf + 1, "null session");
        this->transmitFunction(data_buf);
        return;
    }

    group->insertSession(session);
    session->bindGroup(group);

    data_buf[0] = FABRIC_THEME_PROTOCOL_COMMAND_IS_MALLOC_ROOM;
    phwangEncodeIdIndex(data_buf + 1,
                        group->groupId(), GROUP_MGR_PROTOCOL_GROUP_ID_SIZE,
                        group->groupIndex(), GROUP_MGR_PROTOCOL_GROUP_INDEX_SIZE);

    this->theFabricObject->uFabricObject()->transmitFunction(data_buf);
}

void DFabricClass::processGetSessionData (char *data_val)
{
    this->logit("processGetSessionData", data_val);
}

void DFabricClass::processGetSessionDataResponse (char *data_val, SessionClass *session_object_val)
{
}

/*
void dFabricProcessPutSessionResponseCallbackFunction (void *this0_val, void *data_val)
{
    ((DFabricClass *)(this0_val))->exportedProcessPutSessionResponse(data_val);
}
*/

void DFabricClass::processPutSessionData (char *data_val)
{
    this->logit("processPutSessionData", data_val);

    char *output_data = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);

    SessionClass *session = this->linkMgrObject()->serachSession(data_val);
    if (!session) {
        strcpy(output_data + 1, "null session");
        output_data[0] = WEB_FABRIC_PROTOCOL_RESPOND_IS_PUT_SESSION_DATA;
        this->transmitFunction(output_data);
        return;
    }

    char *room = session->groupObject()->roomIdIndexString();
    if (!room) {
        this->abend("processPutSessionData", "null room");
        output_data[0] = WEB_FABRIC_PROTOCOL_RESPOND_IS_PUT_SESSION_DATA;
        strcpy(output_data + 1, "null room");
        this->transmitFunction(output_data);
        return;
    }

    output_data[0] = FABRIC_THEME_PROTOCOL_COMMAND_IS_PUT_SESSION_DATA;
    memcpy(output_data + 1, room, ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);
    this->theFabricObject->uFabricObject()->transmitFunction(output_data);




    //session->groupObject()->transmitToTheme(data_val, this);

    char *data_buf = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    data_buf[0] = WEB_FABRIC_PROTOCOL_RESPOND_IS_PUT_SESSION_DATA;
    strcpy(data_buf + 1, "TBD");
    this->transmitFunction(data_buf);
}

void DFabricClass::processPutSessionDataResponse (char *data_val, SessionClass *session_object_val)
{
    char *data_buf = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
    data_buf[0] = WEB_FABRIC_PROTOCOL_RESPOND_IS_PUT_SESSION_DATA;
    strcpy(data_buf + 1, (char *) data_val);
    this->transmitFunction(data_buf);
}
