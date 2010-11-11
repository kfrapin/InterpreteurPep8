/* 
 * File:   fonctions.c
 * Author: mousseyed, kevin
 *
 * Created on October 20, 2010, 12:22 PM
 */

//--------------------------------------------------- INCLUDE SYSTEMES

//--------------------------------------------------- INCLUDE PERSONNELS
#include "../includes/constantes.h"
#include "../includes/erreurs.h"
#include "../includes/fonctions.h"
#include "../includes/globales.h"
#ifdef DEBUG
    #include "../includes/debug.h"
#endif

//--------------------------------------------------- FONCTIONS
// Fonction permettant d'empiler la donnee sur 1 mot
// de 16 bits, en mettant à jour le registreSP
void EmpilerMot( uint donnee )
{
#ifdef DEBUG
    printf( "+ EmpilerMot." RET);
    printf( TAB SEP_AVT_MAJ "registreSP" RET );
    AfficherValeurRegistreSP( );
    printf( TAB SEP_FIN RET );
#endif
    
    // On coupe la donnee en 2 x 8 bits
    uchar bitsDroite = (uchar) donnee;
    uchar bitsGauche = (uchar) (donnee >> 8);

    // On sauvegarde d'abord les bits de droite,
    // et ensuite ceux de gauche
    memoire[--registreSP] = bitsDroite;
    memoire[--registreSP] = bitsGauche;
    
#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreSP" RET );
    AfficherValeurRegistreSP( );
    printf( TAB SEP_FIN RET );
    printf( "- EmpilerMot." RET);
#endif    
}

// Fonction permettant d'ajouter une valeur a un registre
void AdditionerRegistre( uint * registreConcerne, uint valeurAAjouter )
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
    uint valeurRegistre = ( * registreConcerne );

    // Signes des opérandes
    uint signeRegistre = valeurRegistre >> 15;
    uint signeValeur = valeurAAjouter >> 15;
    uint debordement, resultat, retenue;

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

// Fonction permettant de decaler un registre vers la droite
void inline DecalerDroiteRegistre( uint * registre )
{
#ifdef DEBUG
    printf( "+ DecalerDroiteRegistre." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
#endif
    // On passe en valeur signée sur 16 bits pour conserver
    // le bit du signe apres le decalage
    ssint valeurSignee = (ssint) ( * registre );

    ( * registre ) = ( valeurSignee >> 1 );

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
    printf( "- DecalerDroiteRegistre." RET);
#endif
}

// Fonction permettant de decaler un registre vers la gauche
void inline DecalerGaucheRegistre( uint * registre )
{
#ifdef DEBUG
    printf( "+ DecalerGaucheRegistre." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
#endif

    ( * registre ) = (ssint) ( ( * registre ) << 1 );

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
    printf( "- DecalerGaucheRegistre." RET);
#endif
}

// Fonction permettant d'ecrire un mot (16 bits) en memoire
void inline EcrireMotEnMemoire( uint valeur, uint adresse )
{
#ifdef DEBUG
    printf( "+ EcrireMotEnMemoire." RET);
    printf( TAB SEP_AVT_MAJ "memoire[ ]" RET );
    printf( TAB "Valeur memoire[%u] : %u" RET, (adresse & MASQUE_16_BITS), memoire[adresse & MASQUE_16_BITS] );
    printf( TAB "Valeur memoire[%u] : %u" RET,(adresse+1) & MASQUE_16_BITS, memoire[(adresse+1) & MASQUE_16_BITS] );
    printf( TAB SEP_FIN RET );
#endif

    // On sauvegarde d'abord les 8 bits de gauche
    memoire[ adresse & MASQUE_16_BITS ] = ( valeur >> 8 );

    // Puis les 8 bits de droite
    memoire[ ( adresse + 1 ) & MASQUE_16_BITS ] =  valeur;

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "memoire[ ]" RET );
    printf( TAB "Valeur memoire[%u] : %u" RET, (adresse & MASQUE_16_BITS), memoire[adresse & MASQUE_16_BITS] );
    printf( TAB "Valeur memoire[%u] : %u" RET,(adresse+1) & MASQUE_16_BITS, memoire[ (adresse+1) & MASQUE_16_BITS] );
    printf( TAB SEP_FIN RET );
    printf( "- EcrireMotEnMemoire." RET);
#endif
}

// Fonction permettant d'ecrire un octet (8 bits) en memoire
void inline EcrireOctetEnMemoire( uint valeur, uint adresse )
{
#ifdef DEBUG
    printf( "+ EcrireOctetEnMemoire." RET);
    printf( TAB SEP_AVT_MAJ "memoire[ ]" RET );
    printf( TAB "Valeur memoire[%u] : %u" RET, (adresse & MASQUE_16_BITS), memoire[adresse & MASQUE_16_BITS] );
    printf( TAB SEP_FIN RET );
#endif

    // On sauvegarde les 8 bits de droite uniquement
    memoire[ adresse & MASQUE_16_BITS ] = valeur;

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "memoire[ ]" RET );
    printf( TAB "Valeur memoire[%u] : %u" RET, (adresse & MASQUE_16_BITS), memoire[adresse & MASQUE_16_BITS] );
    printf( TAB SEP_FIN RET );
    printf( "- EcrireOctetEnMemoire." RET);
#endif
}

// Fonction permettant d'executer l'instruction ADDr 
// en fonction des 4 bits de droite
schar ExecuterADDr( uchar opcodeDroite )
{
#ifdef DEBUG
    printf( "+ ExecuterADDr." RET);
#endif

    // On récupère l'opérande
    MettreAJourOperandeIR();

    // Registre concerné par l'opération
    uint * registreConcerne;

    if( (opcodeDroite & 8) == 0 )
    // Addition sur le registre A
    {
        registreConcerne = &registreA;
    }
    else
    // Addition sur le registre X
    {
        registreConcerne = &registreX;
    }

    // Récupération du mode d'adressage et de la donnée
    uchar adressage = opcodeDroite & 7;
    uint valeurRecuperee = RecupererMotEnMemoire( adressage );

    // On effectue l'addition
    AdditionerRegistre( registreConcerne, valeurRecuperee );


#ifdef DEBUG
    printf( "- ExecuterADDr." RET);
#endif
}

// Fonction permettant d'executer l'instruction ANDr
// en fonction des 4 bits de droite
schar ExecuterANDr( uchar opcodeDroite )
{
#ifdef DEBUG
    printf( "+ ExecuterANDr." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
#endif

    // On récupère l'opérande
    MettreAJourOperandeIR( );

    // Registre concerné par l'opération
    uint * registreConcerne;

    if( (opcodeDroite & 8) == 0 )
    // Addition sur le registre A
    {
        registreConcerne = &registreA;
    }
    else
    // Addition sur le registre X
    {
        registreConcerne = &registreX;
    }

    // Récupération du mode d'adressage et de la donnée
    uchar adressage = opcodeDroite & 7;
    uint valeurRecuperee = RecupererMotEnMemoire( adressage );

    // Mise à jour du registre
    uint nouvelleValeur = ( * registreConcerne ) & valeurRecuperee;
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
}

// Fonction permettant d'executer l'instruction LDBYTEr
// en fonction des 4 bits de droite
schar ExecuterLDBYTEr( uchar opcodeDroite )
{
#ifdef DEBUG
    printf( "+ ExecuterLDBYTEr." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
#endif

    // On récupère l'opérande
    MettreAJourOperandeIR( );

    // Registre concerné par l'opération
    uint * registreConcerne;

    if( (opcodeDroite & 8) == 0 )
    // Chargement dans le registre A
    {
        registreConcerne = &registreA;
    }
    else
    // Chargement dans le registre X
    {
        registreConcerne = &registreX;
    }

    // Récupération du mode d'adressage et de la donnée
    uchar adressage = opcodeDroite & 7;
    ( * registreConcerne ) = 
            ( ( (*registreConcerne) & MASQUE_8_BITS_G )
                | RecupererOctetEnMemoire( adressage )
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
}

// Fonction permettant d'executer l'instruction LDr
// en fonction des 4 bits de droite
schar ExecuterLDr( uchar opcodeDroite )
{
#ifdef DEBUG
    printf( "+ ExecuterLDr." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
#endif

    // On récupère l'opérande
    MettreAJourOperandeIR( );

    // Registre concerné par l'opération
    uint * registreConcerne;

    if( (opcodeDroite & 8) == 0 )
    // Chargement dans le registre A
    {
        registreConcerne = &registreA;
    }
    else
    // Chargement dans le registre X
    {
        registreConcerne = &registreX;
    }

    // Récupération du mode d'adressage et de la donnée
    uchar adressage = opcodeDroite & 7;
    ( * registreConcerne ) = RecupererMotEnMemoire( adressage );

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
}

// Fonction permettant d'executer l'instruction CPr
// en fonction des 4 bits de droite
schar ExecuterCPr( uchar opcodeDroite )
{
#ifdef DEBUG
    printf( "+ ExecuterCPr." RET);
#endif

    // On récupère l'opérande
    MettreAJourOperandeIR( );

    // Registre concerne par la comparaison
    uint valeurRegistre;

    if( (opcodeDroite & 8) == 0 )
    // Comparaison sur le registre A
    {
        valeurRegistre = registreA;
    }
    else
    // Comparaison sur le registre X
    {
        valeurRegistre = registreX;
    }

    // Récupération du mode d'adressage et de la donnée
    uchar adressage = opcodeDroite & 7;
    uint valeurRecuperee = RecupererMotEnMemoire( adressage );

    // On utilise la fonction "AdditionerRegistre", sauf qu'au lieu
    // de tester un registre, elle va tester notre sa valeur dans une
    // variable sans importance -» Non modification du registre
    AdditionerRegistre( &valeurRegistre, ((~valeurRecuperee + 1) & MASQUE_16_BITS) );
            
#ifdef DEBUG
    printf( "- ExecuterCPr." RET);
#endif
}

// Fonction permettant d'executer l'instruction ORr
// en fonction des 4 bits de droite
schar ExecuterORr( uchar opcodeDroite )
{
#ifdef DEBUG
    printf( "+ ExecuterORr." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
#endif

    // Mise à jour de l'opérande
    MettreAJourOperandeIR( );

    // Registre concerné par l'opération
    uint * registreConcerne;

    if( (opcodeDroite & 8) == 0 )
    // Addition sur le registre A
    {
        registreConcerne = &registreA;
    }
    else
    // Addition sur le registre X
    {
        registreConcerne = &registreX;
    }

    // Récupération du mode d'adressage et de la donnée
    uchar adressage = opcodeDroite & 7;
    uint valeurRecuperee = RecupererMotEnMemoire( adressage );

    // Mise à jour du registre
    uint nouvelleValeur = ( * registreConcerne ) | valeurRecuperee;
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
        // Traitement à metrre en place (cf. chapitre 12 du cours du prof)
        return;
    }

    else if( opcodeDroite == MOVSPA_FIN )
    {
        // Copie du pointeur de pile dans le registre A
        registreA = registreSP;
        return;
    }
    else if( opcodeDroite == MOVFLGA_FIN )
    {
        // Copie de NZVC dans le registre A (dans les 4 bits de droite)
        registreA = 0;
        uchar decalageN = codeN << 3;
        uchar decalageZ = codeZ << 2;
        uchar decalageV = codeV << 1;
        registreA = decalageN | decalageZ | decalageV | codeC;
        return;
    }

    // Ici, on sait que : opcodeFin > MOVFLGA_FIN
    // Donc certains tests ont pu être supprimés, et on sait qu'on a besoin de
    // récupérer l'opérande passé à l'instruction
    MettreAJourOperandeIR( );

    if( opcodeDroite <= BR_FIN_S )
    {
        if( (opcodeDroite & 1) == 0 )
        // Adressage immédiat
        {
            // On met dans le registre PC la valeur fournit en opérande
            RecopierOperandeDansPC( );
        }
        // Adressage indexé
        // TODO à mettre en place
    }

    else if( opcodeDroite <= BRLE_FIN_S )
    {
        if( (codeZ == 1) || (codeN == 1) )
        {
            if( (opcodeDroite & 1) == 0 )
            // Adressage immédiat
            {
                // On met dans le registre PC la valeur fournit en opérande
                RecopierOperandeDansPC( );
            }
            // Adressage indexé
            // TODO à mettre en place
        }

    }

    else if( opcodeDroite <= BRLT_FIN_S )
    {
        if( codeN == 1 )
        {
            if( (opcodeDroite & 1) == 0 )
            // Adressage immédiat
            {
                // On met dans le registre PC la valeur fournit en opérande
                RecopierOperandeDansPC( );
            }
            // Adressage indexé
            // TODO à mettre en place
        }
    }

    else if( opcodeDroite <= BREQ_FIN_S )
    {

        if( codeZ == 1 )
        {
            if( (opcodeDroite & 1) == 0 )
            // Adressage immédiat
            {
                // On met dans le registre PC la valeur fournit en opérande
                RecopierOperandeDansPC( );
            }
            // Adressage indexé
            // TODO à mettre en place
        }
    }

    else if( opcodeDroite <= BRNE_FIN_S )
    {
        if( codeZ == 0 )
        {
            if( (opcodeDroite & 1) == 0 )
            // Adressage immédiat
            {
                // On met dans le registre PC la valeur fournit en opérande
                RecopierOperandeDansPC( );
            }
            // Adressage indexé
            // TODO à mettre en place
        }
        
    }

    else
    {
        // Si on arrive ici, instruction = BRGE
        if( codeN == 0 )
        {
            if( (opcodeDroite & 1) == 0 )
            // Adressage immédiat
            {
                // On met dans le registre PC la valeur fournit en opérande
                RecopierOperandeDansPC( );
            }
            // Adressage indexé
            // TODO à mettre en place
        }

    }
    
#ifdef DEBUG
    printf( "- ExecuterInstGr1." RET);
#endif
}

// Fonction permettant d'executer l'instruction du groupe
// GRINST2 au vu de la valeur des 4 derniers bits fournis.
schar ExecuterInstGr2( uchar opcodeDroite )
{
#ifdef DEBUG
    printf( "+ ExecuterInstGr2." RET);
#endif

    if( opcodeDroite <= BRGT_FIN_S )
    {
        // Mise a jour de l'operande
        MettreAJourOperandeIR( );

        if( (codeN == 0) && (codeZ == 0) )
        {
            if( (opcodeDroite & 1) == 0 )
            // Adressage immédiat
            {
                // On met dans le registre PC la valeur fournit en opérande
                RecopierOperandeDansPC( );
            }
            // Adressage indexé
            // TODO à mettre en place
        }
        return;
    }
    else if( opcodeDroite <= BRV_FIN_S )
    {
        // Mise a jour de l'operande
        MettreAJourOperandeIR( );

        if( codeV == 1 )
        {
            if( (opcodeDroite & 1) == 0 )
            // Adressage immédiat
            {
                // On met dans le registre PC la valeur fournit en opérande
                RecopierOperandeDansPC( );
            }
            // Adressage indexé
            // TODO à mettre en place
        }
        return;
    }
    else if( opcodeDroite <= BRC_FIN_S )
    {
        // Mise a jour de l'operande
        MettreAJourOperandeIR( );

        if( codeC == 1 )
        {
            if( (opcodeDroite & 1) == 0 )
            // Adressage immédiat
            {
                // On met dans le registre PC la valeur fournit en opérande
                RecopierOperandeDansPC( );
            }
            // Adressage indexé
            // TODO à mettre en place
        }
        return;
    }
    else if( opcodeDroite <= CALL_FIN_S )
    {
        // Mise a jour de l'operande
        MettreAJourOperandeIR( );

        // On sauvegarde le registrePC sur la pile
        EmpilerMot( registrePC );

        if( (opcodeDroite & 1) == 0 )
        // Adressage immédiat
        {
            // On met dans le registre PC la valeur fournit en opérande
            RecopierOperandeDansPC( );
        }
        // Adressage indexé
        // TODO à mettre en place
        return;
    }

    // A partir d'ici, on est toujours obligé de recuperer
    // le registre concerne par l'operation
    // Registre concerne par la negation
    uint * registreConcerne;

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
        // On effectue la negation du registre
        NierRegistre( registreConcerne );
    }
    else if( opcodeDroite <= NEGR_FIN_S )
    {
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
    }
    else if( opcodeDroite <= ASLR_FIN_S )
    {
        // On recupere le bit de signe qui va "partir" dans
        // le code de condition C
        uchar ancienSigne = ( (*registreConcerne) >> 15 ) & 1;

        // On decale le regitre vers la gauche
        DecalerGaucheRegistre( registreConcerne );

        // Mise a jour des codes de condition V, C
        MettreAJourC( ancienSigne );
        
        uchar nouveauSigne = ( (*registreConcerne) >> 15 ) & 1;
        MettreAJourV( ((ancienSigne == nouveauSigne) ? 0 : 1) );
    }
    else if( opcodeDroite <= ASRR_FIN_S )
    {
        // Mise a jour du code de condition C avec le bit
        // qui "sort"
        MettreAJourC( ( ( * registreConcerne ) & 1 ) );

        // On decale le regitre vers la droite
        DecalerDroiteRegistre( registreConcerne );
    }

    // Mise à jour des codes de condition N,Z
    MettreAJourN( (* registreConcerne) );
    MettreAJourZ( (* registreConcerne) );

#ifdef DEBUG
    printf( "- ExecuterInstGr2." RET);
#endif
}

// Fonction permettant d'executer l'instruction du groupe
// GRINST5 au vu de la valeur des 4 derniers bits fournis.
schar ExecuterInstGr5( uchar opcodeDroite)
{
    // TODO : à implémenter
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

    }
    else
    // Opération RETn
    {
        ExecuterRETn( opcodeDroite );
    }

#ifdef DEBUG
    printf( "- ExecuterInstGr6." RET);
#endif
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

    if( opcodeDroite <= ADDSP_FIN_S )
    {
        // On effectue l'addition
        AdditionerRegistre( &registreSP, operandeIR );
    }
    else
    {
        // On effectue la soustraction
        AdditionerRegistre( &registreSP, ((~operandeIR + 1) & MASQUE_16_BITS) );
    }

#ifdef DEBUG
    printf( "- ExecuterInstGr7." RET);
#endif
}


// Fonction permettant d'executer l'instruction RETr
// en fonction des 4 bits de droite
schar ExecuterRETn( uchar opcodeDroite )
{
#ifdef DEBUG
    printf( "+ ExecuterRETn." RET);
    printf( TAB SEP_AVT_MAJ "registrePC, registreSP" RET );
    AfficherValeurRegistrePC( );
    AfficherValeurRegistreSP( );
    printf( TAB SEP_FIN RET );
#endif

    // On récupère la taille à désempiler
    uchar taille = ( opcodeDroite & 7 );

    // On désempile
    registreSP += taille;

    // On met à jour le registre PC, et on désempile
    // 8 bits de gauche
    registrePC = 0 | ( memoire[registreSP++] << 8 );
    // 8 bits de droite
    registrePC = registrePC | memoire[registreSP++];

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registrePC, registreSP" RET );
    AfficherValeurRegistrePC( );
    AfficherValeurRegistreSP( );
    printf( TAB SEP_FIN RET );
    printf( "- ExecuterRETn." RET);
#endif
}

// Fonction permettant d'executer l'instruction STr
// en fonction des 4 bits de droite
schar ExecuterSTr( uchar opcodeDroite )
{
#ifdef DEBUG
    printf( "+ ExecuterSTr." RET);
#endif

    // On récupère l'opérande
    MettreAJourOperandeIR( );

    uint *  registreConcerne;

    if( (opcodeDroite & 8) == 0 )
    // Soustraction sur le registre A
    {
        registreConcerne = &registreA;
    }
    else
    // soustraction sur le registre X
    {
        registreConcerne = &registreX;
    }

    // Récupération du mode d'adressage et de la donnée
    uchar adressage = opcodeDroite & 7;

    // On recopie le contenu du registre en mémoire
    RecopierMotRegistreEnMemoire( registreConcerne, adressage );

#ifdef DEBUG
    printf( "- ExecuterSTr." RET);
#endif
}

// Fonction permettant d'executer l'instruction STBYTEr
// en fonction des 4 bits de droite
schar ExecuterSTBYTEr( uchar opcodeDroite )
{
#ifdef DEBUG
    printf( "+ ExecuterSTBYTEr." RET);
#endif

    // On récupère l'opérande
    MettreAJourOperandeIR( );

    uint *  registreConcerne;

    if( (opcodeDroite & 8) == 0 )
    // Soustraction sur le registre A
    {
        registreConcerne = &registreA;
    }
    else
    // soustraction sur le registre X
    {
        registreConcerne = &registreX;
    }

    // Récupération du mode d'adressage et de la donnée
    uchar adressage = opcodeDroite & 7;

    // On recopie les 8 bits de droites du registre en mémoire
    RecopierOctetRegistreEnMemoire( registreConcerne, adressage );

#ifdef DEBUG
    printf( "- ExecuterSTBYTEr." RET);
#endif
}

// Fonction permettant d'executer l'instruction r
// en fonction des 4 bits de droite
schar ExecuterSUBr( uchar opcodeDroite )
{
#ifdef DEBUG
    printf( "+ ExecuterSUBr." RET);
#endif

    // On récupère l'opérande
    MettreAJourOperandeIR();

    // Registre concerné par l'opération
    uint * registreConcerne;

    if( (opcodeDroite & 8) == 0 )
    // Soustraction sur le registre A
    {
        registreConcerne = &registreA;
    }
    else
    // soustraction sur le registre X
    {
        registreConcerne = &registreX;
    }

    // Récupération du mode d'adressage et de la donnée
    uchar adressage = opcodeDroite & 7;
    uint valeurRecuperee = RecupererMotEnMemoire( adressage );

    // On effectue la soustraction
    AdditionerRegistre( registreConcerne, ( (~valeurRecuperee + 1) & MASQUE_16_BITS) );

#ifdef DEBUG
    printf( "- ExecuterSUBr." RET);
#endif
}

// Fonction permettant de lire un mot (16 bits) en mémoire
uint LireMotEnMemoire( uint adresse )
{
#ifdef DEBUG
    printf( "+ LireMotEnMemoire." RET);
#endif

    // Récupération des 8 bits de gauche
    uint bitsGauche = memoire[ adresse & MASQUE_16_BITS ];

    // Récupération des 8 bits de droite
    uint bitsDroite = memoire[ ( adresse + 1 ) & MASQUE_16_BITS ];

#ifdef DEBUG
    printf( "- LireMotEnMemoire." RET);
#endif

    return ( ( bitsGauche << 8 ) | bitsDroite );
}

// Fonction permettant de lire un octet (8 bits) en mémoire
uint LireOctetEnMemoire( uint adresse )
{
#ifdef DEBUG
    printf( "+ LireOctetEnMemoire." RET);
#endif

#ifdef DEBUG
    printf( "- LireOctetEnMemoire." RET);
#endif

    return memoire[ adresse & MASQUE_16_BITS ];
}


// Fonction permetter d'effectuer un NOT sur un registre
void inline NierRegistre( uint * registre )
{
#ifdef DEBUG
    printf( "+ NierRegistre." RET);
    printf( TAB SEP_AVT_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
#endif

    // On effectue la négation du registre
    ( * registre ) = (ssint) ~( * registre );

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "registreA | registreX" RET );
    AfficherValeurRegistreA( );
    AfficherValeurRegistreX( );
    printf( TAB SEP_FIN RET );
    printf( "- NierRegistre." RET);
#endif
}

// Fonction permetter d'effectuer une negation en complement
// a deux sur un registre
void inline NierRegistreEnComplement( uint * registre )
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
void inline MettreAJourC( uchar retenue )
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
void inline MettreAJourN( uint valeurRegistre )
{
#ifdef DEBUG
    printf( "+ MettreAJourN." RET);
    printf( TAB SEP_AVT_MAJ "codeN" RET );
    AfficherValeurCodeN( );
    printf( TAB SEP_FIN RET );
#endif

    codeN = (((valeurRegistre >> 15) & 1) == 1) ? 1 : 0;

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "codeN" RET );
    AfficherValeurCodeN( );
    printf( TAB SEP_FIN RET );
    printf( "- MettreAJourN." RET);
#endif
}

// Fonctions permettant de mettre à jour les codes de condition V
// en passant la valeur à leur affecter en paramètre
void inline MettreAJourV( uchar debordement )
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
void inline MettreAJourZ( uint valeurRegistre )
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
    uint bitsGaucheOperande = memoire[registrePC++];
    uint bitsDroiteOperande = memoire[registrePC++];


    // On décale les bits de gauche pour qu'ils soient vraiment à gauche
    uint bitsGaucheDecalage = bitsGaucheOperande << 8;

    operandeIR =  bitsGaucheDecalage | bitsDroiteOperande;

#ifdef DEBUG
    printf( TAB SEP_APR_MAJ "operandeIR" RET );
    AfficherValeurOperandeIR( );
    printf( TAB SEP_FIN RET );
    printf( "- MettreAJourOperandeIR." RET);
#endif
}

// Fonction permettant de recopier un fichier dans une zone mémoire
void RecopierFichierEnMemoire( FILE * fichier, uchar * memoire )
{
#ifdef DEBUG
    printf( "+ RecopierFichierEnMemoire." RET);
#endif
    // On lit le premier caractere
    uint caracLu = fgetc( fichier );

    uint index = 0;

    while( caracLu != EOF )
    {
#ifdef DEBUG
        printf( TAB "Caractere copie en memoire : %d" RET, caracLu );
#endif
        memoire[index++] = caracLu;
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
void RecopierMotRegistreEnMemoire( uint * registre, uchar modeAdressage )
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
void RecopierOctetRegistreEnMemoire( uint * registre, uchar modeAdressage )
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
uint RecupererMotEnMemoire( uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ RecupererMotEnMemoire." RET);
#endif

    uint valeurRecuperee = 0;
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
uint RecupererOctetEnMemoire( uchar modeAdressage )
{
#ifdef DEBUG
    printf( "+ RecupererOctetEnMemoire." RET);
#endif

    uint valeurRecuperee = 0;
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
