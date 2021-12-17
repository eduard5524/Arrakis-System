/*
*	Fremen.c
*	@author Eduard Lecha Puig
*	@Created 2021-22
*	@brief Fremen es la part principal del programa en la qual hi ha implementada la funció Main.
*	(c) Copyright La Salle
*
*/

#include <unistd.h>
#include <signal.h>

#include "Config.h"
#include "Menu.h"
#include "Socket.h"

#define EFITX_ 			"Falten parametres.\n"
#define ERR_UPARAM_ 	"Sobren parametres.\n"
#define MSG_WELCOME_	"Benvingut a Fremen.\n\n"
#define MSG_EXIT_		"Sortida del programa Fremen.\n\n"

Dades dadesFitxer;
int fd_file = -1, fd_server = -1;

/*
*	Funció que s'ocupa d'executar el necessari per a finalitzar el programa.
*/
void terminateProgram(){
	//Missatge de sortida del programa Fremen.
	write(1, MSG_EXIT_, strlen(MSG_EXIT_));

	//Tanca el file descriptor per a que no es refereixi a cap fitxer i pugui ser re-utilitzat.
	if (fd_file > 0) close(fd_file);

	//Allibero memoria.
	//freeDades(&dadesFitxer);

	//Mata els signals generats.
	//raise(SIGKILL);
	signal(SIGINT, SIG_DFL);
}

/*
*	Funció main, la principal funció del programa.
*/
int main(int argc, char *argv[]){
	//Genero un Signal, un event per tal que executi per cada interrupció del Teclat de "CTRL+C".
	signal(SIGINT, terminateProgram);

	//Comprovo si l'entrada de parametres de l'usuari a l'executar el programa es correcte.
    if(argc == 2){
		//Welcome message.
		write(1, MSG_WELCOME_, strlen(MSG_WELCOME_));
		
		int i = 0;
		while(argv[1][i] != '\0') i++;

		char* fileName = (char*)malloc(sizeof(char*)*i);

		//Passo el nom del fitxer de configuració a la variavle "fileName".
        strcpy(fileName, argv[1]);
		
		//Obtenim les dades del fitxer de configuració.
        getData(fileName, &fd_file, &dadesFitxer);
		free(fileName);

		if(dadesFitxer.temps != -1){
			//Obro socket de connexió.
			if(openSocket(&fd_server, dadesFitxer.ip, dadesFitxer.port) >= 0){
				
				//Espero a que l'usuari entri una ordre i quan l'hagi entrat continuo.
				//Per exemple LOGIN XaviC 08022 o SEARCH 08022
				//listenUser(argc) retorna -2 en cas que es vulgui sortir del programa.
				char* order;
				order = readOrder();				
				
				//Dades contè el login de l'usuari i el codi postal.
				switch(getMenuOption(order)){
					case 0:
						executeLogin(order, fd_server);
						break;		
				}

				free(order);
				
				//write(dadesFitxer); //Dades de comunicacio falta nom d'usuari.
				//Nom amb \0 pels caracters no utilitzats.
				//sendMessage(fd_server, dadesComunicacio);
				while(1){
					order = NULL;
				}
			}
		}
     }else if(argc < 2){
        //Escric text per pantalla.	
        write(1, EFITX_, strlen(EFITX_));
		exit(EXIT_FAILURE);
    }else{
		//Escric text per pantalla.	
        write(1, ERR_UPARAM_, strlen(ERR_UPARAM_));
		exit(EXIT_FAILURE);
	}
}