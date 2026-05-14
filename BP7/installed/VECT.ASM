
; *******************************************************
; *							*
; *	Turbo Pascal Runtime Library Version 5.5	*
; *	Interrupt Vector Handling			*
; *							*
; *	Copyright (C) 1988,89 Borland International	*
; *							*
; *******************************************************

	TITLE	VECT

CODE	SEGMENT	BYTE PUBLIC

	ASSUME	CS:CODE

	PUBLIC	GetIntVec

GetIntVec	PROC	FAR

IntNo		EQU	(BYTE PTR [BP+10])
VectorP		EQU	(DWORD PTR [BP+6])

	PUSH	BP
	MOV	BP,SP
	MOV	AL,IntNo
	MOV	AH,35H
	INT	21H
	MOV	AX,ES
	LES	DI,VectorP
	CLD
	XCHG	AX,BX
	STOSW
	XCHG	AX,BX
	STOSW
	POP	BP
	RET	6

GetIntVec	ENDP

	PUBLIC	SetIntVec

SetIntVec	PROC	FAR

IntNo		EQU	(BYTE PTR [BP+10])
Vector		EQU	(DWORD PTR [BP+6])

	PUSH	BP
	MOV	BP,SP
	PUSH	DS
	LDS	DX,Vector
	MOV	AL,IntNo
	MOV	AH,25H
	INT	21H
	POP	DS
	POP	BP
	RET	6

SetIntVec	ENDP

CODE	ENDS

	END
