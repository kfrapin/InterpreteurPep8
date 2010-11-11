main:    LDA                 0x5511,i
         STA             2556,d

         LDX             0x0063,i
         STX             2556,x 
         STX             0x0254,n

         LDX             0x0070,i
         STX             0x0001,s

         LDX             0x0120,i
         STX             0x0001,sf

         LDX             0x2030,i
         STX             0x0001,x

         LDX             0x0201,i
         STX             0x0001,sx

         LDX             0x0956,i
         STX             0x0001,sxf

         LDA             0x0254,n
         LDA             0x0001,s
         LDA             0x0001,sf
         LDA             0x0001,x
         LDA             0x0001,sx
         LDA             0x0001,sxf
endFor2: STOP                
         .END                  
