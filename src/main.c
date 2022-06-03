#include <ncurses.h>

int cursor_x=0;
int cursor_y=0;

int main() {
	int ch;

	initscr();              // Start curses mode
	raw();                  // Disables line buffering
	keypad(stdscr, TRUE);   // We get F1, F2, etc
	noecho();               // Don't echo() on getch

	int WINDMAXX, WINDMAXY;
	getmaxyx(stdscr, WINDMAXY, WINDMAXX);
	move(WINDMAXY/2, WINDMAXX/2);
	printw("(Conway's) Game of Life");
	move(0,0);
	getch();
	clear();
    //ch = getch();           /* If raw() hadn't been called we have to press enter before it * gets to the program      */
	while ((ch = getch()) != 'q') {
		switch (ch) {
			case KEY_UP:
				cursor_x--;
				break;
			case KEY_DOWN:
				cursor_x++;
				break;
			case KEY_RIGHT:
				cursor_y++;
				break;
			case KEY_LEFT:
				cursor_y--;
				break;
			case 'x':
				printw("x");
				refresh();
				break;
		}
		move(cursor_x, cursor_y);
		refresh();
	}

	endwin();           // End curses mode

	return 0;
}
