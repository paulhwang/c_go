# Copyrights reserved
# Written by Paul Hwang

include ../Makefile.inc

LIB	= libphwang.a
OBJS =	phwang.o phwang_class.o

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $(LIB) $?
	$(RANLIB) $(LIB)

##../lib_utils.a: $(OBJS)
##	$(AR) $(ARFLAGS) rv ../lib_utils.a $?
##	$(RANLIB) ../lib_utils.a

phwang.o: phwang.cpp phwang.h
	$(CC) -c phwang.cpp

phwang_class.o: phwang_class.cpp phwang_class.h
	$(CC) -c phwang_class.cpp

clean:
	-$(RM) -f $(OBJS) $(LIB)

force_look:
	true

