#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "6502/controller.h"

int main () {
    intro_screen();
    main_menu();

    return 0;
}


void main_menu () {
    // official list of supported processors
    char processors[3][24] = {"ATMEL 6502 (8b, 16K)", "Intel 8086 (16b, 1MB)", "Intel 80386 (32b, 16MB)"}; // change relevant values when changes are made

    printf("\n");
    printf("Please select a menu option:\n");
    int i;
    for (i = 0; i < 3; i++) {
        printf("%d - %s\n", i, processors[i]);
    }
    printf("\n");
    
    char in = getchar();
    (in == '0' ? processor_6502() : wrong_input());
}

void intro_screen () {
    // display the intro screen
    printf("\n");
    printf("\t_____________________________\n");
    printf("\tVIS-C\n");
    printf("\tAlexander Walford 2025\n");
    printf("\t_____________________________\n");
    printf("\n");
    printf("\tPress any key to show main menu..\n");
    getchar();
}

void wrong_input () {
    printf("\n");
    printf("Incorrect input! Please try again..\n");
    printf("\n");
    main_menu();
}