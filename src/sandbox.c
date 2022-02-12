#include <curses.h>
#include <time.h>

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
    initscr();          // curses start routine
    start_color();      // initialize 3 colors
    init_pair(1, COLOR_CYAN, COLOR_CYAN);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    noecho();           // don't show getch() characters on the screen
    curs_set(0);        // remove cursor


    //nodelay(stdscr, true);

    // clock_t start_t = clock();
    // refresh();
    // while (clock() < start_t + 100000) {}

    // slide through upper/lower border
    //if (r1.y <= MIN_Y + 1) r1.y = MAX_Y - 2;
    //if (r1.y >= MAX_Y - 1) r1.y = MIN_Y + 2;
    //if (r2.y <= MIN_Y + 1) r2.y = MAX_Y - 2;
    //if (r2.y >= MAX_Y - 1) r2.y = MIN_Y + 2;

    // key-presses
    //int input = getch();
    //if (input == 'a') r2.y--;
    //if (input == 'z') r2.y++;
    //if (input == 'k') r1.y--;
    //if (input == 'm') r1.y++;
    //if (input == 27) break;

    //clear();
    //render grid
    //mvvline(MIN_Y, MAX_X/2, ACS_VLINE, MAX_Y);
    //mvhline(MIN_Y, MIN_X, ACS_HLINE, MAX_X);
    //mvhline(MAX_Y, MIN_X, ACS_HLINE, MAX_X);

    //clear();
    //refresh();


    endwin();
    return 0;
}
