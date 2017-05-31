/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_client.cpp
*/

#include <unistd.h>
#include "./utils_dir/transport_class.h"
#include "./utils_dir/logit.h"

#define BASE_ID_SIZE 4
#define MOVE_DATA_BUF_SIZE 32

TransportClass *transport_object;
char base_id[BASE_ID_SIZE + 4];

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

        char move_data_buf[MOVE_DATA_BUF_SIZE];
        move_data_buf[0] = 'd';
        memcpy(move_data_buf + 1, base_id, BASE_ID_SIZE);
        strcpy(move_data_buf + 1 + BASE_ID_SIZE, "Move   03021001");
        printf("=====%s\n", move_data_buf);
        transport_object->exportTransmitData(move_data_buf);
        //transport_object->exportTransmitData((void *)  "dMove   03021001");

    }
    else if (*data == 'd') {
        PRINT_BOARD((char *) data + 1, 19);
    }
}

int main (int argc, char** argv) {
    transport_object = new TransportClass(null);
    transport_object->clientThreadFunction(0, TRANSPORT_PORT_NUMBER_FOR_ME);
    transport_object->exportTransmitData((void *)  "m");
    sleep(1000);
}