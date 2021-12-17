all: Practica.exe

Atreides.o: Atreides.c
	gcc -Wall -Wextra -pthread -c Atreides.c

Config.o: Config.c Config.h
	gcc -Wall -Wextra -c Config.c

PresetFunctions.o: PresetFunctions.c PresetFunctions.h
	gcc -Wall -Wextra -c PresetFunctions.c

Socket.o: Socket.c Socket.h
	gcc -Wall -Wextra -c Socket.c

Practica.exe: Atreides.o Config.o PresetFunctions.o Socket.o
	gcc Atreides.o Config.o PresetFunctions.o Socket.o -Wall -Wextra -pthread -o Atreides

clean:
	rm -rf *.o Atreides