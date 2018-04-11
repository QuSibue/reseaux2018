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
#include <curses.h>

#include<sys/signal.h>
#include<sys/wait.h>
#include<stdlib.h>

#include "fon.h"     		/* Primitives de la boite a outils */
#include "fonct.h"

#define SERVICE_DEFAUT "1111"

char *mot_cache;																																//on instancie le mot qui sera revelé par le jougados voila
char *mot;																																			//on instancie le mot qui correspond a ce qu'on cherche
int nbessaies;																																// nb essais possible

void serveur_appli (char *service);   /* programme serveur */


/******************************************************************************/
/*---------------- programme serveur ------------------------------*/

int main(int argc,char *argv[])
{

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
	get_mot("mot.txt",mot);
	printf("%s",mot);

	serveur_appli(service);
}


/******************************************************************************/
void serveur_appli(char *service)

/* Procedure correspondant au traitemnt du serveur de votre application */

{

/* A completer ... */

}

/******************************************************************************/
