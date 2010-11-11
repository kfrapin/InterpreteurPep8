main:    ADDA  -10,i
         ADDA  -15,i  ; Addition de deux négatifs dans A
         ADDA  25,i  ; Addition d'un négatif et d'un positif dans A
         ADDA  15,i  ; Addition de deux positifs dans A
         ADDA  -40,i ; Retour à la valeur zéro dans A
         ADDX  -10,i
         ADDX  -15,i  ; Addition de deux négatifs dans X
         ADDX  25,i  ; Addition d'un négatif et d'un positif dans X
         ADDX  15,i  ; Addition de deux positifs dans X
         ADDX  -40,i ; Retour à la valeur zéro dans X
end:     STOP      
.END 