/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_frame_class.cpp
*/

#include "../../../../phwang_dir/phwang.h"
#include "mmw_frame_class.h"

MmwFrameClass::MmwFrameClass (void)
{
    phwangDebugS(false, "MmwFrameClass::MmwFrameClass", "start");

    memset(this, 0, sizeof(*this));
    this->theMaxArraySize = MMW_FRAME_CLASS_MAX_ARRAY_SIZE;
    //this->theFrameNumberIndex = 0;
    //this->thePointNumberIndex = 0;
    //this->theArraySize = 0;
    this->theLineArray = (char **) malloc(sizeof(char *) * this->theMaxArraySize);
    memset(this->theLineArray, 0, sizeof(char *) * this->theMaxArraySize);
}

MmwFrameClass::~MmwFrameClass (void)
{
    phwangDebugS(false, "MmwFrameClass::~MmwFrameClass", "start");
    for (int i = 0; i < this->theArraySize; i++) {
        if (this->theLineArray[i]) {
            free(this->theLineArray[i]);
            this->theLineArray[i] = 0;
        }
    }
    free(this->theLineArray);
}

void MmwFrameClass::parseFrame (void)
{
    if (memcmp(this->theLineArray[0], "frameNum: ", 10) == 0) {
        this->theFrameNumberIndex = 10;
        this->theFrameNumber = phwangDecodeNumber(this->frameNumberStr(), strlen(this->frameNumberStr()));
        //printf("%i\n", this->theFrameNumber);
        this->parseNormalFrame();
    }
    else {
        this->parseHeaderFrame();
    }
}


void MmwFrameClass::parseHeaderFrame (void)
{
    this->theFrameType = MMW_FRAME_CLASS_TYPE_HEADER;
}

void MmwFrameClass::parseNormalFrame (void)
{
    this->theFrameType = MMW_FRAME_CLASS_TYPE_NORMAL;
    phwangDebugS(false, "MmwFrameClass::parseNormalFrame", this->frameNumberStr());

    if (memcmp(this->pointeNumberStr(), " PointNumber: ", 14) != 0) {
        phwangAbendS("MmwFrameClass::parseNormalFrame", "ointeNumber not match");
        return;
    }

    this->thePointNumberIndex = 14;
    this->thePointNumber = phwangDecodeNumber(this->pointeNumberStr(), strlen(this->pointeNumberStr()));
    //printf("thePointNumber=%i\n", this->thePointNumber);
    phwangDebugS(false, "MmwFrameClass::parseNormalFrame", this->pointeNumberStr());

    //printf("targetStr=%s\n", this->targetStrArray()[0]);
    //printf("idleMappingStr=%s\n", this->idleMappingStr());

    if (memcmp(this->idleMappingStr(), "[]", 2) == 0) {
        this->parseIdleFrame();
    }
    else {
        this->parseActiveFrame();
    }
}

void MmwFrameClass::parseIdleFrame (void)
{
    phwangDebugS(true, "MmwFrameClass::parseIdleFrame", this->frameNumberStr());
    //printf("idleMappingStr=%s\n", this->idleMappingStrArray()[0]);
}

void MmwFrameClass::parseActiveFrame (void)
{
    this->theFrameType = MMW_FRAME_CLASS_TYPE_ACTIVE;
    phwangDebugS(true, "MmwFrameClass::parseActiveFram", this->frameNumberStr());
    //printf("activeMappingStr=%s\n", this->activeMappingStr());
    for (int i = 0; i < 16; i++) {
        //printf("target=%s\n", this->targetStrArray()[i]);
        //printf("target=%s\n", this->targetStrArray()[i] + 2);
    }
}

void shift3(char *to_val, char *from_val) {
    int before_dot = 1;
    int count_dot = 0;

    for (int i = 0, j = 1; i < strlen(from_val); i++) {
        if (from_val[i] == ' ') {
            continue;
        }
        if (before_dot) {
            if (from_val[i] != '.') {
                //printf("i=%d j=%d from=%s\n", i, j, from_val);
                to_val[j++] = from_val[i];
            } else {
                count_dot = 0;
                before_dot = 0;
            }
        }
        else {
            to_val[j++] = from_val[i];
            count_dot++;
        }

        if (count_dot == 3) {
            to_val[j++] = ']';
            to_val[j] = 0;
            to_val[0] = strlen(&to_val[1]) + 48;
            break;
        }
    }

    //printf("dot = %d\n", count_dot);
    //printf("*********%s\n", from_val);
    //printf("*********%s\n", to_val);
}

char *MmwFrameClass::generateData (void)
{
    int buf_len = 1;
    for (int i = 1; i < 4; i++) {
        buf_len += strlen(this->targetStrArray()[i]);
    }

    char *s = (char *) malloc(buf_len);
    s[0] = 0;
    for (int i = 1; i < 4; i++) {
        char buf[32];
        shift3(buf, this->targetStrArray()[i]);
        strcat(s, buf);
    }
    
    return s;
}
