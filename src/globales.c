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
 * File:   globales.c
 * Author: kevin, mousseyed
 *
 * Created on 28 octobre 2010, 16:13
 *
 * DESCRIPTION
 * ----------------------------------------------------------------------------
 * Fichier permettant d'initialiser les variables globales de l'application,
 * utiles pour manipuler les registres, la mémoire, et les codes de condition
 * partout dans le programme.
 * ----------------------------------------------------------------------------
 */

//--------------------------------------------------- INCLUDE SYSTEMES

//--------------------------------------------------- INCLUDE PERSONELS
#include "includes/globales.h"
#include "includes/constantes.h"


//--------------------------------------------------- GLOBALES
// Variables permettant de savoir si CHARI
// doit lire sur l'entree standard ou dans
// le fichier fichierEntree
uchar entreeLecture = ENTREE_STDIN;

// Fichier dans lequel va lire CHARI lors d'un
// chargement de programme
FILE * fichierEntree = NULL;

// Fichier contenant l'image binaire du systeme d'exploitation
// Pep8
FILE * fichierOS;

// Reserve pour stocker des emplacements de fichiers
char saisie [1024];

//----------------------------------------- CODE DE CONDITIONS
// Tous les codes sont initialisés à zéro
unint codeN = 0;
unint codeV = 0;
unint codeZ = 0;
unint codeC = 0;

//---------------------------------------- MEMOIRE
uchar * memoire;

//---------------------------------------- REGISTRES
// Tous les registres sont initialisés à zéro
unint registreA = 0;
unint registreX = 0;
unint registrePC = 0;

// Pour empiler sur la pile, il faut décrémenter
// le registreSP; et inversement pour dépiler.
// Initialisation faite dans le programme principal.
unint registreSP;

uchar instructionIR = 0;
unint operandeIR = 0;

//---------------------------------------- PREDECODAGE
predecodage * codePredecode;

