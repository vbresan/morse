#include <ctype.h>
#include "morse10t.h"
#include "morseext.h"

int done;

struct ffblk ffblk;

FILE *fp;

void ucitavanje_para()
 { if((fp=fopen("morse.cfg","r"))==NULL)
     { glvn.fq=800;
       glvn.sgnl=100;
       posebna();
       ucitavanje_para();
     }
   fseek(fp,0,SEEK_SET);
   fscanf(fp,"\n%*[^=]s");
   fseek(fp,1,SEEK_CUR);
   if(!fscanf(fp,"%i\n",&glvn.fq) || glvn.fq==0)
     { glvn.fq=800;
       glvn.sgnl=100;
       posebna();
       ucitavanje_para();
     }
   fscanf(fp,"%*[^=]s");
   fseek(fp,1,SEEK_CUR);
   if(!fscanf(fp,"%i",&glvn.sgnl) || glvn.sgnl==0)
     { glvn.fq=800;
       glvn.sgnl=100;
       posebna();
       ucitavanje_para();
     }
   fclose(fp);
   pri_otvaranju=glvn;
 }

void posebna()
 { kontroler=1;
   if((fp=fopen("morse.cfg","w"))==NULL)
	{ printf("\7");
	  clrscr();
	  textbackground(4);textcolor(14);
	  window(18,5,62,10);
	  clrscr();
	  drawer(44,6);
	  window(21,6,59,9);
	  cputs("Greska pri kreiranju inicijalizacijske datoteke! Provjerite da li je disk u   write-protected modu.                  Ako nije, onda ...");
	  getch();
	  EXIT(1);
	}
   fprintf(fp,"[Morse ver. 1.0T]\nFq(Hz)=%i\nsgnl(delay)=%i",glvn.fq,glvn.sgnl);
   fclose(fp);
 }

void najposebna()
 { printf("\a");
   window(1,1,80,25);
   textbackground(0);textcolor(7);clrscr();
   mouse_install();
   _setcursortype(_NOCURSOR);
   textbackground(4);textcolor(14);
   window(18,5,62,10);
   clrscr();
   drawer(44,6);
   window(21,6,59,9);
   cputs("Greska pri kreiranju inicijalizacijske datoteke! Provjerite da li je disk u   write-protected modu.                  Ako nije, onda ...");
   getch();
   EXIT(1);
 }

void drawer(char numx,char numy)
 { register char i;
   clrscr();
   gotoxy(2,1);cputs("Ú");
   gotoxy(numx-1,1);cputs("Ä¿ ");
   gotoxy(2,numy);cputs("À");
   gotoxy(numx-1,numy);cputs("ÄÙ");
   for(i=3;i<numx-1;i++)
    { gotoxy(i,1);cputs("Ä");
      gotoxy(i,numy);cputs("Ä");
    }
   for(i=2;i<numy;i++)
    { gotoxy(2,i);cputs("³");
      gotoxy(numx,i);cputs("³");
    }
 }

void liner(char xl,char xr,char yu,char yd)
 { register char i;
   window(1,1,80,25);
   for(i=yu+1;i<yd+2;i++)
    { gotoxy(xr+1,i);
      cputs("²²");
    }
   for(i=xl+2;i<=xr;i++)
    { gotoxy(i,yd+1);
      cputs("²");
    }
 }

void sjencenje()
 { textcolor(8);
   gotoxy(3,1);cputs("I");
   gotoxy(10,1);cputs("P");
   gotoxy(29,1);cputs("D");
   gotoxy(39,1);cputs("A");
   gotoxy(48,1);cputs("Q");
   gotoxy(75,1);cputs("K");
   textcolor(0);
 }

void para_nacrt()
 { void para();
   sjencenje(); 
   textbackground(10);PARA  
   textbackground(7);
   gotoxy(1,25);
   gettext(9,12,49,17,ptext);
   window(9,2,47,6);
   drawer(38,5);
   liner(9,47,2,6);
   par_n=0;
   para();
 }

void para_nomouse()
 { switch(par_n)
    { case 0: textbackground(10);FRNK 
	      textbackground(7);JDTS RESP
	      gotoxy(1,25);
	      cputs(" [ ] Podesavanje frekvencije                          ");
	      break;
      case 1: textbackground(10);JDTS
	      textbackground(7);FRNK RESP
	      gotoxy(1,25);
	      cputs(" [ ] Podesavanje jedinicne duzine signala             ");
	      break;
      case 2: textbackground(10);RESP
	      textbackground(7);FRNK JDTS
	      gotoxy(1,25);
	      cputs(" [ ] Povrat parametara na 'tvornicke' vrijednosti     ");
	      break;
      default: break;
    }
 }

oba_podesavanja(char ulaz)
 { char niz[5],i=0,a;
   window(51,4,77,6);
   drawer(26,3);
   liner(51,77,4,6);
   gotoxy(54,5);
   if(!ulaz)
     { cprintf("%9i",glvn.fq);
       gotoxy(71,5);cprintf("(Hz)");
     }
   else
     { cprintf("%9i",glvn.sgnl);
       gotoxy(71,5);cprintf("(ms)");
     }
   gotoxy(64,5);cprintf(" ");
   _setcursortype(_SOLIDCURSOR);
   do  
      { a=getch();
	if(((ulaz==0 && i<4) || (ulaz==1 && i<3)) && (a=='0' || a=='1' || a=='2' || a=='3' || a=='4' || a=='5' || a=='6' || a=='7' || a=='8' || a=='9'))
	 { niz[i]=a;
	   cprintf("%c",niz[i]);
	   i++;
	 }
	switch(a)
	 { case 8: if(i)
		    { i--;
		      gotoxy(66+i,5);
		      cputs(" ");gotoxy(66+i,5);
		    }
		   else if(!i)
		     printf("\7"); 
		   break;
	    case 13: if(i)
		       niz[i]='\0';
		     else if(!i) 
		      { if(!ulaz)
			  itoa(glvn.fq,niz,10);
			else
			  itoa(glvn.sgnl,niz,10);
		      }
		     break;
	 }
      if((ulaz==0 && i==4) || (ulaz==1 && i==3))
	_setcursortype(_NOCURSOR);
      else
	_setcursortype(_SOLIDCURSOR);
    }			
  while(((ulaz==0 && i!=5) || (ulaz==1 && i!=4)) && a!='\r');
  _setcursortype(_NOCURSOR);
  return(atoi(niz));
 }

void podesavanje_fq()
 { int probna;
   gotoxy(3,25);cputs("þ");
   probna=oba_podesavanja(0);
   if(probna!=glvn.fq)
     { glvn.fq=probna;
       printf("\7");
     }
   puttext(9,2,49,7,ptext);
   puttext(49,2,79,7,ptext);
   osnovna();
 }

void podesavanje_jdts()
 { int probna;
   gotoxy(3,25);cputs("þ");
   probna=oba_podesavanja(1);
   if(probna!=glvn.sgnl)
     { glvn.sgnl=probna;
       printf("\7");
     }
   puttext(9,2,49,7,ptext);
   puttext(49,2,79,7,ptext);
   osnovna();
 }

void reset()
 { gotoxy(3,25);cputs("þ");
   if(glvn.fq!=800 || glvn.sgnl!=100)
    { glvn.fq=800;
      glvn.sgnl=100;
      printf("\7"); 
    }
   puttext(9,2,49,7,ptext);osnovna();
 }

void datt_nacrt()
 { sjencenje(); 
   textbackground(10);DATO  
   textbackground(7);
   gettext(28,12,49,16,ptext);
   window(28,2,47,5);
   drawer(19,4);
   liner(28,47,2,5);
   dat_n=0;
   datt();
 }

void datt_nomouse()
 { switch(dat_n)
    { case 0: textbackground(10);PISA 
	      textbackground(7);CITA
	      gotoxy(1,25);cputs(" [ ] Pisanje, snimanje i signalizacija poruka         ");
	      break;
      case 1: textbackground(10);CITA
	      textbackground(7);PISA
	      gotoxy(1,25);cputs(" [ ] Citanje i signalizacija vec snimljenih poruka    ");
	      break;
      default: break;
    }
 }

void citanje_poruke()
 { gettext(5,3,77,21,ptext);
   citanje_poruke_fifi();
 }

void citanje_poruke_fifi()
 { char disk,curdir[MAXPATH];
   gotoxy(3,25);cputs("þ");
   liner(5,75,3,20);
   window(5,3,75,20);
   drawer(70,18);
   textcolor(4);
    gotoxy(4,4);cputs("D");
    gotoxy(6,5);cputs("r");
   textcolor(0);
    gotoxy(5,4);cputs("isk           : ");
    gotoxy(4,5);cputs("Di");gotoxy(7,5);cputs("ektorij     : ");
    gotoxy(4,2);cputs("Popis datoteka (manjih od 570 bytova)");
    window(7,8,73,18);
    drawer(66,11);
    window(5,3,75,20);
   textcolor(1);
    disk=getdisk()+'A';gotoxy(21,4);cprintf("%c",disk);
    curdir[0]='\\';
    getcurdir(0,curdir+1);gotoxy(21,5);cprintf("%s\\",curdir);
   textcolor(0);
   citanje_poruke_nenacrt();
 }

void citanje_poruke_nenacrt()
 { int slovo;
   char lola=0,i=1,j=0,fajla[14],x=19,y=17,cic;
   ispis_fajli(0);
   gotoxy(5,17);cputs("             <ENTER> za unosenje imena datoteke! ");
   cic=0;
   while(i)
    { gotoxy(66,15);
      if(!done)
       { gotoxy(66,15);
	 textcolor(1);cputs("");
       }
      if(lola)
       { gotoxy(66,7);
	 cputs("");
       }
      gotoxy(19,17);
      slovo=bioskey(0);
      if(slovo==20480 && !done)
       { ispis_fajli(1);
	 lola=1;
       }
      else if(slovo==18432 && lola)
       { ispis_fajli(0);
	 lola=0;
       }
      else if(slovo==283)
       { puttext(5,3,77,21,ptext);
	 window(1,1,80,25);
	 osnovna();
       }
      else if(slovo==8192)
       { kontroler=2;
	 gotoxy(21,4);textcolor(1);
	 _setcursortype(_SOLIDCURSOR);
	 setdisk(getch()-'a');
	 cic=getdisk()+'A';
	 gotoxy(21,4);cprintf("%c",cic);
	 textcolor(0);
	 _setcursortype(_NOCURSOR);
	 citanje_poruke_fifi();
       }
      else if(slovo==4864)
       { gotoxy(5,17);cputs("                                                ");			
	 gotoxy(5,17);textcolor(0);cputs("Direktorij  : ");
	 _setcursortype(_SOLIDCURSOR);textcolor(1);
	 while((fajla[j]=getch())!='\r' && j<=13)
	  { if((fajla[j]>=65 && fajla[j]<=90) || (fajla[j]>=97 && fajla[j]<=122) || (fajla[j]>=48 && fajla[j]<=57) || fajla[j]==32 || fajla[j]==8 || fajla[j]==46)
	     { if(fajla[j]!=8)
		{ cprintf("%c",fajla[j]);
		  x++;j++;
		}
	       else
		{ if(x>19)
		   { j--;x--;
		     gotoxy(x,y);cputs(" ");
		     gotoxy(x,y);
		   }
		  else
		   printf("\7");
		}
	    }
	  }
	 fajla[j]='\0';
	 i=0;
	 chdir(fajla);
	 _setcursortype(_NOCURSOR);
	 citanje_poruke_nenacrt();
       }
      else if(slovo==7181)
       { gotoxy(5,17);cputs("                                                ");			
	 gotoxy(5,17);textcolor(0);cputs("Ime datoteke: ");
	 _setcursortype(_SOLIDCURSOR);textcolor(1);
	 while((fajla[j]=getch())!='\r' && j<=13)
	  { if((fajla[j]>=65 && fajla[j]<=90) || (fajla[j]>=97 && fajla[j]<=122) || (fajla[j]>=48 && fajla[j]<=57) || fajla[j]==32 || fajla[j]==8 || fajla[j]==46)
	     { if(fajla[j]!=8)
		{ cprintf("%c",fajla[j]);
		  x++;j++;
		}
	       else
		{ if(x>19)
		   { j--;x--;
		     gotoxy(x,y);cputs(" ");
		     gotoxy(x,y);
		   }
		  else
		   printf("\7");
		}
	    }
	  }
	 fajla[j]='\0';
	 i=0;
       }
      textcolor(1);
      gotoxy(19,17);
    }
   if((fp=fopen(fajla,"r"))==NULL || fajla=="." || fajla=="..") 
    { printf("\7");
      textcolor(0);
      gotoxy(5,17);_setcursortype(_NOCURSOR);
      cputs("               Uneseno ime nepostojece datoteke!               ");
      getch();citanje_poruke_nenacrt();
    }
   duzina=0;
   while(!feof(fp) && duzina<570)
    { lola=getc(fp);
       { if((lola>=65 && lola<=90) || (lola>=97 && lola<=122) || (lola>=48 && lola<=57))
	  *(pok_na_text+duzina++)=lola;
	 else
	  *(pok_na_text+duzina++)=32;
       }
    }
   text[duzina]='\0';
   puttext(5,3,77,21,ptext);
   textcolor(0);
   window(5,3,75,17);
   drawer(70,15);
   liner(5,75,3,17);
   window(7,4,73,14);
   drawer(66,11);
   window(9,5,71,13);
   gotoxy(1,1);
   _setcursortype(_NOCURSOR);
   cprintf("%s",text);
   window(5,3,75,17);
   monkey();
 }

void ispis_fajli(int ulaz)
 { char br=0,i=2,j=5;
   textcolor(0);
   window(7,8,73,18);
   drawer(66,11);
   if(!ulaz)
    done=findfirst("*.*",&ffblk,FA_DIREC);
   while(!done && br<=35)
    { if(ffblk.ff_fsize<=570)
       { if(ffblk.ff_attrib==FA_DIREC)
	  textcolor(1);
	 gotoxy(j,i++);
	 cprintf("%s",ffblk.ff_name);
	 textcolor(0);
	 br++;
	 if(i==11)
	  { j+=15;
	    i=2;
	  }
       }
      done=findnext(&ffblk);
    }
   window(5,3,75,20);
 }

void pisanje_poruke()
 { char x=1,y=1;
   void pohrana_mis();
   kontroler=0;
   gotoxy(3,25);cputs("þ");
   gettext(5,3,77,18,ptext);
   window(5,3,75,17);
   drawer(70,15);
   gotoxy(19,13);cputs("<Enter> za kraj unosenja poruke!!");
   liner(5,75,3,17);
   window(7,4,73,14);
   drawer(66,11);
   window(9,5,71,13);
   gotoxy(1,1);
   _setcursortype(_SOLIDCURSOR);
   duzina=0;
   while(duzina<=565 && (letter=getch())!='\r')
    { if((letter>=65 && letter<=90) || (letter>=97 && letter<=122) || (letter>=48 && letter<=57) || letter==32 || letter==8)
       { if(letter!=8)
	   { cprintf("%c",letter);
	     *(pok_na_text+duzina++)=letter;
	     x++;
	     if(x>63)
	       { y++;
		 x=1;
	       }
	   }
	 else
	   { if(x!=1 || y!=1)
	      { duzina--;
		if(x>1)
		  { x--;
		    gotoxy(x,y);cputs(" ");
		    gotoxy(x,y);
		  }
		else
		  { y--;
		    x=63;
		    gotoxy(x,y);cputs(" ");
		    gotoxy(x,y);
		  }
	       }
	      else
	       printf("\7");
	   }
       }
    }
   _setcursortype(_NOCURSOR);
   printf("\7");
   window(5,3,75,17);
   letter='s';
   monkey();
 }

void monkey()
 { int slovo;
   while(1)
    { pohrana_mis();
      slovo=bioskey(0);
      switch(slovo)
       { case 283: window(1,1,80,25);
		   puttext(5,3,77,18,ptext);
		   osnovna();
	 case 6512: letter='p';
		    break;
	 case 6400: if(duzina)
		     { textbackground(10); POHR
		       textbackground(7);
		       cputs("Ü");gotoxy(35,14);cputs("ßßßßßßßßß"); 
		       SIGN cputs(" ");gotoxy(19,14);cputs("              ");
		       IZLA cputs(" ");gotoxy(46,14);cputs("        "); 
		       letter='p';
		       pohrana();
		     }
		    break;
	 case 6480: letter='p';
		    break;
	 case 5993: letter='i';
		    break;
	 case 5888: window(1,1,80,25);
		    puttext(5,3,77,18,ptext);
		    osnovna();break;
	 case 7936: if(duzina)
		     { textbackground(10); SIGN
		       textbackground(7);
		       cputs("Ü");gotoxy(19,14);cputs("ßßßßßßßßßßßßßß");
		       POHR cputs(" ");gotoxy(35,14);cputs("         "); 
		       IZLA cputs(" ");gotoxy(46,14);cputs("        "); 
		       letter='s';
		       signalizacija();
		     }
		    break;
	case 5961: letter='i';
		   break;
	case 19712: if(letter=='s')
		     letter='p';
		    else if(letter=='p')
		     letter='i';
		    else
		     letter='s';
		    break;
	case 19200: if(letter=='s')
		     letter='i';
		    else if(letter=='p')
		     letter='s';
		    else
		     letter='p';
		    break;
	case 7181: if(letter=='s' && duzina!=0)
		    signalizacija();
		   else if(letter=='p' && duzina!=0)
		    pohrana();
		   else
		    { window(1,1,80,25);
		      puttext(5,3,77,18,ptext);
		      osnovna();
		    }
	 default: letter='s';
		  break;
       }
    }
 }

void signalizacija()
 { register int i=0;
   gotoxy(16,13);cputs("Bilo koja tipka za prekid signaliziranja.");
   gotoxy(18,14);cputs("                                         ");
   window(9,5,71,13);
   gotoxy(1,1);
   while(i<duzina && (!kbhit()))
     { char x=wherex(),y=wherey();
       textcolor(4);
       cprintf("%c",text[i]);
       sama_signalizacija(i);	 
       gotoxy(x,y);
       textcolor(0);
       cprintf("%c",text[i]);
       i++;
     }
   window(5,3,75,17);
   pohrana_mis();
 }

void sama_signalizacija(register int i)
 { switch(text[i])
    { case '0': NULA
		break;
      case '1': JEDAN
		break;
      case '2': DVA
		break;
      case '3': TRI
		break;
      case '4': CETRI
		break;
      case '5': PET
		break;
      case '6': SEST
		break;
      case '7': SEDAM
		break;
      case '8': OSAM
		break;
      case '9': DEVET
		break;
      case 'a': 
      case 'A': A
		break;
      case 'b': 
      case 'B': B
		break;
      case 'c': 
      case 'C': C
		break;
      case 'd': 
      case 'D': D
		break;
      case 'e': 
      case 'E': E
		break;
      case 'f': 
      case 'F': F
		break;
      case 'g': 
      case 'G': G
		break;
      case 'h': 
      case 'H': H
		break;
      case 'i': 
      case 'I': I
		break;
      case 'j': 
      case 'J': J
		break;
      case 'k': 
      case 'K': K
		break;
      case 'l': 
      case 'L': L
		break;
      case 'm': 
      case 'M': M
		break;
      case 'n': 
      case 'N': N
		break;
      case 'o': 
      case 'O': O
		break;
      case 'p': 
      case 'P': P
		break;
      case 'q': 
      case 'Q': Q
		break;
      case 'r': 
      case 'R': R
		break;
      case 's': 
      case 'S': S
		break;
      case 't': 
      case 'T': T
		break;
      case 'u': 
      case 'U': U
		break;
      case 'v': 
      case 'V': V
		break;
      case 'w': 
      case 'W': W
		break;
      case 'x': 
      case 'X': X
		break;
      case 'y': 
      case 'Y': Y
		break;
      case 'z': 
      case 'Z': Z
		break;
      case ' ': SPEJS
		break;
      default: break;
    }
 }

void morse_hang()
 { void morse_hang_nenacrt();
   sjencenje();
   gettext(20,7,62,17,ptext);
   window(20,7,60,16);
   clrscr();   
   drawer(40,10);
   gotoxy(16,2);cprintf(" Zivota:");
   liner(20,60,7,16);
   gotoxy(1,25);cputs(" [þ] Igra vjesala                                     ");
   morse_hang_nenacrt();
 }

void morse_hang_nenacrt()
 { char slv,kontr,num,br=0,zivota=3,*rijec[]={"pobjednik","atavizam","medvjed","tulipan","stalaktit","varalica","mimoza","gubitnik","sjecanja","rasplakan","milijarder"};
   register int i;
   window(50,9,58,13);
   clrscr();
   drawer(8,5);
   window(20,7,60,16);
   gotoxy(7,9);cputs(" Spremni? Bilo koja tipka..."); 
   textcolor(4);gotoxy(24,2);cprintf(" %i",zivota);
   textcolor(0);
   num=random(11);
   gotoxy(5,7);cputs("                           ");
   gotoxy(21-strlen(rijec[num])/2,7);
   for(i=0;i<strlen(rijec[num]);i++)
     cputs("-");
   getch();
   duzina=strlen(rijec[num]);
   for(i=0;i<=strlen(rijec[num]);i++)
     text[i]=rijec[num][i];
   for(i=0;i<=strlen(rijec[num]);i++)
     sama_signalizacija(i);
   gotoxy(7,9);cputs("     <Enter> za izlazak.     ");
   do
    { kontr=0;
      if((slv=getch())==13)
       { puttext(20,7,62,17,ptext);
	 window(1,1,80,25);
	 osnovna();
       }
      else
       { for(i=0;i<strlen(rijec[num]);i++)
	  if(text[i]==slv)
	   { gotoxy(21-strlen(rijec[num])/2+i,7);
	     cprintf("%c",slv);
	     kontr=1;br++;
	   }
	 if(!kontr)
	  { printf("\7");
	    zivota--;
	  }
       }
      textcolor(4);gotoxy(24,2);cprintf(" %i",zivota);
      textcolor(0);
      if(br==strlen(rijec[num]))
       { gotoxy(7,9);cputs("   Bravo! Jos jednom(d/n)?   ");
	 if((slv=getch())=='d')
	  morse_hang_nenacrt();
	 else
	  { puttext(20,7,62,17,ptext);
	    window(1,1,80,25);
	    osnovna();
	  }
       }
      if(zivota==2)
       { gotoxy(33,6);cputs("ÍÊÍÍÍ"); }
      if(zivota==1)
       { gotoxy(33,5);cputs(" º   ");}
      if(!zivota)
       { gotoxy(33,4);cputs(" ÉÍÍ»");}
    }
   while(zivota);
   gotoxy(7,9);cputs("   Sorry! Jos jednom(d/n)?   ");
   if((slv=getch())=='d')
    morse_hang_nenacrt();
   else
    { puttext(20,7,62,17,ptext);
      window(1,1,80,25);
      osnovna();
    }
 }


void abe_nomouse(int slovo)
 { switch(slovo)
    { case 7777: 
      case 7745: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=2;
		 abe();break;
      case 7680: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=2; A
		 abe();break;
      case 12386: 
      case 12354: gotoxy(ax,ay);cputs(" ");
		  ax=5;ay=3;
		  abe();break;
      case 12288: gotoxy(ax,ay);cputs(" ");
		  ax=5;ay=3; B
		  abe();break;
      case 11875: 
      case 11843: gotoxy(ax,ay);cputs(" ");
		  ax=5;ay=4;
		  abe();break;
      case 11776: gotoxy(ax,ay);cputs(" ");
		  ax=5;ay=4; C
		  abe();break;
      case 8292: 
      case 8260: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=5;
		 abe();break;
      case 8192: gotoxy(ax,ay);cputs(" ");
		  ax=5;ay=5; D
		  abe();break;
      case 4709: 
      case 4677: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=6;
		 abe();break;
      case 4608: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=6; E
		 abe();break;
      case 8550: 
      case 8518: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=7;
		 abe();break;
      case 8448: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=7; F
		 abe();break;
      case 8807: 
      case 8775: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=8;
		 abe();break;
      case 8704: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=8; G
		 abe();break;
      case 9064: 
      case 9032: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=9;
		 abe();break;
      case 8960: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=9; H
		 abe();break;
      case 5993: 
      case 5961: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=10;
		 abe();break;
      case 5888: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=10; I
		 abe();break;
      case 9322: 
      case 9290: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=11;
		 abe();break;
      case 9216: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=11; J
		 abe();break;
      case 9579: 
      case 9547: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=12;
		 abe();break;
      case 9472: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=12; K
		 abe();break;
      case 9836: 
      case 9804: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=13;
		 abe();break;
      case 9728: gotoxy(ax,ay);cputs(" ");
		 ax=5;ay=13; L
		 abe();break;
      case 12909: 
      case 12877: gotoxy(ax,ay);cputs(" ");
		  ax=29;ay=2;
		  abe();break;
      case 12800: gotoxy(ax,ay);cputs(" ");
		  ax=29;ay=2; M
		  abe();break;
      case 12654: 
      case 12622: gotoxy(ax,ay);cputs(" ");
		  ax=29;ay=3;
		  abe();break;
      case 12544: gotoxy(ax,ay);cputs(" ");
		  ax=29;ay=3; N
		  abe();break;
      case 6255: 
      case 6223: gotoxy(ax,ay);cputs(" ");
		 ax=29;ay=4;
		 abe();break;
      case 6144: gotoxy(ax,ay);cputs(" ");
		 ax=29;ay=4; O
		 abe();break;
      case 6512: 
      case 6480: gotoxy(ax,ay);cputs(" ");
		 ax=29;ay=5;
		 abe();break;
      case 6400: gotoxy(ax,ay);cputs(" ");
		 ax=29;ay=5; P
		 abe();break;
      case 4209: 
      case 4177: gotoxy(ax,ay);cputs(" ");
		 ax=29;ay=6;
		 abe();break;
      case 4096: gotoxy(ax,ay);cputs(" ");
		 ax=29;ay=6; Q
		 abe();break;
      case 4978: 
      case 4946: gotoxy(ax,ay);cputs(" ");
		 ax=29;ay=7;
		 abe();break;
      case 4864: gotoxy(ax,ay);cputs(" ");
		 ax=29;ay=7; R
		 abe();break;
      case 8051: 
      case 8019: gotoxy(ax,ay);cputs(" ");
		 ax=29;ay=8;
		 abe();break;
      case 7936: gotoxy(ax,ay);cputs(" ");
		 ax=29;ay=8; S
		 abe();break;
      case 5236: 
      case 5204: gotoxy(ax,ay);cputs(" ");
		 ax=29;ay=9;
		 abe();break;
      case 5120: gotoxy(ax,ay);cputs(" ");
		 ax=29;ay=9; T
		 abe();break;
      case 5749: 
      case 5717: gotoxy(ax,ay);cputs(" ");
		 ax=29;ay=10;
		 abe();break;
      case 5632: gotoxy(ax,ay);cputs(" ");
		 ax=29;ay=10; U
		 abe();break;
      case 12150: 
      case 12118: gotoxy(ax,ay);cputs(" ");
		  ax=29;ay=11;
		  abe();break;
      case 12032: gotoxy(ax,ay);cputs(" ");
		  ax=29;ay=11; V
		  abe();break;
      case 4471: 
      case 4439: gotoxy(ax,ay);cputs(" ");
		 ax=29;ay=12;
		 abe();break;
      case 4352: gotoxy(ax,ay);cputs(" ");
		 ax=29;ay=12; W
		 abe();break;
      case 11640: 
      case 11608: gotoxy(ax,ay);cputs(" ");
		  ax=29;ay=13;
		  abe();break;
      case 11520: gotoxy(ax,ay);cputs(" ");
		  ax=29;ay=13; X
		  abe();break;
      case 5497: 
      case 5465: gotoxy(ax,ay);cputs(" ");
		 ax=53;ay=2;
		 abe();break;
      case 5376: gotoxy(ax,ay);cputs(" ");
		 ax=53;ay=2; Y
		 abe();break;
      case 11386: 
      case 11354: gotoxy(ax,ay);cputs(" ");
		  ax=53;ay=3;
		  abe();break;
      case 11264: gotoxy(ax,ay);cputs(" ");
		  ax=53;ay=3; Z
		  abe();break;
      case 561: 
      case 545: gotoxy(ax,ay);cputs(" ");
		ax=53;ay=4;
		abe();break;
      case 30720: gotoxy(ax,ay);cputs(" ");
		  ax=53;ay=4; JEDAN
		  abe();break;
      case 818: 
      case 802: gotoxy(ax,ay);cputs(" ");
		ax=53;ay=5;
		abe();break;
      case 30976: gotoxy(ax,ay);cputs(" ");
		  ax=53;ay=5; DVA
		  abe();break;
      case 1075: 
      case 1059: gotoxy(ax,ay);cputs(" ");
		 ax=53;ay=6;
		 abe();break;
      case 31232: gotoxy(ax,ay);cputs(" ");
		  ax=53;ay=6; TRI
		  abe();break;
      case 1332: 
      case 1316: gotoxy(ax,ay);cputs(" ");
		 ax=53;ay=7;
		 abe();break;
      case 31488: gotoxy(ax,ay);cputs(" ");
		  ax=53;ay=7; CETRI
		  abe();break;
      case 1589: 
      case 1573: gotoxy(ax,ay);cputs(" ");
		 ax=53;ay=8;
		 abe();break;
      case 31744: gotoxy(ax,ay);cputs(" ");
		  ax=53;ay=8; PET
		  abe();break;
      case 1846: 
      case 1830: gotoxy(ax,ay);cputs(" ");
		 ax=53;ay=9;
		 abe();break;
      case 32000: gotoxy(ax,ay);cputs(" ");
		  ax=53;ay=9; SEST
		  abe();break;
      case 2103: 
      case 2095: gotoxy(ax,ay);cputs(" ");
		 ax=53;ay=10;
		 abe();break;
      case 32256: gotoxy(ax,ay);cputs(" ");
		  ax=53;ay=10; SEDAM
		  abe();break;
      case 2360: 
      case 2344: gotoxy(ax,ay);cputs(" ");
		 ax=53;ay=11;
		 abe();break;
      case 32512: gotoxy(ax,ay);cputs(" ");
		  ax=53;ay=11; OSAM
		  abe();break;
      case 2617: 
      case 2601: gotoxy(ax,ay);cputs(" ");
		 ax=53;ay=12;
		 abe();break;
      case -32768: gotoxy(ax,ay);cputs(" ");
		   ax=53;ay=12; DEVET
		   abe();break;
      case 2864: 
      case 2877: gotoxy(ax,ay);cputs(" ");
		 ax=53;ay=13;
		 abe();break;
      case -32512: gotoxy(ax,ay);cputs(" ");
		   ax=53;ay=13; NULA
		   abe();break;
      case 18688: gotoxy(ax,ay);cputs(" ");
		  ax=5;ay=2;
		  abe();break;
      case 20736: gotoxy(ax,ay);cputs(" ");
		  ax=5;ay=19;
		  abe();break;
      case 283: break;
      case 20480: if(ay==13)
		   { gotoxy(ax,ay);cputs(" ");
		     ay=15; ax=5;
		   }
		  if(ay==17)
		   { gotoxy(ax,ay);cputs(" ");
		     ay=18; ax=5;
		   }
		  if(ay<19)
		   { gotoxy(ax,ay);cputs(" ");
		     ay++;
		   }
		  abe(); break;
      case 19712: if(ax<53 && ay!=16 && ay!=17 && ay!=19)
		   {  gotoxy(ax,ay);cputs(" ");
		      ax+=24;
		   }
		  abe(); break;
      case 19200: if(ax>5)
		   { gotoxy(ax,ay);cputs(" ");
		     ax-=24;
		   }
		  abe(); break;
      case 18432: if(ay==19)
		   { gotoxy(ax,ay);cputs(" ");
		     ay=18;
		   }
		  if(ay==16)
		   { gotoxy(ax,ay);cputs(" ");
		     ay=14;
		   }
		  if(ay>2)
		   { gotoxy(ax,ay);cputs(" ");
		     ay--;
		   }
		  abe(); break;
      case 7181: if(ay==2)
		   { if(ax==5)  { A abe();}
		     if(ax==29) { M abe();}
		     if(ax==53) { Y abe();}
		   }
		 if(ay==3)
		   { if(ax==5)  { B abe();}
		     if(ax==29) { N abe();}
		     if(ax==53) { Z abe();}
		   }
		 if(ay==4)
		   { if(ax==5)  { C abe();}
		     if(ax==29) { O abe();}
		     if(ax==53) { JEDAN abe();}
		   }
		 if(ay==5) 
		   { if(ax==5)  { D abe();}
		     if(ax==29) { P abe();}
		     if(ax==53) { DVA abe();}
		   }
		 if(ay==6)
		   { if(ax==5)  { E abe();}
		     if(ax==29) { Q abe();}
		     if(ax==53) { TRI abe();
			}
		   }
		 if(ay==7)
		   { if(ax==5)  { F abe();}
		     if(ax==29) { R abe();}
		     if(ax==53) { CETRI abe();}
		   }
		 if(ay==8)
		   { if(ax==5)  { G abe();}
		     if(ax==29) { S abe();}
		     if(ax==53) { PET abe();}
		   }
		 if(ay==9)
		   { if(ax==5)  { H abe();}
		     if(ax==29) { T abe();}
		     if(ax==53) { SEST abe();}
		   }
		 if(ay==10)
		   { if(ax==5)  { I abe();}
		     if(ax==29) { U abe();}
		     if(ax==53) { SEDAM abe();}
		   }
		 if(ay==11)
		   { if(ax==5)  { J abe();}
		     if(ax==29) { V abe();}
		     if(ax==53) { OSAM abe();}
		   }
		 if(ay==12)
		   { if(ax==5)  { K abe();}
		     if(ax==29) { W abe();}
		     if(ax==53) { DEVET abe();}
		   }
		 if(ay==13)
		   { if(ax==5)  { L abe();}
		     if(ax==29) { X abe();}
		     if(ax==53) { NULA  abe();}
		   }
		 if(ay==16 && ax==5) { KRATKI abe();}
		 if(ay==17 && ax==5) { DUGI abe();}
		 if(ay==19 && ax==5) break;
		 break;
      default: abe();break;
    }
 }

void pohrana()
 { void prava_pohrana();
   gettext(5,20,77,23,ptext);
   liner(5,75,20,22);
   window(5,20,75,22);
   drawer(70,3);
   prava_pohrana();
 }

void prava_pohrana()
 { int  i=0;
   char x,y,ime_dat[44];
   gotoxy(3,2);
   textcolor(0);
   cputs(" Unesite ime datoteke: ");
   textcolor(1);
   x=wherex();y=wherey();
   _setcursortype(_SOLIDCURSOR);
   while(i<43 && (ime_dat[i]=getch())!='\r')
     { if((ime_dat[i]>=97 && ime_dat[i]<=122) || (ime_dat[i]>=48 && ime_dat[i]<=57) || ime_dat[i]==46 || ime_dat[i]==58 || ime_dat[i]==92 || ime_dat[i]==8)
	 { if(ime_dat[i]!=8)
	     { cprintf("%c",ime_dat[i]);          
	       x++;
	       i++;
	     }
	   else 
	     { if(i)
		{ x--;
		  gotoxy(x,y);cputs(" ");
		  gotoxy(x,y);
		  i--;
		}
	       else
		  printf("\7");
	     }
	 }
     }
   _setcursortype(_NOCURSOR);
   textcolor(0);
   if(i)
     { ime_dat[i]='\0';
       if((fp=fopen(ime_dat,"w"))==NULL)
	{ printf("\7");gotoxy(3,2);
	  cputs(" Greska pri otvaranju datoteke. Pokusajte s drugim imenom, pathom!");
	  getch();gotoxy(3,2);
	  cputs("                                                                  ");	
	  prava_pohrana();
	}
       for(i=0;i<duzina;i++)
	 fprintf(fp,"%c",text[i]);
       fprintf(fp,"%c",'\0');
       fclose(fp);
     }
   window(5,3,75,17);
   puttext(5,20,77,23,ptext);
   pohrana_mis();
   monkey();
 }

void abe_nacrt()
 { sjencenje();
   gotoxy(1,25);
   cputs(" [þ] Lista Morseovog koda                             ");
   gettext(5,3,77,23,ptext);
   window(5,3,75,23);
   cputs(" ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿ "); 
   cputs(" ³    A . _                   M _ _                   Y _ . _ _      ³ "); 
   cputs(" ³    B _ . . .               N _ .                   Z _ _ . .      ³ ");
   cputs(" ³    C _ . _ .               O _ _ _                 1 . _ _ _ _    ³ ");
   cputs(" ³    D _ . .                 P . _ _ .               2 . . _ _ _    ³ ");
   cputs(" ³    E .                     Q _ _ . _               3 . . . _ _    ³ ");
   cputs(" ³    F . . _ .               R . _ .                 4 . . . . _    ³ ");
   cputs(" ³    G _ _ .                 S . . .                 5 . . . . .    ³ ");
   cputs(" ³    H . . . .               T _                     6 _ . . . .    ³ ");
   cputs(" ³    I . .                   U . . _                 7 _ _ . . .    ³ ");
   cputs(" ³    J . _ _ _               V . . . _               8 _ _ _ . .    ³ ");
   cputs(" ³    K _ . _                 W . _ _                 9 _ _ _ _ .    ³ ");
   cputs(" ³    L . _ . .               X _ . . _               0 _ _ _ _ _    ³ ");
   cputs(" ³                                                                   ³ ");
   cputs(" ³                                                                   ³ ");
   cputs(" ³    .  'kratki signal'                                             ³ ");           
   cputs(" ³    _  'dugi signal'                                               ³ ");
   cputs(" ³                                                                   ³ ");
   cputs(" ³    Izlaz                                                          ³ ");
   cputs(" ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ");
   liner(5,75,3,22);
   abe();
 }

void qiz_nacrt()
 { sjencenje(); 
   gotoxy(1,25);
   cputs(" [þ] Provjera znanja                                  ");
   textbackground(10);UIIZ  
   textbackground(7);
   gettext(47,2,73,6,ptext);
   window(47,2,71,5);
   drawer(24,4);
   liner(46,71,2,5);
   qiz_n=0;
   qiz_pravi();
 }

void qiz_nomouse()
 { switch(qiz_n)
    { case 0: textbackground(10);STAN 
	      textbackground(7);HANG
	      gotoxy(1,25);cputs(" [ ] Izvidjacko natjecanje                            ");
	      break;
      case 1: textbackground(10);HANG
	      textbackground(7);STAN
	      gotoxy(1,25);cputs(" [ ] Igra vjesala                                     ");
	      break;
      default: break;
    }
 }

void alert(int stupanj)
 { printf("\7");
   clrscr();
   textbackground(4);textcolor(14);
   window(17,5,63,15);
   clrscr();
   drawer(46,11);
   window(20,6,60,14);
   if(stupanj==1)
     cputs("Datoteci MORSE10T.EXE promjenjeno je ime!Zbog moguce inficiranosti virusom programodbija daljnji rad.                        \n Pokrenite svoj najdrazi antivirusni      scanner, a za novu verziju Morse-a       pisite na adresu:                                                                        vbresan@jagor.srce.hr");
   getch();
   EXIT(1);
 }

void in()
 { sjencenje();
   gotoxy(1,25);
   cputs(" [þ] Verzija, autor                                   ");
   window(20,6,62,17);
   cputs(" ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿ ");
   cputs(" ³              Morse v1.0T              ³ ");
   cputs(" ³                                       ³ ");
   cputs(" ³                                       ³ ");
   cputs(" ³                                       ³ ");
   cputs(" ³                                       ³ ");
   cputs(" ³                                       ³ ");
   cputs(" ³                                       ³ ");
   cputs(" ³                                       ³ ");
   cputs(" ³                                       ³ ");
   cputs(" ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ");
   liner(20,62,6,16);
   getch();
   puttext(20,6,64,17,ptext);
   osnovna();
 }

