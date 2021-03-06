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
 * File:   debug.c
 * Author: mousseyed,hevin
 *
 * Created on 29 octobre 2010, 13:07
 *
 * DESCRIPTION
 * ---------------------------------------------------------------------------------------------------------------
 * Fonction appelées lors de débogage, pour afficher la valeur des resgitres,
 * code de conditions,...
 * ---------------------------------------------------------------------------------------------------------------
 */

//--------------------------------------------------- INCLUDE SYSTEMES
#include <stdio.h>

//--------------------------------------------------- INCLUDE PERSONNELS
#include "includes/affichage.h"
#include "includes/constantes.h"
#include "includes/debug.h"
#include "includes/globales.h"

//--------------------------------------------------- FONCTIONS
// Fonctions permettant d'afficher la valeur 
// du code de condition C
void inline AfficherValeurCodeC( )
{
    printf( TAB "Valeur codeC : %d." RET, codeC );
}

// Fonctions permettant d'afficher la valeur 
// du code de condition N
void inline AfficherValeurCodeN( )
{
    printf( TAB "Valeur codeN : %d." RET, codeN );
}
// Fonctions permettant d'afficher la valeur 
// du code de condition V
void inline AfficherValeurCodeV( )
{
    printf( TAB "Valeur codeV : %d." RET, codeV );
}

// Fonctions permettant d'afficher la valeur 
// du code de condition Z
void inline AfficherValeurCodeZ( )
{
    printf( TAB "Valeur codeZ : %d." RET, codeZ );
}

// Fonction permettant d'afficher la valeur
// du registre contenant l'opérande
void inline AfficherValeurOperandeIR( )
{
    printf( TAB "Valeur operandeIR : %d." RET, (ssint) operandeIR);
}



// Fonction permettant d'afficher la valeur
// du registre A
void inline AfficherValeurRegistreA( )
{
    printf( TAB "Valeur registreA : %d." RET, (ssint) registreA);
}

// Fonction permettant d'afficher la valeur
// du registre PC
void inline AfficherValeurRegistrePC( )
{
    printf( TAB "Valeur registrePC : %X." RET, (usint) registrePC);
}

// Fonction permettant d'afficher la valeur
// du registre SP
void inline AfficherValeurRegistreSP( )
{
    printf( TAB "Valeur registreSP : %X." RET, (usint) registreSP);
}

// Fonction permettant d'afficher la valeur
// du registre X
void inline AfficherValeurRegistreX( )
{
    printf( TAB "Valeur registreX : %d." RET, (ssint) registreX);
}
   
