#ifndef PCI_H
#define PCI_H

#include <stdint.h>

#define PCI_VENDOR_ID 0x00
#define PCI_DEVICE_ID 0x02
#define PCI_BAR0 0x10

typedef void (*pci_scan_func_t)(uint32_t bus, uint32_t device, uint16_t vendor, uint16_t device_id, void *extra);

uint32_t pci_read_field(uint32_t bus, uint32_t device, uint32_t function, uint32_t offset, uint32_t size);
void pci_write_field(uint32_t bus, uint32_t device, uint32_t function, uint32_t offset, uint32_t size, uint32_t value);
void pci_scan(pci_scan_func_t callback, void *extra);

#endif // PCI_H
