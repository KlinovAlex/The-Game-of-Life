#include <curses.h>
#include <stdlib.h>

#define MAX_X 80
#define MIN_X 0
#define MAX_Y 25
#define MIN_Y 0
void populate(int **cell);
void setState(int **cell);
void render(int **cell);
void game_start(void);
void game_settings(void);
void game_end(void);
void draw(void);

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

    int **cell = malloc((MAX_Y + 2) * sizeof(int*));
    for (int i = 0; i < MAX_Y; i++) {
        cell[i] = malloc((MAX_X + 2) * sizeof(int));
    }
    // welcome screen
    game_start();
    game_settings();
    populate(cell);
    // setInitialState(cell); initialize a state from a file
    nodelay(stdscr, true);

    int speed = 2;
    while(1) {
        refresh();  // refresh the screen every tick
        if (speed != 0) {
            nodelay(stdscr, true);
            timeout(5000 * speed);
        } else {
            nodelay(stdscr, false);
        }

        







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
        render(cell);
    }

    clear();
    nodelay(stdscr, false);

    // call end game screen
    game_end();

    // free memory
    for (int i = 0; i < MAX_Y; i++) {
        free(cell[i]);
    }
    free(cell);

    // free memory of the curses library
    endwin();
    return 0;
}

void game_start(void){
    attron(COLOR_PAIR(3));
    mvvline(9, MAX_X/1.25,'*',7);
    mvvline(9, MAX_X/2.7,'*',7);
    mvhline(8, 30, '*', 34);
    mvhline(16, 30,'*', 34);
    mvprintw(11, MAX_X/2.4, "%s", "Welcome to the game of life!");
    mvprintw(13, MAX_X/2.3, "%s", "Press any buttom to start");
    attroff(COLOR_PAIR(3));
    getch();
    clear();
}

void game_settings(void) {
    attron(COLOR_PAIR(3));
    mvvline(9, MAX_X/1.19,'*',13);
    mvvline(9, MAX_X/2.8,'*',13);
    mvhline(8, 29, '*', 38);
    mvhline(22, 29,'*', 38);
    mvprintw(11, MAX_X/1.85, "%s", "SETTINGS:");
    mvprintw(14, MAX_X/2.4, "%s", "0 - to start step by step mode");
    mvprintw(16, MAX_X/2.5, "%s", "1-9 - to change flow of the time");
    mvprintw(18, MAX_X/2.25, "%s", "ESC - to end \"Game of life\"");
    attroff(COLOR_PAIR(3));
    getch();
}

void populate(int **cell) {
  for(int y = MIN_Y; y < MAX_Y; y++) {
       for(int x = MIN_X; x < MAX_X; x++) {
          cell[y][x]= 0;
        }
    }
}

void setInitialState(int **cell) {
   for(int y = MIN_Y; y < MAX_Y; y++) {
       for(int x = MIN_X; x < MAX_X; x++) {
          scanf("%d", &cell[y][x]);
        }
    }
}

void game_end(void){
    attron(COLOR_PAIR(3));
    mvvline(9, MAX_X/1.19,'*',9);
    mvvline(9, MAX_X/2.8,'*',9);
    mvhline(8, 29, '*', 38);
    mvhline(18, 29,'*', 38);
    mvprintw(11, MAX_X/2.0, "%s", "THE WORLD ENDS!");
    mvprintw(12, MAX_X/2.2, "%s", "THE LIFE NEVER EVOLVED.");
    mvprintw(13, MAX_X/2.5, "%s", "WE ALL DIED AS SINGULAR CELLS :C");
    mvprintw(15, MAX_X/2.2, "%s", "Press any buttom to exit");
    attroff(COLOR_PAIR(3));
    getch();
}

void render(int **cell) {
   for(int y = MIN_Y; y < MAX_Y; y++) {
       for(int x = MIN_X; x < MAX_X; x++) {
          mvprintw(y, x, "%d",cell[y][x]);
        }
    }
}
