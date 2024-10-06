#include "drivers/memory/common.h"
#include "drivers/vga/vga_text.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

volatile uint16_t * VIDEO_RAM = (uint16_t *)0xB8000;

// deal with colors later...
typedef enum default_vga_colors {
  VGA_COLOR_BLACK = 0x0,
	VGA_COLOR_BLUE = 0x1,
	VGA_COLOR_GREEN = 0x2,
	VGA_COLOR_CYAN = 0x3,
	VGA_COLOR_RED = 0x4,
	VGA_COLOR_MAGENTA = 0x5,
	VGA_COLOR_BROWN = 0x6,
	VGA_COLOR_LIGHT_GREY = 0x7,
	VGA_COLOR_DARK_GREY = 0x8,
	VGA_COLOR_LIGHT_BLUE = 0x9,
	VGA_COLOR_LIGHT_GREEN = 0xA,
	VGA_COLOR_LIGHT_CYAN = 0xB,
	VGA_COLOR_LIGHT_RED = 0xC,
	VGA_COLOR_LIGHT_MAGENTA = 0xD,
	VGA_COLOR_LIGHT_BROWN = 0xE,
	VGA_COLOR_WHITE = 0xF,
} default_vga_colors;

static volatile struct text_mode {
  int col;
  int row;
  uint16_t buffer[VGA_HEIGHT][VGA_WIDTH];
} text_mode;

void scroll() {
  for(int i = 1; i < VGA_HEIGHT; i++) {
    for(int j = 0; j < VGA_WIDTH; j++) {
      text_mode.buffer[i-1][j] = text_mode.buffer[i][j];
    }
  }

  for(int j = 0; j < VGA_WIDTH; j++) {
    text_mode.buffer[VGA_HEIGHT - 1][j] = 0x0020;
  }

  text_mode.row = VGA_HEIGHT - 1;
  text_mode.col = 0;
}

void __actually_write() {
  for(int i = 0; i < VGA_HEIGHT; i++) {
    for(int j = 0; j < VGA_WIDTH; j++) {
      VIDEO_RAM[i * VGA_WIDTH + j] = text_mode.buffer[i][j];
    }
  }
}

void __dump_buffer() {
  k_printf("\nVIDEO BUFFER:\n");
  for(int i = 0; i < VGA_HEIGHT; i++) {
    for(int j = 0; j < VGA_WIDTH; j++) {
      k_printf("%x\t", text_mode.buffer[i][j]);
    }
    k_printf("\n");
  }
}

void __dump_video_ram() {
  k_printf("\nVIDEO MEMORY:\n");
  for(int i = 0; i < VGA_HEIGHT; i++) {
    for(int j = 0; j < VGA_WIDTH; j++) {
      k_printf("%x ", VIDEO_RAM[i * VGA_HEIGHT + j]);
    }
    k_printf("\n");
  }
}

void text_mode_write(unsigned char * msg) {
  while(*msg != '\0') {
    switch(*msg) {
      case '\a': {
        // not implemented
      }
      break;
      case '\b': {
        text_mode.buffer[text_mode.row][text_mode.col--] = 0x0020;
      }
      break;
      case '\r':
      case '\n': {
        text_mode.row++;
        text_mode.col = 0;
      }
      break;
      case '\f': {
        // not implemented
      }
      break;
      case '\e': {
        // not implemented
      }
      break;
      default: {
        if (text_mode.col >= VGA_WIDTH) {
          text_mode.row++;
          text_mode.col = 0;
        }

        if (text_mode.row >= VGA_HEIGHT) {
          scroll();
        }

        text_mode.buffer[text_mode.row][text_mode.col++] = *msg | 0x0F << 8;
      }
    }
    msg++;
  }
  __actually_write();
}

void text_mode_clear() {
  for(int i = 0 ;i < VGA_HEIGHT;i++) {
    for(int j = 0; j < VGA_WIDTH; j++) {
      VIDEO_RAM[(i * VGA_HEIGHT) + j] = 0x0020;
      text_mode.buffer[i][j] = 0x0020;
    }
  }
}

void text_mode_init() {
  text_mode.col = 0;
  text_mode.row = 0;
  text_mode_clear();
}