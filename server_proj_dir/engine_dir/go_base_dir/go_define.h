/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_define.h
*/

#pragma once

#define GO_EMPTY_STONE '0'
#define GO_BLACK_STONE '1'
#define GO_WHITE_STONE '2'
#define GO_MARK_DEAD_STONE_DIFF 4
#define THE_MARK_EMPTY_STONE_DIFF 6

#define GO_MARKED_DEAD_BLACK_STONE '5'
#define TGO_MARKED_DEAD_WHITE_STONE '6'

//#define THE_MARKED_DEAD_BLACK_STONE  = (this.THE_BLACK_STONE + this.THE_MARK_DEAD_STONE_DIFF);
//#define THE_MARKED_DEAD_WHITE_STONE  = (this.THE_WHITE_STONE + this.THE_MARK_DEAD_STONE_DIFF);
//#define THE_MARKED_EMPTY_BLACK_STONE = (this.THE_BLACK_STONE + this.THE_MARK_EMPTY_STONE_DIFF);
//#define THE_MARKED_EMPTY_WHITE_STONE = (this.THE_WHITE_STONE + this.THE_MARK_EMPTY_STONE_DIFF);


inline char getOppositeColor (char color_val)
{
    switch (color_val) {
        case GO_BLACK_STONE:
            return GO_WHITE_STONE;

        case GO_WHITE_STONE:
            return GO_BLACK_STONE;

        default:
            phwangAbend("getOppositeColor", "bad color");
            return GO_EMPTY_STONE;
    }
}
