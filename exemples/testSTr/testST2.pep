main:    LDA                 0x5511,i
         STA             2556,d

         LDX                 0x0063,i
         STX             2556,x 

         STA             0x0254,n
         STA             0x0001,s
         STA             0x0001,sf
         STA             0x0001,x
         STA             0x0001,sx
         STA             0x0001,sxf
endFor2: STOP                
         .END                  
