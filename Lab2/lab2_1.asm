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
        LDR R0,=SRC
        MOV R1,#10
UP      LDR R2,[R0]
        ADD R3,R2
        ADD R0,R0,#4
        SUBS R1,#1
        BNE UP
STOP B STOP
    AREA DATASEG,DATA,READWRITE
SRC DCD 8,0X12345678
   END