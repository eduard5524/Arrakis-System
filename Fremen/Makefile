all: Practica.exe

Fremen.o: Fremen.c
	gcc -Wall -Wextra -pthread -c Fremen.c

Config.o: Config.c Config.h
	gcc -Wall -Wextra -c Config.c
	
PresetFunctions.o: PresetFunctions.c PresetFunctions.h
	gcc -Wall -Wextra -c PresetFunctions.c

Socket.o: Socket.c Socket.h
	gcc -Wall -Wextra -c Socket.c

Menu.o: Menu.c Menu.h
	gcc -Wall -Wextra -c Menu.c

Practica.exe: Fremen.o Config.o PresetFunctions.o Menu.o Socket.o
	gcc Fremen.o Config.o PresetFunctions.o Menu.o Socket.o -Wall -Wextra -pthread -o Fremen

clean:
	rm -rf *.o Fremen