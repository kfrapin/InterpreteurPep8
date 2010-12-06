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
 * File:   definitions.h
 * Author: mousseyed, kevin
 *
 * Created on November 11, 2010
 *
 * DESCRIPTION
 * --------------------------------------------------------------------------------------------------------------
 * Fichier contenant toutes les constantes définies pour l'affichage,
 * ainsi que les fonctions interagissant avec l'utilisateur.
 * --------------------------------------------------------------------------------------------------------------
 */

#ifndef AFFICHAGE_H_
#define AFFICHAGE_H_
//--------------------------------------------------- INCLUDE PERSONNELS
#include "typedefs.h"

//--------------------------------------------------------- ERREUR COMMANDE UTILISATEUR
#define ERREUR_CMD_UTILISATEUR "La syntaxe attendue est : InterpreteurPep8 [--os <imageOS>] [ <fichierProgramme> [...] ]"

//--------------------------------------------------------- CONSTANTES AFFICHAGE GENERAL
// Definition de la tabulation
#define TAB "\t"

// Definition du retour chariot
#define RET "\n"

// Definition du retour chariot (caractere)
#define RET_CHAR '\n'

// Definition du separateur permettant d'indiquer que l'on est avant
// une mise a jour d'une variable
#define SEP_AVT_MAJ "------------------------ AVANT MAJ DE : "

// Definition du separateur permettant d'indiquer que l'on est apres
// une mise a jour d'une variable
#define SEP_APR_MAJ "------------------------ APRES MAJ DE : "

// Definition du separateur permettant d'indiquer les variables concernées
// par un affichage de leur valeur
#define SEP_FIN "------------------------"


//--------------------------------------------------------- CONSTANTES AFFICHAGE MENU
// Choix numero 1 du menu
#define MENU_CHOIX_1 "+ 1 - Charger le systeme d'exploitation"

// Choix numero 2 du menu
#define MENU_CHOIX_2 "+ 2 - Charger un programme"

// Choix numero 3 du menu
#define MENU_CHOIX_3 "+ 3 - Executer le programme charge"

// Choix numero  du menu
#define MENU_CHOIX_4 "Q - Quitter le programme"

// Systeme d'exploitation charge
#define MENU_OS_CHARGE "> Systeme d'exploitation charge."

// Programme charge
#define MENU_PROGRAMME_CHARGE "> Programme charge."

// Message d'erreur de saisie
#define MENU_ERREUR_SAISIE "> Erreur de saisie, veuillez recommencer."

// Message d'erreur si impossible d'ouvrir le fichier
#define MENU_ERREUR_OUVERTURE "> Impossible d'ouvrir le fichier : %s."

// Separateur pour l'affichage du menu
#define MENU_SEP "------------------------------------------------"

// Separateur pour le debut d'execution du programme
#define MENU_PROGRAMME_DEBUT_EXEC "////////////////////////////// DEBUT EXECUTION"

// Separateur pour la fin d'execution du programme
#define MENU_PROGRAMME_FIN_EXEC "////////////////////////////// FIN EXECUTION"


//--------------------------------------------------------- CONSTANTES AFFICHAGE MODE BATCH
// Separateur pour le debut d'execution du programme
#define BATCH_PROGRAMME_DEBUT_EXEC "////////////////////////////// DEBUT EXECUTION : %s"

// Separateur pour la fin d'execution du programme
#define BATCH_PROGRAMME_FIN_EXEC "////////////////////////////// FIN EXECUTION : %s"

#endif /* AFFICHAGE_H_ */
