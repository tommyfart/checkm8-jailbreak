#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

void display_ui(int selected) {
    clear();
    printw("\n");
    printw("┌──────────────────────[version: 0.0.1 beta]────────┐\n");
    printw("│welcome to checkm8!                                │\n");
    printw("│───────────────────────────────────────            │\n");
    printw("│Connect your iPhone to begin.                      │\n");
    printw("│                                                   │\n");
    printw("│made by: tommyfart (the only developer)            │\n");
    printw("│───────────────────────────────────────            │\n");
    printw("│credits to:                                        │\n");
    printw("│@checkra1n [inspired by ui]                        │\n");
    printw("│───────────────────────────────────────────────────│\n");
    printw("│ %s Start  %s Quit                                 │\n", selected == 0 ? "[>" : "[ ", selected == 1 ? "<]" : " ]");
    printw("└───────────────────────────────────────────────────┘\n");
    refresh();
}

int main() {
    int ch, selected = 0;
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    while (1) {
        display_ui(selected);
        ch = getch();
        
        if (ch == KEY_LEFT || ch == KEY_RIGHT || ch == '	') {
            selected = !selected; // Toggle selection
        } else if (ch == '
') {
            if (selected == 0) {
                printw("\starting process...\n");
                break;
            } else {
                printw("\exiting...\n");
                endwin();
                exit(0);
            }
        }
    }

    endwin();
    return 0;
}
