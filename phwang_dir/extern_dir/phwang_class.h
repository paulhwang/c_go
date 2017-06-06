/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang_class.h
*/

#pragma once

class PhwangClass {
 public:
    PhwangClass(void){}
    ~PhwangClass(void){}

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
    void printBoard(char const* data_val, int board_size_val);

    void encodeNumber(char *str_val, int number_val, int size_val);
    int decodeNumber(char *str_val, int size_val);
    void encodeIdIndex(char *str_val, int id_val, int id_size_val, int index_val, int index_size_val);
    void decodeIdIndex(char *str_val, int *id_ptr_val, int id_size_val, int *index_ptr_val, int index_size_val);

    void *mallocQueue(int max_size_val);
    void freeQueue(void *queue_val);
    void enqueue(void *queue_val, void *data_val);
    void *dequeue(void *queue_val);

    void *mallocTpServer (
            void *caller_object_val,
            unsigned short port_val,
            void (*accept_callback_func_val)(void *, void *),
            void *accept_callback_parameter_val,
            void (*receive_callback_func_val)(void *, void *),
            void *receive_callback_parameter_val);
    void *tpConnect(unsigned long ip_addr_val, unsigned short port_val, void (*receive_callback_val)(void *, void *), void *receive_object_val);
    void freeTpTransfer(void *tp_transfer_object_val);
    void tpTransmit(void *tp_transfer_object_val, char *data_val);
};
