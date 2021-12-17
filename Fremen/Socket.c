/*
*
*	Socket.c
* 	@author Eduard Lecha Puig
* 	@Created 2021-22
* 	@brief Socket s'encarrega de fer el Socket de connexió client.
* 	(c) Copyright La Salle
*
*/

#include "Socket.h"

#define LOGIN_SUCCESS       "Sesión iniciada\n"
#define LOG_OUT             "Cerrando sesión...\n"
#define ERROR_OP            "ERROR: No se ha podido realizar la operación.\n"
#define MSG_LOGGING_IN      "Iniciant sessió al servidor d'Atreides.\n"
#define MSG_LOGIN_SUCCES    "Has iniciat sessió amb exit.\n"

#define print(X) write(1, X, strlen(X))

CommunicationData dadesCommunicacio;

int fd_server;
char* user;

void close_connection() {
    print(LOG_OUT);
    write(fd_server, "OUT\n", sizeof("OUT\n"));
    close(fd_server);
    free(user);
    exit(0);
}

int connect_to_server(char *ip, int port) {
    struct sockaddr_in s_addr;
    int socket_conn = -1;

    socket_conn = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (socket_conn < 0) {
        print("ERROR durante la creacion del socket.\n");
    } else {
        memset(&s_addr, 0, sizeof(s_addr));
        s_addr.sin_family = AF_INET;
        s_addr.sin_port = htons(port);
        s_addr.sin_addr.s_addr = inet_addr(ip);

        if (connect(socket_conn, (void *) &s_addr, sizeof(s_addr)) < 0) {
            char buff[128];
            printf("ERROR de connexion con el servidor.\n");
            int bytes = sprintf(buff, "errno says: %s\n", strerror(errno)); // molt útil
            write(1, buff, bytes);
            close(socket_conn);
            socket_conn = -1;
        }
    }

    return socket_conn;
}

void start_session() {
    while (1) {
        char buff[128] = "";
        char* product;
        char* quantity;
        int bytes;
        print("\nProducto a modificar: \0");
        product = read_until(0, '\n');
        product[strlen(product)-1] = '\0';
        print("Cantidad: \0");
        quantity = read_until(0, '\n');
        quantity[strlen(quantity)-1] = '\0';
        if (atoi(quantity) == 0 && strcmp(quantity, "-\0") != 0) {
            free(product);
            free(quantity);
            print("ERROR: La cantidad no puede ser 0.\n");
            continue;
        }
        bytes = sprintf(buff, "%s#%s\n", product, quantity);
        write(fd_server, buff, bytes);
        free(product);
        free(quantity);
        char* list = read_until(fd_server, '\n');
        if (strcmp(list, "KO\n") == 0) {
            print("ERROR: No se ha podido realizar la operacion.\n");
        } else {
            bytes = sprintf(buff, "\nLista de %s\n", user);
            write(1, buff, bytes);
            int i = 0;
            int n_prod = 0;
            char letter = list[i];
            write(1, "\t\0", 2);
            while (letter != '\n') {
                if (letter == '$') {
                    write(1, "\n\t\0", 3);
                } else {
                    if (letter == '#') {
                        write(1, "\t---\tx\0", 7);
                        n_prod++;
                    } else {
                        write(1, &letter, 1);
                    }
                }
                i++;
                letter = list[i];
            }
            bytes = sprintf(buff, "\nNumero total de productos = %d\n", n_prod);
            write(1, buff, bytes);
        }
        free(list);
    }
}

/*
*	Obre socket de connexió client per a la connexió al servidor Atreides.
*/
int openSocket(int* fd_server, char* ip, int port) {
	write(1, MSG_LOGGING_IN, strlen(MSG_LOGGING_IN));
	
	//Li passo la IP i el Port.
	*fd_server = connect_to_server(ip, port);
	    
	if (*fd_server < 0) {
        return EXIT_FAILURE;
    }else{
         write(1, MSG_LOGIN_SUCCES, strlen(MSG_LOGIN_SUCCES));
    }
    
    return *fd_server;	
}

/*
*   Aquesta funció parseja els camps origen, tipus i data en una sola cadena de 256 caràcters.
*/
void joinChains(CommunicationData dadesCommunicacio, char buffer[256]){
    //Parsear origen, tipo y data en un solo string de 256 caracteres.
    int j = 0;

    for(int i = 0; i < 15; i++){
        if(dadesCommunicacio.origen[i] > '!'){
            buffer[j] = dadesCommunicacio.origen[i];
        }else{
            buffer[j] = '\0';
        }
        j++;
    }

    buffer[j] = dadesCommunicacio.tipus[0];
    j++;

    for(int i = 0; i < 240; i++){
        if(dadesCommunicacio.data[i] > '!'){
            buffer[j] = dadesCommunicacio.data[i];
        }else{
            buffer[j] = '\0';
        }
        j++;
    }
    
    buffer[j] = '\0';
}

void sendMessage(int fd_server, CommunicationData dadesCommunicacio){
    /*Totes les trames que s’envien tenen exactament la mateixa mida amb 3 camps ocupant sempre un espai total de 256 bytes.*/
    char buffer[256];
    joinChains(dadesCommunicacio, buffer);
    //int bytes = sprintf(buffer, "%s\n", buffer);
    write(fd_server, buffer, 256);
    
    //bytes = sprintf(buffer, "%s\n", dadesCommunicacio.tipus);
    //write(fd_server, buffer, bytes);
    
    //bytes = sprintf(buffer, "%s\n", dadesCommunicacio.data);
    //write(fd_server, buffer, bytes);
}

void getMessage(int fd_server){
    char* response = read_until(fd_server, '\n');
    if (strcmp(response, "KO\n") == 0) {
        print("ERROR: No se ha podido iniciar sesion.\n");
        free(response);
    }else{}
}

int closeSocket(int fd_server){
    close(fd_server);
    return EXIT_SUCCESS;
}


/*
    ----->>>>>>Continuació de getMessage
 else {
        bytes = sprintf(buff, "\nUsuario: %s\n", user);
        write(1, buff, bytes);
        bytes = sprintf(buff, "Lista de %s\n", user);
        write(1, buff, bytes);
        int i = 0;
        int n_prod = 0;
        char letter = response[i];
        write(1, "\t", 1);
        while (letter != '\n') {
            if (letter == '$') {
                write(1, "\n\t", 2);
            } else {
                if (letter == '#') {
                    write(1, "\t---\tx", 6);
                    n_prod++;
                } else {
                    write(1, &letter, 1);
                }
            }
            i++;
            letter = response[i];
        }
        bytes = sprintf(buff, "\nNumero total de productos = %d\n", n_prod);
        write(1, buff, bytes);
        free(response);
     */