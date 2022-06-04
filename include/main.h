#include <stdio.h>

/* read_file
*
* Reads game state from a file line by line.
* Adds game state to memory character by character
*
*/
void read_file(char file_name[],int MAXWIDTH);

/* draw_state
*
* Reads game state from memory
* Draws game state onto ncurses window
* */
void draw_state(int WINDMAXY, int WINDMAXX);
