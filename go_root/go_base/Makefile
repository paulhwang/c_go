include ../../Makefile.inc

OBJLIBS	= ../../lib_go_base.a
OBJS =	go_base_class.o go_move_class.o

all: $(OBJLIBS)

../../lib_go_base.a: $(OBJS)
	$(ECHO) lib_go_base
	$(AR) $(ARFLAGS) rv ../../lib_go_base.a $?
	$(RANLIB) ../../lib_go_base.a

clean:
	-$(RM) -f $(OBJS)

force_look:
	true
