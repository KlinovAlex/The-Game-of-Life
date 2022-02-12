#include <curses.h>

#define MAX_X 80
#define MIN_X 0
#define MAX_Y 25
#define MIN_Y 0

typedef struct {
    int x;
    int y;
    bool alive;
} cell;

int main() {
    initscr();              // curses start routine
    start_color();          // initialize 3 colors
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    noecho();               // don't show getch() characters on the screen
    curs_set(0);            // remove cursor
    keypad(stdscr, true);   // turn off keypad from interrupting the game
    raw();                  // don't accept any keyboard commands

    // welcome screen


    nodelay(stdscr, true);
    int speed = 2;
    while(1) {
        refresh();  // refresh the screen every tick
        if (speed != 0) timeout(5000 * speed);

        // key-presses control
        int input = getch();
        if (input == '0') speed = 0;
        if (input == '1') speed = 1;
        if (input == '2') speed = 2;
        if (input == '3') speed = 3;
        if (input == '4') speed = 4;
        if (input == '5') speed = 5;
        if (input == '6') speed = 6;
        if (input == '7') speed = 7;
        if (input == '8') speed = 8;
        if (input == '9') speed = 9;
        if (input == 27) break;
        clear();

        //render grid
    }

    clear();
    nodelay(stdscr, false);
    // call end game screen

    endwin();
    return 0;
}
