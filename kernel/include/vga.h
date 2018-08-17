#if !defined (__VGA_H)
#define __VGA_H
#include "stddef.h"
#include "stddef.h"
#include "stdint.h"
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

size_t terminalRow, terminalColumn;
uint8_t terminalColor;
uint16_t *terminalBuffer;

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg);
uint16_t vga_entry(unsigned char uc, uint8_t color);
void setColor(uint8_t color);
void putcharAt(char c, uint8_t color, size_t i, size_t j);

#endif