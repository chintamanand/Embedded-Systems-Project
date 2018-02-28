	AREA RESET,DATA,Readonly
	EXPORT __Vectors
__Vectors	
	DCD 0x40000000
	DCD Reset_Handler
	ALIGN
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler
	LDR R0,=NUM1
	LDR R5,RESULT
	MOV R4,#8
	
UP
	LDRB R1,[R0],#4
	AND R1,#0X0F
	ADD R1,#0X30
	SUB R4,#1
	BNE UP
	STR R4,[R5]
STOP B STOP
NUM1 DCD 0X01,0X02,0X03,0X04,0X05,0X06,0X07,0X08
	AREA dataseg,DATA,READWRITE
RESULT DCD 0
	END