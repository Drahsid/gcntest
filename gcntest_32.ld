OUTPUT_ARCH(mips)
EXTERN(entrypoint)
ENTRY(entrypoint)

SECTIONS {
    __rom_offset = 0;

    .boot 0xA4000000 : AT(__rom_offset) {
        KEEP(build/src/asm/header.s.o(.data));
        KEEP(build/boot.6102.o);
    }
    __rom_offset += SIZEOF(.boot);

    __code_start = ADDR(.code);
    __code_start_rom = __rom_offset;
    .code 0x80000400 : AT(__rom_offset) ALIGN(64) SUBALIGN(64) {
        KEEP(build/src/asm/entrypoint.s.o);
        lib/rspboot_o32.o(.text);
        lib/gspF3DEX2.fifo_o32.o(.text);
        *(.text);
        *(.text.*);

        lib/rspboot_o32.o(.rodata);
        lib/gspF3DEX2.fifo_o32.o(.rodata);
        *(.rodata);
        *(.rodata.*);

        lib/rspboot_o32.o(.data);
        lib/gspF3DEX2.fifo_o32.o(.data);
        *(.data);
        *(.data.*);
    }
    __code_end  = ADDR(.code) + SIZEOF(.code);
    __code_size = SIZEOF(.code);
    __rom_offset += SIZEOF(.code);

    __bss_start = ADDR(.bss);
    .bss (NOLOAD) : ALIGN(64) SUBALIGN(64) {
        lib/rspboot_o32.o(.bss);
        lib/gspF3DEX2.fifo_o32.o(.bss);

        *(COMMON);
        *(.scommon);
        *(.sdata);
        *(.sdata.*);
        *(.bss);
    }
    __bss_end = ADDR(.bss) + SIZEOF(.bss);
    __bss_size = SIZEOF(.bss);

    __stack_start = ADDR(.stack);
    .stack (NOLOAD) : ALIGN(16) SUBALIGN(32) {
        *(.stack);
    }
    __stack_end = ADDR(.stack) + SIZEOF(.stack);
    __stack_size = SIZEOF(.stack);

    __framebuffer_start = ADDR(.framebuffer);
    .framebuffer 0x80100000 (NOLOAD) : ALIGN(64) SUBALIGN(0x00100000) {
        *(.framebuffer.*);
    }
    __framebuffer_end = ADDR(.framebuffer) + SIZEOF(.framebuffer);
    __framebuffer_size = SIZEOF(.framebuffer);

    /DISCARD/ : {
      *(*);
    }
}

