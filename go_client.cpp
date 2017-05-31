/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_client.cpp
*/

#include <unistd.h>
#include "./utils_dir/transport_class.h"
#include "./utils_dir/logit.h"

#define BASE_ID_SIZE 4
#define GO_PROTOCOL_CODE_SIZE 7

#define MOVE_DATA_BUF_SIZE 32

TransportClass *transport_object;
char base_id[BASE_ID_SIZE + 4];
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
    char move_data_buf[MOVE_DATA_BUF_SIZE];
    move_data_buf[0] = 'd';
    memcpy(move_data_buf + 1, base_id, BASE_ID_SIZE);
    strcpy(move_data_buf + 1 + BASE_ID_SIZE, "Move   ");
    strcpy(move_data_buf + 1 + BASE_ID_SIZE + GO_PROTOCOL_CODE_SIZE, move_array[move_index++]);
    printf("=====%s\n", move_data_buf);
    transport_object->exportTransmitData(move_data_buf);
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
        memcpy(base_id, data + 1, BASE_ID_SIZE);
        base_id[BASE_ID_SIZE] = 0;
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
    transport_object = new TransportClass(null);
    transport_object->clientThreadFunction(0, TRANSPORT_PORT_NUMBER_FOR_ME);
    transport_object->exportTransmitData((void *)  "m");
    sleep(1000);
}