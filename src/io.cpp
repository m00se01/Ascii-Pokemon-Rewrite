#include <stdlib.h>
#include <ncurses.h>
#include "main.h"


// Initialization for ncurses and colors
void io_init(void){
    initscr();
    raw();
    noecho();
    curs_set(0);
    keypad(stdscr, true);

    if(has_colors()){
        start_color();
        init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
        init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
        init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
        init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
        init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
        init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
    }else{
        mvprintw(23,1,"Colors Not Supported");
    }
  
}

// Terminate ncurses scr
void io_terminate(void){
    endwin();
}

// Display curr_map
void io_display(void){

    clear();

    int x,y;
    for(y= 0; y <MAP_Y; y++){
        for(x= 0; x <MAP_X; x++){
            switch (world.curr_map->map[y][x])
            {
                case ter_boulder:
                case ter_mountain:
                    attron(COLOR_PAIR(COLOR_MAGENTA));
                    mvaddch(y + 1, x, '%');
                    attroff(COLOR_PAIR(COLOR_MAGENTA));
                break;
                case ter_tree:
                case ter_forest:
                    attron(COLOR_PAIR(COLOR_GREEN));
                    mvaddch(y + 1, x, '^');
                    attroff(COLOR_PAIR(COLOR_GREEN));
                break;
                case ter_path:
                case ter_exit:
                    attron(COLOR_PAIR(COLOR_YELLOW));
                    mvaddch(y + 1, x, '#');
                    attroff(COLOR_PAIR(COLOR_YELLOW));
                break;
                case ter_mart:
                    attron(COLOR_PAIR(COLOR_BLUE));
                    mvaddch(y + 1, x, 'M');
                    attroff(COLOR_PAIR(COLOR_BLUE));
                break;
                case ter_center:
                    attron(COLOR_PAIR(COLOR_RED));
                    mvaddch(y + 1, x, 'C');
                    attroff(COLOR_PAIR(COLOR_RED));
                break;
                case ter_grass:
                    attron(COLOR_PAIR(COLOR_GREEN));
                    mvaddch(y + 1, x, ':');
                    attroff(COLOR_PAIR(COLOR_GREEN));
                break;
                case ter_clearing:
                    attron(COLOR_PAIR(COLOR_GREEN));
                    mvaddch(y + 1, x, '.');
                    attroff(COLOR_PAIR(COLOR_GREEN));
                break;
            default:
                attron(COLOR_PAIR(COLOR_CYAN));
                mvaddch(y+1, x, '0');
                attroff(COLOR_PAIR(COLOR_CYAN));
                break;
            }
        }
    }

    mvprintw(23,1,"TESTING");

    refresh();


}

