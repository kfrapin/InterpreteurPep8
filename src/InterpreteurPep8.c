//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Projet sous Licence Apache Version 2.0.	                                            //
//----------------------------------------------------------------------------------------------------------//
//                                                                                                          //
//	Pour plus d'informations concernant cette licence et son utilisation,  //
//	veuillez consulter :                                                                            //
//		- Le document LICENSE                                                                //
//		- http://www.apache.org/licenses/LICENSE-2.0                               //
//                                                                                                          //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * File:   InterpreteurPep8.c
 * Author: kevin, mousseyed
 *
 * DESCRIPTION
 * ----------------------------------------------------------------------------
 * Fichier permettant d'interpréter un fichier de code
 * objet Pep8.
 * ----------------------------------------------------------------------------
 */

//--------------------------------------------------- INCLUDE SYSTEMES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------- INCLUDE PERSONNELS
#include "includes/affichage.h"
#include "includes/constantes.h"
#include "includes/erreurs.h"
#include "includes/fonctions.h"
#include "includes/globales.h"
#include "includes/menu.h"
#include "includes/tests.h"

//--------------------------------------------------- FONCTIONS
#ifndef TEST

int main(int argc, char * * argv) {

	///////////////////////////////////////////////////////////////////// ALLOCATION MEMOIRES

	// On cree un tableau qui represente la memoire utilisee pour stocker
    // le programme Pep8 et le systeme d'exploitation
	memoire = malloc( TAILLE_MEMOIRE_MAX );
	if( memoire == NULL )
	{
#ifdef DEBUG
    printf( "Impossible d'allouer la mémoire de Pep8." RET );
#endif
		return EXIT_FAILURE;
	}
	// On nettoie la memoire
	NettoyerMemoire( memoire, TAILLE_MEMOIRE_MAX );

	// On cree un tableau de la meme taille que la memoire principale
	// pour effectuer du predecodage
	codeDecode = malloc( TAILLE_MEMOIRE_MAX * sizeof( predecodage ) );
	if( codeDecode == NULL )
	{
#ifdef DEBUG
    printf( "Impossible d'allouer la mémoire pour effectuer le prédécodage." RET );
#endif
		return EXIT_FAILURE;
	}
	// On nettoie la memoire
	NettoyerMemoire( ( uchar * ) codeDecode, TAILLE_MEMOIRE_MAX * sizeof( predecodage ) );

	///////////////////////////////////////////////////////////////////// VERIFICATION COMMANDE UTILISATEUR
	if( argc > 1 )
	{
		if( ( strcmp( argv[1], "--os" ) == 0 ) && ( argc > 2 ) )
		// On charge l'OS specifie en parametre
		{
			fichierOS = fopen( argv[2], "rb" );
			if( fichierOS == NULL )
			{
#ifndef DEBUG
	printf( MENU_ERREUR_OUVERTURE RET, argv[2] );
#endif
				return EXIT_FAILURE;
			}

			if( argc > 3 )
			// On joue les programmes passes en parametres
			{
				JouerProgrammesEnParametres( 3, argc, argv );
				return EXIT_SUCCESS;
			}


		}
		else if( strcmp( argv[1], "--os" ) != 0 )
		// On joue les programmes passes en parametres
		{
			fichierOS = fopen( EMPLACEMENT_OS, "rb" );
			if( fichierOS == NULL )
			{
#ifndef DEBUG
	printf( MENU_ERREUR_OUVERTURE RET, EMPLACEMENT_OS );
#endif
				return EXIT_FAILURE;
			}
			JouerProgrammesEnParametres( 1, argc, argv );
			return EXIT_SUCCESS;
		}
		else
		// Mauvaise saisie utilisateur
		{
			puts( ERREUR_CMD_UTILISATEUR );
			return EXIT_FAILURE;
		}
	}

	////////////////////////////////////////////////////////////////////// CHARGEMENT OS
	fichierOS = fopen( EMPLACEMENT_OS, "rb" );
	if( fichierOS == NULL )
	{
#ifndef DEBUG
printf( MENU_ERREUR_OUVERTURE RET, EMPLACEMENT_OS );
#endif
		return EXIT_FAILURE;
	}
	ChargerSystemeExploitation( fichierOS );

	///////////////////////////////////////////////////////////////////// PRESENTATION MENU
	sint toucheSaisie;
	schar * emplacementFichier;
	FILE * fichierACharger;

	while( (toucheSaisie = AfficherMenu( ) )  != 'Q' )
	{
		// On remet les varibales a NULL
		fichierACharger = NULL;
		emplacementFichier = NULL;

		switch( toucheSaisie )
		{
			//------------------------------------ CHARGEMENT DU SYTEME D'EXPLOITATION
			case '1':
				AfficherMenuChargementOS( );
				break;

			//--------------------------------------------------- CHARGEMENT D'UN PROGRAMME
			case '2':
				AfficherMenuChargementProgramme( );
				break;

			//------------------------------------------------------ EXECUTION D'UN PROGRAMME
			case '3':
				registreSP = LireMotEnMemoire( ADR_MEM_SP_USER );
				registrePC = 0;
				puts( MENU_PROGRAMME_DEBUT_EXEC );
				ExecuterInstructions( );
				putchar( RET_CHAR );
				puts( MENU_PROGRAMME_FIN_EXEC );
				break;

			//--------------------------------------------------------------------- SAISIE INCORRECTE
			default:
				puts( MENU_ERREUR_SAISIE );
				break;
		}
	}

    // Caractere de retour chariot a la fin du programme
    putchar( RET_CHAR );

    return (EXIT_SUCCESS);
}

#else
//--------------------------------------------------- FONCTIONS TESTS
int main(int argc, char** argv)
{
	// Affichage permettant de savoir quel type d'entier a la meme taille
	// que les entiers geres nativement par la machine physique
	printf( "Size of ( unsigned int ) : %d bits" RET,  sizeof( unsigned int ) * 8 );
	printf( "Size of ( unsigned long int ) : %d bits" RET,  sizeof( unsigned long int ) * 8 );
	printf( "Size of ( unsigned short int ) : %d bits" RET,  sizeof( unsigned short int ) * 8 );

	printf( "Size of ( signed int ) : %d bits" RET,  sizeof( signed int ) * 8 );
	printf( "Size of ( signed long int ) : %d bits" RET,  sizeof( signed long int ) * 8 );
	printf( "Size of ( signed short int ) : %d bits" RET,  sizeof( signed short int ) * 8 );

    // Mise en place de tests unitaires possible ici
}
#endif
