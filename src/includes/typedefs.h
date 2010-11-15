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
typedef unsigned int uint;

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

#endif	/* TYPEDEFS_H */

