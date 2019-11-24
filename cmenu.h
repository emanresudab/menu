#define MAXINPUT 100
#define BUFSIZE  100
#define LENINPUT (MAXINPUT +\
                  strlen(inputprefix) +\
                  strlen(inputsuffix) +\
                  strlen(inputprompt))
#define ATTEMPTS 150

enum handle_key_exits {SHIFTUP = 1, SHIFTDOWN, EXIT, TERM};
/* phasing these out, 0 for primary 1 for active (?) */
enum colors_ {primary, active};
enum colors {fgcolor, afgcolor, bgcolor, abgcolor, bordercolor};

struct XValues {
	Display *display;
	int screen_num;
	Window root;
	unsigned screen_width;
	unsigned screen_height;
	Visual *visual;
	Colormap colormap;
};

struct XftValues {
	XftFont *font;
	XftDraw *draw;

	XftColor primaryfg;
	XftColor activefg;
};

struct WinValues {
	Window window;
	XWindowChanges xwc;

	GC gc;
};

unsigned parse_arguments(int argc, char **argv);
int read_stdin(char ***lines);

/* X function prototypes */
int init_x(struct XValues *xv);
void terminate_x(struct XValues *xv, struct WinValues *wv);
int grab_keyboard(struct XValues *xv);
int init_window(struct XValues *xv, struct WinValues *wv);
int parse_and_allocate_xcolor(struct XValues *xv, char *name, XColor *color);

/* Xft function prototypes */
int init_xft(struct XValues *xv, struct WinValues *wv,
             struct XftValues *xftv);
void terminate_xft(struct XValues *xv, struct XftValues *xftv);

/* cmenu function prototypes */
void menu_run(struct XValues *xv, struct WinValues *wv,
              struct XftValues *xftv, char *items[], int count);
int handle_key(struct XValues *xv, XKeyEvent xkey, char *inputline);
void draw_menu(struct XValues *xv, struct WinValues *wv,
               struct XftValues *xftv, char *items[], int count, int shift);
int move_and_resize(struct XValues *xv, struct WinValues *wv,
                    struct XftValues *xftv, char *items[], int count);
void draw_items(struct XftValues *xftv, char *items[], int count);
void draw_string(struct XValues *xv, struct WinValues *wv,
                   struct XftValues *xftv, char *line, int index, short swap);

/* utility functions */
int filter_input(char **source, char **out, char *filter);
void get_pointer(struct XValues *xv, int *x, int *y);
void rotate_array(char **array, int count, int dir);
