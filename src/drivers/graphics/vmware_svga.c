 #include "drivers/pci/io.h"
#include "drivers/pci/pci.h"
#include "console/print.h"
#include "drivers/graphics/vmware_svga.h"
#include <stdint.h>

#define SVGA_IO_BASE (vmware_io)
#define SVGA_IO_MUL 1
#define SVGA_INDEX_PORT 0
#define SVGA_VALUE_PORT 1

#define SVGA_REG_ID 0
#define SVGA_REG_ENABLE 1
#define SVGA_REG_WIDTH 2
#define SVGA_REG_HEIGHT 3
#define SVGA_REG_BPP 7
#define SVGA_REG_FB_START 13

static uint32_t vmware_io = 0;

static void vmware_scan_pci(uint32_t bus, uint32_t device, uint16_t vendor, uint16_t device_id, void *extra) {
    if ((vendor == 0x15AD && device_id == 0x0405)) {
        uint32_t bar0 = pci_read_field(bus, device, 0, PCI_BAR0, 4);
        if (bar0 > 0) {
            *((uint8_t **)extra) = (uint8_t *)(bar0 & 0xFFFFFFF0);
        }
    }
}

static void vmware_write(int reg, int value) {
    outportl(SVGA_IO_MUL * SVGA_INDEX_PORT + SVGA_IO_BASE, reg);
    outportl(SVGA_IO_MUL * SVGA_VALUE_PORT + SVGA_IO_BASE, value);
}

static uint32_t vmware_read(int reg) {
    outportl(SVGA_IO_MUL * SVGA_INDEX_PORT + SVGA_IO_BASE, reg);
    return inportl(SVGA_IO_MUL * SVGA_VALUE_PORT + SVGA_IO_BASE);
}

void vmware_set_resolution(uint16_t w, uint16_t h) {
    vmware_write(SVGA_REG_ENABLE, 0);
    vmware_write(SVGA_REG_ID, 0);
    vmware_write(SVGA_REG_WIDTH, w);
    vmware_write(SVGA_REG_HEIGHT, h);
    vmware_write(SVGA_REG_BPP, 32);
    vmware_write(SVGA_REG_ENABLE, 1);

    uint32_t width = vmware_read(SVGA_REG_WIDTH);
    uint32_t bpp = vmware_read(SVGA_REG_BPP);
    uint32_t bytes_per_line = width * (bpp >> 3);
    uint32_t fb_size = vmware_read(15);
    printf("Resolution set to %dx%d, BPP: 32, Bytes per line: %d, Framebuffer size: %d bytes\n", w, h, bytes_per_line, fb_size);
}

void vmware_clear_screen(uint32_t color) {
    uintptr_t fb_addr = vmware_read(SVGA_REG_FB_START);
    uint32_t width = vmware_read(SVGA_REG_WIDTH);
    uint32_t height = vmware_read(SVGA_REG_HEIGHT);
    uint32_t bpp = vmware_read(SVGA_REG_BPP);
    uint32_t bytes_per_pixel = bpp / 8;
    uint32_t bytes_per_line = width * (bpp >> 3);

    uint32_t *framebuffer = (uint32_t *)fb_addr;

    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            framebuffer[y * (bytes_per_line / sizeof(uint32_t)) + x] = color;
        }
    }
}

void vmware_draw_pixel(int x, int y, uint32_t color) {
    uintptr_t fb_addr = vmware_read(SVGA_REG_FB_START);
    uint32_t width = vmware_read(SVGA_REG_WIDTH);
    uint32_t bpp = vmware_read(SVGA_REG_BPP);
    uint32_t bytes_per_pixel = bpp / 8;
    uint32_t bytes_per_line =  width * (bpp >> 3);

    if (x < 0 || x >= width || y < 0 || y >= vmware_read(SVGA_REG_HEIGHT)) {
        return;
    }
    uint32_t *framebuffer = (uint32_t *)fb_addr;

    framebuffer[y * (bytes_per_line / sizeof(uint32_t)) + x] = color;
}

void graphics_install_vmware(uint16_t w, uint16_t h) {
    pci_scan(vmware_scan_pci, &vmware_io);

    if (!vmware_io) {
        printf("VMware SVGA II device not found.\n");
        return;
    }

    printf("VMware SVGA II IO base: 0x%p\n", (void *)(uintptr_t)vmware_io);
    vmware_set_resolution(w, h);

    uintptr_t fb_addr = vmware_read(SVGA_REG_FB_START);
    printf("VMware framebuffer address: 0x%p\n", (void *)fb_addr);
}

//drawing doesnt work.