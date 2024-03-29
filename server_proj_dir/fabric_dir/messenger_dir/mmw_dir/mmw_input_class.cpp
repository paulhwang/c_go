/*
  Copyrights reserved
  Written by Paul Hwang
  File name: mmw_input_class.cpp
*/

#include <errno.h>
#include "../../../../phwang_dir/phwang.h"
#include "mmw_input_class.h"
#include "mmw_frame_class.h"

MmwInputClass::MmwInputClass (MmwClass *mmw_object_val)
{
    phwangDebugS(true, "MmwInputClass::MmwInputClass", "start");

    memset(this, 0, sizeof(*this));
    this->theMmwObject = mmw_object_val;
}

MmwInputClass::~MmwInputClass (void)
{
    phwangDebugS(true, "MmwInputClass::~MmwInputClass", "exit");
}

MmwFrameClass *MmwInputClass::readFrame (int *eof_val) {
    MmwFrameClass *frame_object = new MmwFrameClass();

    if (this->thePrevFrameNum) {
        frame_object->addLineArrayElement(this->thePrevFrameNum);
    }

    while (1) {
        char line_buf[1024];

        this->readNonemptyLine(line_buf, eof_val);

        if (*eof_val) {
            this->thePrevFrameNum = 0;
            //delete frame_object;
            return frame_object;
        }
        else {
            //printf("=%s\n", line_buf);
        }

        char *line_data = (char *) malloc(strlen(line_buf) + 1);
        strcpy(line_data, line_buf);

        if (memcmp(line_buf, "frameNum", 7) == 0) {
            this->thePrevFrameNum = line_data;
            return frame_object;
        }

        frame_object->addLineArrayElement(line_data);
    }
}


void MmwInputClass::readNonemptyLine (char *line_buf_val, int *eof_val) {
    while (1) {
        this->readLine(line_buf_val, eof_val);

        if (*eof_val) {
            return;
        }

        if (line_buf_val[0] != 0) {
            return;
        }
    }
}


void MmwInputClass::readLine (char *line_buf_val, int *eof_val) {
    int index = 0;

    while (1) {
        int c = getc(this->theFpInput);

        if (c == EOF) {
            *eof_val = 1;
            return;
        }

        if (c == 13) {
            continue;
        }

        if (c == 10) {
            line_buf_val[index] = 0;
            break;
        }

        line_buf_val[index++] = c;
     }

     *eof_val = 0;
     return;
}

int MmwInputClass::openFile (char const *filename_val, char const *mode_val)
{
    int errno;

    this->theFpInput = fopen(filename_val, mode_val);
    if (this->theFpInput == 0) {
        printf("***errno=%d\n", errno);
        phwangLogitS("MmwInputClass::openFile", "cannot open file");
        return -1;
    }

    return 0;
}
