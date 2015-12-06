[BITS 64]                           ; Code is 64 bits

; Make function call path from C
global _kInPortByte, _kOutPortByte
global _kLoadGDTR, _kLoadTR, _kLoadIDTR

SECTION .text                       ; Define text section

; Read a byte from the port
;   PARAM: Port number
_kInPortByte:
    push rdx                        ; RDX will be use temporary in this fuction
                                    ; So, push the value of RDX to the stack

    mov rdx, rdi                    ; Store parameter 1 (= RDI) to RDX
    mov rax, 0                      ; Reset RAX
    in al, dx                       ; Read a value from an address
                                    ; which DX refers to
                                    ; And store the value to the AL
    
    pop rdx                         ; Restore RDX from the stack
    ret                             ; Return the caller
    
; Write a byte to the port
;   PARAM: Port number, data
_kOutPortByte:
    push rdx                        ; Push a value of registers which will be
    push rax                        ; used in this function
    
    mov rdx, rdi                    ; Store parameter 1 (= RDI) to RDX
    mov rax, rsi                    ; Store parameter 2 (= RSI) to RAX
    out dx, al                      ; Write a value which is stored in AL
                                    ; to an address which DX refers to
    
    pop rax                         ; Restore RDX and RAX from the stack
    pop rdx
    ret                             ; Return the caller

; Set GDT on GDTR
;   PARAM: Address of GDT data structure
_kLoadGDTR:
    lgdt [rdi]                      ; Load parameter 1 (= Address of GDT data 
                                    ; structure) and set GDTR
    ret
    
; Set TSS on TR
;   PARAM: Offset of TSS descriptor
_kLoadTR:
    ltr di                          ; Load parameter 1 (= Offset of TSS
                                    ; descriptor) ans set TR
    ret
    
; Set IDT on IDTR
;   PARAM: Address of IDT data structure
_kLoadIDTR:
    lidt [rdi]                      ; Load parameter 1 (= Address of IDT data
                                    ; structure) and set IDTR
    ret