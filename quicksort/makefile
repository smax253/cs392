sort: mergesort.o sort.o
	gcc -g mergesort.o sort.o -o sort
sort.o: sort.c
	gcc -g -Wall -Werror -pedantic-errors -c sort.c
mergesort.o: mergesort.c mergesort.h
	gcc -g -Wall -Werror -pedantic-errors -c mergesort.c
quicksort.o: quicksort.c quicksort.h
	gcc -g -Wall -Werror -pedantic-errors -c quicksort.c
clean:
	rm -f *.o sort sort.exe
rebuild:
	make clean
	make sort
