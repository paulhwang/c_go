/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "array_mgr_class.h"

ArrayMgrClass::ArrayMgrClass(
    int debug_on_val,
    char const *who_val,
    char array_type_val,
    int max_array_size_val)
{
    memset(this, 0, sizeof(ArrayMgrClass));
    this->debugOn_ = true && debug_on_val;
    this->theWho = who_val;
    this->theArrayType = array_type_val;
    this->theMaxArraySize = max_array_size_val;
    this->theArraySize = 0;

    this->allocArrayTable();
    phwangDebugWS(false, "ArrayMgrClass::ArrayMgrClass", this->theWho, "init");
}

ArrayMgrClass::~ArrayMgrClass (void)
{
}

void ArrayMgrClass::allocArrayTable (void)
{
    void *ptr;
    int i;
    char c;
    int size;

    switch (this->theArrayType) {
        case 'o': // object
        case 's': // string
            size = sizeof(ptr);
            break;

        case 'i': // integer
            size = sizeof(i);
            break;

        case 'c': // char
            size = sizeof(c);
            break;

        default:
            phwangAbendWS("ArrayMgrClass::allocArrayTable", this->theWho, "bad type");
            size = 16;
            break;
    }

    size *= this->theMaxArraySize;
    this->thePointerArrayTable = (void **) malloc(size);
}

void *ArrayMgrClass::getArrayTable (int *array_size_ptr)
{
    *array_size_ptr = this->theArraySize;

    switch (this->theArrayType) {
        case 'o': 
        case 's': 
            return this->thePointerArrayTable;

        case 'i':
        case 'c':
        default:
            phwangAbendWS("ArrayMgrClass::getArrayTable", this->theWho, "bad type");
            return 0;
    }
}

void ArrayMgrClass::insertElement (void *element_val)
{
    this->insertPointerElement(element_val);
}

void ArrayMgrClass::insertPointerElement (void *element_val)
{
    void *data;

    if (this->theArrayType == 's') {
        int len = strlen((char *) element_val);
        data = malloc(len + 1);
        strcpy((char *) data, (char *) element_val);

        if (true && this->debugOn_) {
            printf("ArrayMgrClass::insertPointerElement(%s) %s\n", this->theWho, (char *) data);
        }
    }
    else {
        data = element_val;
    }

    int i = 0;
    while (i < this->theArraySize) {
        if (!this->thePointerArrayTable[i]) {
            this->thePointerArrayTable[i] = data;
            return;
        }
        i++;
    }

    if (this->theArraySize < this->theMaxArraySize) {
        this->thePointerArrayTable[this->theArraySize] = data;
        this->theArraySize++;
        return;
    }

    phwangAbendWS("ArrayMgrClass::insertPointerElement", this->theWho, "table is full");
}

void ArrayMgrClass::removeElement (void *element_val)
{
    this->removePointerElement(element_val);
}

void ArrayMgrClass::removePointerElement (void *element_val)
{
    if (this->theArrayType == 's') {
        free(element_val);
    }

    int i = 0;
    while (i < this->theMaxArraySize) {
        if (this->thePointerArrayTable[i] == element_val) {
            this->thePointerArrayTable[i] = 0;
            return;
        }
        i++;
    }
    phwangAbendWS("ArrayMgrClass::removePointerElement", this->theWho, "not found");
}
