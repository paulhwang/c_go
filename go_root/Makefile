include ../Makefile.inc

DIRS	= go_base
OBJLIBS	= ../lib_go_root.a ../lib_go_base.a
OBJS =	go_root.o

all: $(OBJLIBS)

../lib_go_root.a:
	$(ECHO) lib_go_root

../lib_go_base.a: force_look
	cd go_base; $(MAKE) $(MFLAGS)

clean:
	-$(RM) -f $(OBJS)
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean); done

force_look:
	true
