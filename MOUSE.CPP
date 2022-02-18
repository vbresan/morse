#include <dos.h>
#include "mouse.h"

mouse_install(void)
 { union REGS inregs,outregs;
   inregs.x.ax=0x0;
   int86(MOUSE_INT,&inregs,&outregs);
   return(outregs.x.ax);
 }

void show_mouse(void)
 { union REGS inregs,outregs;
   inregs.x.ax=0x1;
   int86(MOUSE_INT,&inregs,&outregs);
 }

void hide_mouse(void)
 { union REGS inregs,outregs;
   inregs.x.ax=0x2;
   int86(MOUSE_INT,&inregs,&outregs);
 }

void get_mouse(int *x,int *y,int *button)
 { union REGS inregs,outregs;
   inregs.x.ax=0x3;
   int86(MOUSE_INT,&inregs,&outregs);
   *button=outregs.x.bx & 3;
   *x=outregs.x.cx;
   *y=outregs.x.dx;
 }

void set_mouse(int x,int y)
 { union REGS inregs,outregs;
   inregs.x.ax=0x4;
   inregs.x.cx=x;
   inregs.x.dx=y;
   int86(MOUSE_INT,&inregs,&outregs);
 }

void button_press(int button_no,int *status,int *press,int *x,int *y)
 { union REGS inregs,outregs;
   inregs.x.ax=0x5;
   inregs.x.bx=button_no;
   int86(MOUSE_INT,&inregs,&outregs);
   *status=outregs.x.ax;
   *press=outregs.x.bx;
   *x=outregs.x.cx;
   *y=outregs.x.dx;
 }

void button_release(int button_no,int *status,int *release,int *x,int *y)
 { union REGS inregs,outregs;
   inregs.x.ax=0x6;
   inregs.x.bx=button_no;
   int86(MOUSE_INT,&inregs,&outregs);
   *status=outregs.x.ax;
   *release=outregs.x.bx;
   *x=outregs.x.cx;
   *y=outregs.x.dx;
 }

void mouse_horiz(int minx,int maxx)
 { union REGS inregs,outregs;
   inregs.x.ax=0x7;
   inregs.x.cx=minx;
   inregs.x.dx=maxx;
   int86(MOUSE_INT,&inregs,&outregs);
 }

void mouse_vert(int miny,int maxy)
 { union REGS inregs,outregs;
   inregs.x.ax=0x8;
   inregs.x.cx=miny;
   inregs.x.dx=maxy;
   int86(MOUSE_INT,&inregs,&outregs);
 }

void mouse_grcursor(int h,int v,int cursor_def[])
 { union REGS inregs,outregs;
   struct SREGS segregs;
   inregs.x.ax=0x9;
   inregs.x.bx=h;
   inregs.x.cx=v;
   segregs.es=FP_SEG(cursor_def);
   inregs.x.dx=FP_OFF(cursor_def);
   int86x(MOUSE_INT,&inregs,&outregs,&segregs);
 }

void mouse_txcursor(int cursor_type,int attr_1,int attr_2)
 { union REGS inregs,outregs;
   inregs.x.ax=0xa;
   inregs.x.bx=cursor_type;
   inregs.x.cx=attr_1;
   inregs.x.dx=attr_2;
   int86(MOUSE_INT,&inregs,&outregs);
 }
 
void mouse_motion(int *x,int *y)
 { union REGS inregs,outregs;
   inregs.x.ax=0xb;
   int86(MOUSE_INT,&inregs,&outregs);
   *x=outregs.x.cx;
   *y=outregs.x.dx;
 }

void mouse_ratio(int x_ratio,int y_ratio)
 { union REGS inregs,outregs;
   inregs.x.ax=0xf;
   inregs.x.cx=x_ratio;
   inregs.x.dx=y_ratio;
   int86(MOUSE_INT,&inregs,&outregs);
 }

void remove_mouse(int upper_x,int upper_y,int lower_x,int lower_y)
 { union REGS inregs,outregs;
   inregs.x.ax=0x10;
   inregs.x.cx=upper_x;
   inregs.x.dx=upper_y;
   inregs.x.si=lower_x;
   inregs.x.di=lower_y;
   int86(MOUSE_INT,&inregs,&outregs);
 }

void mouse_sprite(unsigned char width,unsigned char scanlines,char h,char v,int sprite_def[])
 { union REGS inregs,outregs;
   struct SREGS segregs;
   inregs.x.ax=0x12;
   inregs.h.bh=width;
   inregs.h.bl=h;
   inregs.h.cl=v;
   inregs.h.ch=scanlines;
   segregs.es=FP_SEG(sprite_def);
   inregs.x.dx=FP_OFF(sprite_def);
   int86x(MOUSE_INT,&inregs,&outregs,&segregs);
 }

void mouse_speed(int speed)
 { union REGS inregs,outregs;
   inregs.x.ax=0x13;
   inregs.x.dx=speed;
   int86(MOUSE_INT,&inregs,&outregs);
 }