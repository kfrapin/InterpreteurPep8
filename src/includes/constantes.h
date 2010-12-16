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
 * File:   definitions.h
 * Author: mousseyed, kevin
 *
 * Created on October 20, 2010, 11:31 AM
 *
 * DESCRIPTION
 * ----------------------------------------------------------------------------
 *
 *  La structure du fichier est la suivante :
 *
 *  0./ Constantes definies pour le systeme d'exploitation
 *  1./ Constantes (arbitraires) pour définir les opcodes
 *  2./ Constantes permettant de savoir avec les 4 premiers bits :
 *          - Le groupe d'instructions auquel appartient l'opcode (cf. 3./)
 *     [OU] - L'opcode lui-même 
 *  3./ Constantes permettant de définir les opcodes de chaque groupe au vu des
 *      4 derniers bits.
 *   4./ Constantes permettant de définir les modes d'adressages
 *   5./ Constantes permettant de definir les bornes inferieures de chaque instruction
 *   6./ Constantes utilisees pour le predecodage
 * ----------------------------------------------------------------------------
 */

#ifndef CONSTANTES_H
#define	CONSTANTES_H

// Define utilisé pour effectuer des tests, debugs
// #define TEST
// #define DEBUG

//------------------------------------------------------------------------------------
//  0./ Constantes definies pour le systeme d'exploitation
//-------------------------------------------------------------------------------------

//--------------------------------------------------------- EMPLACEMENT OS
// Emplacement de l'OS par defaut
#define EMPLACEMENT_OS "systemeExploitation/OS.bin"

//--------------------------------------------------------- ENTREES DE LECTURE
// Indique que CHARI doit lire sur l'entree standard
#define ENTREE_STDIN (1)

// Indique que CHARI doit lire le fichier "fichierEntree" au lieu
// de la sortie standard
#define ENTREE_FICHIER (2)

//--------------------------------------------------------- VECTEURS INTERRUPTIONS
// Emplacement memoire contenant l'adresse
// du pointeur de pile utilisateur
#define ADR_MEM_SP_USER (0xFFF8)

// Emplacement memoire contenant l'adresse
// du pointeur de pile systeme
#define ADR_MEM_SP_SYS (0xFFFA)

// Emplacement memoire contenant l'adresse
// du LOADER
#define ADR_MEM_LOADER (0xFFFC)

// Emplacement memoire contenant l'adresse
// du TRAP HANDLER
#define ADR_MEM_TRAP_HANDLER (0xFFFE)


//--------------------------------------------------------- OUTILS PROGRAMME
// Taille allouée pour stocker l'ensemble du programme Pep8
#define TAILLE_MEMOIRE_MAX (0xFFFF )

// Masque sur 16 bits (pour les debordements,...)
#define MASQUE_16_BITS (0xFFFF)

// Masque pour les 8 bits de droite
#define MASQUE_8_BITS_D (0x00FF)

// Masque pour les 8 bits de gauche
#define MASQUE_8_BITS_G (0xFF00)


//----------------------------------------------------------------------------
//  1./ Constantes (arbitraires) pour définir les opcodes
//----------------------------------------------------------------------------
#define STOP    (0)
#define RETTR   (1)
#define MOVSPA  (2)
#define MOVFLGA (3)
#define BR      (4)
#define BRLE    (5)
#define BRLT    (6)
#define BREQ    (7)
#define BRNE    (8)
#define BRGE    (9)
#define BRGT    (10)
#define BRV     (11)
#define BRC     (12)
#define CALL    (13)
#define NOTR    (14)
#define NEGR    (15)
#define ASLR    (16)
#define ASRR    (17)
#define ROLR    (18)
#define RORR    (19)
#define NOPN    (20)
#define NOP     (21)
#define DECI    (22)
#define DECO    (23)
#define STRO    (24)
#define CHARI   (25)
#define CHARO   (26)
#define RETN    (27)
#define ADDSP   (28)
#define SUBSP   (29)
#define ADDR    (30)
#define SUBR    (31)
#define ANDR    (32)
#define ORR     (33)
#define CPR     (34)
#define LDR     (35)
#define LDBYTER (36)
#define STR     (37)
#define STBYTER (38)



//----------------------------------------------------------------------------
//  2./
//  Constantes contenant les valeurs possibles des 4 premiers bits d'un opcode
//----------------------------------------------------------------------------

// Constantes permettant de deviner le groupe auquel appartient l'opcode
// (1 groupe = opcodes dont les 4 premiers bits sont identiques)
#define GRINST1 0 //instructions concernees : STOP,RETTR,MOVSPA,MOVFLGA,BR,BRLE,BRLT,BREQ,BRNE,BRGE
#define GRINST2 1 //instructions concernees : BRGT,BRV,BRC,CALL,NOTR,NEGR,ASLR,ASRR
#define GRINST3 2 //instructions concernees : ROLR,RORR,NOPN,NOP
#define GRINST4 3 //instructions concernees : DECI,DECO
#define GRINST5 4 //instructions concernees : STRO,CHARI
#define GRINST6 5 //instructions concernees : CHARO,RETN
#define GRINST7 6 //instructions concernees : ADDSP, SUBSP

// Constantes permettant de deviner directement l'opcode
// (les 4 premiers bits de l'opcode sont uniques dans tout le jeu d'instrutions)
#define ADDR_DEB    7
#define SUBR_DEB    8
#define ANDR_DEB    9
#define ORR_DEB     10
#define CPR_DEB     11
#define LDR_DEB     12
#define LDBYTER_DEB 13
#define STR_DEB     14
#define STBYTER_DEB 15


//----------------------------------------------------------------------------
//  3./
//  Constantes contenant les valeurs possibles des 4 derniers bits d'un opcode
//----------------------------------------------------------------------------

// Groupe d'instructions : GRINST1
#define STOP_FIN    0
#define RETTR_FIN   1
#define MOVSPA_FIN  2
#define MOVFLGA_FIN 3
#define BR_FIN_I    4   // Borne inf. des valeurs possibles pour l'instruction BR
#define BR_FIN_S    5   // Borne sup. des valeurs possibles pour l'instrucion BR
#define BRLE_FIN_I  6
#define BRLE_FIN_S  7
#define BRLT_FIN_I  8
#define BRLT_FIN_S  9
#define BREQ_FIN_I  10
#define BREQ_FIN_S  11
#define BRNE_FIN_I  12
#define BRNE_FIN_S  13
#define BRGE_FIN_I  14
#define BRGE_FIN_S  15

// Groupe d'instructions : GRINST2
#define BRGT_FIN_I  0
#define BRGT_FIN_S  1
#define BRV_FIN_I   2
#define BRV_FIN_S   3
#define BRC_FIN_I   4
#define BRC_FIN_S   5
#define CALL_FIN_I  6
#define CALL_FIN_S  7
#define NOTR_FIN_I  8
#define NOTR_FIN_S  9
#define NEGR_FIN_I  10
#define NEGR_FIN_S  11
#define ASLR_FIN_I  12
#define ASLR_FIN_S  13
#define ASRR_FIN_I  14
#define ASRR_FIN_S  15

// Groupe d'instructions : GRINST3
#define ROLR_FIN_I  0
#define ROLR_FIN_S  1
#define RORR_FIN_I   2
#define RORR_FIN_S   3
#define NOPN_FIN_I   4
#define NOPN_FIN_S   7
#define NOP_FIN_I  8
#define NOP_FIN_S  15

// Groupe d'instructions : GRINST4
#define DECI_FIN_I  0
#define DECI_FIN_S  7
#define DECO_FIN_I   8
#define DECO_FIN_S   15

// Groupe d'instructions : GRINST5
#define STRO_FIN_I  0
#define STRO_FIN_S  7
#define CHARI_FIN_I   8
#define CHARI_FIN_S   15

// Groupe d'instructions : GRINST6
#define CHARO_FIN_I  0
#define CHARO_FIN_S  7
#define RETN_FIN_I   8
#define RETN_FIN_S   15

// Groupe d'instructions : GRINST7
#define ADDSP_FIN_I  0
#define ADDSP_FIN_S  7
#define SUBSP_FIN_I   8
#define SUBSP_FIN_S   15


//----------------------------------------------------------------------------
//  4./ Constantes permettant de définir les modes d'adressages
//----------------------------------------------------------------------------
#define IMMEDIAT                (0)
#define DIRECT                  (1)
#define INDIRECT                (2)
#define PILE                    (3)
#define PILE_INDIRECT           (4)
#define INDEXE                  (5)
#define INDEXE_PILE             (6)
#define INDEXE_PILE_INDIRECT    (7)

//----------------------------------------------------------------------------
//  5./ Constantes permettant de definir les bornes
//	inferieures de chaque instruction
// 	i.e. En ne tenant pas compte des informations
//	concernant les registres et/ou modes d'adressage
//----------------------------------------------------------------------------

// Instructions dont il n'y a rien a ignorer
// Deja definis dans 3./

// Instructions dont on ignore le mode d'adressage
// Ou instructions dont on ignore le registre
// (Bit le plus a droite)
#define BR_I    4
#define BRLE_I  6
#define BRLT_I  8
#define BREQ_I  10
#define BRNE_I  12
#define BRGE_I  14
#define BRGT_I  16
#define BRV_I   18
#define BRC_I   20
#define CALL_I  22
#define NOTR_I  24
#define NEGR_I  26
#define ASLR_I  28
#define ASRR_I  30
#define ROLR_I  32
#define RORR_I   34

// Instruction dont on ignore le valeur n
// (2 bits les plus a droite)
#define NOPN_I   36

// Instructions dont on ignore le mode d'adressage
// Ou instructions dont on ignore la valeur de n
// (3 bits les plus a droite)
#define NOP_I  40
#define DECI_I  48
#define DECO_I   56
#define STRO_I  64
#define CHARI_I   72
#define CHARO_I  80
#define RETN_I   88
#define ADDSP_I  96
#define SUBSP_I   104

// Instructions dont on ignore le mode d'adressage
// Et dont on ignore le registre
#define ADDR_I    	112
#define SUBR_I 		128
#define ANDR_I 		144
#define ORR_I 		160
#define CPR_I     		176
#define LDR_I     		192
#define LDBYTER_I 	208
#define STR_I     		224
#define STBYTER_I 	240

//----------------------------------------------------------------------------
//  6./ Constantes utilisees pour le predecodage
//----------------------------------------------------------------------------

// Constantes permettant de connaitre l'etat du decodage
// pour une instruction donnee
#define DECODAGE_A_FAIRE (0)
#define DECODAGE_FAIT			 (1)
#define DECODAGE_A_IGNORER	     (2)

#endif	/* CONSTANTES_H */

