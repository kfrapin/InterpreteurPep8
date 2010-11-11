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

#include "../includes/constantes.h"
#include "../includes/erreurs.h"
#include "../includes/fonctions.h"
#include "../includes/globales.h"
#include "../includes/tests.h"


#ifndef TEST


int main(int argc, char** argv) {

        // Fichier fourni en paramètre ?
	if( argc < 2)
	{
		puts( "La syntaxe attendue est : ./interpreteur <fichier>" RET );
		return EXIT_FAILURE;
	}

	// On récupère le nom de fichier fourni en paramètre
	uchar * nomFichierEntree = ( uchar *  ) argv[1];

	// On tente d'ouvrir ce fichier en lecture de manière
	FILE * fichierEntree = ( FILE * ) fopen( nomFichierEntree, "rb" );
	if( fichierEntree == NULL )
	{
		printf( "Impossible d'ouvrir le fichier : %s" RET, nomFichierEntree );
		return EXIT_FAILURE;
	}

	// On créé un tableau qui représente la mémoire utilisée pour stocker
        // le programme Pep8
	memoire = malloc(TAILLE_MEMOIRE_MAX);
        if( memoire == NULL )
        {
#ifdef DEBUG
    printf( "Impossible d'allouer la mémoire de Pep8." RET );
#endif
            fclose( fichierEntree );
            return EXIT_FAILURE;
        }

        // On recopie le fichier en mémoire
        RecopierFichierEnMemoire( fichierEntree, memoire );

        // On interprète les insctruction
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
            		// TODO : implémenter
            		break;

            	case GRINST4:
            		// TODO : implémenter
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
