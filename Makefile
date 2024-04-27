mem_test: mem_test.c my_malloc.c
	gcc -Wall -g -o mem_test mem_test.c my_malloc.c

clean:
	rm -f mem_test *.o
