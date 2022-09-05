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
#define PHWNAG_MALLOC_CLASS_MARKER "phwang"
#define PHWNAG_MALLOC_CLASS_MARKER_SIZE 6
#define PHWNAG_MALLOC_CLASS_LENGTH_SIZE 5
#define PHWNAG_MALLOC_CLASS_WHO_SIZE 4
#define PHWNAG_MALLOC_CLASS_WHO_TOTAL_SIZE (PHWNAG_MALLOC_CLASS_WHO_SIZE + 1)
#define PHWNAG_MALLOC_CLASS_HEADER_SIZE (PHWNAG_MALLOC_CLASS_MARKER_SIZE + PHWNAG_MALLOC_CLASS_LENGTH_SIZE + PHWNAG_MALLOC_CLASS_WHO_TOTAL_SIZE)
#define PHWNAG_MALLOC_CLASS_TAILER_SIZE PHWNAG_MALLOC_CLASS_MARKER_SIZE
#define PHWNAG_MALLOC_CLASS_EXTRA_BUFFER_SIZE (PHWNAG_MALLOC_CLASS_HEADER_SIZE + PHWNAG_MALLOC_CLASS_TAILER_SIZE + 8)

void *MallocClass::phwangMalloc (int size_val, int who_val)
{
    if (!this->theDebugCode) {
        return malloc(size_val);
    }

    this->theUserTable[who_val]++;

    char who_str[PHWNAG_MALLOC_CLASS_WHO_TOTAL_SIZE];
    phwangEncodeNumber(who_str, who_val, PHWNAG_MALLOC_CLASS_WHO_SIZE);
    who_str[PHWNAG_MALLOC_CLASS_WHO_SIZE] = 0;

    char *buf = (char *) malloc(size_val + PHWNAG_MALLOC_CLASS_EXTRA_BUFFER_SIZE);
    memcpy(buf, PHWNAG_MALLOC_CLASS_MARKER, PHWNAG_MALLOC_CLASS_MARKER_SIZE);
    phwangEncodeNumber(buf + PHWNAG_MALLOC_CLASS_MARKER_SIZE, size_val, PHWNAG_MALLOC_CLASS_LENGTH_SIZE);
    memcpy(buf + PHWNAG_MALLOC_CLASS_MARKER_SIZE + PHWNAG_MALLOC_CLASS_LENGTH_SIZE, who_str, PHWNAG_MALLOC_CLASS_WHO_TOTAL_SIZE);
    memcpy(buf + PHWNAG_MALLOC_CLASS_HEADER_SIZE + size_val, PHWNAG_MALLOC_CLASS_MARKER, PHWNAG_MALLOC_CLASS_MARKER_SIZE);
    return buf + PHWNAG_MALLOC_CLASS_HEADER_SIZE;
}

void MallocClass::phwangFree (void *input_val)
{
    if (!this->theDebugCode) {
        free(input_val);
        return;
    }

    if (!input_val) {
        phwangAbend("phwangFree", "null data");
        return;
    }

    char *real_malloc_data = ((char *) input_val) - PHWNAG_MALLOC_CLASS_HEADER_SIZE;
    char *length_str = real_malloc_data + PHWNAG_MALLOC_CLASS_MARKER_SIZE;
    char *who_str = length_str + PHWNAG_MALLOC_CLASS_LENGTH_SIZE;
    this->debug(false, "phwangFree", real_malloc_data);

    if (memcmp(real_malloc_data, PHWNAG_MALLOC_CLASS_MARKER, PHWNAG_MALLOC_CLASS_MARKER_SIZE)) {
        printf("phwangFree: data=%s\n", real_malloc_data);
        phwangAbend("phwangFree", "header");
        return;
    }

    int length = phwangDecodeNumber(length_str, PHWNAG_MALLOC_CLASS_LENGTH_SIZE);
    int who_val = phwangDecodeNumber(who_str, PHWNAG_MALLOC_CLASS_WHO_SIZE);

    if (1) {
        char buf[64];
        sprintf(buf, "length=%d user=%d\n", length, who_val);
        this->debug(false, "phwangFree", buf);
    }

    if (memcmp((char *) input_val + length, PHWNAG_MALLOC_CLASS_MARKER, PHWNAG_MALLOC_CLASS_MARKER_SIZE)) {
        printf("phwangFree: data=%s\n", real_malloc_data);
        phwangAbend("phwangFree", "tailer");
        return;
    }

    this->theUserTable[who_val]--;
    free(real_malloc_data);

    this->checkWhoTable();
}

void MallocClass::checkWhoTable (void)
{
    if (0) {
        printf("***checkWhoTable %d %d %d %d %d %d %d %d %d %d %d\n", this->theUserTable[0], this->theUserTable[1], this->theUserTable[2],
               this->theUserTable[3], this->theUserTable[4], this->theUserTable[5], this->theUserTable[6],
               this->theUserTable[7], this->theUserTable[8], this->theUserTable[9], this->theUserTable[10]);
    }

    for (int i = 0; i < MAX_INDEX; i++) {
        int count = this->theUserTable[i];
        switch (i) {
            case 0:
                count -= phwangReceiveThreadCount();
                break;
            default:
                break;
        }

        if (count > 1) {
            char buf[16];
            sprintf(buf, "%d: %d", i, count);
            this->debug(true, "checkWhoTable", buf);
        }
    }
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
