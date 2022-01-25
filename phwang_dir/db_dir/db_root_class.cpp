/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_root.cpp
*/

#include "../phwang.h"
#include "db_root_class.h"

DbRootClass::DbRootClass (void)
{
    this->createDbs();
}

DbRootClass::~DbRootClass (void)
{
}

void DbRootClass::createDbs (void)
{
    this->createLoginDb();
}

void DbRootClass::createLoginDb (void)
{
    //int lib_ver = PQlibVersion();

    printf("********************************Version of libpq: \n");
    //printf("Version of libpq: %d\n", lib_ver);

}


