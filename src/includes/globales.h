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
extern uchar entreeLecture;
extern FILE * fichierEntree;
extern FILE * fichierOS;
extern char saisie [1024];

//----------------------------------------- CODE DE CONDITIONS
extern unint codeN;
extern unint codeV;
extern unint codeZ;
extern unint codeC;

//---------------------------------------- MEMOIRE
extern uchar * memoire;

//---------------------------------------- REGISTRES
extern unint registreA;
extern unint registreX;
extern unint registrePC;
extern unint registreSP;
extern uchar instructionIR;
extern unint operandeIR;

//---------------------------------------- PREDECODAGE
predecodage * codePredecode;

#endif	/* GLOBALES_H */

