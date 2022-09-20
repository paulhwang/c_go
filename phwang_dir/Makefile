# Copyrights reserved
# Written by Paul Hwang

include ../Makefile.inc

PHWANG_DIR        = .
JSON_DIR          = $(PHWANG_DIR)/json_dir
SUSPEND_DIR       = $(PHWANG_DIR)/suspend_dir
LIST_MGR_DIR      = $(PHWANG_DIR)/list_mgr_dir
ARRAY_MGR_DIR     = $(PHWANG_DIR)/array_mgr_dir
ID_INDEX_LIST_DIR = $(PHWANG_DIR)/id_index_list_dir
QUEUE_DIR         = $(PHWANG_DIR)/queue_dir
SQL_DIR           = $(PHWANG_DIR)/sql_dir
ABEND_DIR         = $(PHWANG_DIR)/abend_dir
ATOMIC_DIR        = $(PHWANG_DIR)/atomic_dir
MALLOC_DIR        = $(PHWANG_DIR)/malloc_dir
ENCODE_DIR        = $(PHWANG_DIR)/encode_dir
THREAD_DIR        = $(PHWANG_DIR)/thread_dir
NET_DIR           = $(PHWANG_DIR)/net_dir
TCP_DIR           = $(NET_DIR)/tcp_dir
PORT_DIR          = $(NET_DIR)/port_dir

JSON_OBJS = $(JSON_DIR)/json_class.o 
SUSPEND_OBJS = $(SUSPEND_DIR)/suspend_class.o 
LIST_MGR_OBJS = $(LIST_MGR_DIR)/list_mgr_root_class.o $(LIST_MGR_DIR)/list_mgr_class.o $(LIST_MGR_DIR)/list_entry_class.o
ARRAY_MGR_OBJS = $(ARRAY_MGR_DIR)/array_mgr_root_class.o $(ARRAY_MGR_DIR)/array_mgr_class.o
ID_INDEX_LIST_OBJS = $(ID_INDEX_LIST_DIR)/id_index_list_class.o 
QUEUE_OBJS = $(QUEUE_DIR)/queue_root_class.o $(QUEUE_DIR)/queue_class.o $(QUEUE_DIR)/queue_entry_class.o
TCP_OBJS = $(TCP_DIR)/tcp_server_class.o $(TCP_DIR)/tcp_connect_class.o
PORT_OBJS = $(PORT_DIR)/port_class.o $(PORT_DIR)/port_class_transmit.o $(PORT_DIR)/port_class_receive.o $(PORT_DIR)/port_class_receive2.o
NET_OBJS = $(TCP_OBJS) $(PORT_OBJS) $(NET_DIR)/net_root_class.o
ABEND_OBJS = $(ABEND_DIR)/abend.o
ATOMIC_OBJS = $(ATOMIC_DIR)/atomic.o
MALLOC_OBJS = $(MALLOC_DIR)/malloc_class.o
ENCODE_OBJS = $(ENCODE_DIR)/encode.o
THREAD_OBJS = $(THREAD_DIR)/thread_root_class.o 
OBJECT_OBJS = $(OBJECT_DIR)/object_class.o
PHWANG_OBJS = $(PHWANG_DIR)/phwang.o $(PHWANG_DIR)/phwang_class.o $(JSON_OBJS) $(SUSPEND_OBJS) $(LIST_MGR_OBJS) $(ARRAY_MGR_OBJS) $(ID_INDEX_LIST_OBJS) $(QUEUE_OBJS) $(NET_OBJS) $(MALLOC_OBJS) $(ENCODE_OBJS) $(THREAD_OBJS) $(ABEND_OBJS) $(ATOMIC_OBJS)

PHWANG_STATIC_LIB = libphwang.a
PHWANG_DYNAMIC_LIB = libphwang.so

all: $(PHWANG_STATIC_LIB)

$(PHWANG_STATIC_LIB): $(PHWANG_OBJS)
	$(AR) $(ARFLAGS) $(PHWANG_STATIC_LIB) $?
	$(RANLIB) $(PHWANG_STATIC_LIB)
	#$(AR) t $(PHWANG_STATIC_LIB)

$(PHWANG_DIR)/phwang.o: $(PHWANG_DIR)/phwang.cpp $(PHWANG_DIR)/phwang.h
	$(CC) -c $(PHWANG_DIR)/phwang.cpp -o $(PHWANG_DIR)/phwang.o

$(PHWANG_DIR)/phwang_class.o: $(PHWANG_DIR)/phwang_class.cpp $(PHWANG_DIR)/phwang_class.h
	$(CC) -c $(PHWANG_DIR)/phwang_class.cpp -o $(PHWANG_DIR)/phwang_class.o

$(QUEUE_DIR)/queue_root_class.o: $(QUEUE_DIR)/queue_root_class.cpp $(QUEUE_DIR)/queue_root_class.h
	$(CC) -c $(QUEUE_DIR)/queue_root_class.cpp -o $(QUEUE_DIR)/queue_root_class.o

$(QUEUE_DIR)/queue_class.o: $(QUEUE_DIR)/queue_class.cpp $(QUEUE_DIR)/queue_class.h
	$(CC) -c $(QUEUE_DIR)/queue_class.cpp -o $(QUEUE_DIR)/queue_class.o

$(QUEUE_DIR)/queue_entry_class.o: $(QUEUE_DIR)/queue_entry_class.cpp $(QUEUE_DIR)/queue_entry_class.h
	$(CC) -c $(QUEUE_DIR)/queue_entry_class.cpp -o $(QUEUE_DIR)/queue_entry_class.o

$(ABEND_DIR)/abend.o: $(ABEND_DIR)/abend.cpp 
	$(CC) -c $(ABEND_DIR)/abend.cpp -o $(ABEND_DIR)/abend.o

$(ATOMIC_DIR)/atomic.o: $(ATOMIC_DIR)/atomic.cpp 
	$(CC) -c $(ATOMIC_DIR)/atomic.cpp -o $(ATOMIC_DIR)/atomic.o

$(ENCODE_DIR)/encode.o: $(ENCODE_DIR)/encode.cpp 
	$(CC) -c $(ENCODE_DIR)/encode.cpp -o $(ENCODE_DIR)/encode.o

$(MALLOC_DIR)/malloc_class.o: $(MALLOC_DIR)/malloc_class.cpp $(MALLOC_DIR)/malloc_class.h
	$(CC) -c $(MALLOC_DIR)/malloc_class.cpp -o $(MALLOC_DIR)/malloc_class.o

$(NET_DIR)/net_root_class.o: $(NET_DIR)/net_root_class.cpp $(NET_DIR)/net_root_class.h
	$(CC) -c $(NET_DIR)/net_root_class.cpp -o $(NET_DIR)/net_root_class.o

$(TCP_DIR)/tcp_server_class.o: $(TCP_DIR)/tcp_server_class.cpp $(TCP_DIR)/tcp_server_class.h
	$(CC) -c $(TCP_DIR)/tcp_server_class.cpp -o $(TCP_DIR)/tcp_server_class.o

$(TCP_DIR)/tcp_connect_class.o: $(TCP_DIR)/tcp_connect_class.cpp $(TCP_DIR)/tcp_connect_class.h
	$(CC) -c $(TCP_DIR)/tcp_connect_class.cpp -o $(TCP_DIR)/tcp_connect_class.o

$(PORT_DIR)/port_class.o: $(PORT_DIR)/port_class.cpp $(PORT_DIR)/port_class.h
	$(CC) -c $(PORT_DIR)/port_class.cpp -o $(PORT_DIR)/port_class.o

$(PORT_DIR)/port_class_transmit.o: $(PORT_DIR)/port_class_transmit.cpp $(PORT_DIR)/port_class.h
	$(CC) -c $(PORT_DIR)/port_class_transmit.cpp -o $(PORT_DIR)/port_class_transmit.o

$(PORT_DIR)/port_class_receive.o: $(PORT_DIR)/port_class_receive.cpp $(PORT_DIR)/port_class.h
	$(CC) -c $(PORT_DIR)/port_class_receive.cpp -o $(PORT_DIR)/port_class_receive.o

$(PORT_DIR)/port_class_receive2.o: $(PORT_DIR)/port_class_receive2.cpp $(PORT_DIR)/port_class.h
	$(CC) -c $(PORT_DIR)/port_class_receive2.cpp -o $(PORT_DIR)/port_class_receive2.o

$(LIST_MGR_DIR)/list_mgr_class.o: $(LIST_MGR_DIR)/list_mgr_class.cpp $(LIST_MGR_DIR)/list_mgr_class.h
	$(CC) -c $(LIST_MGR_DIR)/list_mgr_class.cpp -o $(LIST_MGR_DIR)/list_mgr_class.o

$(LIST_MGR_DIR)/list_entry_class.o: $(LIST_MGR_DIR)/list_entry_class.cpp $(LIST_MGR_DIR)/list_entry_class.h
	$(CC) -c $(LIST_MGR_DIR)/list_entry_class.cpp -o $(LIST_MGR_DIR)/list_entry_class.o

$(LIST_MGR_DIR)/list_mgr_root_class.o: $(LIST_MGR_DIR)/list_mgr_root_class.cpp $(LIST_MGR_DIR)/list_mgr_root_class.h
	$(CC) -c $(LIST_MGR_DIR)/list_mgr_root_class.cpp -o $(LIST_MGR_DIR)/list_mgr_root_class.o

$(ARRAY_MGR_DIR)/array_mgr_root_class.o: $(ARRAY_MGR_DIR)/array_mgr_root_class.cpp $(ARRAY_MGR_DIR)/array_mgr_root_class.h
	$(CC) -c $(ARRAY_MGR_DIR)/array_mgr_root_class.cpp -o $(ARRAY_MGR_DIR)/array_mgr_root_class.o

$(ARRAY_MGR_DIR)/array_mgr_class.o: $(ARRAY_MGR_DIR)/array_mgr_class.cpp $(ARRAY_MGR_DIR)/array_mgr_class.h
	$(CC) -c $(ARRAY_MGR_DIR)/array_mgr_class.cpp -o $(ARRAY_MGR_DIR)/array_mgr_class.o

$(THREAD_DIR)/thread_root_class.o: $(THREAD_DIR)/thread_root_class.cpp $(THREAD_DIR)/thread_root_class.h
	$(CC) -c $(THREAD_DIR)/thread_root_class.cpp -o $(THREAD_DIR)/thread_root_class.o

$(SUSPEND_DIR)/suspend_class.o: $(SUSPEND_DIR)/suspend_class.cpp $(SUSPEND_DIR)/suspend_class.h
	$(CC) -c $(SUSPEND_DIR)/suspend_class.cpp -o $(SUSPEND_DIR)/suspend_class.o

$(ID_INDEX_LIST_DIR)/id_index_list_class.o: $(ID_INDEX_LIST_DIR)/id_index_list_class.cpp $(ID_INDEX_LIST_DIR)/id_index_list_class.h
	$(CC) -c $(ID_INDEX_LIST_DIR)/id_index_list_class.cpp -o $(ID_INDEX_LIST_DIR)/id_index_list_class.o

clean:
	-$(RM) -f $(PHWANG_STATIC_LIB) $(PHWANG_OBJS)

force_look:
	true

#.PHONY: project_code

#$(QUEUE_OBJS):
#	cd $(QUEUE_DIR) && make

##	$(MAKE) -C $(QUEUE_DIR)

##../lib_utils.a: $(OBJS)
##	$(AR) $(ARFLAGS) rv ../lib_utils.a $?
##	$(RANLIB) ../lib_utils.a

