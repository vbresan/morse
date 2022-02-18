#include "morse10t.h"
#include "morseext.h"

char CurWDir[MAXPATH];

void PromjeniDirektorij(char **argv)
 { getcwd(CurWDir,MAXPATH);
   for(register int i=strlen(argv[0]);i>=0;i--)
    if(argv[0][i]=='\\')
     { argv[0][i]='\0';
       i=0;
     }
   chdir(argv[0]);
 }