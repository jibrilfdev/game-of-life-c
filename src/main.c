#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "../include/main.h"

// Defining defaults and memory space for map state
int cursorlocx=0;
int cursorlocy=0;
int seed[2000][2000];

void read_file(char file_name[],int MAXWIDTH) {
	// Set file pointer and character array to store data
	FILE* fptr;
	fptr = fopen(file_name, "r");
	char data[MAXWIDTH];

	if (fptr == NULL) {
		printf("The file is not opened.");
	} else {
		// Read each line
		while (fgets(data, MAXWIDTH, fptr)) {
			printw("%s", data);
		}
	}
}

int main() {
	int ch;

	getch();

    initscr();              /* Start curses mode        */
    raw();                  /* Line buffering disabled  */
    keypad(stdscr, TRUE);   /* We get F1, F2 etc..      */
    noecho();               /* Don't echo() while we do getch */

	int WINDMAXX, WINDMAXY;
	getmaxyx(stdscr, WINDMAXY, WINDMAXX);
	move(WINDMAXY/2-1, WINDMAXX/2-10);
	printw("(Conway's) Game of Life");
	move(0,0);
	getch();
	clear();
	read_file("default_seed", WINDMAXX);
	move(0,0);
	refresh();
	getch();
    //ch = getch();           /* If raw() hadn't been called we have to press enter before it * gets to the program      */
	while ((ch = getch()) != 'q') {
		switch (ch) {
			case KEY_UP:
				cursorlocx--;
				break;
			case KEY_DOWN:
				cursorlocx++;
				break;
			case KEY_RIGHT:
				cursorlocy++;
				break;
			case KEY_LEFT:
				cursorlocy--;
				break;
			case 'x':
				printw("X");
				//update_seed();
				refresh();
				break;
		}
		move(cursorlocx, cursorlocy);
        refresh();
	}

    endwin();           /* End curses mode        */

    return 0;
}
