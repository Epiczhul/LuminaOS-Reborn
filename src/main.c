#include <stdint.h>
#include <stddef.h>

#include "console/print.h"
#include "drivers/ps2/keyboard.h"
#include "console/console.h"



void kernel_main() {
    char buffer[78] = {0}; // 80 collums - 2 for the prompt
    uint8_t length = 78;
    uint8_t pointer = 0;

    print_clear();

    writeInfo("Initializing PS2 Controller");
    writeInfo("Initializing PS2 Keyboard");
    ps2_init();
    outb(PS2_DATA_PORT, 0xF4); 
    writeOK("Started PS2 Keyboard!");
    writeOK("(PS/2) Device found: 1");
    writeInfo("Booted LuminaOS-Reborn 0.0.3 (pre-alpha)");
    writeWarn("You are using an pre-alpha build of LuminaOS which could be unstable!");
    print_newline();
    print_newline();
    
    print_newline();
    print_newline();
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("Lumina Operating System is licensed under BSD 3-Clause License\nCopyrght (c) 2024, Epiczhul\nAll rights reserved.");
    print_newline();
    print_newline();

    while(1){
        uint8_t sc = ps2_read_data();
        uint16_t key = sct1[sc];
        if(key > 127){
            handle_unprintable(key, buffer, &pointer, length);
        }
        else if(key != 0){
            handle_ascii(key, buffer, &pointer);
        }
        print_prompt();
        print_buffer(buffer, length);

        int i = 0; // sleep
        while(i < 5000){
            i++;
        }
    }
}