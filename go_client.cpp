/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_client.cpp
*/

#include <unistd.h>
#include <malloc.h>
#include "root_dir/tp_dir/tp_class.h"
#include "root_dir/tp_dir/tp_transfer_class.h"
#include "root_dir/base_mgr_dir/base_mgr_protocol.h"
#include "utils_dir/logit.h"

#define GO_PROTOCOL_CODE_SIZE 7

TpTransferClass *tp_transfer_object;
char base_id[BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE + 4];
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

void play_a_move (void)
{
    char *buf = (char *) malloc(BASE_MGR_DATA_BUFFER_SIZE + 4);
    buf[0] = BASE_MGR_PROTOCOL_COMMAND_DATA;
    memcpy(buf + 1, base_id, BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE);
    strcpy(buf + 1 + BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE, "Move   ");
    strcpy(buf + 1 + BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE + GO_PROTOCOL_CODE_SIZE, move_array[move_index++]);
    printf("=====%s\n", buf);
    tp_transfer_object->exportTransmitData(buf);
}

void mainReceiveDataFromTransport (void* engine_object_val, void *data_val) {
    printf("mainReceiveDataFromTransport() %s\n", (char *) data_val);
    char *data = (char *) data_val;

    if (*data == 'm') {
        if (1) {
            char s[LOGIT_BUF_SIZE];
            sprintf(s, "base_id=%s", data + 1);
            LOGIT("mainReceiveDataFromTransport", s);
        }
        memcpy(base_id, data + 1, BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE);
        base_id[BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE] = 0;
        play_a_move();
    }
    else if (*data == 'd') {
        PRINT_BOARD((char *) data + 1, 19);
        if (move_index < sizeof(move_array) / sizeof(*move_array)) {
            play_a_move();
        }
    }
}

int main (int argc, char** argv) {
    TpClass *transport_object = new TpClass(null);
    tp_transfer_object = transport_object->clientThreadFunction(0, TRANSPORT_PORT_NUMBER_FOR_BASE_MGR);
    if (tp_transfer_object) {
        char *buf = (char *) malloc(BASE_MGR_DATA_BUFFER_SIZE + 4);
        buf[0] = BASE_MGR_PROTOCOL_COMMAND_MALLOC_BASE;
        buf[1] = BASE_MGR_PROTOCOL_GAME_NAME_IS_GO;
        buf[2] = 0;
        tp_transfer_object->exportTransmitData((void *) buf);
    }
    sleep(1000);
}