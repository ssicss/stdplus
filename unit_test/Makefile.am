noinst_PROGRAMS = test_core.out
test_core_out_SOURCES = test_core.c\
			test_linklist.c\
			test_queue.c

test_core_out_LDADD = ${ROOT_DIR}/src/libstdplus.a 
test_core_out_CFLAGS = $(AM_CFLAGS) -Wl,-Map=test_core.map
