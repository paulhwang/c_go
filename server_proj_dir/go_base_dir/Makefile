# Copyrights reserved
# Written by Paul Hwang
# Makefile in go_base_dir

include ../../Makefile.inc

OBJLIBS	= ../../lib_go_base.a
OBJS =	

all: $(OBJLIBS)

../../lib_go_base.a: $(OBJS)
	$(AR) $(ARFLAGS) rv ../../lib_go_base.a $?
	$(RANLIB) ../../lib_go_base.a

clean:
	-$(RM) -f $(OBJS)

force_look:
	true
