/*
  Copyrights reserved
  Written by Paul Hwang
  File name: encode_class.cpp
*/

#include "../phwang.h"
#include "../malloc_dir/malloc_class.h"
#include "encode_class.h"

EncodeClass::EncodeClass (int debug_code_val)
{
    memset(this, 0, sizeof (*this));
    this->theDebugCode = debug_code_val;
}

EncodeClass::~EncodeClass(void)
{
}

void EncodeClass::encodeNumber (char *str_val, int number_val, int size_val)
{
    str_val[size_val] = 0;
    while (size_val > 0) {
        size_val--;
        str_val[size_val] = '0' + number_val % 10;
        number_val /= 10;
    }
}

void EncodeClass::encodeNumberNull (char *str_val, int number_val, int size_val)
{
    this->encodeNumber(str_val, number_val, size_val);
    str_val[size_val] = 0;
}

char *EncodeClass::encodeNumberMalloc (int number_val, int size_val)
{
    char *buf = (char *) phwangMalloc(size_val + 1, MallocClass::encodeNumberMalloc);
    this->encodeNumberNull(buf, number_val, size_val);
    return buf;
}

int EncodeClass::decodeNumber (char const *str_val, int size_val)
{
    int number = 0;
    int factor = 1;

    //printf("decodeNumber() input=%s\n", str_val);
    while (size_val > 0) {
        size_val--;
        number += (str_val[size_val] - '0') * factor;
        factor *= 10;
    }
    //printf("decodeNumber() output=%d\n", number);
    return number;
}

int EncodeClass::decodeNumberNull (char const *str_val)
{
    return this->decodeNumber(str_val, strlen(str_val));
}

int EncodeClass::getEncodeStringMallocSize (char const *str_val) {
    return strlen(str_val) + 7; /* 1 + 5 * length + 1 */
}

void EncodeClass::encodeString (char *output_buf_val, char const *input_str_val)
{

}

char *EncodeClass::encodeStringMalloc (char const *input_str_val) {
    int length_size;
    int length = strlen(input_str_val);
    char *buf = (char *) phwangMalloc(this->getEncodeStringMallocSize(input_str_val), MallocClass::ENCODE_STRING);

    char *data_ptr = buf;
    if (length < 10) {
        data_ptr[0] = '1';
        length_size = 1;
    }
    else if (length < 100) {
        data_ptr[0] = '2';
        length_size = 2;
    }
    else if (length < 1000) {
        data_ptr[0] = '3';
        length_size = 3;
    }
    else if (length < 10000) {
        data_ptr[0] = '4';
        length_size = 4;
    }
    else if (length < 100000) {
        data_ptr[0] = '5';
        length_size = 5;
    }
    data_ptr++;

    this->encodeNumber(data_ptr, length, length_size);
    data_ptr += length_size;
    strcpy(data_ptr, input_str_val);
    return buf;
}

char *EncodeClass::decodeString (char const *input_val, int *input_size_val)
{
    int length = 0;
    int head_size = 2;
    char *buf;

    switch (*input_val++) {
        case '5':
            length = length * 10 + *input_val - 48;
            input_val++;
            head_size++;
 
        case '4':
            length = length * 10 + *input_val - 48;
            input_val++;
            head_size++;
 
        case '3':
            length = length * 10 + *input_val - 48;
            input_val++;
            head_size++;
 
        case '2':
            length = length * 10 + *input_val - 48;
            input_val++;
            head_size++;

       case '1':
            length = length * 10 + *input_val - 48;
            input_val++;
            
            buf = (char *) phwangMalloc(length + 1, MallocClass::DECODE_STRING);
            memcpy(buf, input_val, length);
            buf[length] = 0;
            *input_size_val = length + head_size;
            break;

        default:
            break;
    }
    return buf;
}

void EncodeClass::encodeIdIndex (char *str_val, int id_val, int id_size_val, int index_val, int index_size_val)
{
    this->encodeNumber(str_val, id_val, id_size_val);
    this->encodeNumber(str_val + id_size_val, index_val, index_size_val);
}

void EncodeClass::decodeIdIndex (char const *str_val, int *id_ptr_val, int id_size_val, int *index_ptr_val, int index_size_val)
{
    *id_ptr_val = this->decodeNumber(str_val, id_size_val);
    *index_ptr_val = this->decodeNumber(str_val + id_size_val, index_size_val);
}

void EncodeClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void EncodeClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
