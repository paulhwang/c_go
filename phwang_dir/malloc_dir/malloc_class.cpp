/*
  Copyrights reserved
  Written by Paul Hwang
  File name: malloc_class.cpp
*/

#include "../phwang.h"
#include "malloc_class.h"

MallocClass::MallocClass (int debug_code_val)
{
    memset(this, 0, sizeof (*this));
    this->theDebugCode = debug_code_val;
}

MallocClass::~MallocClass(void)
{
}

//PHWANG_MALLOC_CLASS
#define PHWNAG_CLASS_MALLOC_MARKER "phwang"
#define PHWNAG_CLASS_MALLOC_MARKER_SIZE 6
#define PHWNAG_CLASS_MALLOC_LENGTH_SIZE 5
#define PHWNAG_CLASS_MALLOC_WHO_SIZE 4
#define PHWNAG_CLASS_MALLOC_WHO_TOTAL_SIZE (PHWNAG_CLASS_MALLOC_WHO_SIZE + 1)
#define PHWNAG_CLASS_MALLOC_HEADER_SIZE (PHWNAG_CLASS_MALLOC_MARKER_SIZE + PHWNAG_CLASS_MALLOC_LENGTH_SIZE + PHWNAG_CLASS_MALLOC_WHO_TOTAL_SIZE)
#define PHWNAG_CLASS_MALLOC_TAILER_SIZE PHWNAG_CLASS_MALLOC_MARKER_SIZE
#define PHWNAG_CLASS_MALLOC_EXTRA_BUFFER_SIZE (PHWNAG_CLASS_MALLOC_HEADER_SIZE + PHWNAG_CLASS_MALLOC_TAILER_SIZE + 8)

void *MallocClass::phwangMalloc (int size_val, int who_val)
{
    this->theUserTable[who_val]++;
    printf("***Malloc %d %d %d %d %d %d %d\n", this->theUserTable[0], this->theUserTable[1], this->theUserTable[2],
               this->theUserTable[3], this->theUserTable[4], this->theUserTable[5], this->theUserTable[6]);

    char who_str[PHWNAG_CLASS_MALLOC_WHO_TOTAL_SIZE];
    phwangEncodeNumber(who_str, who_val, PHWNAG_CLASS_MALLOC_WHO_SIZE);
    who_str[PHWNAG_CLASS_MALLOC_WHO_SIZE] = 0;

    char *buf = (char *) malloc(size_val + PHWNAG_CLASS_MALLOC_EXTRA_BUFFER_SIZE);
    memcpy(buf, PHWNAG_CLASS_MALLOC_MARKER, PHWNAG_CLASS_MALLOC_MARKER_SIZE);
    phwangEncodeNumber(buf + PHWNAG_CLASS_MALLOC_MARKER_SIZE, size_val, PHWNAG_CLASS_MALLOC_LENGTH_SIZE);
    strcpy(buf + PHWNAG_CLASS_MALLOC_MARKER_SIZE + PHWNAG_CLASS_MALLOC_LENGTH_SIZE, who_str);
    memcpy(buf + PHWNAG_CLASS_MALLOC_HEADER_SIZE + size_val, PHWNAG_CLASS_MALLOC_MARKER, PHWNAG_CLASS_MALLOC_MARKER_SIZE);
    return buf + PHWNAG_CLASS_MALLOC_HEADER_SIZE;
}

void MallocClass::phwangFree (void *adjusted_malloc_val)
{
    if (!adjusted_malloc_val) {
        phwangAbend("phwangFree", "null data");
        return;
    }
    char *real_malloc_data = ((char *) adjusted_malloc_val) - PHWNAG_CLASS_MALLOC_HEADER_SIZE;
    char *length_str = real_malloc_data + PHWNAG_CLASS_MALLOC_MARKER_SIZE;
    char *user_code_str = length_str + PHWNAG_CLASS_MALLOC_LENGTH_SIZE;
    this->debug(true, "phwangFree", real_malloc_data);

    if (memcmp(real_malloc_data, PHWNAG_CLASS_MALLOC_MARKER, PHWNAG_CLASS_MALLOC_MARKER_SIZE)) {
        phwangAbend("phwangFree Head", real_malloc_data);
        return;
    }
    int length = phwangDecodeNumber(length_str, PHWNAG_CLASS_MALLOC_LENGTH_SIZE);
    int user_code = phwangDecodeNumber(user_code_str, PHWNAG_CLASS_MALLOC_WHO_SIZE);
    printf("length=%d user=%d\n", length, user_code);

    if (memcmp((char *) adjusted_malloc_val + length, PHWNAG_CLASS_MALLOC_MARKER, PHWNAG_CLASS_MALLOC_MARKER_SIZE)) {
        phwangAbend("phwangFree Tail", real_malloc_data);
        return;
    }

    free(real_malloc_data);
}

void MallocClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void MallocClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
