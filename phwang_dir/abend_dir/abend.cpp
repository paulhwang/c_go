/*
  Copyrights reserved
  Written by Paul Hwang
  File name: abend.c
*/

#include "../phwang.h"

int phwang_debug_on_off_switch = 1;

void phwangLogitS (char const *func_name_val, char const *str1_val)
{
    printf("%s() %s\n", func_name_val, str1_val);
}

void phwangLogitWS (char const *func_name_val, char const *who_val, char const *str1_val)
{
    printf("%s:%s() %s\n", func_name_val, who_val, str1_val);
}

void phwangLogitSS (char const *func_name_val, char const *str1_val, char const *str2_val)
{
    printf("%s() %s %s\n", func_name_val, str1_val, str2_val);
}

void phwangLogitWSS (char const *func_name_val, char const *who_val, char const *str1_val, char const *str2_val)
{
    printf("%s:%s() %s %s\n", func_name_val, who_val, str1_val, str2_val);
}

void phwangLogitSSS (char const *func_name_val, char const *str1_val, char const *str2_val, char const *str3_val)
{
    printf("%s() %s %s %s\n", func_name_val, str1_val, str2_val, str3_val);
}

void phwangLogitWSSS (char const *func_name_val, char const *who_val, char const *str1_val, char const *str2_val, char const *str3_val)
{
    printf("%s:%s() %s %s %s\n", func_name_val, who_val, str1_val, str2_val, str3_val);
}

void phwangLogitSI (char const *func_name_val, char const *str1_val, int int1_val)
{
    printf("%s() %s=%d\n", func_name_val, str1_val, int1_val);
}

void phwangLogitWSI (char const *func_name_val, char const *who_val, char const *str1_val, int int1_val)
{
    printf("%s:%s() %s=%d\n", func_name_val, who_val, str1_val, int1_val);
}

void phwangLogitSSI (char const *func_name_val, char const *str1_val, char const *str2_val, int int1_val)
{
    printf("%s() %s %s=%d\n", func_name_val, str1_val, str2_val, int1_val);
}

void phwangLogitWSSI (char const *func_name_val, char const *who_val, char const *str1_val, char const *str2_val, int int1_val)
{
    printf("%s:%s() %s %s=%d\n", func_name_val, who_val, str2_val, str1_val, int1_val);
}

void phwangLogitSISS (char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, char const *str3_val)
{
    printf("%s() %s=%d %s=%s\n", func_name_val, str1_val, int1_val, str2_val, str3_val);
}

void phwangLogitWSISS (char const *func_name_val, char const *who_val, char const *str1_val, int int1_val, char const *str2_val, char const *str3_val)
{
    printf("%s:%s() %s=%d %s=%s\n", func_name_val, who_val, str1_val, int1_val, str2_val, str3_val);
}

void phwangLogitSISI (char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    printf("%s() %s=%d %s=%d\n", func_name_val, str1_val, int1_val, str2_val, int2_val);
}

void phwangLogitWSISI (char const *func_name_val, char const *who_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    printf("%s:%s() %s=%d %s=%d\n", func_name_val, who_val, str1_val, int1_val, str2_val, int2_val);
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

void phwangDebugSS (int on_off_val, char const *func_name_val, char const *str1_val, char const *str2_val)
{
    if (phwang_debug_on_off_switch && on_off_val) {
        phwangLogitSS(func_name_val, str1_val, str2_val);
    }
};

void phwangDebugWSS (int on_off_val, char const *func_name_val, char const *who_val, char const *str1_val, char const *str2_val)
{
    if (phwang_debug_on_off_switch && on_off_val) {
        phwangLogitWSS(func_name_val, who_val, str1_val, str2_val);
    }
};

void phwangDebugSSS (int on_off_val, char const *func_name_val, char const *str1_val, char const *str2_val, char const *str3_val)
{
    if (phwang_debug_on_off_switch && on_off_val) {
        phwangLogitSSS(func_name_val, str1_val, str2_val, str3_val);
    }
};

void phwangDebugWSSS (int on_off_val, char const *func_name_val, char const *who_val, char const *str1_val, char const *str2_val, char const *str3_val)
{
    if (phwang_debug_on_off_switch && on_off_val) {
        phwangLogitWSSS(func_name_val, who_val, str1_val, str2_val, str3_val);
    }
};

void phwangDebugSI (int on_off_val, char const *func_name_val, char const *str1_val, int int1_val)
{
    if (phwang_debug_on_off_switch && on_off_val) {
        phwangLogitSI(func_name_val, str1_val, int1_val);
    }
}

void phwangDebugWSI (int on_off_val, char const *func_name_val, char const *who_val, char const *str1_val, int int1_val)
{
    if (phwang_debug_on_off_switch && on_off_val) {
        phwangLogitWSI(func_name_val, who_val, str1_val, int1_val);
    }
}

void phwangDebugSSI (int on_off_val, char const *func_name_val, char const *str1_val, char const *str2_val, int int1_val)
{
    if (phwang_debug_on_off_switch && on_off_val) {
        phwangLogitSSI(func_name_val, str1_val, str2_val, int1_val);
    }
}

void phwangDebugWSSI (int on_off_val, char const *func_name_val, char const *who_val, char const *str1_val, char const *str2_val, int int1_val)
{
    if (phwang_debug_on_off_switch && on_off_val) {
        phwangLogitWSSI(func_name_val, who_val, str1_val, str2_val, int1_val);
    }
}

void phwangDebugSISS (int on_off_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, char const *str3_val)
{
    if (phwang_debug_on_off_switch && on_off_val) {
        phwangLogitSISS(func_name_val, str1_val, int1_val, str2_val, str3_val);
    }
}

void phwangDebugWSISS (int on_off_val, char const *func_name_val, char const *who_val, char const *str1_val, int int1_val, char const *str2_val, char const *str3_val)
{
    if (phwang_debug_on_off_switch && on_off_val) {
        phwangLogitWSISS(func_name_val, who_val, str1_val, int1_val, str2_val, str3_val);
    }
}

void phwangDebugSISI (int on_off_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    if (phwang_debug_on_off_switch && on_off_val) {
        phwangLogitSISI(func_name_val, str1_val, int1_val, str2_val, int2_val);
    }
}

void phwangDebugWSISI (int on_off_val, char const *func_name_val, char const *who_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    if (phwang_debug_on_off_switch && on_off_val) {
        phwangLogitWSISI(func_name_val, who_val, str1_val, int1_val, str2_val, int2_val);
    }
}

void phwangAbendS (char const *func_name_val, char const *str1_val)
{
    printf("*****ABEND********************************************************************\n");
    printf("%s() %s\n", func_name_val, str1_val);
    printf("*****ABEND********************************************************************\n");
    int *junk = 0;
    *junk = 0;
}

void phwangAbendWS (char const *func_name_val, char const *who_val, char const *str1_val)
{
    printf("*****ABEND********************************************************************\n");
    printf("%s:%s() %s\n", func_name_val, who_val, str1_val);
    printf("*****ABEND********************************************************************\n");
    int *junk = 0;
    *junk = 0;
}

void phwangAbendSS (char const *func_name_val, char const *str1_val, char const *str2_val)
{
    printf("*****ABEND********************************************************************\n");
    printf("%s() %s %s\n", func_name_val, str1_val, str2_val);
    printf("*****ABEND********************************************************************\n");
    int *junk = 0;
    *junk = 0;
}

void phwangAbendWSS (char const *func_name_val, char const *who_val, char const *str1_val, char const *str2_val)
{
    printf("*****ABEND********************************************************************\n");
    printf("%s:%s() %s %s\n", func_name_val, who_val, str1_val, str2_val);
    printf("*****ABEND********************************************************************\n");
    int *junk = 0;
    *junk = 0;
}

void phwangAbendSI (char const *func_name_val, char const *str1_val, int int1_val)
{
    printf("*****ABEND********************************************************************\n");
    printf("%s() %s %d\n", func_name_val, str1_val, int1_val);
    printf("*****ABEND********************************************************************\n");
    int *junk = 0;
    *junk = 0;
}

void phwangAbendWSI (char const *func_name_val, char const *who_val, char const *str1_val, int int1_val)
{
    printf("*****ABEND********************************************************************\n");
    printf("%s:%s() %s %d\n", func_name_val, who_val, str1_val, int1_val);
    printf("*****ABEND********************************************************************\n");
    int *junk = 0;
    *junk = 0;
}
