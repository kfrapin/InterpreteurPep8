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
 * File:   InterpreteurPep8.c
 * Author: kevin, mousseyed
 *
 * DESCRIPTION
 * ----------------------------------------------------------------------------
 * Fichier permettant d'interpréter un fichier de code
 * objet Pep8.
 * ----------------------------------------------------------------------------
 */


#include <stdio.h>
#include <stdlib.h>

#include "includes/affichage.h"
#include "includes/constantes.h"
#include "includes/erreurs.h"
#include "includes/fonctions.h"
#include "includes/globales.h"
#include "includes/tests.h"


#ifndef TEST


int main(int argc, char** argv) {

    // Fichier fourni en paramètre ?
	if( argc < 3 )
	{
		puts( "La syntaxe attendue est : ./interpreteur <imageOS> <fichier>" RET );
		return EXIT_FAILURE;
	}

	// On créé un tableau qui représente la mémoire utilisée pour stocker
    // le programme Pep8 et le systeme d'exploitation
	memoire = malloc(TAILLE_MEMOIRE_MAX);
        if( memoire == NULL )
        {
#ifdef DEBUG
    printf( "Impossible d'allouer la mémoire de Pep8." RET );
#endif
            return EXIT_FAILURE;
        }

	// On charge le systeme d'exploitation Pep8
	uchar * imageOS = ( uchar * ) argv[1];
	FILE * fichierOS = ( FILE * ) fopen( imageOS, "rb" );
	if( fichierOS == NULL )
	{
		printf( "Impossible d'ouvrir le fichier : %s" RET, imageOS );
		return EXIT_FAILURE;
	}
	ChargerSystemeExploitation( fichierOS );

	// On récupère le nom de fichier fourni en paramètre
	uchar * nomFichierEntree = ( uchar *  ) argv[2];

	// On tente d'ouvrir ce fichier en lecture de manière
	FILE * fichierEntree = ( FILE * ) fopen( nomFichierEntree, "rb" );
	if( fichierEntree == NULL )
	{
		printf( "Impossible d'ouvrir le fichier : %s" RET, nomFichierEntree );
		return EXIT_FAILURE;
	}

        // On recopie le fichier en mémoire a partir de l'adresse 0
        RecopierFichierEnMemoire( fichierEntree, memoire, 0 );

        // On interprète les insctruction
        registreSP = LireMotEnMemoire( ADR_MEM_SP_USER );
        registrePC = 0;
        instructionIR = memoire[registrePC++];

        // Variable permettant de savoir si l'exécution s'est bien passée
        schar retourExec = 0;


        // L'overhead est considérable
        while( (instructionIR != STOP) && (retourExec != EXECUTION_KO) )
        {
#ifdef DEBUG
    printf( RET "> Instruction lue : %d." RET, instructionIR );
    printf( SEP_FIN RET );
#endif
            // On récupère les 4 bits de gauche de l'instruction
            uchar opcodeGauche =  ( instructionIR >> 4 );

            // On récupère les 4 bits de droite de l'instruction
            uchar opcodeDroite = 15 & instructionIR;

            switch( opcodeGauche )
            {
            	case GRINST1:
            		retourExec = ExecuterInstGr1( opcodeDroite );
            		break;

            	case GRINST2:
            		retourExec = ExecuterInstGr2( opcodeDroite );
            		break;

            	case GRINST3:
            		retourExec = ExecuterInstGr3( opcodeDroite );
            		break;

            	case GRINST4:
            		retourExec = ExecuterInstGr4( opcodeDroite );
            		break;

            	case GRINST5:
            		retourExec = ExecuterInstGr5( opcodeDroite );
            		break;

            	case GRINST6:
            		retourExec = ExecuterInstGr6( opcodeDroite );
            		break;

            	case GRINST7:
            		 retourExec = ExecuterInstGr7( opcodeDroite );
            		 break;

            	case ADDR_DEB:
            		retourExec = ExecuterADDr( opcodeDroite );
            		break;

            	case SUBR_DEB:
            		retourExec = ExecuterSUBr( opcodeDroite );
            		break;

            	case ANDR_DEB:
            		retourExec = ExecuterANDr( opcodeDroite );
            		break;

            	case ORR_DEB:
            		retourExec = ExecuterORr( opcodeDroite );
            		break;

            	case CPR_DEB:
            		retourExec = ExecuterCPr( opcodeDroite );
            		break;

            	case LDR_DEB:
            		retourExec = ExecuterLDr( opcodeDroite );
            		break;

            	case LDBYTER_DEB:
            		retourExec = ExecuterLDBYTEr( opcodeDroite );
            		break;

            	case STR_DEB:
            		retourExec = ExecuterSTr( opcodeDroite );
            		break;

            	case STBYTER_DEB:
            		retourExec = ExecuterSTBYTEr( opcodeDroite );
            		break;
            }

            instructionIR = memoire[registrePC++];
        }

    // Retour a la ligne avant la fin du programme
    printf( RET );

    return (EXIT_SUCCESS);
}

#else

int main(int argc, char** argv)
{
    // TESTS OK
    //---------------------
    testDeterminerInstGr1();
}
#endif
