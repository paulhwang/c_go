/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang_base.cpp
*/

#include <stdio.h>
#include "../../phwang_dir/extern_dir/phwang_class.h"

PhwangClass *thePhwangObject;
int phwangObjectStarted = 0;

void initPhwangObject(void)
{
	if (phwangObjectStarted) {
		return;
	}
	phwangObjectStarted++;
	thePhwangObject = new PhwangClass();
}
