#include <stdio.h>
#include <stdlib.h>

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

// will likely be moved to its own header file when we've done a bit more then just assign memory addresses..
void processor_6502 () {
    printf("[ ! ] Assigning memory for ATMEL 6502..\n");

    // assign all memory addresses:
    char memory_addresses[65536][7]; // "0xFFFF" + null terminator, hence 7 not 6
    // increment from lowest memory address value to maximum
    for (int i = 0; i < 65536; i++) {
        snprintf(memory_addresses[i], 7, "0x%04X", i);
        printf("%s\n", memory_addresses[i]);
    }

    printf("[ ! ] Done assigning memory for all addresses.\n");
    getchar();
}