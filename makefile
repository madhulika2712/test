CC = gcc
CFLAGS  = -g -Wall 
 
default: test1

test1: test_assign2_1.o storage_mgr.o dberror.o 
	$(CC) $(CFLAGS) test_assign2_1.c storage_mgr.c dberror.c -o test.o
run_test1:
	./test.o

test2: test_assign1_1.o storage_mgr.o dberror.o 
	$(CC) $(CFLAGS) test_assign1_1.c storage_mgr.c dberror.c -o test2.o
run_test2:
	./test2.o

test3: test_assign3_1.o storage_mgr.o dberror.o 
	$(CC) $(CFLAGS) test_assign3_1.c storage_mgr.c dberror.c -o test3.o
run_test3:
	./test3.o


