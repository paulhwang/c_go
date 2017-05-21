# Copyrights reserved
# Written by Paul Hwang
# Makefile in root_dir

include ../Makefile.inc

DIRS	= go_base_dir
OBJLIBS	= ../lib_root.a ../lib_base_mgr.a ../lib_go_base.a
OBJS =	root_class.o

all: $(OBJLIBS)

../lib_root.a: $(OBJS)
	$(ECHO) lib_root
	$(AR) $(ARFLAGS) rv ../lib_root.a $?
	$(RANLIB) ../lib_root.a

../lib_base_mgr.a: force_look
	cd base_mgr_dir; $(MAKE) $(MFLAGS)

../lib_go_base.a: force_look
	cd go_base_dir; $(MAKE) $(MFLAGS)

clean:
	-$(RM) -f $(OBJS)
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean); done

force_look:
	true
