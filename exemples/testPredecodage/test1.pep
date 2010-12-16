         BR      main

j:       .EQUATE 4           ;local variable #2d

main:    SUBSP   2,i         ;allocate #j
         LDA     0,i         
         STA     j,s         ; j = 0
for:     LDA     j,s
         DECO    j,s         ;   << j
         CHARO   '\n',i
         CPA     10,i 
         BRGE    endFor
         LDA     j,s         ; j++
         ADDA    1,i
         STA     j,s 
         ADDA    5,i
         CPA     0,i
         CPA     5,i
         CPA     -5,i
         CPA     -10,i 
         BR      for
endFor:  STOP              
msg:     .ASCII  "- FIN -\x00"    
         .END                  
