
; *******************************************************
; *							*
; *	Turbo Pascal Runtime Library Version 5.5	*
; *	Verify Flag Handling				*
; *							*
; *	Copyright (C) 1988,89 Borland International	*
; *							*
; *******************************************************

	TITLE	VERF

CODE	SEGMENT	BYTE PUBLIC

	ASSUME	CS:CODE

	PUBLIC	GetVerify

GetVerify	PROC	FAR

VerifyP		EQU	(DWORD PTR [BP+6])

	PUSH	BP
	MOV	BP,SP
	MOV	AH,54H
	INT	21H
	LES	DI,VerifyP
	STOSB
	POP	BP
	RET	4

GetVerify	ENDP

	PUBLIC	SetVerify

SetVerify	PROC	FAR

Verify		EQU	(BYTE PTR [BP+6])

	PUSH	BP
	MOV	BP,SP
	MOV	AL,Verify
	MOV	AH,2EH
	INT	21H
	POP	BP
	RET	2

SetVerify	ENDP

CODE	ENDS

	END
