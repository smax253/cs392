sort: sort.o sorts.o
	gcc sort.o sorts.o -o sort
sort.o: sort.c
	gcc -Wall -Werror -pedantic-errors -c sort.c
sorts.o: sorts.c sorts.h
	gcc -Wall -Werror -pedantic-errors -c sorts.c
clean:
	rm -f *.o sort sort.exe