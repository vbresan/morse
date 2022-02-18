#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <bios.h>
#include <dos.h>
#include <dir.h>
#include "mouse.h"
#include "mytxt.h"

#define IGNORE  0
#define RETRY   1
#define ABORT   2

#define SKOKOVI case 6480: case 6512: set_mouse(8*8,0);show_mouse();parametri();break;case 6400: para_nacrt();break;\
		case 8260: case 8292: set_mouse(27*8,0);show_mouse();datoteke();break;case 8192: datt_nacrt();break;\
		case 7777: case 7745: set_mouse(37*8,0);show_mouse();abeceda();break;case 7680: abe_nacrt();break;\
		case 4209: case 4177: set_mouse(46*8,0);show_mouse();qiz();break;case 4096: morse_hang();/*qiz_nacrt();*/break;\
		case 9547: case 9579: set_mouse(73*8,0);show_mouse();kraj();break;case 9472: pravi_kraj();break;\
		case 5993: case 5961: set_mouse(1*8,0);show_mouse();info();break;\
		case 5888: gettext(20,6,64,19,ptext);in();break;

#define ABOT textcolor(4);gotoxy(2,1);cputs(" I");textcolor(0);cputs("nfo ");
#define PARA textcolor(4);gotoxy(9,1);cputs(" P");textcolor(0);cputs("arametri signala ");
#define DATO textcolor(4);gotoxy(28,1);cputs(" D");textcolor(0);cputs("atoteke ");
#define MORS textcolor(4);gotoxy(38,1);cputs(" A");textcolor(0);cputs("beceda ");
#define UIIZ textcolor(4);gotoxy(47,1);cputs(" Q");textcolor(0);cputs("uiz!!! ");
#define RAJK textcolor(4);gotoxy(74,1);cputs(" K");textcolor(0);cputs("raj ");

#define FRNK textcolor(4);gotoxy(11,3);cputs(" F");textcolor(0);cputs("rekvencija                       ");
#define JDTS textcolor(4);gotoxy(11,4);cputs(" J");textcolor(0);cputs("edinicna duzina trajanja signala ");
#define RESP textcolor(4);gotoxy(11,5);cputs(" R");textcolor(0);cputs("eset parametara                  ");
#define PISA textcolor(4);gotoxy(30,3);cputs(" P");textcolor(0);cputs("isanje poruke ");
#define CITA textcolor(4);gotoxy(30,4);cputs(" C");textcolor(0);cputs("itanje poruke ");
#define STAN textcolor(4);gotoxy(49,3);cputs(" S");textcolor(0);cputs("tandardna provjera ");
#define HANG textcolor(4);gotoxy(49,4);cputs(" M");textcolor(0);cputs("orse's hang!       ");

#define SIGN textcolor(4);gotoxy(18,13);cputs(" S");textcolor(0);cputs("ignaliziraj ");
#define POHR textcolor(4);gotoxy(34,13);cputs(" P");textcolor(0);cputs("ohrani ");
#define IZLA textcolor(4);gotoxy(45,13);cputs(" I");textcolor(0);cputs("zlaz! ");

#define DUGI sound(glvn.fq); delay(3*glvn.sgnl); nosound(); delay(glvn.sgnl);
#define RAZMAK delay(3*glvn.sgnl);
#define KRATKI sound(glvn.fq); delay(glvn.sgnl); nosound(); delay(glvn.sgnl);
#define SPEJS delay(6*glvn.sgnl);

#define A KRATKI DUGI RAZMAK
#define B DUGI KRATKI KRATKI KRATKI RAZMAK
#define C DUGI KRATKI DUGI KRATKI RAZMAK
#define D DUGI KRATKI KRATKI RAZMAK
#define E KRATKI RAZMAK
#define F KRATKI KRATKI DUGI KRATKI RAZMAK
#define G DUGI DUGI KRATKI RAZMAK
#define H KRATKI KRATKI KRATKI KRATKI RAZMAK
#define I KRATKI KRATKI RAZMAK
#define J KRATKI DUGI DUGI DUGI RAZMAK
#define K DUGI KRATKI DUGI RAZMAK
#define L KRATKI DUGI KRATKI KRATKI RAZMAK
#define M DUGI DUGI RAZMAK
#define N DUGI KRATKI RAZMAK
#define O DUGI DUGI DUGI RAZMAK
#define P KRATKI DUGI DUGI KRATKI RAZMAK
#define Q DUGI DUGI KRATKI DUGI RAZMAK
#define R KRATKI DUGI KRATKI RAZMAK
#define S KRATKI KRATKI KRATKI RAZMAK
#define T DUGI RAZMAK
#define U KRATKI KRATKI DUGI RAZMAK
#define V KRATKI KRATKI KRATKI DUGI RAZMAK
#define X DUGI KRATKI KRATKI DUGI RAZMAK
#define	Y DUGI KRATKI DUGI DUGI RAZMAK
#define W KRATKI DUGI DUGI RAZMAK
#define	Z DUGI DUGI KRATKI KRATKI RAZMAK
#define	JEDAN KRATKI DUGI DUGI DUGI DUGI RAZMAK
#define	DVA KRATKI KRATKI DUGI DUGI DUGI RAZMAK
#define	TRI KRATKI KRATKI KRATKI DUGI DUGI RAZMAK
#define	CETRI KRATKI KRATKI KRATKI KRATKI DUGI RAZMAK
#define	PET KRATKI KRATKI KRATKI KRATKI KRATKI RAZMAK
#define	SEST DUGI KRATKI KRATKI KRATKI KRATKI RAZMAK
#define	SEDAM DUGI DUGI KRATKI KRATKI KRATKI RAZMAK
#define	OSAM DUGI DUGI DUGI KRATKI KRATKI RAZMAK
#define	DEVET DUGI DUGI DUGI DUGI KRATKI RAZMAK
#define	NULA DUGI DUGI DUGI DUGI DUGI RAZMAK

void ucitavanje_para();
void parametri();
void para_nacrt();
void datoteke();
void datt();
void datt_nacrt();
void ispis_fajli(int);
void citanje_poruke_nenacrt();
void citanje_poruke_fifi();
void pohrana();
void prava_pohrana();
void pohrana_mis();
void monkey();
void abeceda();
void abe_nacrt();
void abe();
void qiz();
void qiz_nacrt();
void qiz_pravi();
void morse_hang();
void kraj();
void pravi_kraj();
void info();
void in();
void osnovna();
void sjencenje();
oba_podesavanja(char);
void posebna();
void najposebna();
void signalizacija();
void drawer(char,char);
void liner(char,char,char,char);
void sama_signalizacija(register int);