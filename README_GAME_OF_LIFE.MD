---

**Rules :**

- Any live cell with two or three live neighbours survives.
- Any dead cell with three live neighbours becomes a live cell.
- All other live cells die in the next generation. Similarly, all other dead cells stay dead.

[https://en.wikipedia.org/wiki/Conway's_Game_of_Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

---

 (1) Main module

- print a welcome screen → call welcome()
- initializing an entity in every cell of the grid → call populate()
- get initial state (1...5) → call setState()
- game loop while(1) (quit on ESC & 1...9 change speed) - **tarticar & render() vidamoqo**
- print the end screen → call gameover()

---

### void game_start(void) -sapphire

- Welcome screen to the player and a game introduction [mvprintv()](https://www.opennet.ru/man.shtml?topic=mvprintw&category=3&russian=4) [getch()](https://linux.die.net/man/3/getch)
    
    ```c
    
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
    ```
    

---

### void game_settings(void) -sapphire

- Welcome screen to the player and a game introduction [mvprintv()](https://www.opennet.ru/man.shtml?topic=mvprintw&category=3&russian=4) [getch()](https://linux.die.net/man/3/getch)
    
    ```c
    
    void game_settings(void) {
        attron(COLOR_PAIR(3));
        mvvline(9, MAX_X/1.19,'*',13);
        mvvline(9, MAX_X/2.8,'*',13);
        mvhline(8, 29, '*', 38);
        mvhline(22, 29,'*', 38);
        mvprintw(11, MAX_X/1.85, "%s", "SETTINGS:");
        mvprintw(14, MAX_X/2.4, "%s", "0 - enter in step by step mode");
        mvprintw(16, MAX_X/2.5, "%s", "1-9 - to change flow of the time");
        mvprintw(18, MAX_X/2.25, "%s", "ESC - to end \"Game of life\"");
        attroff(COLOR_PAIR(3));
        getch();
        clear();
    }
    ```
    

---

### void populate(int **cell) vidamoqo

- Set X and Y coordinates to each cell (80x25 cells)
    
    ```c
    void populate(int **cell) {
      for(int y = 0; y < MAX_Y; y++) {
           for(int x = 0; x < MAX_X; x++) {
              cell[y][x]= 0;
            }  
        }
    }
    ```
    

---

### void setState(int**cell) vidamoqo

- Get initial state through stdin using [scanf()](https://en.cppreference.com/w/c/io/fscanf) and set to a random entity(cell)
    
    ```c
    void setInitialState(int **cell) {
       for(int y = 0; y < MAX_Y; y++) {
           for(int x = 0; x < MAX_X; x++) {
              scanf("%d", &cell[y][x]);
            }  
        }
    }
    ```
    

---

### void game_end(void) sapphire

- Simple render of a end of the game screen [mvprintv()](https://www.opennet.ru/man.shtml?topic=mvprintw&category=3&russian=4) [getch()](https://linux.die.net/man/3/getch)
    
    ```c
    
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
    ```
    

---

### void render(int **cell) - vidamoqo

- Render a cell on the board [mvprintv()](https://www.opennet.ru/man.shtml?topic=mvprintw&category=3&russian=4)
    
    ```c
    void render(int **cell) {
       for(int y = MIN_Y; y < MAX_Y; y++) {
           for(int x = MIN_X; x < MAX_X; x++) {
              mvprintw(y, x, "%d",cell[y][x]);
            }
        }
    }
    ```
    

---

### int main() for render(int **cell) - vidamoqo

- Initialize dynamic memory and free it
    
    ---
    
    ```c
    int main() {
        initscr();          // curses start routine
        start_color();      // initialize 3 colors
        init_pair(1, COLOR_CYAN, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
        noecho();           // don't show getch() characters on the screen
        curs_set(0);        // remove cursor
        int **cell = malloc((MAX_Y + 2) * sizeof(int*));
        for (int i = 0; i < MAX_Y; i++) {
            cell[i] = malloc((MAX_X + 2) * sizeof(int));
        }
        populate(cell);
    		
        render(cell);
        getch();
        for (int i = 0; i < MAX_Y; i++) {
            free(cell[i]);
        }
        free(cell);
        endwin();
        return 0;
    }
    void populate(int **cell) {
      for(int y = 0; y < MAX_Y; y++) {
           for(int x = 0; x < MAX_X; x++) {
              cell[y][x]= 0;
            }
        }
    }
    void setInitialState(int **cell) {
       for(int y = 0; y < MAX_Y; y++) {
           for(int x = 0; x < MAX_X; x++) {
              scanf("%d", &cell[y][x]);
            }
        }
    }
    void render(int **cell) {
       for(int y = 0; y < MAX_Y; y++) {
           for(int x = 0; x < MAX_X; x++) {
              mvprintw(y, x, "%d ",cell[y][x]);
            }
        }
    }
    ```
    

### void createState(int **cell) - sapphire

- Render a cell on the board [mvprintv()](https://www.opennet.ru/man.shtml?topic=mvprintw&category=3&russian=4)
    
    ```c
    for(int y = MIN_Y; y < MAX_Y; y++) {
           for(int x = MIN_X; x < MAX_X; x++) {
    					if (x % 2 == 0) cell[y][x] = 1;
              printf("%d ",cell[y][x]);
            }
        }
    ```
