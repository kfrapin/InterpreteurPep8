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
 * File:   debug.h
 * Author: mousseyed,hevin
 *
 * Created on 29 octobre 2010, 13:07
 *
 * DESCRIPTION
 * ----------------------------------------------------------------------------
 * Fonction appelées lors de débogage, pour afficher la valeur des resgitres,
 * code de conditions,...
 * ----------------------------------------------------------------------------
 */

#ifndef DEBUG_H
#define	DEBUG_H

//--------------------------------------------------- FONCTIONS
// Fonctions permettant d'afficher la valeur
// des codes de conditions
void inline AfficherValeurCodeN( );
void inline AfficherValeurCodeZ( );
void inline AfficherValeurCodeV( );
void inline AfficherValeurCodeC( );

// Fonction permettant d'afficher la valeur
// du registre contenant l'opérande
void inline AfficherValeurOperandeIR( );

// Fonction permettant d'afficher la valeur
// du registre A
void inline AfficherValeurRegistreA( );

// Fonction permettant d'afficher la valeur
// du registre PC
void inline AfficherValeurRegistrePC( );

// Fonction permettant d'afficher la valeur
// du registre SP
void inline AfficherValeurRegistreSP( );

// Fonction permettant d'afficher la valeur
// du registre X
void inline AfficherValeurRegistreX( );

#endif	/* DEBUG_H */

