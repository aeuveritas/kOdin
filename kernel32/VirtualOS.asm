[BITS 16]					; Code is 16 bit

SECTION .text				; Define the text section

jmp 0x1000:START			;Insert 0x1000 to CS register and move to

SECTORCOUNT:
	dw 0x0000				; Store current the sector number

TOTALSECTORCOUNT equ 1024	; The total number of sector for the virtual OS
							; The maximum size is 1152 sectors
							; (= 0x900000 byte)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	Code section
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
START:
	mov ax, cs				; Store CS to AX
	mov ds, ax				; Store AX to DS
	mov ax, 0xB800			; Set ES regisr as the address of video memory
	mov es, ax				

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Code for each section	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	%assign i 0				; Define variable i with the value, 0
	%rep TOTALSECTORCOUNT	; Repeats TOTASECTORCOUNT times
		%assign i i+1		; Increase variable i by 1
		
		; Calculate video memory address from the current sector number
		mov ax, 2			; Two bytes are used for one character
	
		mul word [ SECTORCOUNT ]
							; AX = AX * SECTORCOUNT
		mov si, ax			; Store AX to SI

		; Print the count number from the third line
		mov byte [ es : si + ( 160 * 2 ) ], '0' + ( i  % 10 )
		add word [ SECTORCOUNT ], 1
							; Increase the sector number

		; If the last sector is reached, run the infinite loop
		; It not, move to the next sector
		%if i == TOTALSECTORCOUNT
							; The last sector
			jmp $			; The infinite loop
		%else				; Not the last sector
			jmp ( 0x1000 + i * 0x20 ): 0x0000
							; Go to the next sector
		%endif

		times ( 512 - ( $ - $$ ) % 512 ) db 0x00
							; $: adress of current line
							; $$: start address of current section
							; $ - $$: Offset from current section
							; 513 - ( $ - $$ ): from here to address 512
							; db 0x00: Define 1 byte as 0x00
							; times: repeat
							; From current to address 510, fill 0x00
	
	%endrep					; The end of loop
