#include "drivers/ps2/keyboard.h"




void ps2_init() {

    outb(PS2_COMMAND_PORT, PS2_COMMAND_DISABLE_PORT1);
    outb(PS2_COMMAND_PORT, PS2_COMMAND_DISABLE_PORT2);

    while (inb(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_FULL)
        inb(PS2_DATA_PORT);

    outb(PS2_COMMAND_PORT, PS2_COMMAND_READ_CONFIG);
    uint8_t config = inb(PS2_DATA_PORT);

    config |= 1;
    config &= ~0x10;
    outb(PS2_COMMAND_PORT, PS2_COMMAND_WRITE_CONFIG);
    outb(PS2_DATA_PORT, config);

    outb(PS2_COMMAND_PORT, PS2_COMMAND_ENABLE_PORT1);
}

uint8_t ps2_read_data() {
    while (!(inb(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_FULL))
        ;
    return inb(PS2_DATA_PORT);
}

uint16_t sct1[] = {
    0, 0x0100, 49, 50, 
    51, 52, 53, 54,
    55, 56, 57, 48,
    45, 61, 0x0200, 9,  
    113, 119, 101, 114,
    116, 121, 117, 105,
    111, 112, 91, 93,
    0x0300, 0x0400, 97, 115, 
    100, 102, 103, 104,
    106, 107, 108, 59,
    39, 96, 0x0500, 92, 
    122, 120, 99, 118,
    98, 110, 109, 44,
    46, 47, 0x0500, 42, 
    0x0600, 32, 0x0700, 0x0800, 
    0x0900, 0x0A00, 0x0B00, 0x0C00, 
    0x0D00, 0x0E00, 0x0F00, 0x1000, 
    0x1100, 0x1400, 0x1500, 55, 
    56, 57, 45, 52,
    53, 54, 43, 49,
    50, 51, 48, 46,
    0, 0, 0, 0x1200, 
    0x1300           
};
