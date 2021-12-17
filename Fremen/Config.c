/*
*
*	Config.c
* 	@author Eduard Lecha Puig
* 	@Created 2021-22
* 	@brief PresetFunctions son utilities que es poden utilitzar al llarg 
* 	del programa pels diferents móduls per tal de realitzar funcions específiques.
* 	(c) Copyright La Salle
*
*/

#include "Config.h"
#include <unistd.h>

//Definició de constants.
#define MSG_OPEN_ "The file has been opened correctly and the data stored are the following.\n"
#define ERR_OPEN_ "There has been an error openning the file.\n"

char aux;
long result = -1;

/*
*	Funció que s'ocupa d'extruere l'informació del fitxer de configuració. 
*/
void getData(char* fileName, int* fd_file, Dades* dadesFitxer){
	char buffer[20];
	*fd_file = -1;

	dadesFitxer->temps = -1;
	dadesFitxer->port = -1;
	
    *fd_file = open(fileName, O_RDONLY);
	
    if(*fd_file <= 0){
		write(1, ERR_OPEN_, strlen(ERR_OPEN_));
    }else{
        write(1, MSG_OPEN_, strlen(MSG_OPEN_));
		
		//Lectura del TEMPS del fitxer, la primera linea d'informació.
		char* aux_string;
		aux_string = read_until(*fd_file, '\n');
		//Converteixo l'string a enter, per aixo utilitzo ATOI.	
		dadesFitxer->temps = atoi(aux_string);
		free(aux_string);
		sprintf(buffer, "%d\n", dadesFitxer->temps);	
		write(1, buffer, strlen(buffer));
		

		char final;
		//Lectura de la @IP.
		dadesFitxer->ip = read_until_different_options(*fd_file, '\n', '\n', &final);
		sprintf(buffer, "%s\n", dadesFitxer->ip);	
		write(1, buffer, strlen(buffer));
		
		//Lectura del Port.
		aux_string = read_until_different_options(*fd_file, '\n', '\n', &final);
		//Converteixo l'enter a un string, per aixo utilitzo ATOI.
		dadesFitxer->port = atoi(aux_string);
		free(aux_string);
		sprintf(buffer, "%d\n", dadesFitxer->port);	
		write(1, buffer, strlen(buffer));

		//Lectura de la localització del programa Fremen.
		dadesFitxer->location = read_until_different_options(*fd_file, '\n', '\n', &final);
		sprintf(buffer, "%s\n", dadesFitxer->location);	
		write(1, buffer, strlen(buffer));
    }
}

void freeDades(Dades* dadesFitxer){
	free(dadesFitxer->ip);
	free(dadesFitxer->location);
}