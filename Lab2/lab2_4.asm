	AREA RESET,DATA,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X40000000
	DCD Reset_Handler
	ALIGN
    AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
    LDR R0,=NUM1
	LDR R1,=NUM2
	LDR R8,=RESULT
	MOV R6,#04
	
	MOV R7,#01
	MSR PSR,R7

UP	LDR R2,[R0],#4
	LDR R3,[R1],#4
    
	SUBS R5,R2,R3
	STR R5,[R8],#4
	
	SUB R6,#1
	TEQ R6,#0
	BNE UP
	
	ADD R5,#01
    STR R5,[R8]
	
STOP B STOP 
NUM1 DCD 0X5555,0X7777,0X8888,0X9999
NUM2 DCD 0X5555,0X6666,0X7777,0X8888
	AREA DATASEG,DATA,READWRITE	
RESULT DCD 0
	END