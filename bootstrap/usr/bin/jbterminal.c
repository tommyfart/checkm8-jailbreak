#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

char device_info[256] = "No iPhone detected. Connect your device.";

void check_device() {
    FILE *fp;
    char buffer[128];
    
    fp = popen("ideviceinfo -s | grep -E 'ProductType|ProductVersion'", "r"); // Requires libimobiledevice
    if (fp == NULL) {
        snprintf(device_info, sizeof(device_info), "Error detecting device.");
        return;
    }
    
    char model[64] = "Unknown Model";
    char ios_version[64] = "Unknown iOS";
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strstr(buffer, "ProductType")) {
            sscanf(buffer, "ProductType: %s", model);
        } else if (strstr(buffer, "ProductVersion")) {
            sscanf(buffer, "ProductVersion: %s", ios_version);
        }
    }
    pclose(fp);
    snprintf(device_info, sizeof(device_info), "iPhone (%s) detected! (iOS %s)", model, ios_version);
}

void display_ui(int selected) {
    clear();
    printw("\n");
    printw("┌──────────────────────[version: 0.0.1 beta]────────┐\n");
    printw("│welcome to checkm8!                                │\n");
    printw("│───────────────────────────────────────            │\n");
    printw("│%s\n", device_info);
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
    
    check_device();
    
    while (1) {
        display_ui(selected);
        ch = getch();
        
        if (ch == KEY_LEFT || ch == KEY_RIGHT || ch == '\t') {
            selected = !selected; // Toggle selection
        } else if (ch == '\n') {
            if (selected == 0) {
                printw("\nstarting process...\n");
                break;
            } else {
                printw("\nexiting...\n");
                endwin();
        }
    }
    
    endwin();
    return 0;
}
