;[ORG 0x00]					; Start address is 0x00
[BITS 16]					; Code is 16 bit

SECTION .text				; Define text section

jmp 0x07C0:START			; Insert 0x07C0 to CS register and move to

START:
	mov ax, 0x07C0			; Start address of bootloader is 0x07C0
	mov ds, ax				; Move value of AX to DS (Data Segment Reigster)
	mov ax, 0xB800			; Move 0xB800 to AX register
	mov es, ax				; Move value of AX to ES
							; ES is related to video.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	Clear Screen and color changes to green
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  
	mov si, 0				; Initialize SI register
							; (String Original Index Register)
	
.SCREENCLEARLOOP:			; Clear screen
	mov byte [ es: si ], 0	; Initialize video memory
	mov byte [ es: si + 1], 0x0A	
							; Assign character feature.
	
	add si, 2				; Move to next video memory
	
	cmp si, 80 * 25 * 2		; Total number of register is 80 * 25 * 2
	jl .SCREENCLEARLOOP		; if si is less than 80 * 25 * 2
							; jump to .SCREENCLEARLOOP
					
	mov si, 0				; Initialize SI register
	mov di, 0				; Initialize DI register

.MESSAGELOOP:				; Print message
	mov cl, byte [ si + MESSAGE1]		
							; Copy the value of MESSAGE1 + si address
							; to CL register.
							; CL register is low 1 byte of CX register
									
	cmp cl, 0 				; if charater is 0, it means end.
	je .MESSAGEEND			; if cl is 0, jump to .MESSAGEEND
	
	mov byte [ es: di ], cl	; if cl is not 0, print value of es + di address
	
	add si, 1				; Move to the next character
	add di, 2				; Move to the next address
	
	jmp .MESSAGELOOP		; Move to the next iteration

.MESSAGEEND:
	jmp $					; Infinite loop at this point

MESSAGE1: 
	db 'Dragon Slayer OS Boot Loader Start!!', 0
							; Message for print
							; last 0 means the end of string

times 510 - ( $ - $$ )	db	0x00	
							; $: adress of current line
							; $$: start address of current section
							; $ - $$: Offset from current section
							; 510 - ( $ - $$ ): from here to address 510
							; db 0x00: Define 1 byte as 0x00
							; times: repeat
							; From current to address 510, fill 0x00
									
db 0x55 					; Define 1 byte as 0x55
db 0xAA						; Define 1 byte as 0xAA
							; Address 511, 512 are 0x55, 0xAA