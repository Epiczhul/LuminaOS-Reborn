#pragma once

#include <stdint.h>
#include <stddef.h>


#define PS2_DATA_PORT   0x60    
#define PS2_STATUS_PORT 0x64    
#define PS2_COMMAND_PORT 0x64   

#define PS2_STATUS_OUTPUT_FULL 0x01
#define PS2_STATUS_INPUT_FULL  0x02

#define PS2_COMMAND_READ_CONFIG 0x20
#define PS2_COMMAND_WRITE_CONFIG 0x60
#define PS2_COMMAND_ENABLE_PORT1 0xAE
#define PS2_COMMAND_DISABLE_PORT1 0xAD
#define PS2_COMMAND_ENABLE_PORT2 0xA8
#define PS2_COMMAND_DISABLE_PORT2 0xA7
#define PS2_COMMAND_READ_OUTPUT 0xD0
#define PS2_COMMAND_WRITE_OUTPUT 0xD1


void ps2_init();

uint8_t ps2_read_data();

static inline uint8_t inb(uint16_t port) {
    uint8_t data;
    asm volatile ("inb %1, %0" : "=a" (data) : "Nd" (port));
    return data;
}

static inline void outb(uint16_t port, uint8_t data) {
    asm volatile ("outb %0, %1" : : "a" (data), "Nd" (port));
}

extern uint16_t sct1[];
