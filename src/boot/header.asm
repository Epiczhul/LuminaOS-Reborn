section .multiboot_header
header_start:
	; magic number. wait, hold on! MAGIC?!?!?!? OMG!!!!
	dd 0xe85250d6 
	; architecture. WAIT!!! A BUILDING?!?!?! IN AN OS?!?!?!?
	dd 0 
	dd header_end - header_start
	; checksum, noice an Checksum!
	dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))


	dw 0
	dw 0
	dd 8
header_end: