	AREA Reset,Data,Readonly
	EXPORT __Vectors
__Vectors
	DCD 0x40000000
	DCD Reset_Handler
	ALIGN
	AREA mycode,Code,Readonly
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
    LDR R5,=VALUE1
	LDR R4,[R5]
    MOV R2,#1
	MOV R3,#1
	MOV R1,#1
UP
    MLA R1,R1,R2,R3
	ADD R3,#1
	SUB R4,#1
	CMP R4,#0
	BNE UP
	SUB R1,#1
	STR R1,[R6]
STOP B STOP
VALUE1 DCD 0x4
	AREA DATASEG,DATA,READWRITE	
	END