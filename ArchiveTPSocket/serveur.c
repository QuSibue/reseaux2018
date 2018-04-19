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
#include <string.h>

#include "fon.h"     		/* Primitives de la boite a outils */
#include "fonct.h"
#include "time.h"

#define SERVICE_DEFAUT "1111"
#define TAILLEMAX 27

char *mot_cache;																																//on instancie le mot qui sera revelé par le jougados voila
char mot[TAILLEMAX];																																			//on instancie le mot qui correspond a ce qu'on cherche
int nbessaies;
int fini=0;

int changement;

int id_main_socket_serveur;
int id_socket_serveur_client;

char* tampon;



struct sockaddr_in *p_adr_socket;

const int TAILLE_BUFFER = 500*sizeof(char);




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

	id_main_socket_serveur = h_socket(AF_INET,SOCK_STREAM);

	adr_socket(service,"127.0.0.1",SOCK_STREAM,&p_adr_socket);

	h_bind(id_main_socket_serveur,p_adr_socket);

	h_listen(id_main_socket_serveur,10);

	tampon = malloc(TAILLE_BUFFER);


	int debut = 1;

	while (1){
		id_socket_serveur_client = h_accept(id_main_socket_serveur,p_adr_socket);

		if(fork() == 0){
			h_close(id_main_socket_serveur); 																					//on ferme la socket general pour le fils seulement

			h_writes(id_socket_serveur_client,"BIENVENUE DANS LE PENDU | Veuillez choisir votre niveau de difficulté : 1 pour facile, 2 pour moyens, 3 pour difficile",TAILLE_BUFFER);//on ecrit le message de BIENVENUE au client
			h_writes(id_socket_serveur_client,"Veuillez choisir votre niveau de difficulté : 1 pour facile, 2 pour moyens, 3 pour difficile",TAILLE_BUFFER);//le choix de la difficile

			while(!fini){
				if(debut){
					h_reads(id_socket_serveur_client,tampon,TAILLE_BUFFER);
					while(strcmp(tampon,"1") != 0 && strcmp(tampon,"2") != 0 && strcmp(tampon,"3") != 0 ){
						h_writes(id_socket_serveur_client,"Difficuté choisie non valide, ressaisir",TAILLE_BUFFER);
						h_reads(id_socket_serveur_client,tampon,TAILLE_BUFFER);
					}
					//h_writes(id_socket_serveur_client,tampon,TAILLE_BUFFER);
					switch (atoi(tampon)) {
						case 1:
							nbessaies = 12;
							get_mot("./mots.txt",mot);
							mot_cache = malloc(strlen(mot) * sizeof(char) );
							memset(mot_cache,'-',strlen(mot));
							break;
						case 2:
							nbessaies = 10;
							get_mot("./motsmoy.txt",mot);
							mot_cache = malloc(strlen(mot) * sizeof(char) );
							memset(mot_cache,'-',strlen(mot));
							break;
						case 3:
							nbessaies = 8;
							get_mot("./motsdiff.txt",mot);
							mot_cache = malloc(strlen(mot) * sizeof(char) );
							memset(mot_cache,'-',strlen(mot));
							break;
					}
					debut = 0;
				}

				printf("%s\n",mot);
				printf("%s\n",mot_cache);

				h_reads(id_socket_serveur_client,tampon,TAILLE_BUFFER);

				changement = 0;
				for(int i=0;i<=strlen(mot);i++){
					if(mot[i] == tampon[0]){
						changement = 1;
						mot_cache[i] = tampon[0];

					}
				}
				if(!changement){
					nbessaies--;
				}

				fini = (nbessaies <= 0 || (strcmp(mot,mot_cache) == 0));
				if(nbessaies > 0 && (strcmp(mot,mot_cache) != 0)){
					sprintf(tampon,"mot caché :%s | nbessaies: %d", mot_cache,nbessaies);
				}
				else{
					tampon = "FIN";
				}
				h_writes(id_socket_serveur_client,tampon,TAILLE_BUFFER);
			}

			if(nbessaies <= 0){
				h_writes(id_socket_serveur_client,mot,TAILLE_BUFFER);
				h_writes(id_socket_serveur_client,"PERDU !",TAILLE_BUFFER);
			}
			else{
				h_writes(id_socket_serveur_client,mot,TAILLE_BUFFER);
				h_writes(id_socket_serveur_client,"GAGNE !",TAILLE_BUFFER);
			}

			h_close(id_socket_serveur_client);
			exit(0);
		}
		h_close(id_socket_serveur_client);
	}
	h_close(id_main_socket_serveur);



}

/******************************************************************************/
