// EXIT - izlazak iz programa: postavljanja standardnog DOS ekrana,
//			       gasenje kursora i misa, vracanje u
//			       direktorij iz kojega je vrsen poziv 
//			       programa i vracanje nule OSu          


#define EXIT(status) window(1,1,80,25);                            \
		     textbackground(0);textcolor(7);clrscr();      \
		     _setcursortype(_NORMALCURSOR);mouse_install();\
		     chdir(CurWDir);exit(status);


// UL - up left
// UR - up right
// DL - down left
// DR - down right

#define UL 0
#define UR 1
#define DL 2
#define DR 3


// tipke i njihove ASCII vrijednosti

#define BACKSPACE 8
#define ESC       27


// korisne stvari:
//
// _BACKSPACE - emulacija backspace tipke
// _BEEP      - beep iz PC speakera

#define _BACKSPACE cprintf("\b \b");
#define _BEEP       printf("\a");


// prototipovi funkcija

void sat(char,char);
void peglaj();
void ProzorNormalni(char,char,char,char);
void ProzorSaCrtom(char,char,char,char,char);

char charatcur();


// varijable

extern char CurWDir[MAXPATH];
