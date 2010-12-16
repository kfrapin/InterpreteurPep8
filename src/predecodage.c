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
#include "includes/fonctions.h"
#include "includes/globales.h"
#include "includes/instructions.h"
#include "includes/predecodage.h"

//--------------------------------------------------- FONCTIONS

// Fonction permettant d'executer une instruction predecodee
unint JouerInstructionPredecodee( unint adresseMemoire )
{
#ifdef DEBUG
    puts( "+ JouerInstructionPredecodee.");
#endif

    // Predecodage de l'instruction
    predecodage decodage = codeDecode[adresseMemoire];
    switch( decodage.instructionDecodee )
    {
    	case RETTR:
    		ExecuterRETTR( );
    		break;

    	case MOVSPA:
    		ExecuterMOVSPA( );
    		break;

    	case MOVFLGA:
    		ExecuterMOVFLGA( );
    		break;

    	case BR:
    		MettreAJourOperandeIR( );
    		ExecuterBR( decodage.adressageDecode  );
    		break;

    	case BRLE:
    		MettreAJourOperandeIR( );
    		ExecuterBRLE( decodage.adressageDecode  );
    		break;

    	case BRLT:
    		MettreAJourOperandeIR( );
    		ExecuterBRLT( decodage.adressageDecode  );
    		break;

    	case BREQ:
    		MettreAJourOperandeIR( );
    		ExecuterBREQ( decodage.adressageDecode  );
    		break;

    	case BRNE:
    		MettreAJourOperandeIR( );
    		ExecuterBRNE( decodage.adressageDecode  );
    		break;

    	case BRGE:
    		MettreAJourOperandeIR( );
    		ExecuterBRGE( decodage.adressageDecode  );
    		break;

    	case BRGT:
    		MettreAJourOperandeIR( );
    		ExecuterBRGT( decodage.adressageDecode  );
    		break;

    	case BRV:
    		MettreAJourOperandeIR( );
    		ExecuterBRV( decodage.adressageDecode  );
    		break;

    	case BRC:
    		MettreAJourOperandeIR( );
    		ExecuterBRC( decodage.adressageDecode  );
    		break;

    	case CALL:
    		MettreAJourOperandeIR( );
    		ExecuterCALL( decodage.adressageDecode  );
    		break;

    	case NOTR:
    		ExecuterNOTr( decodage.registreDecode );
    		break;

    	case NEGR:
    		ExecuterNEGr( decodage.registreDecode );
    		break;

    	case ASLR:
    		ExecuterASLr( decodage.registreDecode );
    		break;

    	case ASRR:
    		ExecuterASRr( decodage.registreDecode );
    		break;

    	case ROLR:
    		ExecuterROLr( decodage.registreDecode );
    		break;

    	case RORR:
    		ExecuterRORr( decodage.registreDecode );
    		break;

    	case NOPN:
    	case NOP:
    		AppelerTrapHandler( );
    		break;

    	case DECI:
    	case DECO:
    	case STRO:
    	    MettreAJourOperandeIR( );
    	   	AppelerTrapHandler(  );
    	   	break;

    	case CHARI:
    		MettreAJourOperandeIR( );
    		ExecuterCHARI( decodage.adressageDecode );
    		break;

    	case CHARO:
    		MettreAJourOperandeIR( );
    		ExecuterCHARO( decodage.adressageDecode );
    		break;

    	case RETN:
    		// Lors du predecodage, la valeur de "n" est stockee
    		// dans le champ adressageDecode
    		ExecuterRETn( decodage.adressageDecode );
    		break;

    	case ADDSP:
    		MettreAJourOperandeIR( );
    		ExecuterADDSP( decodage.adressageDecode );
    		break;

    	case SUBSP:
    		MettreAJourOperandeIR( );
    		ExecuterSUBSP( decodage.adressageDecode );
    		break;

    	case ADDR:
    		MettreAJourOperandeIR( );
    		ExecuterADDr( decodage.registreDecode, decodage.adressageDecode );
    		break;

    	case SUBR:
    		MettreAJourOperandeIR( );
    		ExecuterSUBr( decodage.registreDecode, decodage.adressageDecode );
    		break;

    	case ANDR:
    		MettreAJourOperandeIR( );
    		ExecuterANDr( decodage.registreDecode, decodage.adressageDecode );
    		break;

    	case ORR:
    		MettreAJourOperandeIR( );
    		ExecuterORr( decodage.registreDecode, decodage.adressageDecode );
    		break;

    	case CPR:
    		MettreAJourOperandeIR( );
    		ExecuterCPr( decodage.registreDecode, decodage.adressageDecode );
    		break;

    	case LDR:
    		MettreAJourOperandeIR( );
    		ExecuterLDr( decodage.registreDecode, decodage.adressageDecode );
    		break;

    	case LDBYTER:
    		MettreAJourOperandeIR( );
    		ExecuterLDBYTEr( decodage.registreDecode, decodage.adressageDecode );
    		break;

    	case STR:
    		MettreAJourOperandeIR( );
    		ExecuterSTr( decodage.registreDecode, decodage.adressageDecode );
    		break;

    	case STBYTER:
    		MettreAJourOperandeIR( );
    		ExecuterSTBYTEr( decodage.registreDecode, decodage.adressageDecode );
    		break;
    }

#ifdef DEBUG
    puts( "- JouerInstructionPredecodee.");
#endif

    return EXIT_SUCCESS;
}

// Fonction permettant de predeocder une instruction
// et de stocker le code predecode dans la memoire
// codePredecode
unint PredecoderInstruction( unint adresseMemoire )
{
#ifdef DEBUG
    puts( "+ PredecoderInstruction.");
#endif

	// Variables utilisees pour stocker les informations sur le decodage
	unint instructionDecodee = 0;
	unint * registreDecode = 0;
	unint adressageDecode = 0;

	////////////////////////////////////////////////////////////////////////////////////////
	//	On teste si l'intruction peut etre reconnue directement
	// 	a partir du registre IR
	////////////////////////////////////////////////////////////////////////////////////////
	switch( instructionIR )
	{
		case RETTR:
			instructionDecodee = RETTR;
			break;

		case MOVSPA:
			instructionDecodee = MOVSPA;
			break;

		case MOVFLGA:
			instructionDecodee = MOVFLGA;
			break;
	}

	if( instructionDecodee != 0 )
	{
		// On indique que l'instruction est dorenavant predecodee
		codeDecode[adresseMemoire].etatDecodage = DECODAGE_FAIT;

		// On met a jour les champs pour le predecodage
		codeDecode[adresseMemoire].opCodeOriginal = instructionIR;
		codeDecode[adresseMemoire].instructionDecodee = instructionDecodee;
		codeDecode[adresseMemoire].registreDecode = registreDecode;
		codeDecode[adresseMemoire].adressageDecode = adressageDecode;
#ifdef DEBUG
    puts( "- PredecoderInstruction.");
#endif
		return EXIT_SUCCESS;
	}

	////////////////////////////////////////////////////////////////////////////////////////
	// Sinon on teste si l'instruction peut etre reconnue
	// a partir des 7 bits de gauche
	// (Adressage a decoder)
	////////////////////////////////////////////////////////////////////////////////////////
	unint bitsGauche = ( instructionIR & 0xFE );
	switch( bitsGauche )
	{
		case BR_I:
			instructionDecodee = BR;
			break;

		case BRLE_I:
			instructionDecodee = BRLE;
			break;

		case BRLT_I:
			instructionDecodee = BRLT;
			break;

		case BREQ_I:
			instructionDecodee = BREQ;
			break;

		case BRNE_I:
			instructionDecodee = BRNE;
			break;

		case BRGE_I:
			instructionDecodee = BRGE;
			break;

		case BRGT_I:
			instructionDecodee = BRGT;
			break;

		case BRV_I:
			instructionDecodee = BRV;
			break;

		case BRC_I:
			instructionDecodee = BRC;
			break;

		case CALL_I:
			instructionDecodee = CALL;
			break;
	}

	if( instructionDecodee != 0 )
	{
		// On recupere le mode d'adressage
		adressageDecode = ( ( instructionIR & 1 ) == 0 ) ? IMMEDIAT : INDEXE;

		// On indique que l'instruction est dorenavant predecodee
		codeDecode[adresseMemoire].etatDecodage = DECODAGE_FAIT;

		// On met a jour les champs pour le predecodage
		codeDecode[adresseMemoire].opCodeOriginal = instructionIR;
		codeDecode[adresseMemoire].instructionDecodee = instructionDecodee;
		codeDecode[adresseMemoire].registreDecode = registreDecode;
		codeDecode[adresseMemoire].adressageDecode = adressageDecode;
#ifdef DEBUG
    puts( "- PredecoderInstruction.");
#endif
		return EXIT_SUCCESS;
	}

	////////////////////////////////////////////////////////////////////////////////////////
	// Sinon on teste si l'instruction peut etre reconnue
	// a partir des 7 bits de gauche
	// (Registre a decoder)
	////////////////////////////////////////////////////////////////////////////////////////
	switch( bitsGauche )
	{
		case NOTR_I:
			instructionDecodee = NOTR;
			break;

		case  NEGR_I:
			instructionDecodee = NEGR;
			break;

		case  ASLR_I:
			instructionDecodee = ASLR;
			break;

		case  ASRR_I:
			instructionDecodee = ASRR;
			break;

		case  ROLR_I:
			instructionDecodee = ROLR;
			break;

		case  RORR_I:
			instructionDecodee = RORR;
			break;
	}

	if( instructionDecodee != 0 )
	{
		// On recupere le registre concerne
		registreDecode = ( ( instructionIR & 1 ) == 0 ) ? &registreA : &registreX;

		// On indique que l'instruction est dorenavant predecodee
		codeDecode[adresseMemoire].etatDecodage = DECODAGE_FAIT;

		// On met a jour les champs pour le predecodage
		codeDecode[adresseMemoire].opCodeOriginal = instructionIR;
		codeDecode[adresseMemoire].instructionDecodee = instructionDecodee;
		codeDecode[adresseMemoire].registreDecode = registreDecode;
		codeDecode[adresseMemoire].adressageDecode = adressageDecode;
#ifdef DEBUG
    puts( "- PredecoderInstruction.");
#endif
		return EXIT_SUCCESS;
	}

	////////////////////////////////////////////////////////////////////////////////////////
	// Sinon on teste si l'instruction peut etre reconnue
	// a partir des 6 bits de gauche
	////////////////////////////////////////////////////////////////////////////////////////
	bitsGauche = ( instructionIR & 0xFC );
	switch( bitsGauche )
	{
		case NOPN_I:
			instructionDecodee = NOPN;
			break;
	}

	if( instructionDecodee != 0 )
	{
		// On recupere la valeur de n, que l'on va stocker dans l'adressage
		// (Petit tour de passe-passe pour ne  pas declarer un nouveau champ)
		adressageDecode =  ( instructionIR & 3 );

		// On indique que l'instruction est dorenavant predecodee
		codeDecode[adresseMemoire].etatDecodage = DECODAGE_FAIT;

		// On met a jour les champs pour le predecodage
		codeDecode[adresseMemoire].opCodeOriginal = instructionIR;
		codeDecode[adresseMemoire].instructionDecodee = instructionDecodee;
		codeDecode[adresseMemoire].registreDecode = registreDecode;
		codeDecode[adresseMemoire].adressageDecode = adressageDecode;
#ifdef DEBUG
    puts( "- PredecoderInstruction.");
#endif
		return EXIT_SUCCESS;
	}

	////////////////////////////////////////////////////////////////////////////////////////
	// Sinon on teste si l'instruction peut etre reconnue
	// a partir des 5 bits de gauche
	////////////////////////////////////////////////////////////////////////////////////////
	bitsGauche = ( instructionIR & 0xF8 );
	switch( bitsGauche )
	{
		case NOP_I:
			instructionDecodee = NOP;
			break;

		case DECI_I:
			instructionDecodee = DECI;
			break;

		case DECO_I:
			instructionDecodee = DECO;
			break;

		case STRO_I:
			instructionDecodee = STRO;
			break;

		case CHARI_I:
			instructionDecodee = CHARI;
			break;

		case CHARO_I:
			instructionDecodee = CHARO;
			break;

		case RETN_I:
			instructionDecodee = RETN;
			break;

		case ADDSP_I:
			instructionDecodee = ADDSP;
			break;

		case SUBSP_I:
			instructionDecodee = SUBSP;
			break;
	}

	if( instructionDecodee != 0 )
	{
		// On recupere le mode d'adressage si l'instrucion n'est pas RETn
		// Sinon on recupere la valeur de n, que l'on va stocker dans l'adressage
		adressageDecode =  ( instructionIR & 7 );

		// On indique que l'instruction est dorenavant predecodee
		codeDecode[adresseMemoire].etatDecodage = DECODAGE_FAIT;

		// On met a jour les champs pour le predecodage
		codeDecode[adresseMemoire].opCodeOriginal = instructionIR;
		codeDecode[adresseMemoire].instructionDecodee = instructionDecodee;
		codeDecode[adresseMemoire].registreDecode = registreDecode;
		codeDecode[adresseMemoire].adressageDecode = adressageDecode;
#ifdef DEBUG
    puts( "- PredecoderInstruction.");
#endif
		return EXIT_SUCCESS;
	}

	////////////////////////////////////////////////////////////////////////////////////////
	// Sinon on teste si l'instruction peut etre reconnue
	// a partir des 4 bits de gauche
	////////////////////////////////////////////////////////////////////////////////////////
	bitsGauche = ( instructionIR & 0xF0 );
	switch( bitsGauche )
	{
		case ADDR_I:
			instructionDecodee = ADDR;
			break;

		case SUBR_I:
			instructionDecodee = SUBR;
			break;

		case ANDR_I:
			instructionDecodee = ANDR;
			break;

		case ORR_I:
			instructionDecodee = ORR;
			break;

		case CPR_I:
			instructionDecodee = CPR;
			break;

		case LDR_I:
			instructionDecodee = LDR;
			break;

		case LDBYTER_I:
			instructionDecodee = LDBYTER;
			break;

		case STR_I:
			instructionDecodee = STR;
			break;

		case STBYTER_I:
			instructionDecodee = STBYTER;
			break;
	}

	if( instructionDecodee != 0 )
	{
		// On recupere le mode d'adressage
		adressageDecode =  ( instructionIR & 7 );

		// On reucpere le registre concerne
		registreDecode = ( ( instructionIR & 8 ) == 0 ) ? &registreA : &registreX;

		// On indique que l'instruction est dorenavant predecodee
		codeDecode[adresseMemoire].etatDecodage = DECODAGE_FAIT;

		// On met a jour les champs pour le predecodage
		codeDecode[adresseMemoire].opCodeOriginal = instructionIR;
		codeDecode[adresseMemoire].instructionDecodee = instructionDecodee;
		codeDecode[adresseMemoire].registreDecode = registreDecode;
		codeDecode[adresseMemoire].adressageDecode = adressageDecode;
#ifdef DEBUG
    puts( "- PredecoderInstruction.");
#endif
		return EXIT_SUCCESS;
	}

#ifdef DEBUG
    puts( "- PredecoderInstruction.");
#endif

	// Impossible d'arriver ici
	return EXIT_FAILURE;


}
