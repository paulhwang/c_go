# Copyrights reserved
# Written by Paul Hwang

include ../Makefile.inc

### libraries
PHWANG_DIR        = ../phwang_dir
PHWANG_STATIC_LIB = $(PHWANG_DIR)/libphwang.a
PHWANG_DYNAMIC_LIB = $(PHWANG_DIR)/libphwang.so

### Directories
ROBUST_PROJ_DIR     = .
ROBUST_DIR          = $(ROBUST_PROJ_DIR)/robust_dir

### Objects
ROBUST_OBJS = $(ROBUST_DIR)/robust_main.o $(ROBUST_DIR)/robust_root_class.o
ROBUST_PROJ_OBJS = $(ROBUST_OBJS)

### Executable
ROBUST = $(ROBUST_PROJ_DIR)/robust 

all:	$(ROBUST)

$(ROBUST): $(ROBUST_PROJ_OBJS) $(PHWANG_STATIC_LIB)
	$(CC) -o $(ROBUST) $(ROBUST_PROJ_OBJS) -L$(PHWANG_DIR) -lphwang -lstdc++ -pthread

$(ROBUST_DIR)/robust_main.o: $(ROBUST_DIR)/robust_main.cpp
	$(CC) -c $(ROBUST_DIR)/robust_main.cpp -o $(ROBUST_DIR)/robust_main.o

$(ROBUST_DIR)/robust_root_class.o: $(ROBUST_DIR)/robust_root_class.cpp $(ROBUST_DIR)/robust_root_class.h
	$(CC) -c $(ROBUST_DIR)/robust_root_class.cpp -o $(ROBUST_DIR)/robust_root_class.o

clean:
	- $(RM) $(ROBUST) $(ROBUST_PROJ_OBJS) 
