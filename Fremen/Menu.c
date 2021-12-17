#include "Menu.h"

#define MSG_ORDER_RECEIVED		"The order has been received.\n"
#define MSG_REQUEST_ORDER		"\nInsert the order you want to execute.\n"

/*
*	Funció que retorna el nombre de parametres inserits.
*/
int getNumberOfParameters(char* order){
	int num_parameters = 0;
	
	for(int i = 0; order[i] != '\n'; ++i){
		if(order[i] == ' ' && order[i-1] != ' '){
			num_parameters++;
		}
	}

	return num_parameters;
}

/*
*	Retorna l'ordre inserida per l'usuari; LOGIN, PHOTO, SEARCH...
*/
char* getCommand(char* order){
	char* command = NULL;

	int i = 0;
	
	while(order[i] != '\n')	i++;
	
	//Reservation of memory to store the "Command".
	command = (char*)malloc(sizeof(char*)*i);

	//I take the order.
	for(i = 0; order[i] != '\n'; ++i){
		if(order[i] != ' '){
			command[i] = order[i];
		}
	}
	return command;
}

char* getParameter(){
	
	return "Hola";
}

void freeParameter(char* order){
	free(order);
}

/*
*	Funció que s'encarrega de llegir l'ordre inserida per l'usuari i guardar-la a la variable "order".
*/
char* readUserOrder(){
	char* order;
	write(1, MSG_REQUEST_ORDER, strlen(MSG_REQUEST_ORDER));
	
	//Llegeixo primer caracter i comparo amb el primer i aixi successivament.
	order = (char*)malloc(sizeof(char));
	read(1, &order[0], 1);
	for(int i = 1; order[i-1] != '\n'; i++){
		order = (char*)realloc(order, sizeof(char) * (i + 1));
		read(1, &order[i], 1);
		//write(1, &order[i],  1);
	}

	write(1, MSG_ORDER_RECEIVED, strlen(MSG_ORDER_RECEIVED));

	return order;
}

/*
*	Llegeixo la cadena introduïda per l'usuari, la passa tota a minuscules i la retorna.
*/
char* readOrder(){
	char* order;
	//Llegeixo la cadena inserida per l'usuari i la guardo a la variable order.
	//Per exemple LOGIN XaviC 08022 o SEARCH 08022 
	order = readUserOrder();	
	//Converteixo tota la cadena llegida a minuscula.
	tolowerCase(order);

	return order;
}

/*
*    Aquesta funció s'ocupa de la selecció de l'opció del menu de l'usuari.
*/
int getMenuOption(char* order){
	int option = -1;

	if(!strcmp(getCommand(order), "login")){
		option = 0;
	}else if(!strcmp(getCommand(order), "search")){
		option = 1;
	}else if(!strcmp(getCommand(order), "send")){
		option = 2;
	}else if(!strcmp(getCommand(order), "photo")){
		option = 3;
	}else if(!strcmp(getCommand(order), "logout")){
		option = 4;
	}else if(!strcmp(getCommand(order), "who")){
		option = 5;
	}else if(!strcmp(getCommand(order), "ps")){
		option = 6;
	}else if(!strcmp(getCommand(order), "cat")){
		option = 7;
	}else if(!strcmp(getCommand(order), "cd")){
		option = 8;
	}else if(!strcmp(getCommand(order), "chmod")){
		option = 9;
	}else if(!strcmp(getCommand(order), "chown")){
		option = 10;
	}else if(!strcmp(getCommand(order), "clear")){
		option = 11;
	}else if(!strcmp(getCommand(order), "cp")){
		option = 12;
	}else if(!strcmp(getCommand(order), "date")){
		option = 13;
	}else if(!strcmp(getCommand(order), "df")){
		option = 14;
	}else if(!strcmp(getCommand(order), "du")){
		option = 15;
	}else if(!strcmp(getCommand(order), "file")){
		option = 16;
	}else if(!strcmp(getCommand(order), "find")){
		option = 17;
	}else if(!strcmp(getCommand(order), "grep")){
		option = 18;
	}else if(!strcmp(getCommand(order), "kill")){
		option = 19;
	}else if(!strcmp(getCommand(order), "less")){
		option = 20;
	}else if(!strcmp(getCommand(order), "ln")){
		option = 21;
	}else if(!strcmp(getCommand(order), "locate")){
		option = 22;
	}else if(!strcmp(getCommand(order), "lpr")){
		option = 23;
	}else if(!strcmp(getCommand(order), "ls")){
		option = 24;
	}else if(!strcmp(getCommand(order), "man")){
		option = 25;
	}else if(!strcmp(getCommand(order), "mkdir")){
		option = 26;
	}else if(!strcmp(getCommand(order), "mv")){
		option = 27;
	}else if(!strcmp(getCommand(order), "pasoptiond")){
		option = 28;
	}else if(!strcmp(getCommand(order), "pwd")){
		option = 29;
	}else if(!strcmp(getCommand(order), "rm")){
		option = 30;
	}else if(!strcmp(getCommand(order), "rmdir")){
		option = 31;
	}else if(!strcmp(getCommand(order), "ssh")){
		option = 32;
	}else if(!strcmp(getCommand(order), "su")){
		option = 33;
	}else if(!strcmp(getCommand(order), "tail")){
		option = 34;
	}else if(!strcmp(getCommand(order), "tar")){
		option = 35;
	}else if(!strcmp(getCommand(order), "top")){
		option = 36;
	}else if(!strcmp(getCommand(order), "rouch")){
		option = 37;
	}else if(!strcmp(getCommand(order), "exit")){
		option = 38;
	}else if(!strcmp(getCommand(order), "head")){
		option = 39;
	}else if(!strcmp(getCommand(order), "whoami")){
		option = 40;
	}else if(!strcmp(getCommand(order), "wc")){
		option = 41;
	}
	return option;
}

void executeLogin(char* order, int fd_server){
	CommunicationData dadesComunicacio;

	
	write(1, "Option LOGIN selected\n",strlen("Option LOGIN selected\n"));
	if(getNumberOfParameters(order) == 2){
		write(1, "Comanda OK\n",strlen("Comanda OK\n"));
		sendMessage(fd_server, dadesComunicacio);		
	}else if(getNumberOfParameters(order) < 2){
		write(1, "Comanda KO. Falta paràmetres.\n",strlen("Comanda KO. Falta paràmetres.\n"));
	}else{
		write(1, "Comanda KO. Massa paràmetres.\n",strlen("Comanda KO. Massa paràmetres.\n"));
	}
	//Primerament solicito la connexió a Atreides.
	strcpy(dadesComunicacio.origen, "FREMEN");
	dadesComunicacio.tipus[0] = 'C';
	sendMessage(fd_server, dadesComunicacio);

}

int execute(int sw, char* order){
	/*
	char *arg1 = NULL;
	char *arg2 = NULL;

	pid_t child_tip = fork();
	if(child_tip == -1){
		perror("fork");
	}else if(child_tip == 0){
		execlp(command, command, arg1, arg2, NULL);
	}
	close(child_tip);
*/
	//free(command);
	
	
	switch(sw){
		case -1:
			write(1, "The option selected doesn't exist\n",strlen("The option selected doesn't exist\n"));
			return -1;
			break;
		case 0:
			write(1, "Option LOGIN selected\n",strlen("Option LOGIN selected\n"));
			if(getNumberOfParameters(order) == 2){
				write(1, "Comanda OK\n",strlen("Comanda OK\n"));
				
			}else if(getNumberOfParameters(order) < 2){
				write(1, "Comanda KO. Falta paràmetres.\n",strlen("Comanda KO. Falta paràmetres.\n"));
			}else{
				write(1, "Comanda KO. Massa paràmetres.\n",strlen("Comanda KO. Massa paràmetres.\n"));
			}
			return 0;
			break;
		case 1:
			write(1, "Option SEARCH selected\n",strlen("Option SEARCH selected\n"));
			if(getNumberOfParameters(order) == 1){

			}else if(getNumberOfParameters(order) < 1){
				write(1, "Comanda KO. Falta paràmetres.\n",strlen("Comanda KO. Falta paràmetres.\n"));	
			}else{
				write(1, "Comanda KO. Massa paràmetres.\n",strlen("Comanda KO. Massa paràmetres.\n"));
			}
			return 1;
			break;
		case 2:
			write(1, "Option SEND selected\n",strlen("Option SEND selected\n"));
			if(getNumberOfParameters(order) == 1){

			}else if(getNumberOfParameters(order) < 1){
				write(1, "Comanda KO. Falta paràmetres.\n",strlen("Comanda KO. Falta paràmetres.\n"));
			}else{
				write(1, "Comanda KO. Massa paràmetres.\n",strlen("Comanda KO. Massa paràmetres.\n"));
			}
			return 2;
			break;
		case 3:
			write(1, "Option PHOTO selected\n",strlen("Option PHOTO selected\n"));
			return 3;
			break;
		case 4:
			write(1, "Desconnectat d'Atreides. Dew!\n",strlen("Desconnectat d'Atreides. Dew!\n"));
			if(getNumberOfParameters(order) == 0){
				write(1, "Comanda OK.\n",strlen("Comanda OK.\n"));
			}else{
				write(1, "Comanda KO. Massa paràmetres.\n",strlen("Comanda KO. Massa paràmetres.\n"));
			}
			return 4;
			break;
		case 5:
			write(1, "Option who selected\n",strlen("Option who selected\n"));
			if(getNumberOfParameters(order) == 0){
				write(1, "Comanda OK.\n",strlen("Comanda OK.\n"));
				system("who");
			}else{
				write(1, "Comanda KO. Massa paràmetres.\n",strlen("Comanda KO. Massa paràmetres.\n"));
			}
			system("who");
			return 5;
			break;
		case 6:
			write(1, "Option ps selected\n",strlen("Option ps selected\n"));
			if(getNumberOfParameters(order) == 0){
				write(1, "Comanda OK.\n",strlen("Comanda OK.\n"));
				system("ps");
			}else if(getNumberOfParameters(order) == 2){
				write(1, "Comanda OK.\n",strlen("Comanda OK.\n"));
			}else if(getNumberOfParameters(order) == 1){
				write(1, "Comanda KO.\n",strlen("Comanda KO.\n"));
			}else{
				write(1, "Comanda KO. Massa parámetres.\n",strlen("Comanda KO. Massa parámetres.\n"));
			}
			
			return 6;
			break;
		case 7:
			write(1, "Option cat selected\n",strlen("Option cat selected\n"));
			if(getNumberOfParameters(order) == 1){
				write(1, "Comanda OK.\n",strlen("Comanda OK.\n"));
			}else if(getNumberOfParameters(order) == 0){
				write(1, "Comanda KO. Falta paràmetres.\n",strlen("Comanda KO. Falta paràmetres.\n"));
			}else{
				write(1, "Comanda KO. Massa paràmetres.\n",strlen("Comanda KO. Massa paràmetres.\n"));
			}
			break;
		case 24:
			if(getNumberOfParameters(order) == 1){
				system("ls -l");
			}else if(getNumberOfParameters(order) == 2){
				system("ls -l -a");
			}else{
				write(1, "Comanda KO. Massa paràmetres.\n",strlen("Comanda KO. Massa paràmetres.\n"));
			}
			
			return 24;
			break;
		case 29:
			write(1, "Option pwd selected\n",strlen("Option pwd selected\n"));
			if(getNumberOfParameters(order) == 0){
				write(1, "Comanda OK.\n",strlen("Comanda OK.\n"));
				system("pwd");
			}else{
				write(1, "Comanda KO. Massa paràmetres.\n",strlen("Comanda KO. Massa paràmetres.\n"));
			}
			break;
		case 30:
			write(1, "Option rm selected\n",strlen("Option rm selected\n"));
			if(getNumberOfParameters(order) == 1){
				write(1, "Comanda OK.\n",strlen("Comanda OK.\n"));
			}else if(getNumberOfParameters(order) == 0){
				write(1, "Comanda KO. Falta paràmetres.\n",strlen("Comanda KO. Falta paràmetres.\n"));
			}else{
				write(1, "Comanda KO. Massa paràmetres.\n",strlen("Comanda KO. Massa paràmetres.\n"));
			}
			break;
		case 38:
			write(1, "Exit of the program!\n", strlen("Exit of the program!\n"));
			return -2;
			break;
		case 39:
			write(1, "Option head selected\n",strlen("Option head selected\n"));
			if(getNumberOfParameters(order) == 1){
				write(1, "Comanda OK.\n",strlen("Comanda OK.\n"));
			}else if(getNumberOfParameters(order) == 0){
				write(1, "Comanda KO. Falta paràmetres.\n",strlen("Comanda KO. Falta paràmetres.\n"));
			}else{
				write(1, "Comanda KO. Massa paràmetres.\n",strlen("Comanda KO. Massa paràmetres.\n"));
			}
			break;
		case 40:
			write(1, "Option whoami selected\n",strlen("Option whoami selected\n"));
			if(getNumberOfParameters(order) == 0){
				write(1, "Comanda OK.\n",strlen("Comanda OK.\n"));
			}else{
				write(1, "Comanda KO. Massa paràmetres.\n",strlen("Comanda KO. Massa paràmetres.\n"));
			}
			break;
		case 41:
			write(1, "Option wc selected\n",strlen("Option wc selected\n"));
			if(getNumberOfParameters(order) == 1){
				write(1, "Comanda OK.\n",strlen("Comanda OK.\n"));
			}else if(getNumberOfParameters(order) == 0){
				write(1, "Comanda KO. Falta paràmetres.\n",strlen("Comanda KO. Falta paràmetres.\n"));
			}else{
				write(1, "Comanda KO. Massa paràmetres.\n",strlen("Comanda KO. Massa paràmetres.\n"));
			}
			break;	
		default:
			break;
	}
	
	return sw;
}
