[BITS 32]							; Code is 32 bits

; Make function call path from C
global _kReadCPUID, _kSwitchAndExecute64bitsKernel

SECTION .text						; Define text section

; Return CPU information
;	PARAM: DWORD dwEAX, DWORD * pdwEAX, * pdwEBX, * pdwECX, * pdwEDX
_kReadCPUID:
	push ebp						; Insert Base Point Register (EBP) to stack
	mov ebp, esp					; Set EBP as Stack Point Register(ESP)
	push eax						; EAX ~ ESI are temporary values for
	push ebx						; the next stack
	push ecx
	push edx
	push esi
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Execute CPUID instruction with EAX
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov eax, dword [ ebp + 8 ]		; Store parameter 1 (dwEAX) in EAX
	cpuid							; Execute CPUID instruction
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Execute CPUID instruction with EAX
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	; *pdwEAX
	mov esi, dword [ ebp + 12 ]		; Store parameter 2 (dwEAX) in ESI
	mov dword [ esi ], eax			; pdwEAX is a pointer
									; Store paramter 2 (EAX) in the address 
									; of pdwEAX
	
	; *pdwEBX
	mov esi, dword [ ebp + 16 ]		; Store parameter 3 (dwEBX) in ESI
	mov dword [ esi ], ebx			; pdwEBX is a pointer
									; Store paramter 3 (EAX) in the address 
									; of pdwEBX
	
	; *pdwECX
	mov esi, dword [ ebp + 20 ]		; Store parameter 4 (dwECX) in ESI
	mov dword [ esi ], ecx			; pdwECX is a pointer
									; Store paramter 4 (EAX) in the address 
									; of pdwECX
	
	; *pdwEDX
	mov esi, dword [ ebp + 24 ]		; Store parameter 5 (dwEDX) in ESI
	mov dword [ esi ], edx			; pdwEDX is a pointer
									; Store paramter 5 (EAX) in the address 
									; of pdwEDX
	
	pop esi							; After the function finished,
	pop edx							; restore ESI ~ EAX in ther reversed order
	pop ecx
	pop ebx
	pop eax
	pop ebp							; Restore Base Point Register (EBP)
	ret								; Return the caller
	
; Change to IA-32e and Execute 64 bit Kernel 
;	PARAM: None
_kSwitchAndExecute64bitsKernel:
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Set PAE bit in CR4 as 1
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov eax, cr4					; Store the value of CR4 to EAX
	or eax, 0x20					; Set PAE bit as 1
	mov cr4, eax					; Restore CR4
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Enable cache and Store PLM4T address in CR3
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov eax, 0x100000				; Store address of PML4T (= 0x100000, 1 MB)
									; in EAX
	mov cr3, eax					; Store 0x100000 (= 1 MB) in CR3
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Set IA32_EFER.LME as 1 to enable IA-32e mode
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov ecx, 0xC0000080				; Store address of IA32_EFER MSR
	rdmsr							; Read MSR
	
	or eax, 0x0100					; Set LME bit in lower 32 bits of IA32_EFER
									; as 1
	wrmsr							; Write MSR
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Enable cache and paging function
	;	by setting CR0
	;	NW (29 th bit) as 0
	;	CD (30 th bit) as 0
	;	PG (31 th bit) as 1
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov eax, cr0					; Store CR0 in EAX
	or eax, 0xE0000000				; Set NW, CD, and PG bits as 1
	xor eax, 0x60000000				; Set NW and CD bit as 0
	mov cr0, eax					; Restore CR0
	
	jmp 0x08:0x200000				; Change CS segment selector to IA-32e code 
									; segment descriptor
									; and Jump to 0x200000 (= 2 MB)

	; Not execute
	jmp $
	
	