// pci.c

#include "drivers/pci/pci.h"
#include "drivers/pci/io.h"

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA 0xCFC

// Construct PCI address format
uint32_t pci_get_address(uint32_t bus, uint32_t device, uint32_t function, uint32_t offset) {
    return (1 << 31) | (bus << 16) | (device << 11) | (function << 8) | (offset & 0xFC);
}

uint32_t pci_read_field(uint32_t bus, uint32_t device, uint32_t function, uint32_t offset, uint32_t size) {
    uint32_t address = pci_get_address(bus, device, function, offset);
    outportl(PCI_CONFIG_ADDRESS, address);

    uint32_t data = inportl(PCI_CONFIG_DATA);
    if (size == 1) {
        return (data >> ((offset & 3) * 8)) & 0xFF;
    } else if (size == 2) {
        return (data >> ((offset & 2) * 8)) & 0xFFFF;
    } else {
        return data;
    }
}

void pci_write_field(uint32_t bus, uint32_t device, uint32_t function, uint32_t offset, uint32_t size, uint32_t value) {
    uint32_t address = pci_get_address(bus, device, function, offset);
    outportl(PCI_CONFIG_ADDRESS, address);
    outportl(PCI_CONFIG_DATA, value);
}

// Scan PCI bus and run a callback for each device
void pci_scan(pci_scan_func_t callback, void *extra) {
    for (uint32_t bus = 0; bus < 256; bus++) {
        for (uint32_t device = 0; device < 32; device++) {
            uint16_t vendor_id = pci_read_field(bus, device, 0, PCI_VENDOR_ID, 2);
            if (vendor_id == 0xFFFF) continue; // No device
            uint16_t device_id = pci_read_field(bus, device, 0, PCI_DEVICE_ID, 2);
            callback(bus, device, vendor_id, device_id, extra);
        }
    }
}
