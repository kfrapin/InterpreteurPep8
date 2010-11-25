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

int main(int argc, char** argv) {

	///////////////////////////////////////////////////////////////////// ALLOCATION MEMOIRE

	// On cree un tableau qui represente la memoire utilisee pour stocker
    // le programme Pep8 et le systeme d'exploitation
	memoire = malloc(TAILLE_MEMOIRE_MAX);
	if( memoire == NULL )
	{
#ifdef DEBUG
    printf( "Impossible d'allouer la mémoire de Pep8." RET );
#endif
		return EXIT_FAILURE;
	}

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

//--------------------------------------------------- FONCTIONS TESTS
#else

int main(int argc, char** argv)
{
    // Mise en place de tests unitaires possible ici
}
#endif
