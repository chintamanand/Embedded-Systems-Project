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
     LDR R1,[R0]
     LDR R3,=NUM2
     LDR R2,[R3]
     SUB R4,R1,R2
STOP B STOP
NUM1 DCD 0X77777777
NUM2 DCD 0X11111111
     AREA data,DATA,READWRITE   
		END