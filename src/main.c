#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "../include/main.h"

// Defining defaults and memory space for map state
int cursor_x=0;
int cursor_y=0;
int seed[2000][2000];
int current_state[2000][2000];

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
			case 'k':
				cursor_x--;
				break;
			case 'j':
				cursor_x++;
				break;
			case 'l':
				cursor_y++;
				break;
			case 'h':
				cursor_y--;
				break;
			case 'x':
				if (seed[cursor_x][cursor_y]==1) {
					printw(" ");
				} else {
					printw("X");
				}
				//update_seed();
				seed[cursor_x][cursor_y] = seed[cursor_x][cursor_y]==1 ? 0 : 1;
				refresh();
				break;
		}
		move(cursor_x, cursor_y);
        refresh();
	}
	clear();
	refresh();
	move(0,0);
	printw("Seed state saved. Press ENTER to start the simulation.");

	draw_state(WINDMAXY, WINDMAXX);
	// get_next_state
	getch();

    endwin();           /* End curses mode        */

    return 0;
}

void read_file(char file_name[],int MAXWIDTH) {
	// Set seed array to nothing
	for (int i=0; i<2000; ++i) {
		for (int j=0; j<2000; ++j) {
			seed[i][j] = 0;
			current_state[i][j] = 0;
		}
	}
	// Set file pointer and character array to store data
	FILE* fptr;
	fptr = fopen(file_name, "r");
	char data[MAXWIDTH];

	if (fptr == NULL) {
		printf("The file is not opened.");
	} else {
		// Read each line
		int i=0;
		while (fgets(data, MAXWIDTH, fptr)) {
			printw("%s", data);
			for (int j=0; j<sizeof(data); ++j) {
				if (data[j]=='X') {
					seed[i][j]=1;
				}
				// Make sure everything else is set to 0 otherwise max value from last row gets carried over.
				if (j==sizeof(data)-1) {
					for (int k=sizeof(data); k<MAXWIDTH; ++k) {
						seed[i][k]=0;
					}
				}
			}
			i++;
		}
	}
}

void draw_state(int WINDMAXY, int WINDMAXX) {
	getch();
	move(0,0);
	for (int i=0; i<WINDMAXY; i++) {
		for (int j=0; j<WINDMAXX; j++) {
			if (seed[i][j]==1) {
				printw("X");
			} else {
				printw(" ");
			}
		}
	}
	curs_set(0);
	refresh();

}
