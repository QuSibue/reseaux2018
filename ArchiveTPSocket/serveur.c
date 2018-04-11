/******************************************************************************/
/*			Application: ....			              */
/******************************************************************************/
/*									      */
/*			 programme  SERVEUR 				      */
/*									      */
/******************************************************************************/
/*									      */
/*		Auteurs :  ....						      */
/*		Date :  ....						      */
/*									      */
/******************************************************************************/

#include<stdio.h>
#include<string.h>
#include <curses.h>

#include<sys/signal.h>
#include<sys/wait.h>
#include<stdlib.h>

#include "fon.h"     		/* Primitives de la boite a outils */
#include "fonct.h"
#include "time.h"

#define SERVICE_DEFAUT "1111"
#define TAILLEMAX 27

char *mot_cache;																																//on instancie le mot qui sera revelé par le jougados voila
char mot[TAILLEMAX];																																			//on instancie le mot qui correspond a ce qu'on cherche
int nbessaies;
int fini;

int id_socket;
struct sockaddr_in *p_adr_socket;
struct sockaddr_in *p_adr_client;

void serveur_appli (char *service);   /* programme serveur */


/******************************************************************************/
/*---------------- programme serveur ------------------------------*/

int main(int argc,char *argv[])
{
	srand(time(NULL));
	char *service= SERVICE_DEFAUT; /* numero de service par defaut */


	/* Permet de passer un nombre de parametre variable a l'executable */
	switch (argc)
 	{
   	case 1:
		  printf("defaut service = %s\n", service);
		  		  break;
		case 2:
		  service=argv[1];
            break;

   	default :
		  printf("Usage:serveur service (nom ou port) \n");
		  exit(1);
 	}

	/* service est le service (ou numero de port) auquel sera affecte
	ce serveur*/

	serveur_appli(service);
}


/******************************************************************************/
void serveur_appli(char *service)

/* Procedure correspondant au traitemnt du serveur de votre application */

{

/* A completer ... */

	id_socket = h_socket(AF_INET,SOCK_STREAM);
	adr_socket(service,"127.0.0.1",SOCK_STREAM,&p_adr_socket);
	h_bind(id_socket,p_adr_socket);

	h_listen(id_socket,10);
	h_accept(id_socket,p_adr_client);

	get_mot("./mots.txt",mot);
	mot_cache = malloc(strlen(mot) * sizeof(char) );
	memset(mot_cache,'-',strlen(mot));

	while (!fini){

		fini = nbessaies = 0 || (strcmp(mot,mot_cache) == 0);
	}



}

/******************************************************************************/
