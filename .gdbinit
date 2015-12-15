set arch i386:x86-64:intel
symbol-file ./OUT/kernel32/Kernel32.elf
add-symbol-file ./OUT/kernel64/Kernel64.elf 0x200000

