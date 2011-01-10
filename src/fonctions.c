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
 * File:   fonctions.c
 * Author: mousseyed, kevin
 *
 * Created on October 20, 2010, 12:22 PM
 */

//--------------------------------------------------- INCLUDE SYSTEMES
#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------- INCLUDE PERSONNELS
#include "includes/affichage.h"
#include "includes/constantes.h"
#include "includes/erreurs.h"
#include "includes/fonctions.h"
#include "includes/globales.h"
#include "includes/instructions.h"
#include "includes/predecodage.h"
#ifdef DEBUG
    #include "includes/debug.h"
#endif

//--------------------------------------------------- FONCTIONS

// Fonction permettant d'ajouter une valeur a un registre
void AdditionerRegistre( unint * registreConcerne, unint valeurAAjouter )
{
#ifdef DEBUG
    printf( "+ AdditionerRegistre." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX | registreSP" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    AfficherValeurRegistreSP( );
    printf( TAB SEP_FIN RET );
#endif

    // Valeur du registre et son signe
    unint valeurRegistre = ( * registreConcerne );

    // Signes des opérandes
    unint signeRegistre = valeurRegistre >> 15;
    unint signeValeur = valeurAAjouter >> 15;
    unint debordement, resultat, retenue;

    resultat  = valeurRegistre + valeurAAjouter;
    retenue = ( (resultat >> 16) != 0 ) ? 1 : 0;

    if( signeRegistre != signeValeur )
    // Deux signes différents, pas de souci
    {    
        debordement = 0;
    }
    else if( signeRegistre == 0 )
    // Deux valeurs positives
    {
        debordement = ((resultat >> 15) & 1);
    }
    else
    // Deux valeurs négatives
    {
        debordement = (((resultat >> 15) & 1) == 0) ? 1 : 0;
    }

    // Mise à jour du registre
    ( * registreConcerne ) = (resultat & MASQUE_16_BITS);

    // Mise a jour des codes de conditions
    MettreAJourN( (*registreConcerne) );
    MettreAJourZ( (*registreConcerne) );
    MettreAJourV( debordement );
    MettreAJourC( retenue );


#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreA | registreX | registreSP" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    AfficherValeurRegistreSP( );
    printf( TAB SEP_FIN RET );
    printf( "- AdditionerRegistre." RET);
#endif
}

// Fonction permettant de sauvegarder et mettre a jour les registres afin
// d'effectuer un appel a une trap du systeme d'exploitation
void AppelerTrapHandler(  )
{
#ifdef DEBUG
    printf( "+ AppelerTrapHandler." RET);
    printf( TAB SEP_AVT_MAJ "registreA,  registreX, registrePC, registreSP" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    AfficherValeurRegistrePC( );
    AfficherValeurRegistreSP( );
    printf( TAB SEP_FIN RET );
#endif

    // Sauvegarde des registres dans la pile systeme
    unint temp = LireMotEnMemoire( ADR_MEM_SP_SYS );
    EcrireOctetEnMemoire( instructionIR, ( temp - 1 ) );
    EcrireMotEnMemoire( registreSP, ( temp - 3 ) );
    EcrireMotEnMemoire( registrePC , ( temp - 5 ) );
    EcrireMotEnMemoire( registreX,  ( temp - 7 ) );
    EcrireMotEnMemoire( registreA, ( temp - 9 ) );
    EcrireOctetEnMemoire( ConcatenerNZVC( ), ( temp - 10 ) );

    // Mise a jour du pointeur de pile
    registreSP = ( temp - 10 );

    // Mise a jour du compteur de programme pour appeler le trap handler
    registrePC = LireMotEnMemoire( ADR_MEM_TRAP_HANDLER );

#ifdef DEBUG
    printf( TAB SEP_AVT_MAJ "registreA,  registreX, registrePC, registreSP" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    AfficherValeurRegistrePC( );
    AfficherValeurRegistreSP( );
    printf( TAB SEP_FIN RET );
    printf( "- AppelerTrapHandler." RET);
#endif
}

// ATTENTION
//---------------------------------------------------------------------------------------------------------------------
// Cette fonction est prevue pour charger l'image du systeme d'exploitation
// fournie avec l'application, et n'est pas generique, elle necessiterait quelques
// traitements supplémentaires pour le devenir
//----------------------------------------------------------------------------------------------------------------------

// Fonction permettant de charger un programme en memoire
void ChargerProgramme( FILE * fichierProg )
{
#ifdef DEBUG
    printf( "+ ChargerProgramme." RET);
#endif

    // On positionne les registres pour appeler le loader
    // du systeme d'exploitation
    registreSP = LireMotEnMemoire( ADR_MEM_SP_SYS );
    registrePC = LireMotEnMemoire( ADR_MEM_LOADER );

    // On indique que CHARI devra lire dans le fichier
    // fourni et non sur l'entree standard
    fichierEntree = fichierProg;
    entreeLecture = ENTREE_FICHIER;

    // On lance l'execution du chargement
    ExecuterInstructions( );

    // On indique que maintenant CHARI devra lire
    // sur l'entree standard
    fichierEntree = NULL;
    entreeLecture = ENTREE_STDIN;

#ifdef DEBUG
    printf( "- ChargerProgramme." RET);
#endif
}

// Fonction permettant de charger l'image du système d'exploitation
// en fin de memoire (ie, derniere instruction a l'adresse TAILLE_MEMOIRE_MAX)
void ChargerSystemeExploitation( FILE * fichierOS )
{
#ifdef DEBUG
    printf( "+ ChargerSystemeExploitation." RET);
#endif

    // On charge a partir de l'adresse 64599 (0xFC57)
    // car on connait la taille de l'image de l'OS
    RecopierFichierEnMemoire( fichierOS, memoire, 64599 );

#ifdef DEBUG
    printf( "- ChargerSystemeExploitation." RET);
#endif
}

// Fonction permettant de mettre les codes de condition NZVC
// sous la forme d'un char
unint ConcatenerNZVC( )
{
#ifdef DEBUG
    printf( "+ ConcatenerNZVC." RET);
#endif

    // Concatenation des codes de condition
	// 	- Bit 3 : code N
	//	- Bit 2 : code Z
	//	- Bit 1 : code V
	//	- Bit 0 : code C
    unint decalageN = codeN << 3;
    unint decalageZ = codeZ << 2;
    unint decalageV = codeV << 1;

#ifdef DEBUG
    printf( "- ConcatenerNZVC." RET);
#endif

    return (  decalageN | decalageZ | decalageV | codeC );
}

// Fonction permettant d'ecrire un mot (16 bits) en memoire
void inline EcrireMotEnMemoire( unint valeur, unint adresse )
{
#ifdef DEBUG
    printf( "+ EcrireMotEnMemoire." RET);
    printf( TAB SEP_AVT_MAJ "memoire[ ]" RET );
    printf( TAB "Valeur memoire[%X] : %X" RET, (adresse & MASQUE_16_BITS), memoire[adresse & MASQUE_16_BITS] );
    printf( TAB "Valeur memoire[%X] : %X" RET,(adresse+1) & MASQUE_16_BITS, memoire[(adresse+1) & MASQUE_16_BITS] );
    printf( TAB SEP_FIN RET );
#endif

    // On sauvegarde d'abord les 8 bits de gauche
    memoire[ adresse & MASQUE_16_BITS ] = ( valeur >> 8 );

    // Puis les 8 bits de droite
    memoire[ ( adresse + 1 ) & MASQUE_16_BITS ] =  valeur;

#ifdef DEBUG
   printf( TAB SEP_APR_MAJ "memoire[ ]" RET );
   printf( TAB "Valeur memoire[%X] : %X" RET, (adresse & MASQUE_16_BITS), memoire[adresse & MASQUE_16_BITS] );
   printf( TAB "Valeur memoire[%X] : %X" RET,(adresse+1) & MASQUE_16_BITS, memoire[ (adresse+1) & MASQUE_16_BITS] );
   printf( TAB SEP_FIN RET );
   printf( "- EcrireMotEnMemoire." RET);
#endif
}

// Fonction permettant d'ecrire un octet (8 bits) en memoire
void inline EcrireOctetEnMemoire( unint valeur, unint adresse )
{
#ifdef DEBUG
    printf( "+ EcrireOctetEnMemoire." RET);
    printf( TAB SEP_AVT_MAJ "memoire[ ]" RET );
    printf( TAB "Valeur memoire[%X] : %X" RET, (adresse & MASQUE_16_BITS), memoire[adresse & MASQUE_16_BITS] );
    printf( TAB SEP_FIN RET );
#endif

    // On sauvegarde les 8 bits de droite uniquement
    memoire[ adresse & MASQUE_16_BITS ] = valeur;

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "memoire[ ]" RET );
    printf( TAB "Valeur memoire[%X] : %X" RET, (adresse & MASQUE_16_BITS), memoire[adresse & MASQUE_16_BITS] );
    printf( TAB SEP_FIN RET );
    printf( "- EcrireOctetEnMemoire." RET);
#endif
}



// Fonction permettant d'executer l'instruction du groupe
//  GRINST1 au vu de la valeur des 4 derniers bits fournis
schar ExecuterInstGr1(uchar opcodeDroite)
{
#ifdef DEBUG
    printf( "+ ExecuterInstGr1." RET);
#endif
    
    if( opcodeDroite > 15 )
    {
        return EXECUTION_KO;
    }

    if( opcodeDroite == STOP_FIN )
    // (pas possible en principe, car géré dans la condition du WHILE)
    {
        exit(EXIT_SUCCESS);
    }

    else if( opcodeDroite == RETTR_FIN )
    {
        ExecuterRETTR( );
        return EXIT_SUCCESS;
    }

    else if( opcodeDroite == MOVSPA_FIN )
    {
    	ExecuterMOVSPA( );
        return EXIT_SUCCESS;
    }
    else if( opcodeDroite == MOVFLGA_FIN )
    {
    	ExecuterMOVFLGA( );
        return EXIT_SUCCESS;
    }

    // Ici, on sait que : opcodeFin > MOVFLGA_FIN
    // Donc certains tests ont pu être supprimés, et on sait qu'on a besoin de
    // récupérer l'opérande passée à l'instruction
    MettreAJourOperandeIR( );
    uchar modeAdressage = ( opcodeDroite & 1 );

    // Il faut convertir le mode d'adressage INDEXE pour qu'il puisse etre reconnu
    // dans la fonction RecupererMotEnMemoire
    if( modeAdressage == 1 )
    {
    	modeAdressage = INDEXE;
    }

    if( opcodeDroite <= BR_FIN_S )
    {
    	ExecuterBR( modeAdressage );
    }

    else if( opcodeDroite <= BRLE_FIN_S )
    {
    	ExecuterBRLE( modeAdressage );
    }

    else if( opcodeDroite <= BRLT_FIN_S )
    {
    	ExecuterBRLT( modeAdressage );
    }

    else if( opcodeDroite <= BREQ_FIN_S )
    {
    	ExecuterBREQ( modeAdressage );
    }

    else if( opcodeDroite <= BRNE_FIN_S )
    {
    	ExecuterBRNE( modeAdressage );
    }
    else
    {
        // Si on arrive ici, instruction = BRGE
    	ExecuterBRGE( modeAdressage );
    }
    
#ifdef DEBUG
    printf( "- ExecuterInstGr1." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction du groupe
// GRINST2 au vu de la valeur des 4 derniers bits fournis.
schar ExecuterInstGr2( uchar opcodeDroite )
{
#ifdef DEBUG
    printf( "+ ExecuterInstGr2." RET);
#endif

    // Recuperation du mode d'adressage
    // IMMEDIAT ou INDEXE
    // (Pas utile pour toutes les opérations)
    uchar modeAdressage = (opcodeDroite & 1);
    if( modeAdressage == 1 )
    {
    	modeAdressage = INDEXE;
    }

    if( opcodeDroite <= BRGT_FIN_S )
    {
        // Mise a jour de l'operande
        MettreAJourOperandeIR( );
        ExecuterBRGT( modeAdressage );
        return EXIT_SUCCESS;
    }
    else if( opcodeDroite <= BRV_FIN_S )
    {
        // Mise a jour de l'operande
        MettreAJourOperandeIR( );
        ExecuterBRV( modeAdressage );
        return EXIT_SUCCESS;
    }
    else if( opcodeDroite <= BRC_FIN_S )
    {
        // Mise a jour de l'operande
        MettreAJourOperandeIR( );
        ExecuterBRC( modeAdressage );
        return EXIT_SUCCESS;
    }
    else if( opcodeDroite <= CALL_FIN_S )
    {
        // Mise a jour de l'operande
        MettreAJourOperandeIR( );
        ExecuterCALL( modeAdressage );
        return EXIT_SUCCESS;
    }

    // A partir d'ici, on est toujours obligé de recuperer
    // le registre concerne par l'operation
    // Registre concerne par la negation
    unint * registreConcerne;

    if( (opcodeDroite & 1) == 0 )
    // Negation du registre A
    {
        registreConcerne = &registreA;
    }
    else
    // Addition sur le registre X
    {
         registreConcerne = &registreX;
    }

    if( opcodeDroite <= NOTR_FIN_S )
    {
        ExecuterNOTr( registreConcerne );
    }
    else if( opcodeDroite <= NEGR_FIN_S )
    {
    	ExecuterNEGr( registreConcerne );
    }
    else if( opcodeDroite <= ASLR_FIN_S )
    {
    	ExecuterASLr( registreConcerne );
    }
    else if( opcodeDroite <= ASRR_FIN_S )
    {
    	ExecuterASRr( registreConcerne );
    }

#ifdef DEBUG
    printf( "- ExecuterInstGr2." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction du groupe
// GRINST3 au vu de la valeur des 4 derniers bits fournis.
schar ExecuterInstGr3( uchar opcodeDroite )
{
#ifdef DEBUG
    printf( "+ ExecuterInstGr3." RET);
#endif

    // Registre concerné par l'opération
    // (Pas utile pour toutes les opérations)
    unint * registreConcerne;

    if( (opcodeDroite & 1) == 0 )
    {
        registreConcerne = &registreA;
    }
    else
    {
        registreConcerne = &registreX;
    }

    // Instruction en cours
    if( opcodeDroite <= ROLR_FIN_S )
    {
    	ExecuterROLr( registreConcerne );
    }
    else if( opcodeDroite <= RORR_FIN_S )
    {
    	ExecuterRORr( registreConcerne );
    }
    else
    {
        // Sinon on est sur une opération NOP
        AppelerTrapHandler( );
    }

#ifdef DEBUG
    printf( "- ExecuterInstGr3." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction du groupe
// GRINST4 au vu de la valeur des 4 derniers bits fournis.
schar ExecuterInstGr4( uchar opcodeDroite )
{
#ifdef DEBUG
    printf( "+ ExecuterInstGr4." RET);
#endif

    // On met a jour l'operande
    MettreAJourOperandeIR( );

    // Operation DECI ou DECO -> Appel du Trap Handler
   	AppelerTrapHandler(  );

#ifdef DEBUG
    printf( "- ExecuterInstGr4." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction du groupe
// GRINST5 au vu de la valeur des 4 derniers bits fournis.
schar ExecuterInstGr5( uchar opcodeDroite)
{
#ifdef DEBUG
    printf( "+ ExecuterInstGr5." RET);
#endif

	if( opcodeDroite <= STRO_FIN_S )
	{
		MettreAJourOperandeIR( );
		AppelerTrapHandler( );
	}
	else
	{
		MettreAJourOperandeIR( );
		uchar modeAdressage = opcodeDroite & 7;
		ExecuterCHARI( modeAdressage );
	}

#ifdef DEBUG
    printf( "- ExecuterInstGr5." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction du groupe
// GRINST6 au vu de la valeur des 4 derniers bits fournis.
schar ExecuterInstGr6( uchar opcodeDroite )
{
#ifdef DEBUG
    printf( "+ ExecuterInstGr6." RET);
#endif

    if( opcodeDroite <= CHARO_FIN_S )
    {
		MettreAJourOperandeIR( );
		uchar modeAdressage = opcodeDroite & 7;
    	ExecuterCHARO( modeAdressage );
    }
    else
    // Opération RETn
    {
        // On récupère la taille à désempiler
        unint valeurN = ( opcodeDroite & 7 );
        ExecuterRETn( valeurN );
    }

#ifdef DEBUG
    printf( "- ExecuterInstGr6." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant d'executer l'instruction du groupe
// GRINST7 au vu de la valeur des 4 derniers bits fournis.
schar ExecuterInstGr7( uchar opcodeDroite )
{
#ifdef DEBUG
    printf( "+ ExecuterInstGr7." RET);
#endif

    // On recupere l'operande de l'instruction
    MettreAJourOperandeIR( );

    // Récupération du mode d'adressage et de la donnée
    uchar modeAdressage = opcodeDroite & 7;

    if( opcodeDroite <= ADDSP_FIN_S )
    {
    	ExecuterADDSP( modeAdressage );
    }
    else
    {
        ExecuterSUBSP( modeAdressage );
    }

#ifdef DEBUG
    printf( "- ExecuterInstGr7." RET);
#endif
    return EXIT_SUCCESS;
}

// Fonction permettant de lancer l'execution des instructions
void ExecuterInstructions( )
{
#ifdef DEBUG
    printf( "+ ExecuterInstructions." RET);
#endif

	// Variable permettant de savoir si l'exécution s'est bien passee
	schar retourExec = 0;
	instructionIR = memoire[registrePC++];

    while( (instructionIR != STOP) && (retourExec != EXECUTION_KO) )
    {
#ifdef DEBUG
printf( RET "> Instruction lue : %d." RET, instructionIR );
#endif

		// Instruction deja predecodee ?
		predecodage decodage = codeDecode[registrePC-1];
		//if( entreeLecture == ENTREE_STDIN )
		//	printf( "decodage.etatDecodage : %d" RET, decodage.etatDecodage );

/*
		switch( decodage.etatDecodage )
		{
			case DECODAGE_A_FAIRE:
#ifdef DEBUG
	printf( SEP_FIN RET );
	puts( "  DECODAGE_A_FAIRE" ) ;
	puts( "  -> DECODAGE_FAIT" );
	printf( SEP_FIN RET );
#endif
				PredecoderInstruction( registrePC  - 1 );
				retourExec = JouerInstructionPredecodee( registrePC - 1 );
				break;

			case DECODAGE_FAIT:
				// On teste s'il s'agit toujours de la meme instruction
				if( decodage.opCodeOriginal == instructionIR )
				// Code inchange
				{
#ifdef DEBUG
	printf( SEP_FIN RET );
	puts( "  DECODAGE_FAIT" );
	puts( "  -> DECODAGE_FAIT" );
	printf( SEP_FIN RET );
#endif
					retourExec = JouerInstructionPredecodee( registrePC - 1 );
				}
				else
				// Code modifie
				{
#ifdef DEBUG
	printf( SEP_FIN RET );
	puts( "  DECODAGE_FAIT" );
	puts( "  -> DECODAGE_A_IGNORER" );
	printf( SEP_FIN RET );
#endif
					// On indique qu'on ne decodera plus jamais cette instruction
					decodage.etatDecodage = DECODAGE_A_IGNORER;
					// On execute l'instruction sans utiliser le predecodage
					retourExec = JouerInstructions( );
				}
				break;

			case DECODAGE_A_IGNORER:
#ifdef DEBUG
	printf( SEP_FIN RET );
	puts( "  DECODAGE_A_IGNORER" );
	puts( "  -> DECODAGE_A_IGNORER" );
	printf( SEP_FIN RET );
#endif
				retourExec = JouerInstructions( );
				break;
		}
*/

		if( decodage.etatDecodage == DECODAGE_FAIT )
		{
			if( decodage.opCodeOriginal == instructionIR )
			// Code inchange
			{
				JouerInstructionPredecodee( registrePC - 1 );
			}
			else
			// Code modifie
			{
				decodage.etatDecodage = DECODAGE_A_IGNORER;
				JouerInstructions( );
			}
		}
		else if( decodage.etatDecodage == DECODAGE_A_FAIRE )
		{
			PredecoderInstruction( registrePC  - 1 );
			retourExec = JouerInstructionPredecodee( registrePC - 1 );
		}
		else if( decodage.etatDecodage == DECODAGE_A_IGNORER )
		{
			 JouerInstructions( );
		}

		// retourExec = JouerInstructions( );

        instructionIR = memoire[registrePC++];
    }

#ifdef DEBUG
    printf( "- ExecuterInstructions." RET);
#endif
}

// Fonction permettant de jouer les instructions
// sans utiliser le predecodage
schar JouerInstructions( )
{
#ifdef DEBUG
    printf( "+ JouerInstructions." RET);
#endif

	// Variable permettant de savoir si l'exécution s'est bien passee
	schar retourExec = 0;

    // On récupère les 4 bits de gauche de l'instruction
	uchar opcodeGauche =  ( instructionIR >> 4 );

	// On récupère les 4 bits de droite de l'instruction
	uchar opcodeDroite = 15 & instructionIR;
	unint * registreConcerne;
	uchar modeAdressage;

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
			MettreAJourOperandeIR( );
			registreConcerne = ( ( instructionIR & 8 ) == 0 ) ? &registreA : &registreX;
			modeAdressage = opcodeDroite & 7;
			retourExec = ExecuterADDr( registreConcerne, modeAdressage );
			break;

		case SUBR_DEB:
			MettreAJourOperandeIR( );
			registreConcerne = ( ( instructionIR & 8 ) == 0 ) ? &registreA : &registreX;
			modeAdressage = opcodeDroite & 7;
			retourExec = ExecuterSUBr( registreConcerne, modeAdressage );
			break;

		case ANDR_DEB:
			MettreAJourOperandeIR( );
			registreConcerne = ( ( instructionIR & 8 ) == 0 ) ? &registreA : &registreX;
			modeAdressage = opcodeDroite & 7;
			retourExec = ExecuterANDr( registreConcerne, modeAdressage );
			break;

		case ORR_DEB:
			MettreAJourOperandeIR( );
			registreConcerne = ( ( instructionIR & 8 ) == 0 ) ? &registreA : &registreX;
			modeAdressage = opcodeDroite & 7;
			retourExec = ExecuterORr( registreConcerne, modeAdressage );
			break;

		case CPR_DEB:
			MettreAJourOperandeIR( );
			registreConcerne = ( ( instructionIR & 8 ) == 0 ) ? &registreA : &registreX;
			modeAdressage = opcodeDroite & 7;
			retourExec = ExecuterCPr( registreConcerne, modeAdressage );
			break;

		case LDR_DEB:
			MettreAJourOperandeIR( );
			registreConcerne = ( ( instructionIR & 8 ) == 0 ) ? &registreA : &registreX;
			modeAdressage = opcodeDroite & 7;
			retourExec = ExecuterLDr( registreConcerne, modeAdressage );
			break;

		case LDBYTER_DEB:
			MettreAJourOperandeIR( );
			registreConcerne = ( ( instructionIR & 8 ) == 0 ) ? &registreA : &registreX;
			modeAdressage = opcodeDroite & 7;
			retourExec = ExecuterLDBYTEr( registreConcerne, modeAdressage );
			break;

		case STR_DEB:
			MettreAJourOperandeIR( );
			registreConcerne = ( ( instructionIR & 8 ) == 0 ) ? &registreA : &registreX;
			modeAdressage = opcodeDroite & 7;
			retourExec = ExecuterSTr( registreConcerne, modeAdressage );
			break;

		case STBYTER_DEB:
			MettreAJourOperandeIR( );
			registreConcerne = ( ( instructionIR & 8 ) == 0 ) ? &registreA : &registreX;
			modeAdressage = opcodeDroite & 7;
			retourExec = ExecuterSTBYTEr( registreConcerne, modeAdressage );
			break;
	}

#ifdef DEBUG
    printf( "- JouerInstructions." RET);
#endif

    return retourExec;
}

// Fonction permettant de jouer les programmes passes
// en parametre lors de l'appel de l'interpreteur
void JouerProgrammesEnParametres( uchar debut, uchar fin, char * * nomsFichier )
{
#ifdef DEBUG
    printf( "+ JouerProgrammesEnParametres." RET);
#endif

    char * nomFichier;
    FILE * fichierAJouer;
    uchar i;
    for( i = debut; i < fin; i++ )
    {
    		nomFichier = nomsFichier[i];
    		fichierAJouer = fopen( nomFichier, "rb" );
			if( fichierAJouer == NULL )
			{
#ifndef DEBUG
	printf( MENU_ERREUR_OUVERTURE RET, nomFichier );
#endif
			}
			else
			{
				// On nettoie la memoire
				NettoyerMemoire( memoire, TAILLE_MEMOIRE_MAX );

				// On se remet au debut du fichier de l'OS
				fseek( fichierOS, SEEK_SET, 0 );
				// On charge l'OS en cas de corruption par le programme
				// joue auparavant
				ChargerSystemeExploitation( fichierOS );

				// On charge le programme
				ChargerProgramme( fichierAJouer );

				// On lance le programme
				registreSP = LireMotEnMemoire( ADR_MEM_SP_USER );
				registrePC = 0;
				registreA = 0; registreX = 0;
				codeC = 0; codeN = 0; codeV = 0; codeZ = 0;
				printf( BATCH_PROGRAMME_DEBUT_EXEC RET, nomFichier );
				ExecuterInstructions( );
				putchar( RET_CHAR );
				printf( BATCH_PROGRAMME_FIN_EXEC RET, nomFichier );
			}
    }

#ifdef DEBUG
    printf( "- JouerProgrammesEnParametres." RET);
#endif
}


// Fonction permettant de lire un mot (16 bits) en mémoire
unint LireMotEnMemoire( unint adresse )
{
#ifdef DEBUG
    printf( "+ LireMotEnMemoire." RET);
#endif

    // Récupération des 8 bits de gauche
    unint bitsGauche = memoire[ adresse & MASQUE_16_BITS ];

    // Récupération des 8 bits de droite
    unint bitsDroite = memoire[ ( adresse + 1 ) & MASQUE_16_BITS ];

#ifdef DEBUG
    printf( "- LireMotEnMemoire." RET);
#endif

    return ( ( bitsGauche << 8 ) | bitsDroite );
}

// Fonction permettant de lire un octet (8 bits) en mémoire
uchar LireOctetEnMemoire( unint adresse )
{
#ifdef DEBUG
    printf( "+ LireOctetEnMemoire." RET);
#endif

#ifdef DEBUG
    printf( "- LireOctetEnMemoire." RET);
#endif

    return memoire[ adresse & MASQUE_16_BITS ];
}

// Fonction permettant de vider la memoire du systeme Pep8
void NettoyerMemoire( uchar * memoireANettoyer, unint tailleMemoire )
{
#ifdef DEBUG
    printf( "+ NettoyerMemoire." RET);
#endif

    unint i;
    for( i=0; i <= tailleMemoire; i++ )
    {
    	memoireANettoyer[i] = 0;
    }

#ifdef DEBUG
    printf( "- NettoyerMemoire." RET);
#endif
}

// Fonction permetter d'effectuer une negation en complement
// a deux sur un registre
void inline NierRegistreEnComplement( unint * registre )
{
#ifdef DEBUG
    printf( "+ NierRegistreEnComplement." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
#endif

    // On recupere de la valeur signee sur 16 bits
    ssint valeurSignee = (ssint) ( * registre );

    // On effectue sa negation
    ( * registre ) = - valeurSignee;
    
#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
    printf( "- NierRegistreEnComplement." RET);
#endif
}

// Fonctions permettant de mettre à jour le code de condition C
// en passant la valeur à leur affecter en paramètre
void inline MettreAJourC( unint retenue )
{
#ifdef DEBUG
    printf( "+ MettreAJourC." RET);
    printf( TAB SEP_AVT_MAJ "codeC" RET );
    AfficherValeurCodeC( );
    printf( TAB SEP_FIN RET );
#endif

    codeC = retenue;

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "codeC" RET );
    AfficherValeurCodeC( );
    printf( TAB SEP_FIN RET );
    printf( "- MettreAJourC." RET);
#endif
}

// Fonctions permettant de mettre à jour le code de condition N
// indiquant la valeur du registre concerné
void inline MettreAJourN( unint valeurRegistre )
{
#ifdef DEBUG
    printf( "+ MettreAJourN." RET);
    printf( TAB SEP_AVT_MAJ "codeN" RET );
    AfficherValeurCodeN( );
    printf( TAB SEP_FIN RET );
#endif

    codeN = (((valeurRegistre >> 15) & 1) == 1 ) ? 1 : 0;

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "codeN" RET );
    AfficherValeurCodeN( );
    printf( TAB SEP_FIN RET );
    printf( "- MettreAJourN." RET);
#endif
}

// Fonctions permettant de mettre à jour les codes de condition V
// en passant la valeur à leur affecter en paramètre
void inline MettreAJourV( unint debordement )
{
#ifdef DEBUG
    printf( "+ MettreAJourV." RET);
    printf( TAB SEP_AVT_MAJ "codeV" RET );
    AfficherValeurCodeV( );
    printf( TAB SEP_FIN RET );
#endif

    codeV = debordement;

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "codeV" RET );
    AfficherValeurCodeV( );
    printf( TAB SEP_FIN RET );
    printf( "- MettreAJourV." RET);
#endif
}

// Fonctions permettant de mettre à jour le code de condition Z
// en passant la valeur à leur affecter en paramètre
void inline MettreAJourZ( unint valeurRegistre )
{
#ifdef DEBUG
    printf( "+ MettreAJourZ." RET);
    printf( TAB SEP_AVT_MAJ "codeZ" RET );
    AfficherValeurCodeZ( );
    printf( TAB SEP_FIN RET );
#endif

    codeZ = ( valeurRegistre == 0 ) ? 1 : 0;

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "codeZ" RET );
    AfficherValeurCodeZ( );
    printf( TAB SEP_FIN RET );
    printf( "- MettreAJourZ." RET);
#endif
}

// Fonction permettant de mettre à jour la variable operandeIR,
// afin de récupérer l'opérande de l'instruction en cours
void MettreAJourOperandeIR( )
{
#ifdef DEBUG
    printf( "+ MettreAJourOperandeIR." RET);
    printf( TAB SEP_AVT_MAJ "operandeIR" RET );
    AfficherValeurOperandeIR( );
    printf( TAB SEP_FIN RET );
#endif

    // Récupération des 8 bits de gauche et des 8 bits de droite de l'opérande
    unint bitsGaucheOperande = memoire[registrePC++];
    unint bitsDroiteOperande = memoire[registrePC++];


    // On décale les bits de gauche pour qu'ils soient vraiment à gauche
    unint bitsGaucheDecalage = bitsGaucheOperande << 8;

    operandeIR =  bitsGaucheDecalage | bitsDroiteOperande;

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "operandeIR" RET );
    AfficherValeurOperandeIR( );
    printf( TAB SEP_FIN RET );
    printf( "- MettreAJourOperandeIR." RET);
#endif
}

// Fonction permettant de recopier un fichier dans une zone mémoire
// a partir de l'index indexDebut
void RecopierFichierEnMemoire( FILE * fichier, uchar * memoire, unint indexDebut )

{
#ifdef DEBUG
    printf( "+ RecopierFichierEnMemoire." RET);
#endif
    // On lit le premier caractere
    unint caracLu = fgetc( fichier );

	while( caracLu != EOF )
	{
#ifdef DEBUG
    printf( TAB "Caractere copie en memoire[%X] : %X" RET, indexDebut, caracLu );
#endif
    	memoire[indexDebut++] = caracLu;
    	caracLu = fgetc( fichier );
	}

#ifdef DEBUG
    printf( "- RecopierFichierEnMemoire." RET);
#endif
}

// Fonction permettant mettre à jour le registre PC avec l'opérande
// fournit à l'instruction
void inline RecopierOperandeDansPC( )
{
#ifdef DEBUG
    printf( "+ RecopierOperandeDansPC." RET);
    printf( TAB SEP_AVT_MAJ "registrePC" RET );
    AfficherValeurRegistrePC( );
    printf( TAB SEP_FIN RET );
#endif

    registrePC = operandeIR;
    
#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registrePC" RET );
    AfficherValeurRegistrePC( );
    printf( TAB SEP_FIN RET );
    printf( "- RecopierOperandeDansPC." RET);
#endif
}

// Fonction permettant de recopier le mot contenu dans un registre
// en mémoire
// ATTENTION : l'operande IR doit avoir été mise à jour auparavant
void RecopierMotRegistreEnMemoire( unint * registre, uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ RecopierMotRegistreEnMemoire." RET);
#endif
    
    switch( modeAdressage )
    {
        case IMMEDIAT:
            // Impossible
            break;
      
        case DIRECT:
            EcrireMotEnMemoire( (* registre), operandeIR );
            break;

        case INDIRECT:
        	EcrireMotEnMemoire( (* registre), LireMotEnMemoire( operandeIR ) );
        	break;

        case PILE:
        	EcrireMotEnMemoire( (* registre), operandeIR + registreSP );
        	break;

        case PILE_INDIRECT:
        	EcrireMotEnMemoire( (* registre), LireMotEnMemoire( operandeIR + registreSP ) );
        	break;

        case INDEXE:
        	EcrireMotEnMemoire( (* registre), operandeIR + registreX );
        	break;

        case INDEXE_PILE:
        	EcrireMotEnMemoire( (* registre), operandeIR + registreSP + registreX );
        	break;

        case INDEXE_PILE_INDIRECT:
        	EcrireMotEnMemoire( (* registre), LireMotEnMemoire( operandeIR + registreSP ) + registreX );
        	break;

        default:
        	// Impossible
            break;
    }

#ifdef DEBUG
    printf( "- RecopierMotRegistreEnMemoire." RET);
#endif
}

// Fonction permettant de recopier la partie droite (8 bits)
// d'un mot (contenu dans un registre) en mémoire
// ATTENTION : l'operande IR doit avoir été mise à jour auparavant
void RecopierOctetRegistreEnMemoire( unint * registre, uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ RecopierOctetRegistreEnMemoire." RET);
#endif

    switch( modeAdressage )
    {
        case IMMEDIAT:
            // Impossible
            break;

        case DIRECT:
            EcrireOctetEnMemoire( (* registre), operandeIR );
            break;

        case INDIRECT:
        	EcrireOctetEnMemoire( (* registre), LireMotEnMemoire( operandeIR ) );
        	break;

        case PILE:
        	EcrireOctetEnMemoire( (* registre), operandeIR + registreSP );
        	break;

        case PILE_INDIRECT:
        	EcrireOctetEnMemoire( (* registre), LireMotEnMemoire( operandeIR + registreSP ) );
        	break;

        case INDEXE:
        	EcrireOctetEnMemoire( (* registre), operandeIR + registreX );
        	break;

        case INDEXE_PILE:
        	EcrireOctetEnMemoire( (* registre), operandeIR + registreSP + registreX );
        	break;

        case INDEXE_PILE_INDIRECT:
        	EcrireOctetEnMemoire( (* registre), LireMotEnMemoire( operandeIR + registreSP  ) + registreX );
        	break;

        default:
        	// Impossible
            break;
    }

#ifdef DEBUG
    printf( "- RecopierOctetRegistreEnMemoire." RET);
#endif
}

// Fonction permettant de récupérer un mot (16bits) en mémoire, connaissant
// le mode d'adressage pour y accéder.
// ATTENTION : la variable operandeIR, doit auparavant
// avoir été mise à jour.
unint RecupererMotEnMemoire( uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ RecupererMotEnMemoire." RET);
#endif

    unint valeurRecuperee = 0;
    switch( modeAdressage )
    {
        case IMMEDIAT:
            valeurRecuperee = operandeIR;
            break;

       case DIRECT:
    	   valeurRecuperee = LireMotEnMemoire( operandeIR );
    	   break;

        case INDIRECT:
        	valeurRecuperee = LireMotEnMemoire( LireMotEnMemoire( operandeIR ) );
        	break;

        case PILE:
        	valeurRecuperee = LireMotEnMemoire( registreSP + operandeIR );
        	break;

        case PILE_INDIRECT:
        	valeurRecuperee = LireMotEnMemoire( LireMotEnMemoire( registreSP + operandeIR ) );
        	break;

        case INDEXE:
        	valeurRecuperee = LireMotEnMemoire( registreX + operandeIR );;
        	break;

        case INDEXE_PILE:
        	valeurRecuperee = LireMotEnMemoire( operandeIR + registreSP + registreX );
        	break;

        case INDEXE_PILE_INDIRECT:
        	valeurRecuperee = LireMotEnMemoire( LireMotEnMemoire( operandeIR + registreSP ) + registreX );
        	break;

        default:
        	// Impossible
            break;
    }

#ifdef DEBUG
    printf( "- RecupererMotEnMemoire." RET);
#endif

    return valeurRecuperee;
}

// Fonction permettant de récupérer un octet (8 bits) en mémoire, connaissant
// le mode d'adressage pour y accéder.
// ATTENTION : la variable operandeIR, doit auparavant
// avoir été mise à jour.
uchar RecupererOctetEnMemoire( uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ RecupererOctetEnMemoire." RET);
#endif

    uchar valeurRecuperee = 0;
    switch( modeAdressage )
    {
        case IMMEDIAT:
            valeurRecuperee = ( operandeIR & MASQUE_8_BITS_D );
            break;

        case DIRECT:
     	   valeurRecuperee = LireOctetEnMemoire( operandeIR );
     	   break;

         case INDIRECT:
         	valeurRecuperee = LireOctetEnMemoire( LireMotEnMemoire( operandeIR ) );
         	break;

         case PILE:
         	valeurRecuperee = LireOctetEnMemoire( registreSP + operandeIR );
         	break;

         case PILE_INDIRECT:
         	valeurRecuperee = LireOctetEnMemoire( LireMotEnMemoire( registreSP + operandeIR ) );
         	break;

         case INDEXE:
         	valeurRecuperee = LireOctetEnMemoire( registreX + operandeIR );;
         	break;

         case INDEXE_PILE:
         	valeurRecuperee = LireOctetEnMemoire( operandeIR + registreSP + registreX );
         	break;

         case INDEXE_PILE_INDIRECT:
         	valeurRecuperee = LireOctetEnMemoire( LireMotEnMemoire( operandeIR + registreSP ) + registreX );
         	break;

         default:
         	// Impossible
             break;
    }

#ifdef DEBUG
    printf( "- RecupererOctetEnMemoire." RET);
#endif

    return valeurRecuperee;
}
