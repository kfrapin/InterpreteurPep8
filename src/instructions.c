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
 * File:   instructions.c
 * Author: kevin
 *
 * Created on 14 december 2011
 *
 *
 * DESCRIPTION
 * -------------------------------------------------------------------------------------------------------
 * Fichier omplementant les fonctions permettant d'executer les
 * instructions du jeu d'instructions Pep8
 * ------------------------------------------------------------------------------------------------------
 */

//--------------------------------------------------- INCLUDE SYSTEMES
#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------- INCLUDE PERSONNELS
#include "includes/affichage.h"
#include "includes/constantes.h"
#include "includes/fonctions.h"
#include "includes/globales.h"
#include "includes/instructions.h"
#include "includes/typedefs.h"
#ifdef DEBUG
    #include "includes/debug.h"
#endif
// Fonction permettant d'executer l'instruction ADDr
schar ExecuterADDr( unint * registreConcerne, uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterADDr." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
#endif

    // On recupere la valeur en memoire
    unint valeurRecuperee = RecupererMotEnMemoire( modeAdressage );
    // On l'ajoute au registre concerne
    AdditionerRegistre( registreConcerne, valeurRecuperee );

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
    printf( "- ExecuterADDr." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction ADDSP
void inline ExecuterADDSP( uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterADDSP." RET);
    printf( TAB SEP_AVT_MAJ "registreSP" RET );
    AfficherValeurRegistreSP( );
    printf( TAB SEP_FIN RET );
#endif

    // On recupere la valeur en memoire
    unint valeurRecuperee = RecupererMotEnMemoire( modeAdressage );
    // On l'ajoute au registre SP
    AdditionerRegistre( &registreSP, valeurRecuperee );

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreSP" RET );
    AfficherValeurRegistreSP( );
    printf( TAB SEP_FIN RET );
    printf( "- ExecuterADDSP." RET);
#endif
}

// Fonction permettant d'executer l'instruction ANDr
schar ExecuterANDr( unint * registreConcerne, uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterANDr." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
#endif


    unint valeurRecuperee = RecupererMotEnMemoire( modeAdressage );

    // Mise à jour du registre
    unint nouvelleValeur = ( * registreConcerne ) & valeurRecuperee;
    ( * registreConcerne ) = nouvelleValeur;

    // Mise à jour des code de conditions N, Z
    MettreAJourN( nouvelleValeur );
    MettreAJourZ( nouvelleValeur );

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
    printf( "- ExecuterANDr." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction ASLr
void inline ExecuterASLr( unint * registreConcerne )
{
#ifdef DEBUG
    printf( "+ ExecuterASLr." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
#endif

    // On recupere le bit de signe qui va "partir" dans
	// le code de condition C
	unint ancienSigne = ( (*registreConcerne) >> 15 ) & 1;

	// On decale le regitre vers la gauche
	( * registreConcerne ) = (ssint) ( ( * registreConcerne ) << 1 );

	// Mise a jour des codes de condition V, C
	MettreAJourC( ancienSigne );

	uchar nouveauSigne = ( (*registreConcerne) >> 15 ) & 1;
	MettreAJourV( ((ancienSigne == nouveauSigne) ? 0 : 1) );

    // Mise à jour des codes de condition N,Z
    MettreAJourN( (* registreConcerne) );
    MettreAJourZ( (* registreConcerne) );

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
    printf( "- ExecuterASLr." RET);
#endif
}

// Fonction permettant d'executer l'instruction ASRr
void inline ExecuterASRr( unint * registreConcerne )
{
#ifdef DEBUG
    printf( "+ ExecuterASRr." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
#endif

    // Mise a jour du code de condition C avec le bit
    // qui "sort"
    MettreAJourC( ( ( * registreConcerne ) & 1 ) );

    // On passe en valeur signée sur 16 bits pour conserver
    // le bit du signe apres le decalage
    ssint valeurSignee = (ssint) ( * registreConcerne );

    ( * registreConcerne ) = ( valeurSignee >> 1 );

    // Mise à jour des codes de condition N,Z
    MettreAJourN( (* registreConcerne) );
    MettreAJourZ( (* registreConcerne) );

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
    printf( "- ExecuterASRr." RET);
#endif
}

// Fonction permettant d'executer l'instruction BR
void inline ExecuterBR( uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterBR." RET);
#endif

    // On saute a l'instruction specifiee
    registrePC = RecupererMotEnMemoire( modeAdressage );

#ifdef DEBUG
    printf( "- ExecuterBR." RET);
#endif
}


// Fonction permettant d'executer l'instruction BRC
void inline ExecuterBRC( uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterBRC." RET);
#endif

    if( codeC == 1 )
    {
    	// On saute a l'instruction specifiee
    	registrePC = RecupererMotEnMemoire( modeAdressage );
    }

#ifdef DEBUG
    printf( "- ExecuterBRC." RET);
#endif
}


// Fonction permettant d'executer l'instruction BREQ
void inline ExecuterBREQ( uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterBREQ." RET);
#endif

    if( codeZ == 1 )
    {
    	// On saute a l'instruction specifiee
    	registrePC = RecupererMotEnMemoire( modeAdressage );
    }

#ifdef DEBUG
    printf( "- ExecuterBREQ." RET);
#endif
}


// Fonction permettant d'executer l'instruction BRGE
void inline ExecuterBRGE( uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterBRGE." RET);
#endif

    if( codeN == 0 )
    {
    	// On saute a l'instruction specifiee
    	registrePC = RecupererMotEnMemoire( modeAdressage );
    }

#ifdef DEBUG
    printf( "- ExecuterBRGE." RET);
#endif
}


// Fonction permettant d'executer l'instruction BRGT
void inline ExecuterBRGT( uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterBRGT." RET);
#endif

    if( (codeN == 0) && (codeZ == 0) )
    {
    	// On saute a l'instruction specifiee
    	registrePC = RecupererMotEnMemoire( modeAdressage );
    }

#ifdef DEBUG
    printf( "- ExecuterBRGT." RET);
#endif
}


// Fonction permettant d'executer l'instruction BRLE
void inline ExecuterBRLE( uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterBRLE." RET);
#endif

    if( (codeZ == 1) || (codeN == 1) )
    {
    	// On saute a l'instruction specifiee
    	registrePC = RecupererMotEnMemoire( modeAdressage );
    }

#ifdef DEBUG
    printf( "- ExecuterBRLE." RET);
#endif
}

// Fonction permettant d'executer l'instruction BRLT
void inline ExecuterBRLT( uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterBRLT." RET);
#endif

    if( codeN == 1 )
    {
    	// On saute a l'instruction specifiee
    	registrePC = RecupererMotEnMemoire( modeAdressage );
    }

#ifdef DEBUG
    printf( "- ExecuterBRLT." RET);
#endif
}


// Fonction permettant d'executer l'instruction BRNE
void inline ExecuterBRNE( uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterBRNE." RET);
#endif

    if( codeZ == 0 )
    {
    	// On saute a l'instruction specifiee
    	registrePC = RecupererMotEnMemoire( modeAdressage );
    }

#ifdef DEBUG
    printf( "- ExecuterBRNE." RET);
#endif
}


// Fonction permettant d'executer l'instruction BRV
void inline ExecuterBRV( uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterBRV." RET);
#endif

    if( codeV == 1 )
    {
    	// On saute a l'instruction specifiee
    	registrePC = RecupererMotEnMemoire( modeAdressage );
    }

#ifdef DEBUG
    printf( "- ExecuterBRV." RET);
#endif
}


// Fonction permettant d'executer l'instruction CALL
void inline ExecuterCALL( uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterCALL." RET);
#endif

    // On sauvegarde le registrePC sur la pile
    registreSP -= 2;
    EcrireMotEnMemoire( registrePC, registreSP );

    // On saute a l'instruction specifiee
    registrePC = RecupererMotEnMemoire( modeAdressage );

#ifdef DEBUG
    printf( "- ExecuterCALL." RET);
#endif
}


// Fonction permettant d'executer l'instruction CHARI
schar ExecuterCHARI( uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterCHARI." RET);
#endif

	sint caractereSaisi = EOF;
	if( entreeLecture == ENTREE_STDIN )
	{
		// On recupere un caractere au clavier et on le stocke en memoire
		caractereSaisi = getchar( );
	}
	else if( entreeLecture == ENTREE_FICHIER )
	{
		// On recupere un caractere dans le fichier "fichierEntree"
		caractereSaisi = getc( fichierEntree );
	}

	if( caractereSaisi == EOF )
	// Erreur a la lecture
	{
#ifdef DEBUG
    puts( "! ExecuterCHARI : Erreur durant la lecture du caractère" );
#endif
		return EXIT_FAILURE;
	}

	RecopierOctetRegistreEnMemoire( ( unint * ) &caractereSaisi, modeAdressage );

#ifdef DEBUG
    printf( "- ExecuterCHARI." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction CHARO
schar ExecuterCHARO( uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterCHARO." RET);
#endif

    uchar valeurRecuperee = RecupererOctetEnMemoire( modeAdressage );

    // Affichage de cette valeur sur la sortie standard
    putchar( valeurRecuperee );

#ifdef DEBUG
    printf( "- ExecuterCHARO." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction CPr
schar ExecuterCPr( unint * registreConcerne, uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterCPr." RET);
#endif

    unint valeurRegistre = ( * registreConcerne );
    unint valeurRecuperee = RecupererMotEnMemoire( modeAdressage );

    // On utilise la fonction "AdditionerRegistre", sauf qu'au lieu
    // de tester un registre, elle va tester notre sa valeur dans une
    // variable sans importance -» Non modification du registre
    AdditionerRegistre( &valeurRegistre, ((~valeurRecuperee + 1) & MASQUE_16_BITS) );

#ifdef DEBUG
    printf( "- ExecuterCPr." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction LDBYTEr
schar ExecuterLDBYTEr( unint * registreConcerne, uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterLDBYTEr." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
#endif

    ( * registreConcerne ) =
            ( ( (*registreConcerne) & MASQUE_8_BITS_G )
                | RecupererOctetEnMemoire( modeAdressage )
            );

    // Mise à jour des codes de condition N,Z
    MettreAJourN( (* registreConcerne) );
    MettreAJourZ( (* registreConcerne) );


#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
    printf( "- ExecuterLDBYTEr." RET);
#endif
    return EXIT_SUCCESS;
}



// Fonction permettant d'executer l'instruction LDr
schar ExecuterLDr( unint * registreConcerne, uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterLDr." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
#endif

    ( * registreConcerne ) = RecupererMotEnMemoire( modeAdressage );

    // Mise à jour des codes de condition N,Z
    MettreAJourN( (* registreConcerne) );
    MettreAJourZ( (* registreConcerne) );

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
    printf( "- ExecuterLDr." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction MOVFLGA
void inline ExecuterMOVFLGA( )
{
#ifdef DEBUG
    printf( "+ ExecuterMOVFLGA." RET);
#endif

    // Copie de NZVC dans le registre A (dans les 4 bits de droite)
    registreA = ConcatenerNZVC( );

#ifdef DEBUG
    printf( "- ExecuterMOVFLGA." RET);
#endif
}

// Fonction permettant d'executer l'instruction MOVSPA
void inline ExecuterMOVSPA( )
{
#ifdef DEBUG
    printf( "+ ExecuterMOVSPA." RET);
#endif

    // Copie du pointeur de pile dans le registre A
	registreA = registreSP;

#ifdef DEBUG
    printf( "- ExecuterMOVSPA." RET);
#endif
}

// Fonction permettant d'executer l'instruction NEGr
void inline ExecuterNEGr( unint * registreConcerne )
{
#ifdef DEBUG
    printf( "+ ExecuterNEGr." RET);
#endif

    if( ((ssint) (*registreConcerne)) == -32768 )
    // Si la valeur a inverser est -32768 : overflow
    {
        MettreAJourV( 1 );
    }
    else
    {
        MettreAJourV( 0 );
    }

    // On effectue la negation en complement a deux
    NierRegistreEnComplement( registreConcerne );

    // Mise à jour des codes de condition N,Z
    MettreAJourN( (* registreConcerne) );
    MettreAJourZ( (* registreConcerne) );

#ifdef DEBUG
    printf( "- ExecuterNEGr." RET);
#endif
}

// Fonction permettant d'executer l'instruction NOTr
void inline ExecuterNOTr( unint * registreConcerne )
{
#ifdef DEBUG
    printf( "+ ExecuterNOTr." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
#endif

    // On effectue la négation du registre
    ( * registreConcerne ) = ( ssint ) ~( * registreConcerne );

    // Mise à jour des codes de condition N,Z
    MettreAJourN( (* registreConcerne) );
    MettreAJourZ( (* registreConcerne) );

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
    printf( "- ExecuterNOTr." RET);
#endif
}

// Fonction permettant d'executer l'instruction ORr
schar ExecuterORr( unint * registreConcerne, uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterORr." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
#endif

    unint valeurRecuperee = RecupererMotEnMemoire( modeAdressage );

    // Mise à jour du registre
    unint nouvelleValeur = ( * registreConcerne ) | valeurRecuperee;
    ( * registreConcerne ) = nouvelleValeur;

    // Mise à jour des code de conditions N, Z
    MettreAJourN( nouvelleValeur );
    MettreAJourZ( nouvelleValeur );

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
    printf( "- ExecuterORr." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction RETTR
schar ExecuterRETTR(  )
{
#ifdef DEBUG
    printf( "+ ExecuterRETTR." RET);
    printf( TAB SEP_AVT_MAJ "registreA,  registreX, registrePC, registreSP" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    AfficherValeurRegistrePC( );
    AfficherValeurRegistreSP( );
    printf( TAB SEP_FIN RET );
#endif

    // Remise en place du contexte present avant l'appel au trap handler
    // Codes de condition
    uchar codesNZVC = LireOctetEnMemoire( registreSP );
    codeN = ( ( codesNZVC & 8 ) != 0 ) ? 1 : 0;
    codeZ = ( ( codesNZVC & 4 ) != 0 ) ? 1 : 0;
    codeV = ( ( codesNZVC & 2 ) != 0 ) ? 1 : 0;
    codeC = ( codesNZVC & 1 );

    // Registres
    registreA = LireMotEnMemoire( registreSP + 1 );
    registreX = LireMotEnMemoire( registreSP + 3 );
    registrePC = LireMotEnMemoire( registreSP + 5 );
    registreSP = LireMotEnMemoire( registreSP + 7 );

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreA,  registreX, registrePC, registreSP" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    AfficherValeurRegistrePC( );
    AfficherValeurRegistreSP( );
    printf( TAB SEP_FIN RET );
    printf( "- ExecuterRETTR." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction ROLr
schar ExecuterROLr( unint *  registreConcerne )
{
#ifdef DEBUG
    printf( "+ ExecuterROLr." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
#endif

    // On met de cote la future valeur du code de condition
    unint nouvelleValeurC = ( ( * registreConcerne ) >> 15 ) & 1;

    // On met a jour le registre
    ( * registreConcerne ) = ( ( * registreConcerne ) << 1 ) | codeC;

    // On met a jour le code de condiction C
    MettreAJourC( nouvelleValeurC );

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
    printf( "- ExecuterROLr." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction RORr
schar ExecuterRORr( unint * registreConcerne )
{
#ifdef DEBUG
    printf( "+ ExecuterRORr." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
#endif

    // On met de cote la future valeur du code de condition
    unint nouvelleValeurC = ( * registreConcerne ) & 1;

    // On met a jour le registre
    ( * registreConcerne ) = ( ( * registreConcerne ) >> 1 ) | ( codeC << 15 );

    // On met a jour le code de condiction C
    MettreAJourC( nouvelleValeurC );

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
    printf( "- ExecuterRORr." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction RETr
schar ExecuterRETn( unint valeurN )
{
#ifdef DEBUG
    printf( "+ ExecuterRETn." RET);
    printf( TAB SEP_AVT_MAJ "registrePC, registreSP" RET );
    AfficherValeurRegistrePC( );
    AfficherValeurRegistreSP( );
    printf( TAB SEP_FIN RET );
#endif

    // On désempile
    registreSP += valeurN;

    // On met à jour le registre PC, et on désempile
    registrePC = LireMotEnMemoire( registreSP );
    registreSP += 2;

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registrePC, registreSP" RET );
    AfficherValeurRegistrePC( );
    AfficherValeurRegistreSP( );
    printf( TAB SEP_FIN RET );
    printf( "- ExecuterRETn." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction STr
schar ExecuterSTr( unint * registreConcerne, uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterSTr." RET);
#endif

    // On recopie le contenu du registre en mémoire
    RecopierMotRegistreEnMemoire( registreConcerne, modeAdressage );

#ifdef DEBUG
    printf( "- ExecuterSTr." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction STBYTEr
schar ExecuterSTBYTEr( unint * registreConcerne, uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterSTBYTEr." RET);
#endif

    // On recopie les 8 bits de droites du registre en mémoire
    RecopierOctetRegistreEnMemoire( registreConcerne, modeAdressage );

#ifdef DEBUG
    printf( "- ExecuterSTBYTEr." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction r
schar ExecuterSUBr( unint * registreConcerne, uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterSUBr." RET);
#endif

    // On recupere la valeur en memoire
    unint valeurRecuperee = RecupererMotEnMemoire( modeAdressage );

    // On la soustrait au registre
    AdditionerRegistre( registreConcerne, ( (~valeurRecuperee + 1) & MASQUE_16_BITS) );

#ifdef DEBUG
    printf( "- ExecuterSUBr." RET);
#endif
    return EXIT_SUCCESS;
}


// Fonction permettant d'executer l'instruction SUBSP
void inline ExecuterSUBSP( uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ ExecuterSUBSP." RET);
    printf( TAB SEP_AVT_MAJ "registreSP" RET );
    AfficherValeurRegistreSP( );
    printf( TAB SEP_FIN RET );
#endif

    unint valeurRecuperee = RecupererMotEnMemoire( modeAdressage );

    // On effectue la soustraction
    AdditionerRegistre( &registreSP, ((~valeurRecuperee + 1) & MASQUE_16_BITS) );

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreSP" RET );
    AfficherValeurRegistreSP( );
    printf( TAB SEP_FIN RET );
    printf( "- ExecuterSUBSP." RET);
#endif
}
