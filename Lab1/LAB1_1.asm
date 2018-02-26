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
	LDR R0,#0X87654321
	MOV R1,#0123
	MOV R2,#33
	MOV R1,R0
	
STOP B STOP
    END
