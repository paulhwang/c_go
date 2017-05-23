/*
  Copyrights reserved
  Written by Paul Hwang
  File name: root_class.cpp
*/

#include <stdio.h>
#include "go_base_dir/go_base_class.h"
#include "root_class.h"

RootClass::RootClass (void)
{
  new GoBaseClass(this);
  printf("hello\n");
}
