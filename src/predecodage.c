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
 * File:   predecodage.c
 * Author: kevin
 *
 * Created on 5 Decembre 2010
 *
 * DESCRIPTION
 * ---------------------------------------------------------------------------------------------------------
 * Fichier definissant les fonctions permettant d'effectuer du
 * predecodage au sein de l'interpreteur.
 * --------------------------------------------------------------------------------------------------------
 */

//--------------------------------------------------- INCLUDE SYSTEMES
#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------- INCLUDE PERSONNELS
#include "includes/constantes.h"
#include "includes/predecodage.h"

//--------------------------------------------------- FONCTIONS
// Fonction permettant de tester si le code soumis
// a deja ete predecode, et le predecoder sinon
// Retourner le resultat de l'operation
unint PredecoderEtRetourner( unint adresseMemoire )
{
#ifdef DEBUG
    puts( "+ PredecoderEtRetourner.");
#endif

    return EXIT_SUCCESS;

#ifdef DEBUG
    puts( "- PredecoderEtRetourner.");
#endif
}
