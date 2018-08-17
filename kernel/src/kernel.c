#include "../include/stdio.h"
#include "../include/registers.h"

void initialize(enum vga_color letter_color, enum vga_color screen_color){
    size_t i, j;
    terminalRow = 0;
    terminalColumn = 0;
    terminalColor = vga_entry_color(letter_color, screen_color);
    terminalBuffer = (uint16_t*) 0xB8000;

    for(i = 0; i < VGA_HEIGHT; i++)
        for(j = 0; j < VGA_WIDTH; j++){
            size_t index = i * VGA_WIDTH + j;
            terminalBuffer[index] = vga_entry(' ', terminalColor);
        }

}

void printRegisters(){
	printf("cs = %d\nds = %d\nss = %d\n", (int) getcs(), (int) getds(), (int) getss());
}

void printMessage(){
    printf("OSiX kernel initialized successfully!\n");
}

void kernel_main(){
    initialize(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    printRegisters();
    printMessage();
}
