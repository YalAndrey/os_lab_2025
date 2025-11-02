CC=gcc
CFLAGS=-I.

all: parallel_min_max process_memory parallel_sum

parallel_sum: parallel_sum.o utils.o libsum_p.a
	$(CC)  parallel_sum.o utils.o  -L. -lsum_p -o parallel_sum

libsum_p.a: parallel_s.o
	ar rcs libsum_p.a parallel_s.o

parallel_s.o:
	$(CC) -lpthread parallel_s.c -o parallel_s.o

parallel_sum.o : utils.o
	$(CC) -o parallel_sum.o -c parallel_sum.c utils.o $(CFLAGS)

process_memory:
	$(CC) -o process_memory process_memory.c $(CFLAGS)

parallel_min_max : utils.o find_min_max.o utils.h find_min_max.h
	$(CC) -o parallel_min_max utils.o find_min_max.o parallel_min_max.c $(CFLAGS)

utils.o : utils.h
	$(CC) -o utils.o -c utils.c $(CFLAGS)

find_min_max.o : utils.h find_min_max.h
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)

	
clean :
	rm utils.o find_min_max.o parallel_min_max process_memory libsum_p.a parallel_sum