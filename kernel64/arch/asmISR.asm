[BITS 64]                           ; Code is 64 bits

SECTION .text                       ; Define text section

; Define external function
extern _kCommonExceptionHandler, _kCommonInterruptHandler, _kKeyboardHandler

; Make function call path from C
; ISR for exceptions
global _kISRDivideError, _kISRDebug, _kISRNMI, _kISRBreakPoint, _kISROverflow
global _kISRBoundRangeExceeded, _kISRInvalidOpcode, _kISRDeviceNotAvailable
global _kISRDoubleFault, _kISRCoprocessorSegmentOverrun, _kISRInvalidTSS
global _kISRSegmentNotPresent, _kISRStackSegmentFault, _kISRGeneralProtection
global _kISRPageFault, _kISR15, _kISRFPUError, _kISRAlignmentCheck
global _kISRMachineCheck, _kISRSIMDError, _kISRETCException

; ISR for interrupt
global _kISRTimer, _kISRKeyboard, _kISRSlavePIC, _kISRSerial1, _kISRSerial2
global _kISRParallel1, _kISRParallel2, _kISRFloppy, _kISRRTC, _kISRReserved
global _kISRNotUsed1, _kISRNotUsed2, _kISRMouse, _kISRCoprocessor, _kISRHDD1
global _kISRHDD2, _kISRETCInterrupt

; Macro to store the context and change selector
%macro KSAVECONTEXT 0               ; No parameter for KSAVECONTEXT
    ; Store RBP ~ GS segment selector in the stack
    push rbp
    mov rbp, rsp
    push rax
    push rbx
    push rcx
    push rdx
    push rdi
    push rsi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    mov ax, ds                      ; Store DS segment register and ES segment
    push rax                        ; register in the stack via RAX register
    mov ax, es
    push rax
    push fs
    push gs
    
    ; Change segment selector
    mov ax, 0x10                    ; Store kernel data segment descriptor in AX
    mov ds, ax                      ; From DS segment selector to FS segment 
    mov es, ax                      ; selector, change kernel data segments
    mov gs, ax
    mov fs, ax
%endmacro                           ; Macro end

; Macro to restore the context
%macro KLOADCONTEXT 0               ; No parameter for KLOADCONTEXT
    ; Restore GS segment register ~ RBP from the stack
    pop gs
    pop fs
    pop rax
    mov es, ax                      ; Restore ES segment selector and 
    pop rax                         ; DS segment selector via RAX
    mov ds, ax
    
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsi
    pop rdi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop rbp
%endmacro                           ; Macro end

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Exception handlers
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; #0, Divide Error ISR
_kISRDivideError:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
   
    ; Insert exception number to the hander and call the handler
    mov rdi, 0
    call _kCommonExceptionHandler

    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling

; #1, Debug ISR
_kISRDebug:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor

    ; Insert exception number to the hander and call the handler
    mov rdi, 1
    call _kCommonExceptionHandler

    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
; #2, NMI ISR
_kISRNMI:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number to the hander and call the handler
    mov rdi, 2
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling   
                                    
; #3, BreakPoint ISR
_kISRBreakPoint:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number to the hander and call the handler
    mov rdi, 3
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
; #4, Overflow ISR
_kISROverflow:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number to the hander and call the handler
    mov rdi, 4
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling

                                                                        
; #5, Bound Range Exceeded ISR
_kISRBoundRangeExceeded:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number to the hander and call the handler
    mov rdi, 5
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
                                                                        
; #6, Invalid Opcode ISR
_kISRInvalidOpcode:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number to the hander and call the handler
    mov rdi, 6
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                                                        
; #7, Device Not Available ISR
_kISRDeviceNotAvailable:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number to the hander and call the handler
    mov rdi, 7
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                                                        
; #8, Double Fault ISR
_kISRDoubleFault:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number and error code to the hander and call the handler
    mov rdi, 8
    mov rsi, qword [rbp + 8]
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    add rsp, 8                      ; Remove error code from stack
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                                                        
; #9, Coprocessor Segment Overrun ISR
_kISRCoprocessorSegmentOverrun:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number to the hander and call the handler
    mov rdi, 9
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                                                        
; #10, Invalid ISR
_kISRInvalidTSS:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number and error code to the hander and call the handler
    mov rdi, 10
    mov rsi, qword [rbp + 8]
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    add rsp, 8                      ; Remove error code from stack
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                                                        
; #11, Segment Not Present ISR
_kISRSegmentNotPresent:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number and error code to the hander and call the handler
    mov rdi, 11
    mov rsi, qword [rbp + 8]
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    add rsp, 8                      ; Remove error code from stack
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                   
; #12, Stack Segment Fault ISR
_kISRStackSegmentFault:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number and error code to the hander and call the handler
    mov rdi, 12
    mov rsi, qword [rbp + 8]
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    add rsp, 8                      ; Remove error code from stack
    iretq                           ; Return the event point after interrupt
                                    ; handling

; #13, General Protection ISR
_kISRGeneralProtection:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number and error code to the hander and call the handler
    mov rdi, 13
    mov rsi, qword [rbp + 8]
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    add rsp, 8                      ; Remove error code from stack
    iretq                           ; Return the event point after interrupt
                                    ; handling

; #14, Page Fault ISR
_kISRPageFault:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number and error code to the hander and call the handler
    mov rdi, 14
    mov rsi, qword [rbp + 8]
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    add rsp, 8                      ; Remove error code from stack
    iretq                           ; Return the event point after interrupt
                                    ; handling

; #15, Reserved ISR
_kISR15:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number to the hander and call the handler
    mov rdi, 15
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling

; #16, FPU Error ISR
_kISRFPUError:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number to the hander and call the handler
    mov rdi, 16
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling

; #17, Alignment Check ISR
_kISRAlignmentCheck:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number and error code to the hander and call the handler
    mov rdi, 17
    mov rsi, qword [rbp + 8]
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    add rsp, 8                      ; Remove error code from stack
    iretq                           ; Return the event point after interrupt
                                    ; handling

; #18, Machine Check ISR
_kISRMachineCheck:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number to the hander and call the handler
    mov rdi, 18
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling

; #19, SIMD Floating Point Exception ISR
_kISRSIMDError:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number to the hander and call the handler
    mov rdi, 19
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling

; #20 ~ #31, Reserved ISR
_kISRETCException:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert exception number to the hander and call the handler
    mov rdi, 20
    call _kCommonExceptionHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Exception handlers
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; #32, Timer ISR
_kISRTimer:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert interrupt number to the hander and call the handler
    mov rdi, 32
    call _kCommonInterruptHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
; #33, Keyboard ISR
_kISRKeyboard:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert interrupt number to the hander and call the handler
    mov rdi, 33
    call _kKeyboardHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
; #34, Slave ISR
_kISRSlavePIC:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert interrupt number to the hander and call the handler
    mov rdi, 34
    call _kCommonInterruptHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
; #35, Serial Port 2 ISR
_kISRSerial2:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert interrupt number to the hander and call the handler
    mov rdi, 35
    call _kCommonInterruptHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
; #36, Serial Port 1 ISR
_kISRSerial1:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert interrupt number to the hander and call the handler
    mov rdi, 36
    call _kCommonInterruptHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
; #37, Parallel Port 2 ISR
_kISRParallel2:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert interrupt number to the hander and call the handler
    mov rdi, 37
    call _kCommonInterruptHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
; #38, Floppy Disk Controller ISR
_kISRFloppy:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert interrupt number to the hander and call the handler
    mov rdi, 38
    call _kCommonInterruptHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
; #39, Parallel Port 1 ISR
_kISRParallel1:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert interrupt number to the hander and call the handler
    mov rdi, 39
    call _kCommonInterruptHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
; #40, RTC ISR
_kISRRTC:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert interrupt number to the hander and call the handler
    mov rdi, 40
    call _kCommonInterruptHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
; #41, Reserved interrupt ISR
_kISRReserved:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert interrupt number to the hander and call the handler
    mov rdi, 41
    call _kCommonInterruptHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
; #42, Not used ISR
_kISRNotUsed1:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert interrupt number to the hander and call the handler
    mov rdi, 42
    call _kCommonInterruptHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
; #43, Not used ISR
_kISRNotUsed2:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert interrupt number to the hander and call the handler
    mov rdi, 43
    call _kCommonInterruptHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
; #44, Mouse ISR
_kISRMouse:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert interrupt number to the hander and call the handler
    mov rdi, 44
    call _kCommonInterruptHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
; #45, Coprocessor ISR
_kISRCoprocessor:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert interrupt number to the hander and call the handler
    mov rdi, 45
    call _kCommonInterruptHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
; #46, HDD 1 ISR
_kISRHDD1:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert interrupt number to the hander and call the handler
    mov rdi, 46
    call _kCommonInterruptHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
; #47, HDD 2 ISR
_kISRHDD2:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert interrupt number to the hander and call the handler
    mov rdi, 47
    call _kCommonInterruptHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    
; #48 ~ , Other ISR
_kISRETCInterrupt:
    KSAVECONTEXT                    ; Store the context and change selector to
                                    ; kernel data descriptor
                                    
    ; Insert interrupt number to the hander and call the handler
    mov rdi, 48
    call _kCommonInterruptHandler
    
    KLOADCONTEXT                    ; Restore the context
    iretq                           ; Return the event point after interrupt
                                    ; handling
                                    