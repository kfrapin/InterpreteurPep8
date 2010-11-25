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
 * File:   menu.h
 * Author: kevin
 *
 * Created on 25 Novembre 2010, 11:23
 *
 * DESCRIPTION
 * ---------------------------------------------------------------------------------------------------------
 * Fichier contenant des constantes et fonctions utiles pour l'affichage
 * d'un menu interagissant avec l'utilisateur.
 * --------------------------------------------------------------------------------------------------------
 */

#ifndef MENU_H_
#define MENU_H_

//--------------------------------------------------- INCLUDE SYSTEMES
#include <stdio.h>

//--------------------------------------------------- CONSTANTES

// Constante utilisee pour savoir si l'utilisateur souhaite
// charger le systeme d'exploitation ou un programme
// et adpater le texte du menu en consequence
#define CHARGEMENT_OS		(1)
#define CHARGEMENT_PROG	(2)

//--------------------------------------------------- FONCTIONS

// Fonction permettant de demander a l'utilisateur ou se trouve
// le fichier (OS ou programme) a charger
schar *  AfficherDemandeEmplacement( uchar typeChargement );

// Fonction permettant d'afficher un menu a l'utilisateur afin qu'il
// choisisse ce qu'il souhaite faire parmi :
//	- Charger le systeme d'exploitation
//	- Charger un programme
//  - Executer le prgramme charge
//	- Quitter le menu
sint AfficherMenu( );

// Fonction permettant d'afficher le menu pour demander
// a l'utilisateur l'emplacement de l'image du systeme d'exploitation
void AfficherMenuChargementOS( );

// Fonction permettant d'afficher le menu pour demander
// a l'utilisateur l'emplacement du programme a charger
void AfficherMenuChargementProgramme( );


#endif /* MENU_H_ */
