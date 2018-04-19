/******************************************************************************/
/*			Application: ...					*/
/******************************************************************************/
/*									      */
/*			 programme  CLIENT				      */
/*									      */
/******************************************************************************/
/*									      */
/*		Auteurs : ... 					*/
/*									      */
/******************************************************************************/


#include <stdio.h>
#include <curses.h> 		/* Primitives de gestion d'ecran */
#include <sys/signal.h>
#include <sys/wait.h>
#include<stdlib.h>
#include <string.h>

#include "fon.h"     		/* Primitives de la boite a outils */
#include "fonct.h"
#include "time.h"
#define SERVICE_DEFAUT "1111"
#define SERVEUR_DEFAUT "127.0.0.1"


int id_socket;
struct sockaddr_in *p_adr_socket;

int jeu = 1;

char* tampon;
char lettre;

const int TAILLE_BUFFER = 500*sizeof(char);

void client_appli (char *serveur, char *service);


/*****************************************************************************/
/*--------------- programme client -----------------------*/

int main(int argc, char *argv[])
{

	char *serveur= SERVEUR_DEFAUT; /* serveur par defaut */
	char *service= SERVICE_DEFAUT; /* numero de service par defaut (no de port) */


	/* Permet de passer un nombre de parametre variable a l'executable */
	switch(argc)
	{
 	case 1 :		/* arguments par defaut */
		  printf("serveur par defaut: %s\n",serveur);
		  printf("service par defaut: %s\n",service);
		  break;
  	case 2 :		/* serveur renseigne  */
		  serveur=argv[1];
		  printf("service par defaut: %s\n",service);
		  break;
  	case 3 :		/* serveur, service renseignes */
		  serveur=argv[1];
		  service=argv[2];
		  break;
    default:
		  printf("Usage:client serveur(nom ou @IP)  service (nom ou port) \n");
		  exit(1);
	}

	/* serveur est le nom (ou l'adresse IP) auquel le client va acceder */
	/* service le numero de port sur le serveur correspondant au  */
	/* service desire par le client */

	client_appli(serveur,service);
}

/*****************************************************************************/
void client_appli (char *serveur,char *service)

/* procedure correspondant au traitement du client de votre application */
{

	id_socket = h_socket(AF_INET,SOCK_STREAM);
	adr_socket(service,serveur,SOCK_STREAM,&p_adr_socket);
	h_connect(id_socket,p_adr_socket);

	tampon=malloc(TAILLE_BUFFER);
	int debut = 1;

	for(int i=0;i<2;i++){
		h_reads(id_socket,tampon,TAILLE_BUFFER);
		printf("Serveur : %s\n",tampon);
	}

		while(1){
			if(debut){
				scanf("%s",tampon);
				h_writes(id_socket,tampon,TAILLE_BUFFER);

				while(strcmp(tampon,"1") != 0 && strcmp(tampon,"2") != 0 && strcmp(tampon,"3") != 0 ){
					h_reads(id_socket,tampon,TAILLE_BUFFER);
					printf("Serveur : %s\n",tampon);
					scanf("%s",tampon);
					h_writes(id_socket,tampon,TAILLE_BUFFER);
				}
				printf("Difficulté choisie : %s\n",tampon);
				switch (atoi(tampon)) {
					case 1:
						printf("Nombre d'essais : 12\n");
						break;
					case 2:
						printf("Nombre d'essais : 10\n");
						break;
					case 3:
						printf("Nombre d'essais : 8\n");
						break;
				}
				debut = 0;
			}

				printf("Proposer une lettre : ");
				scanf("%s",tampon);
				while(strlen(tampon) > 1){
					printf("Un seul caractères doit etre saisi, recommencer\n");
					scanf("%s",tampon);
				}
				h_writes(id_socket,tampon,TAILLE_BUFFER);

				h_reads(id_socket,tampon,TAILLE_BUFFER);
				if (strcmp(tampon, "FIN") == 0) {
      		printf("Fin de partie\n");
					jeu = 0;
      		break;
    		}else{
					printf("%s\n",tampon);
				}
			}

	if(!jeu){
		h_reads(id_socket,tampon,TAILLE_BUFFER);
		printf("Le mot à trouver était %s\n",tampon);

		h_reads(id_socket,tampon,TAILLE_BUFFER);
		printf("Vous avez %s\n",tampon);
	}
	h_close(id_socket);

}

/*****************************************************************************/
