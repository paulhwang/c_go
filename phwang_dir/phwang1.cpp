/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang1.cpp
*/

#include "phwang.h"

int phwang_debug_on_off_switch = 1;

void phwangLogitS (char const *func_name_val, char const *str1_val)
{
    printf("%s() %s\n", func_name_val, str1_val);
}

void phwangLogitWS (char const *func_name_val, char const *who_val, char const *str1_val)
{
    printf("%s:%s() %s\n", func_name_val, who_val, str1_val);
}

void phwangLogit (char const *func_name_val, char const *str1_val)
{
    printf("%s() %s\n", func_name_val, str1_val);
}

void phwangLogit2 (char const *func_name_val, char const *str1_val, char const *str2_val)
{
    printf("%s() %s %s\n", func_name_val, str1_val, str2_val);
}

void phwangLogitInt (char const *func_name_val, char const *str1_val, int int1_val)
{
    printf("%s() %s=%d\n", func_name_val, str1_val, int1_val);
}

void phwangLogitInt2 (char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    printf("%s() %s=%d %s=%d\n", func_name_val, str1_val, int1_val, str2_val, int2_val);
}

void phwangDebugS (int on_off_val, char const *func_name_val, char const *str1_val)
{
    if (phwang_debug_on_off_switch && on_off_val) {
        phwangLogitS(func_name_val, str1_val);
    }
};

void phwangDebugWS (int on_off_val, char const *func_name_val, char const *who_val, char const *str1_val)
{
    if (phwang_debug_on_off_switch && on_off_val) {
        phwangLogitWS(func_name_val, who_val, str1_val);
    }
};

void phwangDebug (int on_off_val, char const *func_name_val, char const *str1_val)
{
    if (phwang_debug_on_off_switch && on_off_val) {
        phwangLogit(func_name_val, str1_val);
    }
};

void phwangDebug2 (int on_off_val, char const *func_name_val, char const *str1_val, char const *str2_val)
{
    if (phwang_debug_on_off_switch && on_off_val) {
        phwangLogit2(func_name_val, str1_val, str2_val);
    }
};

void phwangDebugInt (int on_off_val, char const *func_name_val, char const *str1_val, int int1_val)
{
    if (phwang_debug_on_off_switch && on_off_val) {
        phwangLogitInt(func_name_val, str1_val, int1_val);
    }
}

void phwangDebugInt2 (int on_off_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    if (phwang_debug_on_off_switch && on_off_val) {
        phwangLogitInt2(func_name_val, str1_val, int1_val, str2_val, int2_val);
    }
}

void phwangAbend (char const *func_name_val, char const *str1_val)
{
    printf("*****ABEND******************************************\n");
    printf("%s() %s\n", func_name_val, str1_val);
    printf("*****ABEND******************************************\n");
    int *junk = 0;
    *junk = 0;
}

void phwangAbendS (char const *func_name_val, char const *str1_val)
{
    printf("*****ABEND******************************************\n");
    printf("%s() %s\n", func_name_val, str1_val);
    printf("*****ABEND******************************************\n");
    int *junk = 0;
    *junk = 0;
}

void phwangAbendWS (char const *func_name_val, char const who_val, char const *str1_val)
{
    printf("*****ABEND******************************************\n");
    printf("%s:%s() %s\n", func_name_val, who_val, str1_val);
    printf("*****ABEND******************************************\n");
    int *junk = 0;
    *junk = 0;
}

void phwangAbend2 (char const *func_name_val, char const *str1_val, char const *str2_val)
{
    printf("*****ABEND******************************************\n");
    printf("%s(), %s %s\n", func_name_val, str1_val, str2_val);
    printf("*****ABEND******************************************\n");
    int *junk = 0;
    *junk = 0;
}

void phwangComposeFuncName(char *buf_val, char const *object_name_val, char const *func_name_val)
{
    sprintf(buf_val, "%s::%s", object_name_val, func_name_val);
}

void phwangComposeFuncNameExtra(char *buf_val, char const *object_name_val, char const *func_name_val, char const *extra_info_val)
{
    sprintf(buf_val, "%s::%s[%s]", object_name_val, func_name_val, extra_info_val);
}

/* atomic */
void phwangIncrementAtomicCount (std::atomic<int> *count_val, char const *who_val, int max_count_val)
{
    (*count_val)++;
    if (*count_val > max_count_val) {
        printf("phwangIncrementAtomicCount(), count=%d\n", (*count_val).load());
        phwangAbend("phwangIncrementAtomicCount", who_val);
    }
}

void phwangDecrementAtomicCount (std::atomic<int> *count_val, char const *who_val)
{
    (*count_val)--;
    if (*count_val < 0) {
        printf("phwangDecrementAtomicCount(), count=%d\n", (*count_val).load());
        phwangAbend("phwangDecrementAtomicCount", who_val);
    }
}
