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
 * File:   menu.c
 * Author: kevin
 *
 * Created on 25 Novembre 2010, 11:23
 *
 * DESCRIPTION
 * ---------------------------------------------------------------------------------------------------------
 * Fichier definissant les fonctions permettant d'afficher un menu
 * pour interagir avec l'utilisateur.
 * --------------------------------------------------------------------------------------------------------
 */

//--------------------------------------------------- INCLUDE SYSTEMES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------- INCLUDE PERSONNELS
#include "includes/affichage.h"
#include "includes/globales.h"
#include "includes/menu.h"

//--------------------------------------------------- FONCTIONS

// Fonction permettant de demander a l'utilisateur ou se trouve
// le fichier (OS ou programme) a charger
schar *  AfficherDemandeEmplacement( uchar typeChargement )
{
	// Entete du menu
	puts( MENU_SEP );
	if( typeChargement == CHARGEMENT_OS )
	{
		puts( "> Entrez l'emplacement de l'image du systeme" );
		puts( "d'exploitation :" );
	}
	else if( typeChargement == CHARGEMENT_PROG )
	{
		puts( "> Entrez l'emplacement du programme a charger :" );
	}
	puts( MENU_SEP );

	// Recuperation de l'emplacement
	char saisie [1024];

	// On ignore les retours a la ligne
	schar toucheSaisie;
	while( ( toucheSaisie = getchar( ) ) == '\n'  );

	// On stocke le premier caractere de l'emplacement
	saisie[0] = toucheSaisie;

	// On recupere le reste de l'emplacement
	fgets( ( saisie + 1 ) , 1023, stdin );

	// On supprime le '\n' present a la fin
	char * retourChariot = strchr( saisie, '\n'  );
	if ( retourChariot )
	{
		( * retourChariot ) = 0;
	}

	return ( ( schar * ) saisie );
}

// Fonction permettant d'afficher un menu a l'utilisateur afin qu'il
// choisisse ce qu'il souhaite faire parmi :
//	- Charger le systeme d'exploitation
//	- Charger un programme
//  - Executer le programme charge
//	- Quitter le menu
sint AfficherMenu( )
{
	// Une ligne de separation
	puts( "" );

	// Entete du menu
	puts( MENU_SEP );
	puts( "Que souhaitez-vous faire ?");
	puts( MENU_SEP );

	// Differents choix proposes
	puts( MENU_CHOIX_1 );
	puts( MENU_CHOIX_2 );
	puts( MENU_CHOIX_3 );
	puts( " ");
	puts( MENU_CHOIX_4 );

	// Separateur de fin du menu
	puts( MENU_SEP );

	// On ignore les retour a la ligne
	sint toucheSaisie;
	while( ( toucheSaisie = getchar( ) ) == '\n'  );

	// On recupere le reste de la chaine si plus d'un caractere a ete saisi
	char vidageBuffer [1024];
	fgets( vidageBuffer, 1024, stdin );

	return ( toucheSaisie  );
}

// Fonction permettant d'afficher le menu pour demander
// a l'utilisateur l'emplacement de l'image du systeme d'exploitation
void AfficherMenuChargementOS( )
{
	// On demande l'emplacement a l'utilisateur
	schar *emplacementFichier = AfficherDemandeEmplacement( CHARGEMENT_OS );

	// On tente d'ouvrir le fichier
	fichierOS = fopen( emplacementFichier, "rb" );
	if( fichierOS == NULL )
	{
#ifndef DEBUG
		printf( MENU_ERREUR_OUVERTURE RET, emplacementFichier );
#endif
	}
	else
	{
		// On charge l'OS
		ChargerSystemeExploitation( fichierOS );
#ifndef DEBUG
	puts( MENU_OS_CHARGE );
#endif
	}
}

// Fonction permettant d'afficher le menu pour demander
// a l'utilisateur l'emplacement du programme a charger
void AfficherMenuChargementProgramme( )
{
	// On demande l'emplacement du fichier
	schar * emplacementFichier = AfficherDemandeEmplacement( CHARGEMENT_PROG );

	// On tente d'ouvrir le fichier
	FILE * fichierACharger = fopen( emplacementFichier, "rb" );
	if( fichierACharger == NULL )
	{
#ifndef DEBUG
		printf( MENU_ERREUR_OUVERTURE RET, emplacementFichier );
#endif
	}
	else
	{
		// On charge le programe
		ChargerProgramme( fichierACharger );
#ifndef DEBUG
	puts( MENU_PROGRAMME_CHARGE );
#endif
	}
}

