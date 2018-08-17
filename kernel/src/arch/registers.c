#include "../../include/registers.h"

uint16_t getcs(){
    uint16_t cs;

    __asm__ __volatile__ ("movl %%cs, %0" : "=r"(cs) :);
    return cs;
}


uint16_t getds(){
    uint16_t ds;

    __asm__ __volatile__ ("movl %%ds, %0" : "=r"(ds) :);
    return ds;
}


uint16_t getss(){
    uint16_t ss;

    __asm__ __volatile__ ("movl %%ss, %0" : "=r"(ss) :);
    return ss;
}
