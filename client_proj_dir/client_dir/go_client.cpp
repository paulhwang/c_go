/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_client.cpp
*/

#include <unistd.h>
#include "../../phwang_dir/phwang.h"
#include "../../include_dir/protocol_dir/link_mgr_protocol.h"
#include "../../include_dir/protocol_dir/base_mgr_protocol.h"

int test_base_mgr = 1;

void *link_mgr_tp_transfer_object;
char link_id_index[LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + 4];

#define GO_PROTOCOL_CODE_SIZE 7
void *base_mgr_tp_transfer_object;
char base_id_index[BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE + 4];
int move_index = 0;
char const *move_array[] = {
    "03021001",
    "02052002",
    "03041003",
    "03052004",
    "04051005",
    "04062006",
    "03031007",
};

void baseMgrPlayAMove (void)
{
    char *buf = (char *) malloc(BASE_MGR_DATA_BUFFER_SIZE + 4);
    buf[0] = BASE_MGR_PROTOCOL_COMMAND_IS_TRANSFER_DATA;
    buf[1] = BASE_MGR_PROTOCOL_GAME_NAME_IS_GO;
    memcpy(buf + 2, base_id_index, BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE);
    strcpy(buf + 2 + BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE, "Move   ");
    strcpy(buf + 2 + BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE + GO_PROTOCOL_CODE_SIZE, move_array[move_index++]);
    printf("=====%s\n", buf);
    phwangTpTransmit(base_mgr_tp_transfer_object, buf);
}

void baseMgrReceiveDataFromTransport (void* engine_object_val, void *data_val)
{
    printf("mainReceiveDataFromTransport() %s\n", (char *) data_val);
    char *data = (char *) data_val;

    if (*data == BASE_MGR_PROTOCOL_RESPOND_IS_MALLOC_BASE) {
        if (1) {
            char s[LOGIT_BUF_SIZE];
            sprintf(s, "base_id_index=%s", data + 1);
            phwangLogit("mainReceiveDataFromTransport", s);
        }
        data++;
        data++;
        memcpy(base_id_index, data, BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE);
        base_id_index[BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE] = 0;
        baseMgrPlayAMove();
    }
    else if (*data == BASE_MGR_PROTOCOL_RESPOND_IS_TRANSFER_DATA) {
        data++;
        if (*data = BASE_MGR_PROTOCOL_GAME_NAME_IS_GO) {
            data++;
            phwangPrintBoard((char *) data, 19);
            if (move_index < sizeof(move_array) / sizeof(*move_array)) {
                baseMgrPlayAMove();
            }
        }
    }
}

void baseMgrTest (void)
{
    base_mgr_tp_transfer_object = phwangTpConnect(0, BASE_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, baseMgrReceiveDataFromTransport, 0);
    if (base_mgr_tp_transfer_object) {
        char *buf = (char *) malloc(BASE_MGR_DATA_BUFFER_SIZE + 4);
        buf[0] = BASE_MGR_PROTOCOL_COMMAND_IS_MALLOC_BASE;
        buf[1] = BASE_MGR_PROTOCOL_GAME_NAME_IS_GO;
        buf[2] = 0;
        phwangTpTransmit(base_mgr_tp_transfer_object, buf);
    }
}

void linkMgrReceiveDataFromTransport (void* engine_object_val, void *data_val)
{
    printf("linkMgrReceiveDataFromTransport() %s\n", (char *) data_val);
    char *data = (char *) data_val;

    if (*data == LINK_MGR_PROTOCOL_RESPOND_IS_MALLOC_LINK) {
        if (1) {
            char s[LOGIT_BUF_SIZE];
            sprintf(s, "link_id_index=%s", data + 1);
            phwangLogit("linkMgrReceiveDataFromTransport", s);
        }
        data++;
        data++;
        memcpy(link_id_index, data, LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE);
        link_id_index[LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE] = 0;
        //baseMgrPlayAMove();
    }
}

void linkMgrTest (void)
{
    char const *name = "phwang";
    link_mgr_tp_transfer_object = phwangTpConnect(0, LINK_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, linkMgrReceiveDataFromTransport, 0);
    if (link_mgr_tp_transfer_object) {
        char *buf = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        buf[0] = LINK_MGR_PROTOCOL_COMMAND_IS_MALLOC_LINK;
        strcpy(buf + 1, name);
        buf[strlen(name) + 1] = 0;
        phwangTpTransmit(link_mgr_tp_transfer_object, buf);
    }
}

int main (int argc, char** argv) {
    baseMgrTest();
    sleep(1);
    linkMgrTest();
    sleep(1000);
}