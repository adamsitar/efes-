
; *******************************************************
; *							*
; *	Turbo Pascal Runtime Library Version 5.5	*
; *	DOS Version Routine				*
; *							*
; *	Copyright (C) 1988,89 Borland International	*
; *							*
; *******************************************************

	TITLE	VERS

CODE	SEGMENT	BYTE PUBLIC

	ASSUME	CS:CODE

	PUBLIC	DosVersion

DosVersion	PROC	FAR

	MOV	AH,30H
	INT	21H
	RET

DosVersion	ENDP

CODE	ENDS

	END
