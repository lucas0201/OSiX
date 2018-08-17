#include "../include/vga.h"

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}

void setColor(uint8_t color) {
	terminalColor = color;
}

void putcharAt(char c, uint8_t color, size_t i, size_t j){
    size_t index = j * VGA_WIDTH + i;
    terminalBuffer[index] = vga_entry(c, color);
}