include ../Makefile.inc

OBJLIBS	= libphwang.a
OBJS =	phwang.o phwang_class.o

all: $(OBJLIBS)

lib_phwang.a: $(OBJS)
	$(AR) $(ARFLAGS) rcs libphwang.a $?
	$(RANLIB) libphwang.a

##../lib_utils.a: $(OBJS)
##	$(AR) $(ARFLAGS) rv ../lib_utils.a $?
##	$(RANLIB) ../lib_utils.a

phwang.o: phwang.cpp phwang.h
	$(CC) -c phwang.cpp

phwang_class.o: phwang_class.cpp phwang_class.h
	$(CC) -c phwang_class.cpp

clean:
	-$(RM) -f $(OBJS) $(OBJLIBS)

force_look:
	true

