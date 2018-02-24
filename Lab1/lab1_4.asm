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
	LDR R1,=SRC+10*4
	LDR R3,[R0]
    STR R3,[R1]
    ADD R0,R0,#4
	ADD R1,R1,#4
	
	LDR R3,[R0]
    STR R3,[R1]
    ADD R0,R0,#4
	ADD R1,R1,#4
	
	LDR R3,[R0]
    STR R3,[R1]
    ADD R0,R0,#4
	ADD R1,R1,#4
	
	LDR R3,[R0]
    STR R3,[R1]
    ADD R0,R0,#4
	ADD R1,R1,#4
	
	LDR R3,[R0]
    STR R3,[R1]
    ADD R0,R0,#4
	ADD R1,R1,#4
	
	LDR R3,[R0]
	STR R3,[R1]
	ADD R0,R0,#4
	ADD R1,R1,#4
	
    LDR R3,[R0]
    STR R3,[R1]
	ADD R0,R0,#4
	ADD R1,R1,#4
	
	LDR R3,[R0]
    STR R3,[R1]
	ADD R0,R0,#4
	ADD R1,R1,#4
	
	LDR R3,[R0]
    STR R3,[R1]
	ADD R0,R0,#4
	ADD R1,R1,#4
	
	LDR R3,[R0]
    STR R3,[R1]
	ADD R0,R0,#4
	ADD R1,R1,#4
	
STOP B STOP
	END