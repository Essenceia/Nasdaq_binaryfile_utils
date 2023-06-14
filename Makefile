FLAGS = -std=gnu99 -Wall -Wextra -Wconversion -Wshadow -Wundef -fno-common  -Wno-unused-parameter -Wno-type-limits
CC = cc $(if $(debug),-DDEBUG -g)
LD = cc

select : file.o select.o
	$(LD) -o select -g select.o file.o

select.o: select.c
	$(CC) -c select.c $(FLAGS)


file.o: file.h file.c
	$(CC) -c file.c $(FLAGS)

clean:
	rm -f *.o	
	rm -f select
