#include "drivers/ps2/memory_op.h"

int strcmp(char *str1, char *str2) {
    
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }

    
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

void zero_char(char* buffer, uint8_t length){
    for(int i; i<length; i++){
        buffer[i] = 0;
    }
}