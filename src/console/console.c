#include "console/print.h"
#include "console/console.h"



void writeOK(char* string) {
    print_newline();
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("[");
    print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLACK);
    print_str("  OK  ");
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("] ");
    print_str(string);
}

void writeWarn(char* string) {
    print_newline();
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("[");
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    print_str(" WARN ");
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("] ");
    print_str(string);
}

void writeInfo(char* string) {
    print_newline();
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("[");
    print_set_color(PRINT_COLOR_CYAN, PRINT_COLOR_BLACK);
    print_str(" INFO ");
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("] ");
    print_str(string);
}

void writeError(char* string) {
    print_newline();
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("[");
    print_set_color(PRINT_COLOR_RED, PRINT_COLOR_BLACK);
    print_str(" Error ");
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("] ");
    print_str(string);
}

void handle_unprintable(uint16_t key, char* buffer, uint8_t* pointer, uint8_t length){
    switch(key){
        case BACKSPACE:
            if(*pointer == 0){
                buffer[*pointer] = 0;
                set_col(17+(*pointer));
                print_char(' ');
            }
            else{
                (*pointer)--;
                buffer[*pointer] = 0;
                set_col(12+(*pointer));
                print_char(' ');
            }
            break;
        case ENTER:
            do_buffer(buffer, length, pointer);
            break;
    }
}

void handle_ascii(char key, char* buffer, uint8_t* pointer){
    if(*pointer < 78){
        buffer[*pointer] = key;
        (*pointer)++;
    }
}

void print_prompt(){
    set_col(0);
    print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLACK);
    print_str("LuminaOS");
    print_set_color(PRINT_COLOR_LIGHT_GRAY, PRINT_COLOR_BLACK);
    print_str(":");
    print_set_color(PRINT_COLOR_LIGHT_BLUE, PRINT_COLOR_BLACK);
    print_str("/");
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("$ ");
}

void print_buffer(char* buffer, uint8_t length){
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    set_col(12);
    for(int i; i<length; i++){
        if(buffer[i] == 0){
            break;
        }
        print_char(buffer[i]);
    }
}

void do_buffer(char* buffer, uint8_t length, uint8_t* pointer){
    if(strcmp(buffer, "ver") == 0 || strcmp(buffer, "version") == 0){
        print_newline();
        print_str("Version: 0.0.3 (pre-alpha)");
        zero_char(buffer, length);
        *pointer = 0;
        print_newline();
    }
    else if(strcmp(buffer, "shutdown") == 0){
        print_newline();
        zero_char(buffer, length);
        *pointer = 0;
        print_newline();
        print_clear();
        print_str("CPU Halted, you can now shutdown your PC");
        asm("hlt");
    }
    else if(strcmp(buffer, "clear") == 0){
        print_clear();
        zero_char(buffer, length);
        *pointer = 0;
    }
    else if(strcmp(buffer, "luminafetch") == 0){
        print_newline();
        print_str("----------OS----------");
        print_newline();
        print_newline();
        print_str("Name: LuminaOS-Reborn");
        print_newline();
        print_str("Version: 0.0.3 (Pre-Release)");
        print_newline();
        print_newline();
        print_str("-------Hardware-------");
        print_newline();
        print_newline();
        print_str("CPU: ");
        CpuName();
        print_newline();
        print_str("GPU: Not found (not Implemented)");
        print_newline();
        print_str("RAM: Not Implemented, didnt work well");
        print_newline();
        print_newline();
        zero_char(buffer, length);
        *pointer = 0;
        print_newline();
      
    }

    else {
        print_newline();
        print_str("command not found");
        zero_char(buffer, length);
        *pointer = 0;
        print_newline();
    }
}