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
 * Fichier permettant de définir des types de données, permettant de s'adapter
 * facilement à la machine de déploiement.
 * ----------------------------------------------------------------------------
 */


#ifndef TYPEDEFS_H
#define	TYPEDEFS_H

//--------------------------------------------------- TYPEDEFS

//----------------------------------------- ENTIERS
// Type uint : Entier sur 32 bits non signé
typedef unsigned int unint;

// Type uint : Entier sur 32 bits signé
typedef signed int sint;

// Type ssint : Entier sur 16 bits non signé
typedef signed short int ssint;

// Type ssint : Entier sur 16 bits signé
typedef unsigned short int usint;

//----------------------------------------- CARACTERES
// Type uchar : Caractère sur 8 bits non signé
typedef unsigned char uchar;

// Type schar : Caractère sur 8 bits signé
typedef signed char schar;

//--------------------------------------------------- STRUCTURE
// Structure utilise pour le predecodage
typedef struct Predecodage
{
	// Flag permettant de savoir si on decode ou non cette instruction
	//  Si etatPredecodage = DECODAGE_A_FAIRE, on decode l'instruction
	//  Sinon si etatPredecodage = DECODAGE_FAIT, on ne decode pas l'instruction, et on se sert du resultat
	//	Sinon si etatPredecodage = DECODAGE_A_IGNORER, on ne decode pas l'instruction
	unint etatDecodage;

	// Code original predecode
	unint opCodeOriginal;

	// Instruction predecodee
	unint instructionDecodee;

	// Registre predecode
	unint * registreDecode;

	// Mode d'adressage predecode
	unint adressageDecode;

} predecodage;

#endif	/* TYPEDEFS_H */

