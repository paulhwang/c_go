/*
  Copyrights reserved
  Written by Paul Hwang
  File name: encode_class.h
*/

#pragma once

class EncodeClass
{
    char const *objectName(void) {return "EncodeClass";}

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    EncodeClass(void);
    ~EncodeClass(void);

    void encodeNumber(char *str_val, int number_val, int size_val);
    int decodeNumber(char const *str_val, int size_val);
    void encodeIdIndex(char *str_val, int id_val, int id_size_val, int index_val, int index_size_val);
    void decodeIdIndex(char const *str_val, int *id_ptr_val, int id_size_val, int *index_ptr_val, int index_size_val);
    char *encodeString (char const *input_str_val);
    char *decodeString (char const *input_val, int *input_size_val);
};
