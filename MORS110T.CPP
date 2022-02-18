#include "morse10t.h"
#include "morseext.h"

int duzina=0,disk; 
char kontroler=0,ax=5,ay=2,par_n,dat_n,qiz_n,ptext[4096],text[566],*pok_na_text=text,letter,path[MAXPATH]; 
static char *err_msg[] = {
    "Zastita pisanja !!!",
    "'Unknown unit #@?!'",
    "Drive nije spreman!",
    "Nepoznata naredba!!",
    "'Data error (CRC)!'",
    "'Bad request !#@??'",
    "   'Seek error !'  ",
    " Unknown media type",
    "'Sector not found!'",
    "printer out of paper",
    "   'Write fault!'  ",
    "   'Read fault !'  ",
    "'General failure! '",
    "    'Reserved !'   ",
    "    'Reserved !'   ",
    "Invalid disk change"
};

sve glvn,pri_otvaranju;

void osnovna()
 { int slovo,
       x,y,button;
   ABOT PARA DATO MORS UIIZ RAJK
   gotoxy(1,25);
   cputs("                                                      ");
   show_mouse();
   do
    { get_mouse(&x,&y,&button);
      if(x>=2*8 && x<=6*8) 
	 info();
      if(x>=8*8 && x<=26*8)
	 parametri();
      if(x>=27*8 && x<=36*8)
	 datoteke();
      if(x>=37*8 && x<=45*8)
	 abeceda();
      if(x>=46*8 && x<=54*8)
	 qiz();
      if(x>=73*8 && x<78*8)
	 kraj();
    }
   while(!kbhit());
   slovo=bioskey(0);
   switch(slovo)
     { SKOKOVI
       default: info();break;
     }
 }

void parametri()
 { int slovo,
       x,y,button;
   gotoxy(1,25);
   cputs(" [ ] Podesavanje parametara signala                   ");
   hide_mouse();
   textbackground(10);PARA  
   show_mouse();
   do
    { get_mouse(&x,&y,&button);
      if(x>=2*8 && x<=6*8) 
	{ textbackground(7);PARA
	  info();
	}
      if(x>=27*8 && x<=36*8)
	{ textbackground(7);PARA
	  datoteke();
	}
      if(x>=37*8 && x<=45*8)
	{ textbackground(7);PARA
	  abeceda();
	}
      if(x>=8*8 && x<=26*8 && button==1 && y==0)
	{ textbackground(7);PARA  
	  para_nacrt();
	}
    }
   while(!kbhit());
   hide_mouse();
   slovo=bioskey(0);
   textbackground(7);PARA  
   switch(slovo)
    { SKOKOVI
      case 19712: set_mouse(27*8,0);show_mouse();
		  datoteke();break;
      case 19200: set_mouse(1*8,0);show_mouse();
		  info();break;
      case 7181:  para_nacrt();break;
      default: show_mouse();parametri();break;
    }
 }

void para()
 { int slovo,
       x,y,button;
   void podesavanje_fq(),podesavanje_jdts(),reset(),para_nomouse();
   para_nomouse();
   show_mouse();
   do
    { get_mouse(&x,&y,&button);
      if(button==2)
       { hide_mouse();
	 puttext(9,2,49,7,ptext);
	 osnovna();
       }
      if(button==1 && y==2*8)
       { hide_mouse(); podesavanje_fq(); }
      if(button==1 && y==3*8)
       { hide_mouse(); podesavanje_jdts(); }
      if(button==1 && y==4*8)
       { hide_mouse(); reset(); }
      if(y==0 && x>=27*8 && x<=45*8)
       { hide_mouse();
	 textbackground(7);PARA
	 gettext(9,12,29,17,ptext);
	 puttext(9,2,29,7,ptext);
	 textcolor(1);
	 gotoxy(29,7);cputs("°°°°°°°°°°°°°°°°°°°°°");
	 datt_nacrt();
       }
      /*if(y==0 && x>=46*8 && x<=54*8)
	{ hide_mouse();
	  textbackground(7);PARA
	  puttext(9,2,49,7,ptext);
	  qiz_nacrt();
	  morse_hang();? 
	}*/
      if(par_n==0)
       { if(y==3*8)
	  { par_n=1; hide_mouse(); para(); }
	 if(y==4*8)
	  { par_n=2; hide_mouse(); para();  }
       }
      if(par_n==1)
       { if(y==2*8)
	  { par_n=0; hide_mouse(); para(); }
	 if(y==4*8)
	  { par_n=2; hide_mouse(); para(); }
       }
      if(par_n==2)
       { if(y==3*8)
	  { par_n=1; hide_mouse(); para(); }
	 if(y==2*8)
	  { par_n=0; hide_mouse(); para(); }
       }
    }
   while(!kbhit());
   slovo=bioskey(0);
   hide_mouse();
   switch(slovo)
    { case 283: 
      case 6512: 
      case 6480: 
      case 6400: puttext(9,2,49,7,ptext);osnovna();break;
      case 19712: textbackground(7);PARA
		  gettext(9,12,29,17,ptext);
		  puttext(9,2,29,7,ptext);
		  textcolor(1);
		  gotoxy(29,7);cputs("°°°°°°°°°°°°°°°°°°°°°");
		  set_mouse(27*8,0);
		  datt_nacrt();break;
      case 8550: 
      case 8518: par_n=0;
		 set_mouse(10*8,2*8);para();break;
      case 9322:
      case 9290: par_n=1;
		 set_mouse(10*8,3*8);para();break;
      case 4978: 
      case 4946: par_n=2;
		 set_mouse(10*8,4*8);para();break;
      case 20480: if(par_n==2) 
		    { set_mouse(10*8,2*8); par_n=0; }
		  else if(!par_n)
		    { set_mouse(10*8,3*8); par_n=1; }
		  else
		    { set_mouse(10*8,4*8); par_n=2; }
		  para();break;
      case 18432: if(!par_n)
		    { set_mouse(10*8,4*8); par_n=2; }
		  else if(par_n==1)
		    { set_mouse(10*8,2*8); par_n=0; }
		  else
		    { set_mouse(10*8,3*8); par_n=1; }
		  para();break;
      case 4864: textbackground(10);RESP
		 textbackground(7);FRNK JDTS
		 gotoxy(1,25);
		 cputs(" [ ] Povrat parametara na 'tvornicke' vrijednosti     ");
		 reset();break;
      case 7181: if(!par_n)
		    podesavanje_fq();
		 else if(par_n==1)
		    podesavanje_jdts();
		 else
		    reset();
		 break;
      case 8448: textbackground(10);FRNK
		 textbackground(7);RESP JDTS
		 gotoxy(1,25);
		 cputs(" [ ] Podesavanje frekvencije                          ");
		 podesavanje_fq();
		 break;
      case 9216: textbackground(10);JDTS
		 textbackground(7);FRNK RESP
		 gotoxy(1,25);
		 cputs(" [ ] Podesavanje jedinicne duzine signala             ");
		 podesavanje_jdts();
		 break;
      default: para();break;
    }
 }

void datoteke()
 { int slovo,
       x,y,button;
   gotoxy(1,25);
   cputs(" [ ] Pisanje, snimanje, citanje i signalizacija poruka");
   hide_mouse();
   textbackground(10);DATO
   show_mouse();
   do
    { get_mouse(&x,&y,&button);
      if(x>=2*8 && x<=6*8)
	 { textbackground(7);DATO
	   info();
	 }
      if(x>=8*8 && x<=26*8)
	 { textbackground(7);DATO
	   parametri();
	 }
      if(x>=37*8 && x<=45*8)
	 { textbackground(7);DATO
	   abeceda();
	 }
      if(x>=46*8 && x<=54*8)
	 { textbackground(7);DATO
	   qiz();
	 }
      if(x>=27*8 && x<=36*8 && button==1 && y==0)
	 { textbackground(7);DATO
	   datt_nacrt();
	 }
    }
   while(!kbhit());
   hide_mouse();
   slovo=bioskey(0);
   textbackground(7);DATO
   switch(slovo)
    { SKOKOVI
      case 19712: set_mouse(37*8,0);show_mouse();
		  abeceda();break;
      case 19200: set_mouse(8*8,0);show_mouse();
		  parametri();break;
      case 7181: datt_nacrt();break;
      default: show_mouse();datoteke();break;
    }
 }

void datt()
 { int slovo,
       x,y,button;
   void pisanje_poruke(),citanje_poruke(),datt_nomouse();
   datt_nomouse();
   show_mouse();
   do
     { get_mouse(&x,&y,&button);
       if(button==2)
	{ hide_mouse();
	  puttext(28,2,49,6,ptext);
	  osnovna();
	}
       if(y==0 && x>=8*8 && x<=26*8)
	{ hide_mouse();
	  textbackground(7);DATO
	  para_nacrt();
	}
       /*if(y==0 && x>=46*8 && x<=54*8)
	{ hide_mouse();
	  textbackground(7);DATO
	  puttext(28,2,49,6,ptext);
	  qiz_nacrt();
	  morse_hang();
	}*/
       if(y==2*8 && button==1)
	{ hide_mouse();
	  puttext(28,2,49,6,ptext);
	  textbackground(7);DATO
	  sjencenje();
	  pisanje_poruke();
	}
       if(y==3*8 && button==1)
	{ hide_mouse();
	  puttext(28,2,49,6,ptext);
	  textbackground(7);DATO
	  sjencenje();
	  citanje_poruke();
	}
       if(dat_n==1 && y<=2*8)
	{ dat_n=0;
	  hide_mouse();
	  datt();
	}
       if(dat_n==0 && y>=3*8)
	{ dat_n=1;
	  hide_mouse();
	  datt();
	}
     }
   while(!kbhit());
   slovo=bioskey(0);
   hide_mouse();
   switch(slovo)
    { case 7181: if(!dat_n)
		    { puttext(28,2,49,6,ptext);
		      textbackground(7);DATO
		      sjencenje();
		      pisanje_poruke();
		    }
		 else 
		    { puttext(28,2,49,6,ptext);
		      textbackground(7);DATO
		      sjencenje();
		      citanje_poruke();
		    }
		 break;
      case 283: 
      case 8292: 
      case 8192: 
      case 8260: puttext(28,2,49,6,ptext);
		 osnovna();break;
      case 19200: textbackground(7);DATO
		  set_mouse(8*8,0);
		  para_nacrt();break;
      case 19712: textbackground(7);DATO
		  puttext(28,2,49,6,ptext);abe_nacrt();break;
      case 6512: 
      case 6480: dat_n=0;
		 set_mouse(29*8,2*8);datt();break;
      case 11875: 
      case 11843: dat_n=1;
		  set_mouse(29*8,3*8);datt();break;
      case 20480: if(dat_n)
		     { set_mouse(29*8,2*8); dat_n=0; }
		  else
		     { set_mouse(29*8,3*8); dat_n=1; }
		  datt();break;
      case 18432: if(!dat_n)
		     { set_mouse(29*8,3*8); dat_n=1; }
		  else
		     { set_mouse(29*8,2*8); dat_n=0; }
		  datt();break;
      case 6400: puttext(28,2,49,6,ptext);
		 textbackground(7);DATO
		 sjencenje();
		 pisanje_poruke();
		 break;
      case 11776: puttext(28,2,49,6,ptext);
		  textbackground(7);DATO
		  sjencenje();
		  citanje_poruke();
		  break;
      default: datt();break;
    } 
 }

void pohrana_mis()
 { int x,y,button;
   gotoxy(16,13);cputs("                                         ");
   switch(letter)
    { case 's': textbackground(10); SIGN
		textbackground(7);
		cputs("Ü");gotoxy(19,14);cputs("ßßßßßßßßßßßßßß");
		POHR cputs(" ");gotoxy(35,14);cputs("         "); 
		IZLA cputs(" ");gotoxy(46,14);cputs("        "); 
		break;
      case 'p': textbackground(10); POHR
		textbackground(7);
		cputs("Ü");gotoxy(35,14);cputs("ßßßßßßßßß"); 
		SIGN cputs(" ");gotoxy(19,14);cputs("              ");
		IZLA cputs(" ");gotoxy(46,14);cputs("        "); 
		break;
      case 'i': textbackground(10); IZLA
		textbackground(7); 
		cputs("Ü");gotoxy(46,14);cputs("ßßßßßßßß"); 
		POHR cputs(" ");gotoxy(35,14);cputs("         ");
		SIGN cputs(" ");gotoxy(19,14);cputs("              ");
		break;
    }
   show_mouse();
   do
    { get_mouse(&x,&y,&button);
      if(button==2)
       { hide_mouse();
	 window(1,1,80,25);
	 puttext(5,3,77,18,ptext);
	 osnovna();
       }
       if(x>=21*8 && x<=34*8 && letter!='s')
	{ hide_mouse();
	  textbackground(10); SIGN
	  textbackground(7);
	  cputs("Ü");gotoxy(19,14);cputs("ßßßßßßßßßßßßßß");
	  POHR cputs(" ");gotoxy(35,14);cputs("         "); 
	  IZLA cputs(" ");gotoxy(46,14);cputs("        "); 
	  letter='s';
	  show_mouse();
	}
       if(x>=37*8 && x<=45*8 && letter!='p')
	{ hide_mouse();
	  textbackground(10); POHR
	  textbackground(7);
	  cputs("Ü");gotoxy(35,14);cputs("ßßßßßßßßß"); 
	  SIGN cputs(" ");gotoxy(19,14);cputs("              ");
	  IZLA cputs(" ");gotoxy(46,14);cputs("        "); 
	  letter='p';
	  show_mouse();
	}
       if(x>=48*8 && x<=55*8 && letter!='i')
	{ hide_mouse();
	  textbackground(10); IZLA
	  textbackground(7); 
	  cputs("Ü");gotoxy(46,14);cputs("ßßßßßßßß"); 
	  POHR cputs(" ");gotoxy(35,14);cputs("         ");
	  SIGN cputs(" ");gotoxy(19,14);cputs("              ");
	  letter='i';
	  show_mouse();
	}
       if(button==1 && y==14*8)
	{ if(x>=21*8 && x<=34*8)
	   { hide_mouse();
	     signalizacija();
	     show_mouse();
	   }
	  if(x>=37*8 && x<=45*8)
	   { hide_mouse();
	     pohrana();
	     show_mouse();
	   }
	  if(x>=48*8 && x<=55*8)
	   { hide_mouse();
	     window(1,1,80,25);
	     puttext(5,3,77,18,ptext);
	     osnovna();
	   }
	}
    }
   while(!kbhit());
   hide_mouse();
 }

void abeceda()
 { int slovo,
       x,y,button;
   gotoxy(1,25);
   cputs(" [ ] Lista Morseovog koda                             ");
   hide_mouse();
   textbackground(10);
   gotoxy(38,1);MORS
   show_mouse();
   do
    { get_mouse(&x,&y,&button);
      if(x>=8*8 && x<=26*8)
	 { textbackground(7);MORS
	   parametri();
	 }
      if(x>=27*8 && x<=36*8)
	 { textbackground(7);MORS
	   datoteke();
	 }
      if(x>=46*8 && x<=54*8)
	 { textbackground(7);MORS
	   qiz();
	 }
      if(x>=37*8 && x<=45*8 && button==1 && y==0)
	{ hide_mouse();
	  textbackground(7);MORS
	  abe_nacrt();
	}
    }
   while(!kbhit());
   hide_mouse();
   slovo=bioskey(0);
   textbackground(7);MORS
   switch(slovo)
    { SKOKOVI
      case 19712: set_mouse(46*8,0);show_mouse();
		  qiz();break;
      case 19200: set_mouse(27*8,0);show_mouse();
		  datoteke();break;
      case 7181: abe_nacrt();break;
      default: show_mouse();abeceda();break;
    }
 }

void abe()
 { int slovo,
       x,y,button;
   void abe_nomouse(int);
   window(5,3,75,23);
   gotoxy(ax,ay);cputs("");
   show_mouse();
   do
    { get_mouse(&x,&y,&button);
      if(button==1)
       { if(x>=10*8)
	  { if(x<=14*8 && y==3*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=5;ay=2; A
	       abe();
	     }
	    if(x<=18*8 && y==4*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=5;ay=3; B
	       abe();
	     }
	    if(x<=18*8 && y==5*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=5;ay=4; C
	       abe();
	     }
	    if(x<=16*8 && y==6*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=5;ay=5; D
	       abe();
	     }  
	    if(x<=12*8 && y==7*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=5;ay=6; E
	       abe();
	     }
	    if(x<=18*8 && y==8*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=5;ay=7; F
	       abe();
	     }
	    if(x<=16*8 && y==9*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=5;ay=8; G
	       abe();
	     }
	    if(x<=18*8 && y==10*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=5;ay=9; H
	       abe();
	     }
	    if(x<=14*8 && y==11*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=5;ay=10; I
	       abe();
	     }
	    if(x<=18*8 && y==12*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=5;ay=11; J
	       abe();
	     }
	    if(x<=16*8 && y==13*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=5;ay=12; K
	       abe();
	     }
	    if(x<=18*8 && y==14*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=5;ay=13; L
	       abe();
	     }
	    if(x<=27*8 && y==17*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=5;ay=16; KRATKI
	       abe();
	     }
	    if(x<=25*8 && y==18*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=5;ay=17; DUGI
	       abe();
	     }
	    if(x<=14*8 && y==20*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=5;ay=19; 
	       hide_mouse();
	       window(1,1,80,25);
	       puttext(5,3,77,23,ptext);
	       osnovna();
	     }
	  }
	 if(x>=34*8) 
	  { if(x<=38*8 && y==3*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=29;ay=2; M
	       abe();
	     }
	    if(x<=38*8 && y==4*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=29;ay=3; N
	       abe();
	     }
	    if(x<=40*8 && y==5*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=29;ay=4; O
	       abe();
	     }
	    if(x<=42*8 && y==6*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=29;ay=5; P
	       abe();
	     }
	    if(x<=42*8 && y==7*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=29;ay=6; Q
	       abe();
	     }
	    if(x<=40*8 && y==8*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=29;ay=7; R
	       abe();
	     }
	    if(x<=40*8 && y==9*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=29;ay=8; S
	       abe();
	     }
	    if(x<=36*8 && y==10*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=29;ay=9; T
	       abe();
	     }
	    if(x<=40*8 && y==11*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=29;ay=10; U
	       abe();
	     }
	    if(x<=42*8 && y==12*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=29;ay=11; V
	       abe();
	     }
	    if(x<=40*8 && y==13*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=29;ay=12; W
	       abe();
	     }
	    if(x<=42*8 && y==14*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=29;ay=13; X
	       abe();
	     }
	  }
	 if(x>=58*8)
	  { if(x<=66*8 && y==3*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=53;ay=2; Y
	       abe();
	     }
	    if(x<=66*8 && y==4*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=53;ay=3; Z
	       abe();
	     }
	    if(x<=68*8 && y==5*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=53;ay=4; JEDAN	
	       abe();
	     }
	    if(x<=68*8 && y==5*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=53;ay=4; JEDAN	
	       abe();
	     }
	    if(x<=68*8 && y==6*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=53;ay=5; DVA	
	       abe();
	     }
	    if(x<=68*8 && y==7*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=53;ay=6; TRI	
	       abe();
	     }
	    if(x<=68*8 && y==8*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=53;ay=7; CETRI	
	       abe();
	     }
	    if(x<=68*8 && y==9*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=53;ay=8; PET	
	       abe();
	     }
	    if(x<=68*8 && y==10*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=53;ay=9; SEST	
	       abe();
	     }
	    if(x<=68*8 && y==11*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=53;ay=10; SEDAM	
	       abe();
	     }
	    if(x<=68*8 && y==12*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=53;ay=11; OSAM	
	       abe();
	     }
	    if(x<=68*8 && y==13*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=53;ay=12; DEVET	
	       abe();
	     }
	    if(x<=68*8 && y==14*8)
	     { gotoxy(ax,ay);cputs(" ");
	       ax=53;ay=13; NULA		
	       abe();
	     }
	  }
       }
      if(button==2)
       { hide_mouse();
	 window(1,1,80,25);
	 puttext(5,3,77,23,ptext);
	 osnovna();
       }
    }
   while(!kbhit());
   slovo=bioskey(0);
   hide_mouse();
   abe_nomouse(slovo);
   window(1,1,80,25);
   puttext(5,3,77,23,ptext);
   osnovna();
 }

void qiz()
 { int slovo,
       x,y,button;
   gotoxy(1,25);
   cputs(" [ ] Provjera znanja                                  ");
   hide_mouse();
   textbackground(10);
   gotoxy(56,1);UIIZ 
   show_mouse();
   do
    { get_mouse(&x,&y,&button);
      if(x>=27*8 && x<=36*8)
	 { textbackground(7);UIIZ
	   datoteke();
	 }
      if(x>=37*8 && x<=45*8)
	 { textbackground(7);UIIZ
	   abeceda();
	 }
      if(x>=73*8 && x<=78*8)
	 { textbackground(7);UIIZ
	   kraj();
	 }
      if(x>=46*8 && x<=54*8 && y==0 && button==1)
	 { hide_mouse();
	   textbackground(7);UIIZ
	   /*qiz_nacrt();*/
	   morse_hang();
	 }
    }
   while(!kbhit());
   hide_mouse();
   slovo=bioskey(0);
   textbackground(7);UIIZ
   switch(slovo)
    { SKOKOVI
      case 19712: set_mouse(55*8,0);show_mouse();
		  kraj();break;
      case 19200: set_mouse(37*8,0);show_mouse();
		  abeceda();break;
      case 7181: morse_hang();/*qiz_nacrt();*/break;
      default: show_mouse();qiz();break;
    }
 }

void qiz_pravi()
 { int slovo,
       x,y,button;         
   void qiz_nomouse();
   qiz_nomouse();
   show_mouse();
   do
     { get_mouse(&x,&y,&button);
       if(button==2)
	{ hide_mouse();
	  puttext(47,2,73,6,ptext);    
	  osnovna();
	}
       if(button==1)
	{ if(y==3*8)
	   { hide_mouse();
	     textbackground(7);UIIZ
	     puttext(47,2,73,6,ptext);
	     morse_hang();
	   }
	}
       if(qiz_n==1 && y<=2*8)
	{ qiz_n=0;
	  hide_mouse();
	  qiz_pravi();
	}
       if(qiz_n==0 && y>=3*8)
	{ qiz_n=1;
	  hide_mouse();
	  qiz_pravi();
	}
       if(x>=8*8 && x<=26*8 && y==0)
	{ hide_mouse();
	  puttext(47,2,73,6,ptext);    
	  textbackground(7);UIIZ
	  para_nacrt();
	}
       if(x>=27*8 && x<=36*8 && y==0)
	{ hide_mouse();
	  puttext(47,2,73,6,ptext);    
	  textbackground(7);UIIZ
	  datt_nacrt();
	}
     }
   while(!kbhit());
   slovo=bioskey(0);
   hide_mouse();
   switch(slovo)
    { case 283: 
      case 4209: 
      case 4177: 
      case 4096: puttext(47,2,73,6,ptext);    
		 osnovna();break;
      case 8051:
      case 8019: qiz_n=0;set_mouse(48*8,2*8);
		 qiz_pravi();break;
      case 12909:
      case 12877: qiz_n=1;set_mouse(48*8,3*8);
		  qiz_pravi();break;
      case 12800: textbackground(7);UIIZ
		  puttext(47,2,73,6,ptext);
		  morse_hang();break;
      case 7181: if(qiz_n)
		   { textbackground(7);UIIZ
		     puttext(47,2,73,6,ptext);
		     morse_hang();  
		   }
		  break;
      case 20480: if(qiz_n)
		   { qiz_n=0;set_mouse(48*8,2*8);
		     qiz_pravi();
		   }
		  else
		   { qiz_n=1;set_mouse(48*8,3*8);
		     qiz_pravi(); 
		   }
		  break;
      case 18432: if(qiz_n)
		   { qiz_n=0;set_mouse(48*8,2*8);
		     qiz_pravi();
		   }
		  else
		   { qiz_n=1;set_mouse(48*8,3*8);
		     qiz_pravi(); 
		   }
		  break;
      case 19200: textbackground(7);UIIZ
		  puttext(47,2,73,6,ptext);    
		  abe_nacrt();break;
      case 19712: textbackground(7);UIIZ
		  puttext(47,2,73,6,ptext);    
		  kraj();break;
      default: qiz_pravi();
    }
 }

void kraj()
 { int slovo,
       x,y,button;
   gotoxy(1,25);
   cputs(" [ ] Izlazak iz programa                              ");
   hide_mouse();
   textbackground(10);
   gotoxy(68,1);RAJK
   show_mouse();
   do
    { get_mouse(&x,&y,&button);
      if(x>=46*8 && x<=54*8)
	 { textbackground(7);RAJK
	   qiz();
	 }
      if(x>=55*8 && x<=71*8)
	 { textbackground(7);RAJK
	   qiz();
	 }
      if(x>=73*8 && x<=78*8 && button==1)
	{ hide_mouse();
	  textbackground(7);RAJK
	  show_mouse();
	  pravi_kraj();
	}
    }
   while(!kbhit());
   hide_mouse();
   slovo=bioskey(0);
   textbackground(7);RAJK
   switch(slovo)
    { SKOKOVI
      case 19712: set_mouse(1*8,0);show_mouse();
		  info();break;
      case 19200: set_mouse(55*8,0);show_mouse();
		  qiz();break;
      case 7181: pravi_kraj();break;
      default: show_mouse();kraj();break;
    }
 }

void pravi_kraj()
 { int x,y,button;
   char izbor;
   void pravi_izlaz();
   gotoxy(1,25);
   cputs(" [þ] Izlazak iz programa                              ");
   sjencenje();
   gettext(8,10,74,13,ptext);
   window(8,10,72,12);
   clrscr();
   drawer(64,3);
   gotoxy(15,2);cputs("Zaista zelite izlaz iz      -a (d/n)?");
   textcolor(1);gotoxy(38,2);cputs("Morse");
   textcolor(0);
   liner(8,72,10,12);
   show_mouse();
   do
     { get_mouse(&x,&y,&button);
       if(x==55*8 && y==10*8 && button==1)
	 { hide_mouse();
	   puttext(8,10,74,13,ptext);
	   osnovna();
	 }
       if(x==53*8 && y==10*8 && button==1)
	 { hide_mouse();
	   pravi_izlaz();
	 }
     }
   while(!kbhit());
   if((izbor=getch())!='d')
     { hide_mouse();
       puttext(8,10,74,13,ptext);
       osnovna();
     }
   pravi_izlaz();
 }

void pravi_izlaz()
 { int x,y,button;
   char izbor;
   if(pri_otvaranju.fq!=glvn.fq || pri_otvaranju.sgnl!=glvn.sgnl)
       { window(8,10,72,12);
	 gotoxy(5,2);cputs("Zelite li sacuvati trenutne vrijednosti parametara (d/n)?");
	 show_mouse();
	 do
	  { get_mouse(&x,&y,&button);
	    if(x==65*8 && y==10*8 && button==1)
	     EXIT(0);
	    if(x==63*8 && y==10*8 && button==1)
	     { posebna();
	       EXIT(0);
	     }
	  }
	 while(!kbhit());
	 if((izbor=getch())=='d')
	   posebna(); 
       }
   EXIT(0);
 }

void info()
 { int slovo,
       x,y,button;
   gotoxy(1,25);
   cputs(" [ ] Verzija, autor                                   ");
   hide_mouse();
   textbackground(10);
   gotoxy(1,1);ABOT
   show_mouse();
   do
    { get_mouse(&x,&y,&button);
      if(x>=8*8 && x<=26*8)
	{ textbackground(7);ABOT
	  parametri();
	}
      if(x>=27*8 && x<=36*8)
	{ textbackground(7);ABOT
	  datoteke();
	}
      if(x>=1*8 && x<=6*8 && button==1 && y==0)
	{ hide_mouse();
	  textbackground(7);ABOT
	  gettext(20,6,64,19,ptext);in();
	}
    }
   while(!kbhit());
   hide_mouse();
   slovo=bioskey(0);
   textbackground(7);ABOT
   switch(slovo)
    { SKOKOVI
      case 19712: set_mouse(8*8,0);show_mouse();
		  parametri();break;
      case 19200: set_mouse(73*8,0);show_mouse();
		  kraj();break;
      case 7181: gettext(20,6,64,19,ptext);in();break;
      default: show_mouse();info();break;
    }
 }

error_win(char *msg)
 { int retval;
   if(kontroler==1)
    { mouse_install();
      najposebna();
    }
   if(kontroler==2)
    { gotoxy(21,4);cputs(msg);printf("\7");
      getch();cputs("                                                 ");	
      setdisk(2);
      textcolor(0);
      citanje_poruke_fifi();
    }
   gotoxy(3,2);cputs("                                                                  ");
   gotoxy(27,2);cputs(msg);printf("\7");
   getch();gotoxy(3,2);
   cputs("                                                                  ");	
   prava_pohrana();
   while(1)
   {
       retval= getch();
       if (retval == 'a' || retval == 'A')
       {
           retval = ABORT;
           break;
       }
       if (retval == 'r' || retval == 'R')
       {
           retval = RETRY;
           break;
       }
       if (retval == 'i' || retval == 'I')
       {
           retval = IGNORE;
           break;
       }
   }

   return(retval);
}

/*
pragma warn -par reduces warnings which occur
due to the non use of the parameters errval,
bp and si to the handler.
*/



#pragma warn -par

int handler(int errval,int ax,int bp,int si)
{
   static char msg[80];
   unsigned di;
   int errorno;

   di= _DI;
/*
if this is not a disk error then it was
another device having trouble
*/

   if (ax < 0)
   {
      /* report the error */
      error_win("Device error");
      /* and return to the program directly requesting abort */
      hardretn(ABORT);
   }
/* otherwise it was a disk error */
   errorno = di & 0x00FF;
/* report which error it was */
   sprintf(msg,"%s",err_msg[errorno]);
/*
return to the program via dos interrupt 0x23 with abort, retry,
or ignore as input by the user.
*/
   hardresume(error_win(msg));
   return RETRY;
}
#pragma warn +par

odjebi()
 { textbackground(0);clrscr();
   printf("\7");
   printf("Iz programa se moze izaci i na manje brutalan nacin! Za kaznu pricekaj 10 s.");
   sleep(10);
   printf("\nStay beautiful!");
   return(0);
 }
   
main(int argv,char **argc)
 { const char *ime="MORSE10T.EXE";
   char *cmp=&argc[0][strlen(argc[0])-12];
   void alert(int),
	PromjeniDirektorij(char **argc);
   int odjebi();
	
   ctrlbrk(odjebi);
   randomize();
   disk=getdisk();getcurdir(0,path);
   _setcursortype(_NOCURSOR);
   
   PromjeniDirektorij(argc);

   if(strcmp(cmp,ime))
    alert(1);

   ucitavanje_para();
   if(argv>=3)
     glvn.sgnl=atoi(argc[2]);
   if(argv>=4)
     glvn.fq=atoi(argc[3]);
   if(argv>=2)
    { if(!strcmp(argc[1],"/?"))
       { printf("\nMorse ver1.0t");
	 printf("\nZa ispravno pokretanje programa iz parametarske linije koristite:");
	 printf("\n\n  morse10t \"tekst za signaliziranje\" [duzina_jedinice frekvencija]");
	 printf("\n\n gdje je:");
	 printf("\n tekst za signaliziranje - skup slova engleske abecede, brojeva i razmaknica");
	 printf("\n duzina_jedinice         - cijelobrijna vrijednost duzine trajanja osnovne");
	 printf("\n                           jedinice signala izrazene u milisekundama");
	 printf("\n frekvencija             - cijelobrojna vrijednost frekvencije izrazene u Hz");
	 printf("\n\n");
	 exit(0);
       }
     
      strcpy(text,argc[1]);
      for(register int i=0;i<=strlen(argc[1]);i++)
       sama_signalizacija(i);
      EXIT(0);
    }
   
   mouse_install();
   set_mouse(0,0);
   mouse_ratio(8,8);
   mouse_horiz(0,79*8);
   mouse_vert(0,23*8);
   
   textbackground(7);
   textcolor(1); 
   clrscr();

   peglaj();

   harderr(handler);
   osnovna();
 }  
 