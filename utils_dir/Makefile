include ../Makefile.inc

OBJLIBS	= ../lib_utils.a
OBJS =	logit.o transport_class.o queue_entry_class.o queue_mgr_class.o

all: $(OBJLIBS)

../lib_utils.a: $(OBJS)
	$(AR) $(ARFLAGS) rv ../lib_utils.a $?
	$(RANLIB) ../lib_utils.a

clean:
	-$(RM) -f $(OBJS)

force_look:
	true

