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
 * File:   fonctions.h
 * Author: kevin, mousseyed
 *
 * Created on October 20, 2010, 12:21 PM
 *
 * DESCRIPTION
 * ----------------------------------------------------------------------------
 * Fichier fournissant l'ensemble des définitions des fonctions utlisées
 * dans l'application.
 * ----------------------------------------------------------------------------
 */

#ifndef FONCTIONS_H
#define	FONCTIONS_H

//--------------------------------------------------- INCLUDE SYSTEMES
#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------- INCLUDE PERSONNELS
#include "typedefs.h"


//--------------------------------------------------- FONCTIONS
// Fonction permettant d'ajouter une valeur à un registre
void AdditionerRegistre( unint * registreConcerne, unint valeurAAjouter );

// Fonction permettant de sauvegarder et mettre a jour les registres afin
// d'effectuer un appel a une trap du systeme d'exploitation
void AppelerTrapHandler(  );

// Fonction permettant de charger un programme en memoire
void ChargerProgramme( FILE * fichierProg );

// Fonction permettant de charger l'image du système d'exploitation
// en fin de memoire (ie, derniere instruction a l'adresse TAILLE_MEMOIRE_MAX)
void ChargerSystemeExploitation( FILE * fichierOS );

// Fonction permettant de mettre les codes de condition NZVC
// sous la forme d'un int
unint ConcatenerNZVC( );

// Fonction permettant d'ecrire un mot (16 bits) en memoire
void inline EcrireMotEnMemoire( unint valeur, unint adresse );

// Fonction permettant d'ecrire un octet (8 bits) en memoire
void inline EcrireOctetEnMemoire( unint valeur, unint adresse );

// Fonction permettant de lancer l'execution d'un programme
// ou d'une interruption systeme
// ATTENTION : les registres SP et PC devront avoir ete mis a
// jour auparavant si necessaire
void ExecuterInstructions(  );

// Fonction permettant d'executer l'instruction du groupe 
// GRINST1 au vu de la valeur des 4 derniers bits fournis.
schar ExecuterInstGr1(uchar opcodeDroite);

// Fonction permettant d'executer l'instruction du groupe
// GRINST2 au vu de la valeur des 4 derniers bits fournis.
schar ExecuterInstGr2( uchar opcodeDroite );

// Fonction permettant d'executer l'instruction du groupe
// GRINST3 au vu de la valeur des 4 derniers bits fournis.
schar ExecuterInstGr3( uchar opcodeDroite );

// Fonction permettant d'executer l'instruction du groupe
// GRINST4 au vu de la valeur des 4 derniers bits fournis.
schar ExecuterInstGr4( uchar opcodeDroite );

// Fonction permettant d'executer l'instruction du groupe 
// GRINST5 au vu de la valeur des 4 derniers bits fournis.
schar ExecuterInstGr5( uchar opcodeDroite);

// Fonction permettant d'executer l'instruction du groupe 
// GRINST6 au vu de la valeur des 4 derniers bits fournis.
schar ExecuterInstGr6( uchar opcodeDroite );

// Fonction permettant d'executer l'instruction du groupe 
// GRINST7 au vu de la valeur des 4 derniers bits fournis.
schar ExecuterInstGr7( uchar opcodeDroite );

// Fonction permettant de lancer l'execution des instructions
void ExecuterInstructions( );

// Fonction permettant de jouer les instructions
// sans utiliser le predecodage
schar JouerInstructions( );

// Fonction permettant de jouer les programmes passes
// en parametre lors de l'appel de l'interpreteur
void JouerProgrammesEnParametres( uchar debut, uchar fin, char * * nomsFichier );

// Fonction permettant de lire un mot (16 bits) en mémoire
unint LireMotEnMemoire( unint adresse );

// Fonction permettant de lire un octet (8 bits) en mémoire
uchar LireOctetEnMemoire( unint adresse );

// Fonction permettant de vider la memoire du systeme Pep8
void NettoyerMemoire( uchar * memoireANettoyer, unint tailleMemoire );

// Fonction permetter d'effectuer une negation en complement
// a deux sur un registre
void inline NierRegistreEnComplement( unint * registre );

// Fonctions permettant de mettre à jour les codes de condition 
// N, Z en indiquant la valeur du registre concerné
void inline MettreAJourN( unint valeurRegistre );
void inline MettreAJourZ( unint valeurRegistre );

// Fonctions permettant de mettre à jour les codes de condition 
// V, C en passant la valeur à leur affecter en paramètre
void inline MettreAJourC( unint retenue );
void inline MettreAJourV( unint debordement );


// Fonction permettant de mettre à jour la variable operandeIR,
// afin de récupérer l'opérande de l'instruction en cours
void MettreAJourOperandeIR( );

// Fonction permettant de recopier un fichier dans une zone mémoire
// a partir de l'index indexDebut
void RecopierFichierEnMemoire( FILE * fichier, uchar * memoire, unint indexDebut );

// Fonction permettant mettre à jour le registre PC avec l'opérande
// fournit à l'instruction
void inline RecopierOperandeDansPC( );

// Fonction permettant de recopier le mot contenu dans un registre
// en mémoire
// ATTENTION : l'operande IR doit avoir été mise à jour auparavant
void RecopierMotRegistreEnMemoire( unint * registre, uchar modeAdressage );

// Fonction permettant de recopier la partie droite (8 bits)
// d'un mot (contenu dans un registre) en mémoire
// ATTENTION : l'operande IR doit avoir été mise à jour auparavant
void RecopierOctetRegistreEnMemoire( unint * registre, uchar modeAdressage );

// Fonction permettant de récupérer un octet (8 bits) en mémoire, connaissant
// le mode d'adressage pour y accéder.
// ATTENTION : la variable operandeIR, doit auparavant
// avoir été mise à jour.
uchar RecupererOctetEnMemoire( uchar modeAdressage );

// Fonction permettant de récupérer un mot (16 bits) en mémoire, connaissant
// le mode d'adressage pour y accéder.
// ATTENTION : la variable operandeIR, doit auparavant
// avoir été mise à jour.
unint RecupererMotEnMemoire( uchar modeAdressage );

#endif	/* FONCTIONS_H */

