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
    LDR R1,=12345678
	LDR R2,=12345678
	ADD R1,R2
STOP B STOP
	END


	