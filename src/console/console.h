#pragma once

#include <stdint.h>
#include <stddef.h>
#include "console/print.h"
#include "drivers/ps2/memory_op.h"

enum unprintable{
    ESCAPE = 0x0100,
    BACKSPACE = 0x0200,
    ENTER = 0x0300,
    CONTROL = 0x0400,
    SHIFT = 0x0500,
    ALT = 0x0600,
    CAPSLOCK = 0x0700,
    F1 = 0x0800,
    F2 = 0x0900,
    F3 = 0x0A00,
    F4 = 0x0B00,
    F5 = 0x0C00,
    F6 = 0x0D00,
    F7 = 0x0E00,
    F8 = 0x0F00,
    F9 = 0x1000,
    F10 = 0x1100,
    F11 = 0x1200,
    F12 = 0x1300,
    NUMLOCK = 0x1400,
    SCROLLLOCK = 0x1500
};


void handle_unprintable(uint16_t key, char* buffer, uint8_t* pointer, uint8_t length);

void handle_ascii(char key, char* buffer, uint8_t* pointer);

void do_buffer(char* buffer, uint8_t length, uint8_t* pointer);

void print_prompt();
void print_buffer(char* buffer, uint8_t length);

void writeOK(char* string);
void writeWarn(char* string);
void writeInfo(char* string);
void writeError(char* string);