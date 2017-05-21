# Copyrights reserved
# Written by Paul Hwang
# Makefile in base_mgr_dir

include ../../Makefile.inc

OBJLIBS	= ../../lib_base_mgr.a
OBJS =	base_mgr_class.o 

all: $(OBJLIBS)

../../lib_base_mgr.a: $(OBJS)
	$(AR) $(ARFLAGS) rv ../../lib_base_mgr.a $?
	$(RANLIB) ../../lib_base_mgr.a

clean:
	-$(RM) -f $(OBJS)

force_look:
	true
