/*
*	Atreides.c
*	@author Eduard Lecha Puig
*	@Created 2021-22
*	@brief Atreides es la part principal del programa en la qual hi ha implementada la funció Main de la Fase 2 de la pràctica 1.
*	(c) Copyright La Salle
*
*/

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "Config.h"
#include "Socket.h"

#define MSG_EFITX 					"Falten parametres.\n"
#define MSG_WELCOME					"SERVIDOR ATREIDES\n"
#define MSG_EXIT					"Sortida del programa Fremen.\n\n"
#define MSG_CLOSE_SOCKET 			"Close el socket del servidor.\n"	
#define MSG_ERROR_SOCKET 			"Error a l'obrir el socket del servidor.\n"	
#define	MSG_ERROR_THREADCREATION	"ERROR: could not create thread\n"	
#define MSG_ERROR_UPARAM 				"Sobren parametres.\n"

Dades dadesFitxer;
int fd = -1, fd_server = -1, fd_client = 1;

/*
*	Funció que s'ocupa d'executar el necessari per a finalitzar el programa.
*/
void terminateProgram(){
	//Missatge de sortida del programa Fremen.
	//write(1, MSG_EXIT, strlen(MSG_EXIT));

	//Tanca el file descriptor per a que no es refereixi a cap fitxer i pugui ser re-utilitzat.
	if (fd > 0) close(fd);

	//Allibero memoria.
	//freeDades(&dadesFitxer);

	//Mata els signals generats.
	//raise(SIGKILL);
}

void handle_signal(int signum) {
	if(signum == SIGINT) {
		write(1, MSG_CLOSE_SOCKET, sizeof(MSG_CLOSE_SOCKET));
		close(fd_client);
		close(fd_server);
		exit(0);
	}
}

void* connection_handler(void* fd_client)
{

	int i = *((int*)fd_client);
	char buffer[256];
	read(i, buffer, 256);
	write(1, "Valor leido:", strlen("Valor leido:"));
	write(1, buffer, 256);
	
	return 0;
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
		write(1, MSG_WELCOME, strlen(MSG_WELCOME));
		
		//Get the total num of characters of the filename inserted by the user and book memory for them.
		int i = 0;
		while(argv[1][i] != '\0') i++;
		char* fileName = (char*)malloc(sizeof(char*)*i);

		//Passo el nom del fitxer de configuració a la variavle "fileName".
        strcpy(fileName, argv[1]);
		
		//Obtenim les dades del fitxer de configuració.
        getData(fileName, &fd, &dadesFitxer);
		free(fileName);

		//Per quan presiono CTRL+C executo "handle_signal".
		signal(SIGINT, handle_signal);

		//La següent funció s'ocupa d'obrir un socket servidor i acceptar les conexions entrants.
		if(launchServer(dadesFitxer.port, dadesFitxer.ip, &fd_server) >= 0){
			//Declarem variable per crear threads.
			pthread_t* threads_id;
			pthread_t thread_id;
			//int ret_pthread = 0;
			int* clients;
			int counter = 0;
			int ret_pthread = 0;
		
			//Inicialitzo array dinamic sockets de clients i de threads.
			clients = (int*)malloc(sizeof(int));
			threads_id = (pthread_t*)malloc(sizeof(pthread_t));

			while(1){
				//Guradem nova connexio socket al array dinamic
				fd_client = runServer(fd_server);	
				clients[counter] = fd_client;		
				clients = (int*)realloc(clients, (counter+1)*sizeof(int));

				if(fd_client >= 0){
					//Creo el thread i crido el "connection_handler".
					ret_pthread = pthread_create(&thread_id, NULL, connection_handler, (void*)&fd_client);

					if(ret_pthread < 0){
						write(1, MSG_ERROR_THREADCREATION, strlen(MSG_ERROR_THREADCREATION));
						terminateProgram();
						exit(EXIT_FAILURE);
					}else{
						//En el cas que s'hagi creat correctament, guardem l'ID del nou thread al array dinamic de threads_id
						threads_id[counter] = thread_id;
						threads_id = (pthread_t*)realloc(threads_id, (counter+1)*sizeof(pthread_t));					
					}
					counter++; 	
				}	
			}
			
			clients[counter] = 0;
			free(clients);
			clients = NULL;
			free(threads_id);
			threads_id = NULL;
			//Esperem que tanqui el fill.
			wait(NULL);

		}else{
			write(1, MSG_ERROR_SOCKET, sizeof(MSG_ERROR_SOCKET));
		}

		//if(dadesFitxer.temps != -1){
			//Estic atent a entrades de l'usuari.
			//while(listenUser() != -2);
		//}
     }else if(argc < 2){
        //Escric text per pantalla.	
        write(1, MSG_EFITX, strlen(MSG_EFITX));
		exit(EXIT_FAILURE);
    }else{
		//Escric text per pantalla.	
        write(1, MSG_ERROR_UPARAM, strlen(MSG_ERROR_UPARAM));
		exit(EXIT_FAILURE);
	}
}