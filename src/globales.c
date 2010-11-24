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

//----------------------------------------- CODE DE CONDITIONS
// Tous les codes sont initialisés à zéro
uchar codeN = 0;
uchar codeV = 0;
uchar codeZ = 0;
uchar codeC = 0;

//---------------------------------------- MEMOIRE
uchar * memoire;

//---------------------------------------- REGISTRES
// Tous les registres sont initialisés à zéro
uint registreA = 0;
uint registreX = 0;
uint registrePC = 0;

// Pour empiler sur la pile, il faut décrémenter
// le registreSP; et inversement pour dépiler.
// Initialisation faite dans le programme principal.
uint registreSP;

uchar instructionIR = 0;
uint operandeIR = 0;

FILE * fichierTest = 0;

