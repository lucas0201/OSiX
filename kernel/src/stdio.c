#include "../include/stdio.h"

void putchar(char c){
    if(c == '\n'){
        terminalColumn = 0;
        if(++terminalRow == VGA_HEIGHT)
            terminalRow = 0;
    } else {
        putcharAt(c, terminalColor, terminalColumn, terminalRow);
        if(++terminalColumn == VGA_WIDTH){
            terminalColumn = 0;
            if(++terminalRow == VGA_HEIGHT)
                terminalRow = 0;
        }
    }
}

void puts(char *input){
    size_t i;
    for(i = 0; i < strlen(input); i++)
        putchar(input[i]);
    putchar('\n');
}

int print_d(int i) {
    int aux, b, n, div, first;
    div = 10000;
    first = 0;
    n = 0;
    b = i;
    while(div > 0){
        aux = b/div;
        switch(aux) {
            case 0:
                if(first != 0)
                    putchar('0');
                break;
            case 1:
                putchar('1');
                first++;
                break;
            case 2:
                putchar('2');
                first++;
                break;
            case 3:
                putchar('3');
                first++;
                break;
            case 4:
                putchar('4');
                first++;
                break;
            case 5:
                putchar('5');
                first++;
                break;
            case 6:
                putchar('6');
                first++;
                break;
            case 7:
                putchar('7');
                first++;
                break;
            case 8:
                putchar('8');
                first++;
                break;
            case 9:
                putchar('9');
                first++;
                break;
            default:
                putchar('0');
        }
    b = b - (aux * div);
    div = div/10;
    n++;
    }
    return i;
}

int print_x(int i) {
    int b, aux, n;

    puts("0x");
    n = 2;
    for(b = 8*sizeof(int) - 4; b >= 4 && !((i >> b) & 0xF); b -= 4);
    while(b >= 0) {
        aux = (i >> b) & 0xF;
        switch(aux) {
            case 10: putchar('A');
                 break;
            case 11: putchar('B');
                 break;
            case 12: putchar('C');
                 break;
            case 13: putchar('D');
                 break;
            case 14: putchar('E');
                 break;
            case 15: putchar('F');
                 break;
            default: putchar(aux + '0');
        }
        n++;
        b -= 4;
    }
    return n;
}

int print_b(int i) {
    int b;

    for(b = 8*sizeof(int) - 1; b >= 0; b--) {
        if((1 << b) & i)
            putchar('1');
        else
            putchar('0');
    }
    return 8*sizeof(int);
}

int printf(const char * format, ...){
    int i, n;
    va_list args;

    va_start(args, format);

    n = 0;
    i = 0;
    while(format[i]){
        if(format[i] == '%'){
            i++;
            switch(format[i]){
                case 'c':
                    putchar((unsigned char)va_arg(args, int));
                    n++;
                    break;
                case 's':
                    n += printf(va_arg(args, char *));
                    break;
                case 'd':
                    n += print_d(va_arg(args, int));
                    break;
                case 'x':
                    n += print_x(va_arg(args, int));
                    break;
                case 'b':
                    n += print_b(va_arg(args, int));
                    break;
                default:
                    putchar(format[i]);
                    n++;
            }
        } else {
            putchar(format[i]);
            n++;
        }
    i++;
    }
    va_end(args);
    return n;
}
