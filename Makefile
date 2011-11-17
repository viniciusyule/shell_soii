export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib:

OBJS = Signal.o CoreFunctions.o Builtin.o Process.o History.o StringFunctions.o
LIBS = libsig.so libcore.so libbuiltin.so libhist.so libjob.so libstrfunc.so

all: shell

shell: ${LIBS}
	gcc  -Wall -L./lib Main.c -lbuiltin -lcore -lhist -ljob -lsig -lstrfunc -o shell

Signal.o:
	gcc  -fPIC -o obj/Signal.o -c source/Signal.c

CoreFunctions.o:
	gcc  -fPIC -o obj/CoreFunctions.o -c source/CoreFunctions.c

Builtin.o:
	gcc  -fPIC -o obj/Builtin.o -c source/Builtin.c

Process.o:
	gcc  -fPIC -o obj/Process.o -c source/Process.c

History.o:
	gcc  -fPIC -o obj/History.o -c source/History.c

StringFunctions.o:
	gcc  -fPIC -o obj/StringFunctions.o -c source/StringFunctions.c

libsig.so: Signal.o
	gcc  -shared -fPIC -o lib/libsig.so obj/Signal.o

libcore.so: CoreFunctions.o
	gcc  -shared -fPIC -o lib/libcore.so obj/CoreFunctions.o

libbuiltin.so: Builtin.o
	gcc  -shared -fPIC -o lib/libbuiltin.so obj/Builtin.o

libjob.so: Process.o
	gcc  -shared -fPIC -o lib/libjob.so obj/Process.o

libhist.so: History.o
	gcc  -shared -fPIC -o lib/libhist.so obj/History.o

libstrfunc.so: StringFunctions.o
	gcc  -shared -fPIC -o lib/libstrfunc.so obj/StringFunctions.o


