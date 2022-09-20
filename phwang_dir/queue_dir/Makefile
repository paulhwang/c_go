# Copyrights reserved
# Written by Paul Hwang

include ../../Makefile.inc

LIB	= libqueue.a
OBJS =	queue_class.o queue_entry_class.o queue_root_class.o

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $(LIB) $?
	$(RANLIB) $(LIB)

queue_class.o: queue_class.cpp queue_class.h
	$(CC) -c queue_class.cpp

queue_entry_class.o: queue_entry_class.cpp queue_entry_class.h
	$(CC) -c queue_entry_class.cpp

queue_root_class.o: queue_root_class.cpp queue_root_class.h
	$(CC) -c queue_root_class.cpp

clean:
	-$(RM) -f $(OBJS) $(LIB)

force_look:
	true

