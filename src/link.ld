SECTIONS
{
    . = 0x8000;
    __start = .;

    .text : {
        KEEP(*(.text.boot))
        *(.text)
    }

    .rodata : {
        __rodata_start = .;
        *(.rodata)
        *(.rodata.*)
        KEEP(*(.font))  /* Explicitly keep font data */
        __rodata_end = .;
    }

    .data : {
        __data_start = .;
        *(.data)
        __data_end = .;
    }

    . = ALIGN(0x1000);
    __bss_start = .;
    .bss : {
        *(.bss)
    }
    __bss_end = .;

    . = ALIGN(0x1000);
    __heap_start = .;
    __heap_size = 0x4000000;
    . = __heap_start + __heap_size;
    __heap_end = .;


    __end = .;
}
