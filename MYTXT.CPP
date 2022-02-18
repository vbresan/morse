#include <bios.h>
#include <conio.h>
#include <time.h>
#include <dir.h>
#include "mytxt.h"

void sat(char pozicija,char boja)
 { long bios_time;
   struct tm *vrijeme; 
   time_t seconds;
   char dan[7][4]={{"Ned"},{"Pon"},{"Uto"},{"Sri"},{"Cet"},{"Pet"},{"Sub"}};
   bios_time =biostime(0,0L);
   time(&seconds);	
   vrijeme=localtime(&seconds);
   textcolor(boja);
   switch(pozicija)
    { case 0:  gotoxy(2,1);
	       break;
      case 1:  gotoxy(62,1);
	       break;
      case 2:  gotoxy(2,25);
	       break;
      case 3:  gotoxy(62,25);
	       break;
      default: gotoxy(62,25);
	       break;
    }
   cprintf("%i.%0.2i (%s) %0.2i:%0.2i", vrijeme->tm_mday, vrijeme->tm_mon+1, dan[vrijeme->tm_wday],(int) (bios_time/CLK_TCK/3600),(int) (bios_time/CLK_TCK/60)-(int) (bios_time/CLK_TCK/3600)*60);
 }

void peglaj()
 { gotoxy(1,2);
   for(register char i=0;i<23;i++)
    cputs("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°");
 }

void ProzorNormalni(char left,char top,char right,char bottom)
 { void siena(char left,char top,char right,char bottom);
   window(left,top,right,bottom);
   clrscr();
   gotoxy(2,1);cputs("Ú");
   gotoxy((right-left)-1,1);cputs("Ä¿ ");
   gotoxy(2,(bottom-top)+1);cputs("À");
   gotoxy((right-left)-1,(bottom-top)+1);cputs("ÄÙ");
   for(register char i=3;i<(right-left)-1;i++)
    { gotoxy(i,1);cputs("Ä");
      gotoxy(i,(bottom-top)+1);cputs("Ä");
    }
   for(i=2;i<(bottom-top)+1;i++)
    { gotoxy(2,i);cputs("³");
      gotoxy((right-left),i);cputs("³");
    }
   window(1,1,80,25);
   siena(left,top,right,bottom);
 }

void ProzorSaCrtom(char left,char top,char right,char bottom,char koji)
 { void siena(char left,char top,char right,char bottom);
   window(left,top,right,bottom);
   clrscr();
   gotoxy(2,1);cputs("Ú");
   gotoxy((right-left)-1,1);cputs("Ä¿ ");
   gotoxy(2,(bottom-top)+1);cputs("À");
   gotoxy((right-left)-1,(bottom-top)+1);cputs("ÄÙ");
   for(register char i=3;i<(right-left)-1;i++)
    { gotoxy(i,1);cputs("Ä");
      gotoxy(i,koji+1);cputs("Ä");
      gotoxy(i,(bottom-top)+1);cputs("Ä");
    }
   for(i=2;i<(bottom-top)+1;i++)
    { gotoxy(2,i);cputs("³");
      gotoxy((right-left),i);cputs("³");
    }
   gotoxy(2,koji+1);cputs("Ã");
   gotoxy((right-left),koji+1);cputs("´");
   gotoxy((right-left)-1,koji+1);cputs("Ä");
   window(1,1,80,25);
   siena(left,top,right,bottom);
 }

void siena(char left,char top,char right,char bottom)
 { for(register char i=top+1;i<bottom+2;i++)
    { gotoxy(right+1,i);
      cputs("²²");
    }
   for(i=left+2;i<=right;i++)
    { gotoxy(i,bottom+1);
      cputs("²");
    } 
 }
