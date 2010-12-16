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
 * File:   predecodage.h
 * Author: kevin
 *
 * Created on 5 december 2011
 *
 *
 * DESCRIPTION
 * -------------------------------------------------------------------------------------------------------
 * Fichier regroupant les fonctions permettant d'effectuer du
 * predecodage au sein de l'interpreteur.
 * ------------------------------------------------------------------------------------------------------
 */

#ifndef PREDECODAGE_H_
#define PREDECODAGE_H_

//--------------------------------------------------- INCLUDE SYSTEMES

//--------------------------------------------------- INCLUDE PERSONNELS
#include "typedefs.h"

//--------------------------------------------------- FONCTIONS

// Fonction permettant d'executer une instruction predecodee
unint JouerInstructionPredecodee( unint adresseMemoire );

// Fonction permettant de predeocder une instruction
// et de stocker le code predecode dans la memoire
// codePredecode
unint PredecoderInstruction( unint adresseMemoire );

#endif /* PREDECODAGE_H_ */
