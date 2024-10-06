#pragma once

void vmware_set_resolution(uint16_t w, uint16_t h);
void vmware_clear_screen(uint32_t color);
void vmware_draw_pixel(int x, int y, uint32_t color);
void graphics_install_vmware(uint16_t w, uint16_t h);