;[ORG 0x00]						; Start address is 0x00
[BITS 16]						; Code is 16 bits

SECTION .text					; Define the text section

jmp 0x07C0:START				; Insert 0x07C0 to CS register and move to

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	kOdin OS Configurations
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
TOTALSECTORCOUNT:	
	dw 0x02						; The size of kOdin OS excepting for
								; the bootloader
								; The maximum size is 1152 sectors 
								; (= 0x900000byte)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	Code section
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
START:
	mov ax, 0x07C0				; Start address of the bootloader is 0x07C0
								; To set a segment register, AX is used as an 
								; auxiliary register.
	mov ds, ax					; Move value of AX to DS (Data Segment Reigster)
	mov ax, 0xB800				; Move 0xB800 to AX register
	mov es, ax					; Move value of AX to ES
								; ES is related to video.
							
	; Create the stack whose range is 0x0000:0000 ~ 0x0000:FFFF(64KB)
	mov ax, 0x0000				; Start address of the stack is 0x0000
	mov ss, ax					; Move values of AX to SS (Stack Segment Register)
	mov sp, 0xFFFE				; Set address of SP register as 0xFFFE
	mov bp, 0xFFFE				; set address of BP register as 0xFFFE

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Clear screen and color changes to green
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov si, 0					; Initialize SI register
								; (String Original Index Register)
	
.SCREENCLEARLOOP:				; Clear screen
	mov byte [ es: si ], 0		; Initialize video memory
	mov byte [ es: si + 1], 0x0A	
								; Assign character feature.
	
	add si, 2					; Move to next video memory
	
	cmp si, 80 * 25 * 2			; Total number of register is 80 * 25 * 2
	jl .SCREENCLEARLOOP			; if si is less than 80 * 25 * 2
								; jump to .SCREENCLEARLOOP
							
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Print start message at top of screen
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	push MESSAGE1				; Push the address of the message in the stack
	push 0						; Push the point of Y
	push 0						; Push the point of X
	call PRINTMESSAGE			; Call the function PRINTMESSAGE
	add sp, 6					; Remove parameters
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Print message to let user know loading is start
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	push IMAGELOADINGMESSAGE
								; Push the address of the message in the stack
	push 1						; Push the point of Y
	push 0						; Push the point of X
	call PRINTMESSAGE			; Call the function PRINTMESSAGE
	add sp, 6					; Remove parameters
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Loading OS image from disk
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Before loading, reset
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
RESETDISK:						; The start point to reset disk
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Call BIOS Reset Function
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	; Service number = 0, Dirve number = 0 (floppy disk)
	mov ax, 0
	mov dl, 0
	int 0x13
	; If error occurrs, jump to service routine for error
	jc HANDLEDISKERROR
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Read sector from disk
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	; Target address in memory is 0x10000, and it is set in ES and BX
	mov si, 0x1000				; To set segment register, SI is used
	mov es, si					; Set ES register
	mov bx, 0x0000				; BX is used as an offest,
								; so, 0x1000:0000 (= 0x10000) is set now.
	
	mov di, word [ TOTALSECTORCOUNT ]
								; Set DI register as the number of sector
								; to be copied
							
READDATA:
	; Check the copy is done
	cmp di, 0					; Compare with the the number of sector to be copied
								; and 0
	je READEND					; if they are the same, reading is done
	sub di, 0x1					; if not, decrease di by 1
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Call BIOS Read Function
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov ah, 0x02				; Service number 2 (Read sector)
	mov al, 0x1					; Set how many sectors will be read in this time
								; For now, only one sector
	mov ch, byte [ TRACKNUMBER ]
								; Set the track number to be read
	mov cl, byte [ SECTORNUMBER ]
								; Set the sector number to be read
	mov dh, byte [ HEADNUMBER ]
								; Set the head number to be read
	mov dl, 0x00				; Set the driver number (0 = Floppy disk)
	int 0x13					; Execute the interrpt service
	jc HANDLEDISKERROR			; If error occurrs, 
								; jump to service routine for error
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Calculate the addresses of track, head, sector
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	add si, 0x0020 				; By the BIOS Read Function, we read 512 (0x200) 
								; byte. 
	mov es, si					; Increase the segment register by 0x0020
								; to set the next target address
	
	; After reading one sector, increasing the sector number is necessary
	; If the increased sector number is 19, go to increase the head number
	; If not, go back to READDATA
	mov al, byte [ SECTORNUMBER ]
								; Store the sector number to AL register
	add al, 0x01				; Increase the sector number
	mov byte [ SECTORNUMBER ], al
								; Restore the sector number from AL register
	cmp al, 19					; Compare the sector number and 19
	jl READDATA					; If the sector number is less than 19,
								; jump to the READDATA
	
	; If the sector number is 19, toggle the head
	; and change the sector number as 1
	xor byte [ HEADNUMBER ], 0x01
								; Toggle the head number
	mov byte [SECTORNUMBER ], 0x01
								; Set the sector number as 1
	
	; If the head was changed from 1 to 0, the bootloader read front and back
	; of disk, so it should increase the track number
	cmp byte [ HEADNUMBER ], 0x00
								; Compare the head number and 0x00
	jne READDATA				; If not, jump to the READDATA
	
	; Increase the track number
	add byte [ TRACKNUMBER ], 0x01
								; Increasing the track number
	jmp READDATA				; jump to thr READDATA
READEND:

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Print message to let user know loading is done
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	push LOADINGCOMPLETEMESSAGE
								; Push the address of the message in the stack
	push 1						; Push the point of Y
	push 20						; Push the point of X
	call PRINTMESSAGE			; Call the function PRINTMESSAGE
	add sp, 6					; Remove parameters
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Execute OS image which is loaded
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	jmp 0x1000:0x0000
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	Function section
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Function for disk error handling
HANDLEDISKERROR:
	push DISKERRORMESSAGE		; Push the address of the message in the stack
	push 1						; Push the point of Y
	push 20						; Push the point of X
	call PRINTMESSAGE			; Call the function PRINTMESSAGE
	
	jmp $						; Infinite loop at this point
	
; Function for printing message
;	PARAM: x point, y point, string
PRINTMESSAGE:
	push bp						; Push BP (Base Pooint) register
	mov bp, sp					; Store SP in BP
								; BP will be used to calculate to find address of 
								; the specific parameter
							
	push es						; Push from ES to DX registers
	push si						; there will be restore at the end of the function
	push di						; The reason why BX is not pushed is
	push ax						; BX is currently used to read sector
	push cx					
	push dx
	
	; Set ES register as the start address of video memory
	mov ax, 0xB800				; The start address of Video meory is 0xB8000
	mov es, ax					; Set ES register
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;	Calculate video address of X and Y point
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	; Calculate address of Y point
	mov ax, word [ bp + 6 ]		; Read second parameter and set AX as it
	mov si, 160					; 160 ( 80 * 2 ) is the number of byte for one
								; line in screen
	mul si						; Y point = AX = AX * SI
	mov di, ax					; Y point is stored in DI
	
	; Calculate address of X point
	mov ax, word [ bp + 4 ]		; Read first parameter and set AX as it
	mov si, 2					; Two bytes are used for one character
	mul si						; X point = AX = AX * SI
	add di, ax					; DI had a start address of the line
								; and it is added by point of X
							
	; Address of string
	mov si, word [ bp + 8 ]		; Read third parameter
	
.MESSAGELOOP:					; Print message
	mov cl, byte [ si ]		
								; Copy the value of si address
								; to CL register.
								; CL register is low 1 byte of CX register
									
	cmp cl, 0 					; if character is 0, it means end.
	je .MESSAGEEND				; if cl is 0, jump to .MESSAGEEND
	
	mov byte [ es: di ], cl		; if cl is not 0, print value of ES + DI address
	
	add si, 1					; Move to the next character
	add di, 2					; Move to the next address
	
	jmp .MESSAGELOOP			; Move to the next iteration

.MESSAGEEND:
	pop dx						; At the end of the function,
	pop cx						; the values of the registers for the caller
	pop ax						; should be restored
	pop di						; The order is reversed of the push
	pop si					
	pop es					
	pop bp						; Restore BP
	ret							; Return to the caller

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	Data section
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Message of bootloader starting
MESSAGE1: 
	db 'kOdin OS Boot Loader Start!!', 0
								; Message for print
								; last 0 means the end of string

DISKERRORMESSAGE:
	db 'DISK Error~!!', 0
IMAGELOADINGMESSAGE:
	db 'OS Image Loading...', 0
LOADINGCOMPLETEMESSAGE:
	db 'Complete~!!', 0
	
; Variables for disk read
SECTORNUMBER: 
	db 0x02						; The sector number which OS image start
HEADNUMBER:
	db 0x00						; The head number which OS image start
TRACKNUMBER:
	db 0x00						; The track number which OS image start
	
times 510 - ( $ - $$ )	db	0x00	
								; $: adress of current line
								; $$: start address of current section
								; $ - $$: Offset from current section
								; 510 - ( $ - $$ ): from here to address 510
								; db 0x00: Define 1 byte as 0x00
								; times: repeat
								; From current to address 510, fill 0x00
									
db 0x55 						; Define 1 byte as 0x55
db 0xAA							; Define 1 byte as 0xAA
								; Address 511, 512 are 0x55, 0xAA
