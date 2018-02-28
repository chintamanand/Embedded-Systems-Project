    AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler

Reset_Handler
	LDR R0,=NUM1
	LDR R1,[R0]
	MOV R4,#0XA
	LDR R5,=RESULT
	
	AND R3,R1,#0X0F
	AND R2,R1,#0XF0
	LSR R2,#4
	MUL R2,R4
	ADD R2,R3
	STR R2,[R5]
STOP B STOP
NUM1 DCD 0X99
	AREA data,DATA,READWRITE
RESULT DCD 0
	END	