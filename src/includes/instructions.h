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
 * File:   instructions.h
 * Author: kevin
 *
 * Created on 14 december 2011
 *
 *
 * DESCRIPTION
 * -------------------------------------------------------------------------------------------------------
 * Fichier regroupant les fonctions permettant d'executer les
 * instructions du jeu d'instructions Pep8
 * ------------------------------------------------------------------------------------------------------
 */

#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

// Fonction permettant d'executer l'instruction ADDr
schar ExecuterADDr( unint * registreConcerne, uchar modeAdressage );

// Fonction permettant d'executer l'instruction ADDSP
void inline ExecuterADDSP( uchar modeAdressage );

// Fonction permettant d'executer l'instruction ANDr
schar ExecuterANDr( unint * registreConcerne, uchar modeAdressage );

// Fonction permettant d'executer l'instruction ASLr
void inline ExecuterASLr( unint * registreConcerne );

// Fonction permettant d'executer l'instruction ASRr
void inline ExecuterASRr( unint * registreConcerne );

// Fonction permettant d'executer l'instruction BR
void inline ExecuterBR( uchar modeAdressage );

// Fonction permettant d'executer l'instruction BRC
void inline ExecuterBRC( uchar modeAdressage );

// Fonction permettant d'executer l'instruction BREQ
void inline ExecuterBREQ( uchar modeAdressage );

// Fonction permettant d'executer l'instruction BRGE
void inline ExecuterBRGE( uchar modeAdressage );

// Fonction permettant d'executer l'instruction BRGT
void inline ExecuterBRGT( uchar modeAdressage );

// Fonction permettant d'executer l'instruction BRLE
void inline ExecuterBRLE( uchar modeAdressage );

// Fonction permettant d'executer l'instruction BRLT
void inline ExecuterBRLT( uchar modeAdressage );

// Fonction permettant d'executer l'instruction BRNE
void inline ExecuterBRNE( uchar modeAdressage );

// Fonction permettant d'executer l'instruction BRNE
void inline ExecuterBRV( uchar modeAdressage );

// Fonction permettant d'executer l'instruction CALL
void inline ExecuterCALL( uchar modeAdressage );

// Fonction permettant d'executer l'instruction CHARI
schar ExecuterCHARI( uchar modeAdressage );

// Fonction permettant d'executer l'instruction CHARO
schar ExecuterCHARO( uchar modeAdressage );

// Fonction permettant d'executer l'instruction CPr
schar ExecuterCPr( unint * registreConcerne, uchar modeAdressage );

// Fonction permettant d'executer l'instruction LDBYTEr
schar ExecuterLDBYTEr( unint * registreConcerne, uchar modeAdressage );

// Fonction permettant d'executer l'instruction LDr
schar ExecuterLDr( unint * registreConcerne, uchar modeAdressage );

// Fonction permettant d'executer l'instruction MOVFLGA
void inline ExecuterMOVFLGA( );

// Fonction permettant d'executer l'instruction MOVSPA
void inline ExecuterMOVSPA( );

// Fonction permettant d'executer l'instruction NEGr
void inline ExecuterNEGr( unint * registreConcerne );

// Fonction permettant d'executer l'instruction NOTr
void inline ExecuterNOTr( unint * registreConcerne );

// Fonction permettant d'executer l'instruction ORr
schar ExecuterORr( unint * registreConcerne, uchar modeAdressage );

// Fonction permettant d'executer l'instruction RETTR
schar ExecuterRETTR(  );

// Fonction permettant d'executer l'instruction ROLr
schar ExecuterROLr( unint * registreConcerne );

// Fonction permettant d'executer l'instruction RORr
schar ExecuterRORr( unint *  registreConcerne );

// Fonction permettant d'executer l'instruction STBYTEr
schar ExecuterSTBYTEr( unint * registreConcerne, uchar modeAdressage );

// Fonction permettant d'executer l'instruction RETr
schar ExecuterRETn( unint valeurN );

// Fonction permettant d'executer l'instruction STr
schar ExecuterSTr( unint * registreConcerne, uchar modeAdressage );

// Fonction permettant d'executer l'instruction r
schar ExecuterSUBr( unint * registreConcerne, uchar modeAdressage );

// Fonction permettant d'executer l'instruction SUBSP
void inline ExecuterSUBSP( uchar modeAdressage );

#endif /* INSTRUCTIONS_H_ */
