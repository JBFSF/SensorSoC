ENTRY(_start)

MEMORY {
  RAM (rwx) : ORIGIN = 0x00000000, LENGTH = 0x00001000
}

SECTIONS {
  PROVIDE(__global_pointer$ = ORIGIN(RAM) + 0x800);

  .text : {
    *(.text*)
    *(.rodata*)
  } > RAM

  .data : {
    *(.data*)
  } > RAM

  .bss : {
    *(.bss*)
    *(COMMON)
  } > RAM

  _stack_top = ORIGIN(RAM) + LENGTH(RAM);
}
