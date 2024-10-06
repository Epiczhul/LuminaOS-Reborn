# Find all C source files in the src/ directory and subdirectories
kernel_source_files := $(shell find src/ -name *.c)
kernel_object_files := $(patsubst src/%.c, build/%.o, $(kernel_source_files))

# Find all assembly files in the src/ directory and subdirectories
x86_64_asm_source_files := $(shell find src/ -name *.asm)
x86_64_asm_object_files := $(patsubst src/%.asm, build/%.o, $(x86_64_asm_source_files))

# Combine C and Assembly object files
x86_64_object_files := $(kernel_object_files) $(x86_64_asm_object_files)

# Rule for compiling C source files
$(kernel_object_files): build/%.o : src/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I src -ffreestanding $< -o $@

# Rule for compiling Assembly source files
$(x86_64_asm_object_files): build/%.o : src/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $< -o $@

# Target for building x64-efi
.PHONY: x64-efi
x64-efi: $(x86_64_object_files)
	mkdir -p dist/x86_64 && \
	x86_64-elf-ld -n -o dist/x86_64/kernel.bin -T src/linker.ld $(x86_64_object_files) && \
	gzip -9 dist/x86_64/kernel.bin && \
	cp dist/x86_64/kernel.bin.gz iso_root/boot/kernel.bin.gz && \
	grub-mkrescue /usr/lib/grub/x86_64-efi -o dist/x86_64/kernel.iso iso_root

# Target for building x64 legacy BIOS bootable image
.PHONY: x64-legacy
build-x86_64-legacy: $(x86_64_object_files)
	mkdir -p dist/x86_64 && \
	x86_64-elf-ld -n -o dist/x86_64/kernel.bin -T src/linker.ld $(x86_64_object_files) && \
	gzip -9 dist/x86_64/kernel.bin && \
	cp dist/x86_64/kernel.bin.gz iso_root/boot/kernel.bin.gz && \
	grub-mkrescue /usr/lib/grub/i386 -o dist/x86_64/kernel.iso iso_root

# Clean target to remove build artifacts
.PHONY: clean
clean:
	@echo "Cleaning build directories..." && \
	rm -rf build/**/*.o dist/x86_64/* iso_root/boot/kernel.bin.gz
