         BR      0x0012      ;Branch around data
         .BLOCK  2           ;Storage for one integer
         .ASCII  "Hello World \x00"
;
         STRO    0x0005,d    ;Output "Hello World \x00"
         STOP                
         .END                  
