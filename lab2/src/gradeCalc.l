%{
 #include <stdio.h>
%}



%%

[a-zA-Z] {return (LETTER);}
[1-9][0-9]*  {return (integer);}
[\t\n] ; 


. printf("unexpected character");

%%
