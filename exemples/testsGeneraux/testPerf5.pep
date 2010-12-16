;3 Boucles imbriquées
;--------------------
; for( int j = 0; i<100; j++ )
;    for( int k = 0; k<1000; k++ )
;      for( int k = 0; k<1000; k++ )
;	{
;		NEGX
;	        ASLX 
;	        ASRX
;	        NOTX
;	        ORX     0x54CD,i
;	        ROLX
;	        ANDX    0x25E8,i
;	        RORX
;	        SUBX    0xCF12,i
;	        ADDX    0xD15C,i
;	}





         BR      main        
j:       .EQUATE 4           ;local variable #2d
k:       .EQUATE 2           ;local variable #2d
l:       .EQUATE 0           ;local variable #2d
;
main:    SUBSP   6,i         ;allocate #j #k #l
         LDA     0,i         
         STA     j,s         ; j = 0
         STA     k,s         ; k = 0
         STA     l,s         ; k = 0
         LDX     0x52DE,i
for:     LDA     j,s
         CPA     100,i         ;   j < 100
         BRGE    endFor      
         LDA     j,s         ;   j++)
         ADDA    1,i
         STA     j,s  
         LDA     0,i         
         STA     k,s         ; k = 0
         BR      for2         
for2:    LDA     k,s
         CPA     2000,i         ;   k < 2000
         BRGE    for      
         LDA     k,s         ;   k++)
         ADDA    1,i         
         STA     k,s  
         LDA     0,i         
         STA     l,s         ; l = 0
         BR      for3    
for3:    LDA     l,s
         CPA     1000,i         ;   l < 1000
         BRGE    for2      
         LDA     l,s         ;   l++)
         ADDA    1,i         
         STA     l,s  
         NEGX
         ASLX 
         ASRX
         NOTX
         ORX     0x54CD,i
         ROLX
         ANDX    0x25E8,i
         RORX
         SUBX    0xCF12,i
         ADDX    0xD15C,i
         BR      for3    
endFor:  ADDSP   6,i         ;deallocate #j #k #l
         STOP                
         .END    
