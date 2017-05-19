include ../Makefile.inc

DIRS	= go_base
OBJLIBS	= ../lib_go_root.a ../lib_go_base.a
OBJS =	go_root_class.o

all: $(OBJLIBS)

../lib_go_root.a: $(OBJS)
	$(ECHO) lib_go_root
	$(AR) $(ARFLAGS) rv ../lib_utils.a $?
	$(RANLIB) ../lib_utils.a

../lib_go_base.a: force_look
	cd go_base; $(MAKE) $(MFLAGS)

clean:
	-$(RM) -f $(OBJS)
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean); done

force_look:
	true
