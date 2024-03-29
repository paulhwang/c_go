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

#define PHWNAG_MALLOC_CLASS_MARKER      "phwang"
#define PHWNAG_MALLOC_CLASS_MARKER_FREE "-free-"
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
        phwangAbendS("MallocClass::phwangFree", "null data");
        return;
    }

    char *real_malloc_data = ((char *) input_val) - PHWNAG_MALLOC_CLASS_HEADER_SIZE;
    char *length_str = real_malloc_data + PHWNAG_MALLOC_CLASS_MARKER_SIZE;
    char *who_str = length_str + PHWNAG_MALLOC_CLASS_LENGTH_SIZE;
    phwangDebugS(false, "MallocClass::phwangFree", real_malloc_data);

    if (memcmp(real_malloc_data, PHWNAG_MALLOC_CLASS_MARKER, PHWNAG_MALLOC_CLASS_MARKER_SIZE)) {
        if (!memcmp(real_malloc_data, PHWNAG_MALLOC_CLASS_MARKER_FREE, PHWNAG_MALLOC_CLASS_MARKER_SIZE)) {
            printf("phwangFree: data=%s\n", real_malloc_data);
            phwangAbendS("MallocClass::phwangFree", "free twice");
            return;
        }
        else {
            printf("phwangFree: data=%s\n", real_malloc_data);
            phwangAbendS("MallocClass::phwangFree", "header");
            return;
        }
    }

    int length = phwangDecodeNumber(length_str, PHWNAG_MALLOC_CLASS_LENGTH_SIZE);
    int who_val = phwangDecodeNumber(who_str, PHWNAG_MALLOC_CLASS_WHO_SIZE);

    phwangDebugSISI(false, "MallocClass::phwangFree", "length=", length, "user=", who_val);

    if (memcmp((char *) input_val + length, PHWNAG_MALLOC_CLASS_MARKER, PHWNAG_MALLOC_CLASS_MARKER_SIZE)) {
        printf("MallocClass::phwangFree: data=%s\n", real_malloc_data);
        phwangAbendS("MallocClass::phwangFree", "tailer");
        return;
    }

    this->theUserTable[who_val]--;
    memcpy(real_malloc_data, PHWNAG_MALLOC_CLASS_MARKER_FREE, PHWNAG_MALLOC_CLASS_MARKER_SIZE);
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
            case MallocClass::receiveThreadFunction:
                count -= phwangReceiveThreadCount();
                break;

            case MallocClass::GroupClass:
                count -= 3; // 3 per group
                break;

            default:
                break;
        }

        if (count > 2) {
            phwangDebugSISI(true, "MallocClass::checkWhoTable", "who=", i, " count=", count);
        }
    }
}

char *MallocClass::mallocConstStrBuf (char const * str_val)
{
    char *buf = (char *) phwangMalloc(strlen(str_val) + 1, MallocClass::mallocConstStrBuf_);
    strcpy(buf, str_val);
    return buf;
}
