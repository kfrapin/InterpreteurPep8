;3 Boucles imbriquées
;--------------------
; for( int i = 0; i<10; i++ )
;    for( int j = 0; j<100; j++ )
;      for( int k = 0; k<1000; k++ )
;
; cout << "j = " << j << endl
; cout << "k = " << k << endl
; cout << "l = " << l << endl
;


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
for:     LDA     j,s
         CPA     510,i         ;   j < 10 (j = 2, 6, 14, 30, 62, 126, 254, 510)
         BRGE    endFor      
         LDA     j,s         ;   (j+1) * 2)
         ADDA    1,i
         ASLA
         STA     j,s  
         LDA     0,i         
         STA     k,s         ; k = 0     
         BR      for2         
for2:    LDA     k,s
         CPA     100,i         ;   k < 9999
         BRGE    for      
         LDA     k,s         ;   k++)
         ADDA    1,i         
         STA     k,s  
         LDA     0,i         
         STA     l,s         ; l = 0
         BR      for3    
for3:    LDA     l,s
         CPA     1000,i         ;   l < 9999
         BRGE    for2      
         LDA     l,s         ;   l++)
         ADDA    1,i         
         STA     l,s  
         BR      for3    
;endFor:  STRO    msgFin
endFor:   STRO    msg,d       ;cout << "j = "
         DECO    j,s         ;   << j
         CHARO   '\n',i      ;   << endl
         STRO    msg2,d       ;cout << "k = "
         DECO    k,s         ;   << k
         CHARO   '\n',i      ;   << endl
         STRO    msg3,d       ;cout << "l = "
         DECO    l,s         ;   << l
         CHARO   '\n',i      ;   << endl
         ADDSP   6,i         ;deallocate #j #k #l
         STOP                
msg:     .ASCII  "j = \x00"  
msg2:     .ASCII  "k = \x00" 
msg3:     .ASCII  "l = \x00" 
msgFin:     .ASCII  "-- Fin Programme --\x00" 
         .END    