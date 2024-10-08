#ifndef IO_H
#define IO_H

#include <stdint.h>

uint8_t inportb(uint16_t port);
void outportb(uint16_t port, uint8_t data);
uint16_t inportw(uint16_t port);
void outportw(uint16_t port, uint16_t data);
uint32_t inportl(uint16_t port);
void outportl(uint16_t port, uint32_t data);


#endif // IO_H
