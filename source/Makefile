OBJS = Signal.o CoreFunctions.o Builtin.o Process.o History.o StringFunctions.o

all: shell

shell: ${OBJS}
	gcc -pg -Wall ../obj/*.o -o ../prof/shell ../Main.c

Signal.o:
	gcc -pg  -o ../obj/Signal.o -c Signal.c

CoreFunctions.o:
	gcc -pg  -o ../obj/CoreFunctions.o -c CoreFunctions.c

Builtin.o:
	gcc -pg  -o ../obj/Builtin.o -c Builtin.c

Process.o:
	gcc -pg  -o ../obj/Process.o -c Process.c

History.o:
	gcc -pg  -o ../obj/History.o -c History.c

StringFunctions.o:
	gcc -pg  -o ../obj/StringFunctions.o -c StringFunctions.c

