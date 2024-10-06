unsigned char in_byte(unsigned short port) {
  unsigned char byte;
  asm("inb %[port_number], %[input]"
  : [input] "=a" (byte): [port_number] "Nd" (port) );
  return byte;
}

void out_byte(unsigned short port, unsigned char byte) {
  asm("outb %[output], %[port_number]"
  : : [output] "a" (byte), [port_number] "Nd" (port) );
}