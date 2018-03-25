	;ASSIGNMENT 2 QUESTION 2
	;WALP TO ADD 2, 8 DIGIT BCD NUMBERS IN THE UNPACKED ASCII
	;FORM AVAILABLE IN THE CODE MEMORY, AND STORE THE BCD RESULT IN THE ASCII FORM IN THE RAM
	
	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x40000000
	DCD Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0, =SRC1
	ADD R0, #32
	LDR R1, =SRC2
	ADD R1, #32
	LDR R7, =DEST
	ADD R7, #8		;for packed ASCII, store in each byte for a total of 8 bytes
	MOV R2, #08 	;8 LDRH OPERATIONS WILL BE THERE

	MOV R9, #0X00
	MSR XPSR, R9 
	
LOOP
	LDRH R3, [R0, #-4]!
	LDRH R4, [R1, #-4]!
	
	AND R3, R3, #0X0F
	AND R4, R4, #0X0F
	
	ADC R3, R4
	CMP R3, #09
	BLS DOWN1
	ADD R3, #06
	AND R3, #0X0F
	LDR R9, =0X20000000
	B DOWN2
DOWN1
	LDR R9, =0X00000000
DOWN2
	MSR XPSR, R9
	
	LDR R8, =0X00000030		;SINCE THE QUESTION SAYS "in the ASCII form in RAM"; if result had to be in "unpacked ASCII" load 0x0300 here
	ADD R8, R3
	
	STRB R8, [R7, #-1]!
	
	SUB R2, #01
	TEQ R2, #00
	BNE LOOP

STOP B STOP
	
SRC1 DCD 0X0305, 0X0309, 0X0301, 0X0304, 0X0304, 0X0309, 0X0308, 0X0302  ; THERE IS NO DCH, THE NUMBERS WILL GET STORED IN LITTLE ENDIAN AND PADDED  	
SRC2 DCD 0X0301, 0X0303, 0X0304, 0X0309, 0X0301, 0X0303, 0X0304, 0X0309	

	AREA myarea, DATA, READWRITE
DEST DCB 0
	END