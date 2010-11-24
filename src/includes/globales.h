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
 * File:   globales.h
 * Author: kevin, mousseyed
 *
 * Created on 28 octobre 2010, 16:13
 *
 * DESCRIPTION
 * ----------------------------------------------------------------------------
 * Fichier permettant de définir les variables globales de l'application,
 * utiles pour manipuler les registres, la mémoire, et les codes de condition
 * partout dans le programme.
 * ----------------------------------------------------------------------------
 */

#ifndef GLOBALES_H
#define	GLOBALES_H

//--------------------------------------------------- INCLUDE SYSTEMES
#include <stdio.h>

//--------------------------------------------------- INCLUDE PERSONNELS
#include "typedefs.h"

//--------------------------------------------------- GLOBALES

//----------------------------------------- CODE DE CONDITIONS
extern uchar codeN;
extern uchar codeV;
extern uchar codeZ;
extern uchar codeC;

//---------------------------------------- MEMOIRE
extern uchar * memoire;

//---------------------------------------- REGISTRES
extern uint registreA;
extern uint registreX;
extern uint registrePC;
extern uint registreSP;
extern uchar instructionIR;
extern uint operandeIR;

extern FILE * fichierTest;

#endif	/* GLOBALES_H */

