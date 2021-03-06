[BITS 16]                       ; Code is 16 bits

SECTION .text                   ; Define the text section

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Code section
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
START:
    mov ax, 0x1000              ; Start address of the protected mode is 0x1000
                                ; To set a segment register, AX is used as an
                                ; auxiliary register
    mov ds, ax                  ; Move value of AX to DS (Data Segment Reigster)
    mov es, ax                  ; Move value of AX to ES
                                ; ES is related to video

    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;   Activate A20
    ;   Try BIOS service at first
    ;   If it fals, try system control port
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ; By BIOS service
    mov ax, 0x2401              ; 0x2041 is a value for activating A20 gate
    int 0x15                    ; Call BIOS interrupt service

    jc .A20GATEERROR            ; Check BIOS service success
    jmp .A20GATESUCCESS         ; If succeed, jump to .A20GATESUCCESS

    ; If failed, try system control port
.A20GATEERROR:
    in al, 0x92                 ; Read one byte from system cotrol port(0x92)
                                ; and store it to AX register
    or al, 0x02                 ; Set the 1 bit of A20 gate as 1
    and al, 0xFE                ; Set the 0 bit as 0 to prevent system reset
    out 0x92, al                ; Restore the value
                                ; to the system control port(x092)

.A20GATESUCCESS:
    cli                         ; Disable interrupts
    lgdt [ GDTR ]               ; Load GDT by setting GDTR on the processor

    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;   Enter the protected mode
    ;   Disable paging, cache, Internal FPU, and aligning check
    ;   Enable ProtectedMode
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov eax, 0x4000003B         ; PG = 0, CD = 1, NW = 0, AM = 0, WP = 0,
                                ; NE = 1, ET = 1, TS = 1, EM = 0, MP = 1, PE = 1
    mov cr0, eax                ; Set CR0 via EAX

    ; Change kernel code segment which refer to 0x00,and Set EIP as 0x00
    ; CS segment selector : EIP
    jmp dword 0x18 : ( PROTECTEDMODE - $$ + 0x10000 )
                                ; Even though kernel code segment refers to
                                ; 0x00, there is a 0x10000 offset from the
                                ; physical address.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Enter the protected mode
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
[BITS 32]                       ; Below code is 32 bits code
PROTECTEDMODE:
    mov ax, 0x20                ; The location of data segment selector
    mov ds, ax                  ; DS segment selector
    mov es, ax                  ; ES segment selector
    mov fs, ax                  ; FS segment selector
    mov gs, ax                  ; GS segment selector

    ; Create a stack whose rage is 0x00000000 ~ 0x0000FFFF(64 KB)
    mov ss, ax                  ; Set SS
    mov esp, 0xFFFE             ; Set ESP register
    mov ebp, 0xFFFE             ; Set EBP register

    ; Print greeting message
    push (SWITCHSUCCESSMESSAGE - $$ + 0x10000)
                                ; Push the address of the message
    push 2                      ; Y point
    push 0                      ; X point
    call PRINTMESSAGE           ; Call print function
    add esp, 12                 ; Remove parameters

    jmp dword 0x18: 0x10200     ; Jump to 0x10200 at which C++ kernel is located

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Function section
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Function for printing message
;   PARAM: x point, y point, string
PRINTMESSAGE:
    push ebp                    ; Push BP (Base Pooint) register
    mov ebp, esp                ; Store SP in BP
                                ; BP will be used to calculate to find address
                                ; of the specific parameter

    push esi                    ; there will be restored at the end of
                                ; the function
    push edi                    ; The reason why BX is not pushed is
    push eax                    ; BX is currently used to read sector
    push ecx
    push edx

    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;   Calculate video address of X and Y point
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ; Calculate address of Y point
    mov eax, dword [ ebp + 12 ]
                                ; Read second parameter and set AX as it
    mov esi, 160                ; 160 ( 80 * 2 ) is the number of byte for one
                                ; line in screen
    mul esi                     ; Y point = AX = AX * SI
    mov edi, eax                ; Y point is stored in DI

    ; Calculate address of X point
    mov eax, dword [ ebp + 8 ]
                                ; Read first parameter and set AX as it
    mov esi, 2                  ; Two bytes are used for one character
    mul esi                     ; X point = AX = AX * SI
    add edi, eax                ; DI had a start address of the line
                                ; and it is added by point of X

    ; Address of string
    mov esi, dword [ ebp + 16 ]
                                ; Read third parameter

.MESSAGELOOP:                   ; Print message
    mov cl, byte [ esi ]
                                ; Copy the value of si address
                                ; to CL register.
                                ; CL register is low 1 byte of CX register

    cmp cl, 0                   ; if character is 0, it means end.
    je .MESSAGEEND              ; if cl is 0, jump to .MESSAGEEND

    mov byte [ edi + 0xB8000 ], cl
                                ; if cl is not 0, print value of EDI + 0x8000
                                ; address

    add esi, 1                  ; Move to the next character
    add edi, 2                  ; Move to the next address

    jmp .MESSAGELOOP            ; Move to the next iteration

.MESSAGEEND:
    pop edx                     ; At the end of the function,
    pop ecx                     ; the values of the registers for the caller
    pop eax                     ; should be restored
    pop edi                     ; The order is reversed of the push
    pop esi
    pop ebp                     ; Restore BP
    ret                         ; Return to the caller

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Data section
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Align below data in b 8 bytes
align 8, db 0

; To align the end of GDTR in 8 bytes
dw 0x0000

; GDTR data structure
GDTR:
    dw GDTEND - GDT - 1         ; The size of GDT
    dd ( GDT - $$ + 0x10000 )
                                ; The start address of GDT in physical memory

; GDT Table
GDT:
    ; NULL descriptor
    NULLDESCRIPTOR:
        dw 0x0000
        dw 0x0000
        db 0x00
        db 0x00
        db 0x00
        db 0x00

    ; IA-32e mode kernel code segment descriptor
    IA_32eCODEDESCRIPTOR:
        dw 0xFFFF               ; Limit [ 15 : 0 ]
        dw 0x0000               ; Base [ 15 : 0 ]
        db 0x00                 ; Base [ 23 : 16 ]
        db 0x9A                 ; P = 1, DPL = 0, Code Segment, Executed/Read
        db 0xAF                 ; G = 1, D = 0, L = 1, Limit [ 19 : 16 ]
        db 0x00                 ; Base [ 31 : 24 ]

    ; IA-32e mode kernel data segment descriptor
    IA_32eDATADESCRIPTOR:
        dw 0xFFFF               ; Limit [ 15 : 0 ]
        dw 0x0000               ; Base [ 15 : 0 ]
        db 0x00                 ; Base [ 23 : 16 ]
        db 0x92                 ; P = 1, DPL = 0, Data Segment, Read/Write
        db 0xAF                 ; G = 1, D = 0, L = 1, Limit [ 19 : 16 ]
        db 0x00                 ; Base [ 31: 24 ]

    ; Protected mode kernel code segment descriptor
    CODEDESCRIPTOR:
        dw 0xFFFF               ; Limit [ 15 : 0 ]
        dw 0x0000               ; Base [ 15 : 0 ]
        db 0x00                 ; Base [ 23 : 16 ]
        db 0x9A                 ; P = 1, DPL = 0, Code Segment, Executed/Read
        db 0xCF                 ; G = 1, D = 1, L = 0, Limit [ 19 : 16 ]
        db 0x00                 ; Base [ 31 : 24 ]

    ; Protected mode kernel data segment descriptor
    DATADESCRIPTOR:
        dw 0xFFFF               ; Limit [ 15 : 0 ]
        dw 0x0000               ; Base [ 15 : 0 ]
        db 0x00                 ; Base [ 23 : 16 ]
        db 0x92                 ; P = 1, DPL = 0, Data Segment, Read/Write
        db 0xCF                 ; G = 1, D = 1, L = 0, Limit [ 19 : 16 ]
        db 0x00                 ; Base [ 31: 24 ]
GDTEND:

; Greeting message
SWITCHSUCCESSMESSAGE: 
    db "[ PASS ]  Switch To The Protected Mode", 0

times 512 - ( $ - $$ )  db  0x00
                                ; To fill 512 byte, the rest of memory is filled
                                ; with 0
