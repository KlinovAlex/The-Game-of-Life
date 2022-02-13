#include <curses.h>
#include <stdlib.h>

#define MAX_X 80
#define MIN_X 0
#define MAX_Y 25
#define MIN_Y 0

void populate(int cell[MAX_Y][MAX_X]);
void setState(int cell[MAX_Y][MAX_X]);
void render(int cell[MAX_Y][MAX_X]);
void game_start(void);
void game_settings(void);
void game_end(void);
void copy_matrix(int original[MAX_Y][MAX_X], int copy[MAX_Y][MAX_X]);
int calc_neighbours(int gen[MAX_Y][MAX_X], int y, int x);

int main() {
    initscr();              // curses start routine
    start_color();          // initialize 3 colors
    init_pair(1, COLOR_GREEN, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    noecho();               // don't show getch() characters on the screen
    curs_set(0);            // remove cursors   
    keypad(stdscr, true);
    raw();                  // don't accept any keyboard commands

    // generate matrixes
    int gen[MAX_Y][MAX_X];
    int next_gen[MAX_Y][MAX_X];

    // welcome screen
    game_start();
    game_settings();

    populate(gen);
    setState(gen);
    copy_matrix(gen, next_gen);

    // return keyboard control
    freopen("/dev/tty", "rw", stdin);

    nodelay(stdscr, true);

    int speed = 1;
    while(1) {
        refresh();  // refresh the screen every tick
        if (speed != 0) {
            nodelay(stdscr, true);
            timeout(300 / speed);
        } else {
            nodelay(stdscr, false);
        }

        // game loop
        for (int y = MIN_Y; y < MAX_Y; y++) {
            for (int x = MIN_X; x < MAX_X; x++) {
                int count = calc_neighbours(gen, y, x);
                if (gen[y][x]) {
                    if (count != 2 && count != 3) next_gen[y][x] = 0;
                }
                if (!gen[y][x]) {
                    if (count == 3)  next_gen[y][x] = 1;
                }
            }
        }
        copy_matrix(next_gen, gen);
        
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
        render(gen);
    }
    refresh();
    clear();
    nodelay(stdscr, false);

    // call end game screen
    game_end();

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
}

void populate(int cell[MAX_Y][MAX_X]) {
  for(int y = MIN_Y; y < MAX_Y; y++) {
       for(int x = MIN_X; x < MAX_X; x++) {
            cell[y][x]= 0;
        }
    }
}

void setState(int cell[MAX_Y][MAX_X]) {
   for(int y = MIN_Y; y < MAX_Y; y++) {
       for(int x = MIN_X; x < MAX_X; x++) {
          scanf("%d", &cell[y][x]);
        }
    }
}

void game_end(void) {
    attron(COLOR_PAIR(3));
    mvvline(9, MAX_X/1.19,'*',9);
    mvvline(9, MAX_X/2.8,'*',9);
    mvhline(8, 29, '*', 38);
    mvhline(18, 29,'*', 38);
    mvprintw(11, MAX_X/2.0, "%s", "THE WORLD ENDS!");
    mvprintw(12, MAX_X/2.2, "%s", "THE LIFE HAS NEVER EVOLVED.");
    mvprintw(13, MAX_X/2.5, "%s", "WE ALL DIED AS SINGULAR CELLS :C");
    mvprintw(15, MAX_X/2.2, "%s", "Press any buttom to exit");
    attroff(COLOR_PAIR(3));
    getch();
}

void render(int cell[MAX_Y][MAX_X]) {
   for(int y = MIN_Y; y < MAX_Y; y++) {
       for(int x = MIN_X; x < MAX_X; x++) {
            if (cell[y][x] == 1) {
                attron(COLOR_PAIR(1));
                mvprintw(y, x, "%d", cell[y][x]);
                attroff(COLOR_PAIR(1));
            }
            if (cell[y][x] == 0) {
                attron(COLOR_PAIR(2));
                mvprintw(y, x, "%d", cell[y][x]);
                attroff(COLOR_PAIR(2));
            }
        }
    }
}

int calc_neighbours(int gen[MAX_Y][MAX_X], int y, int x) {
    int count = 0;
    int curr_x;
    int curr_y;
    for (int i = y - 1; i < y + 2; i++) {
        for (int j = x - 1; j < x + 2; j++) {
            if (i == MAX_Y) { 
                curr_y = MIN_Y;
            } else if (i == -1) { 
                curr_y = MAX_Y - 1;
            } else curr_y = i;

            if (j == MAX_X) { 
                curr_x = MIN_X;
            } else if (j == -1) {
                curr_x = MAX_X - 1; 
            }
            else curr_x = j;
        
            count+=gen[curr_y][curr_x];
        }
    }
    count -= gen[y][x];
    return count;
}


void copy_matrix(int original[MAX_Y][MAX_X], int copy[MAX_Y][MAX_X]) {
    for (int y = MIN_Y; y < MAX_Y; y++) {
        for (int x = MIN_X; x < MAX_X; x++) {
            copy[y][x] = original[y][x];
        }
    }
}
