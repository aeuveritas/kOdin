[BITS 64]                       ; Code is 64 bits

SECTION .text                   ; Define text section

; Define external function
extern main

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Code section
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
START:
    mov ax, 0x10                ; Store data segment descriptor of
                                ; IA-32e in AX register
    mov ds, ax                  ; Set DS register
    mov es, ax                  ; Set ES register
    mov fs, ax                  ; Set FS register
    mov gs, ax                  ; Set GS register

    ; Make 1MB stack from 0x600000 to 0x6FFFFF
    mov ss, ax                  ; Set SS register
    mov rsp, 0x6FFFF8           ; Set RSP register as 0x6FFFF8
    mov rbp, 0x6FFFF8           ; Set RBP register as 0x6FFFF8

    call main                   ; Call main function in C++

    jmp $
