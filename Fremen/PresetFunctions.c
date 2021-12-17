/*
*   PresetFunctions.c
*   @author Eduard Lecha Puig
*   @Created 2021-22
*   @brief PresetFunctions son utilities que es poden utilitzar al llarg 
*   del programa pels diferents móduls per tal de realitzar funcions específiques.
*   (c) Copyright La Salle
*
*/

#include "PresetFunctions.h"

/**
    Funció que serveix per a passar caracters d'una cadena a minuscula.
**/
void tolowerCase(char* order){
	for(int aux = 0; order[aux] != '\0'; aux++){
		if(order[aux]>64 && order[aux]<91){
			order[aux] = order[aux] - 'A' + 'a';
		} 
    }
}

/**
    Funció que serveix per llegir fins determinats caracters, i en cas que s'arribi al segon caracter definit 
    en el segon parametre s'indiqui a través de la variable final, la qual es passa per referencia.
**/
char* read_until_different_options(int fd, char end, char end2, char* final) {
    int i = 0, size;
    char c = '\0';
    char* string = (char*)malloc(sizeof(char));
    *final = 0;
    while(1){
        size = read(fd, &c, sizeof(char));
        if(c != end && c != end2 && size > 0) {
            string = (char*)realloc(string, sizeof(char) * (i + 2));
            string[i++] = c;
        }else{
            if (c == end2) {
                *final = 1;
            }
            break;
        }
    }

    string[i] = '\0';
    return string;
}

/**
    Funció que serveix per llegir tots els caracters que hi ha fins trobar-se un caracter
**/
char* read_until(int fd, char end) {
    int i = 0, size;
    char c = '\0';
    char* string = (char*)malloc(sizeof(char));

    while (1) {
        size = read(fd, &c, sizeof(char));
        
        if (c != end && size > 0) {
            string = (char*)realloc(string, sizeof(char) * (i + 2));
            string[i++] = c;
        } else {
            break;
        }
    }

    string[i] = '\0';
    return string;
}