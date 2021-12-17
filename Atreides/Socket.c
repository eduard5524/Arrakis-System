/*
*
*	Socket.c
* 	@author Eduard Lecha Puig
* 	@Created 2021-22
* 	@brief Socket s'utilitza per dur a terme el socket de servidor.
* 	(c) Copyright La Salle
*
*/
#include "Socket.h"

#define MSG_INPUT_USER          "Introdueix el teu nom d'usuari.\n"
#define MSG_LOGGING_IN          "Iniciant sessió...\n"
#define MSG_LOGIN_SUCCESS       "Sessió iniciada\n"
#define MSG_LOG_OUT             "Tancant sessió...\n"
#define MSG_SERVER_INIT         "[Servidor en funcionament]\n"
#define MSG_WAIT_CONN           "Esperant connexions...\n"
#define MSG_NEW_CONN            "[Conexion establecida]\n"
#define MSG_CLOSE			    "[Cerrando servidor]\n"
#define MSG_WAIT			    "Esperando usuario.\n"
#define MSG_SENT			    "Lista enviada.\n"

#define MSF_ERROR_OP            "Error, no s'ha pogut realitzar l'operació.\n"
#define MSG_ERROR			    "Error creant el socket.\n"
#define MSG_ERROR_ARGS          "Error, nombre d'arguments incorrecte.\n"
#define MSG_ERROR_SOCKET        "Error durant la creació del socket.\n"
#define MSG_ERROR_CLIENT        "Error, connexió no acceptada.\n"
#define MSG_ERROR_BIND          "Error durant el bind del port.\n"
#define MSG_ERROR_LAUNCH        "Error en la creació del servidor.\n"
#define MSG_ERROR_COM           "Error en la comunicació. Enllaç interromput amb el client.\n"
#define MSG_ERROR_OPTION		"Missatge no reconegut.\n"
#define MSG_ERROR_POS			"Posició no vàlida.\n"
#define MSG_ERROR_BOARD		    "Error amb el fitxer del tauler.\n"

#define LISTEN_BACKLOG		64
#define NUM_ARGS			3

typedef struct _producte{
    char* nom;
    int quantitat;
}Producte;

/*
*   Funció que llança el servidor i retorna 1 si tot ha anat correctament.
*/
int launchServer(int port, char *ip, int *fd_socket) {
    struct sockaddr_in s_addr;

    //Informo que el servidor ha estat inicialitzat.
    //write(1, MSG_SERVER_INIT, strlen(MSG_SERVER_INIT));

    //Obro el socket del servidor.
    *fd_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //Comprovo si s'ha pogut obrir el socket correctament.
    if(*fd_socket < 0){
        write(1, MSG_ERROR_SOCKET, sizeof(MSG_ERROR_SOCKET));
    }else{
        bzero(&s_addr, sizeof(s_addr));
        s_addr.sin_family = AF_INET;
        s_addr.sin_port = htons(port);
        s_addr.sin_addr.s_addr = inet_addr(ip);

        //The bind() function shall assign a local socket address address to a socket 
        //identified by descriptor socket that has no local socket address assigned.
        if(bind(*fd_socket, (void*)&s_addr, sizeof(s_addr)) < 0){
            //Informo en cas que el bind del port no s'hagi pogut efectuar correctament.
            write(1, MSG_ERROR_BIND, sizeof(MSG_ERROR_BIND));
        }else{
         	listen(*fd_socket, LISTEN_BACKLOG);
            return 1;
        }
    }
    return 0;
}

/*
*
*/
void logic(int fd_client){
    int fd;

    write(1, MSG_WAIT, sizeof(MSG_WAIT));
    
    char* name;
    name = read_until(fd_client, '\n');
    //Pinto el nom per pantalla.
    write(1, name, sizeof(name));

    //Obro el fitxer i si no existeix el creo.
    char buffer[100];
    
    sprintf(buffer, "./lists/%s.txt", name);
    fd = open(buffer, O_RDONLY | O_CREAT, 00666);
    if (fd < 0){ 

	}else{
        //read(fd, &current, 1);
        close(fd);
    }

    //Mostro el missatge lista enviada.
    write(1, MSG_SENT, sizeof(MSG_SENT));
}

/*
*   Aquesta funció està en execució i obre els sockets de connexió.
*/
int runServer(int fd_server) {
    struct sockaddr_in c_addr;
    socklen_t c_len = sizeof(c_addr);
    int fd_client;

    write(1, MSG_WAIT_CONN, sizeof(MSG_WAIT_CONN));
    fd_client = accept(fd_server, (void*) &c_addr, &c_len);
    
    if (fd_client < 0){
		write(1, MSG_ERROR_CLIENT, sizeof(MSG_ERROR_CLIENT));
		closeSocket(&fd_client);
        exit(EXIT_FAILURE);
    }else{
        write(1, MSG_NEW_CONN, sizeof(MSG_NEW_CONN));
    }
    return fd_client;
}

void closeSocket(int *fd_client){
    close(*fd_client);
}