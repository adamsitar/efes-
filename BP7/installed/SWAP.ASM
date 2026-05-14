
; *******************************************************
; *							*
; *	Turbo Pascal Runtime Library Version 5.5	*
; *	Interrupt Vector Swapping			*
; *							*
; *	Copyright (C) 1988,89 Borland International	*
; *							*
; *******************************************************

	TITLE	SWAP

	LOCALS	@@

DATA	SEGMENT	WORD PUBLIC

	EXTRN	SaveInt00:DWORD

DATA	ENDS

CODE	SEGMENT	BYTE PUBLIC

	ASSUME	CS:CODE,DS:DATA

	PUBLIC	SwapVectors

    IFDEF _DPMI_

SwapVectors	PROC	FAR

	MOV	DI,OFFSET SaveInt00
	MOV	SI,OFFSET SaveIntTab
	MOV	CX,SaveIntCnt
	CLD
@@1:	PUSH	CX
	SEGCS	LODSW
	MOV	BL,AH
	MOV	AH,2
	INT	31H
	XCHG	DX,[DI]
	XCHG	CX,[DI+2]
	INC	AX
	INT	31H
	POP	CX
	ADD	DI,4
	LOOP	@@1
	RET

SwapVectors	ENDP

; Saved interrupt and exception numbers

SaveIntTab	LABEL	BYTE

	DB	2,00H
	DB	4,02H
	DB	2,0CH
	DB	2,0DH
	DB	4,1BH
	DB	4,21H
	DB	0,23H
	DB	0,24H
	DB	4,34H
	DB	4,35H
	DB	4,36H
	DB	4,37H
	DB	4,38H
	DB	4,39H
	DB	4,3AH
	DB	4,3BH
	DB	4,3CH
	DB	4,3DH
	DB	4,3EH
	DB	4,3FH
	DB	4,75H

SaveIntCnt	EQU	($-SaveIntTab)/2

    ELSE

SwapVectors	PROC	FAR

	MOV	DI,OFFSET SaveInt00
	MOV	SI,OFFSET SaveIntTab
	MOV	CX,SaveIntCnt
	CLD
@@1:	SEGCS	LODSB
	MOV	AH,35H
	INT	21H
	PUSH	ES
	PUSH	BX
	PUSH	DS
	LDS	DX,[DI]
	MOV	AH,25H
	INT	21H
	POP	DS
	POP	WORD PTR [DI]
	POP	WORD PTR [DI+2]
	ADD	DI,4
	LOOP	@@1
	RET

SwapVectors	ENDP

; Saved interrupt numbers

SaveIntTab	DB	00H,02H,1BH,21H,23H,24H,34H,35H,36H,37H
		DB	38H,39H,3AH,3BH,3CH,3DH,3EH,3FH,75H
SaveIntCnt	EQU	$-SaveIntTab

    ENDIF

CODE	ENDS

	END
