include ../Makefile.inc

DIRS	= go_base_dir
OBJLIBS	= ../lib_go_root.a ../lib_go_base.a
OBJS =	root_class.o

all: $(OBJLIBS)

../lib_go_root.a: $(OBJS)
	$(ECHO) lib_go_root
	$(AR) $(ARFLAGS) rv ../lib_go_root.a $?
	$(RANLIB) ../lib_go_root.a

../lib_go_base.a: force_look
	cd go_base_dir; $(MAKE) $(MFLAGS)

clean:
	-$(RM) -f $(OBJS)
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean); done

force_look:
	true
