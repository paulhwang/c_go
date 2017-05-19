include ../../Makefile.inc

OBJLIBS	= ../../lib_go_base.a
OBJS =	go_base_class.o go_engine_class.o go_board_class.o go_move_class.o go_port_class.o go_group_class.o go_group_lst_class.o

all: $(OBJLIBS)

../../lib_go_base.a: $(OBJS)
	$(AR) $(ARFLAGS) rv ../../lib_go_base.a $?
	$(RANLIB) ../../lib_go_base.a

clean:
	-$(RM) -f $(OBJS)

force_look:
	true
