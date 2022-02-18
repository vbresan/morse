#define MOUSE_INT 0x33

mouse_install(void);
void show_mouse(void);
void hide_mouse(void);
void get_mouse(int *x, int *y,int *button);
void set_mouse(int x,int y);
void button_press(int button_no,int *status,int *press,int *x,int *y);
void button_release(int button_no,int *status,int *release,int *x,int *y);
void mouse_horiz(int minx,int maxx);
void mouse_vert(int miny,int maxy);
void mouse_grcursor(int h,int v,int cursor_def[]);
void mouse_txcursor(int cursor_type,int attr_1,int attr_2);
void mouse_motion(int *x,int *y);
void mouse_ratio(int x_ratio,int y_ratio);
void remove_mouse(int upper_x,int upper_y,int lower_x,int lower_y);
void mouse_sprite(unsigned char width,unsigned char scanlines,char h,char v,int sprite_def[]);
void mouse_speed(int speed);