[BITS 64]                           ; Code is 64 bits

; Make function call path from C
global _kInPortByte, _kOutPortByte
global _kLoadGDTR, _kLoadTR, _kLoadIDTR
global _kEnableInterrupt, _kDisableInterrupt, _kReadRFLAGS
global _kReadTSC

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
    
; Enable interrupt
;   PARAM: None
_kEnableInterrupt:
    sti                             ; Enable interrupt
    ret
    
; Disable interrupt
;   PARAM: None
_kDisableInterrupt:
    cli                             ; Disable interrupt
    ret
    
; Read RFLGAS and return it
;   PARAM: None
_kReadRFLAGS:
    pushfq                          ; Store value of RFLAGS to the stack
    pop rax                         ; Copy value in the stack to the RAX,
                                    ; because RAX is the return value
    ret
    
; Read TSC (Time Stamp Counter)
;   PARAM: None
_kReadTSC
    push rdx                        ; Store RDX in the stack
    
    rdtsc                           ; Read TSC and store the value in RDX:RAX
    
    shl rdx, 32                     ; Merge RDX and RAX in RAX
    or rax, rdx
    
    pop rdx                         ; Restore RDX
    ret