#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

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

void display_recovery_screen() {
    clear();
    printw("┌──────────────────────[version: 0.0.1 beta]────────┐\n");
    printw("│The iPhone will be put into Recovery Mode         │\n");
    printw("│to boot into DFU mode. This prevents system       │\n");
    printw("│corruption. Press [ Start ] to continue.         │\n");
    printw("└───────────────────────────────────────────────────┘\n");
    refresh();
    getch();
}

void boot_into_recovery() {
    const char spinner[] = "|/-\\";
    int i = 0;
    clear();
    printw("Booting into recovery mode ");
    while (i < 10) { // development
        printw("%c\b", spinner[i % 4]);
        refresh();
        usleep(250000);
        i++;
    }
    printw("\nDevice in Recovery Mode. Follow DFU instructions.\n");
    refresh();
    sleep(2);
}

void dfu_mode_instructions() {
    clear();
    printw("┌──────────────────────[version: 0.0.1 beta]────────┐\n");
    printw("│DFU Mode Instructions:                             │\n");
    printw("│1. Hold Power + Home/Volume Down for 10s.        │\n");
    printw("│2. Release Power, keep holding Home/Vol Down.    │\n");
    printw("│3. Wait until DFU mode detected.                  │\n");
    printw("└───────────────────────────────────────────────────┘\n");
    refresh();
    sleep(2);
}

void start_jailbreak() {
    clear();
    printw("┌──────────────────────[version: 0.0.1 beta]────────┐\n");
    printw("│checkm8                                            │\n");
    printw("│                                                  │\n");
    printw("│    Exploiting...                                │\n");
    printw("│   ┌────────────────────────────────────────┐    │\n");
    for (int i = 0; i < 30; i++) {
        printw("│   │ ");
        for (int j = 0; j < i; j++) printw("█");
        for (int j = i; j < 30; j++) printw(" ");
        printw(" │    │\n");
        refresh();
        usleep(200000);
    }
    printw("│   └────────────────────────────────────────┘    │\n");
    printw("│ Installing Sileo...                             │\n");
    refresh();
    sleep(4);
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
                display_recovery_screen();
                boot_into_recovery();
                dfu_mode_instructions();
                start_jailbreak();
                printw("Your device has been jailbroken! Exiting in 5 seconds...\n");
                refresh();
                sleep(5);
                break;
            } else {
                printw("\nExiting...\n");
                endwin();
                exit(0);
            }
        }
    }
    
    endwin();
    return 0;
}

