
; *******************************************************
; *							*
; *	Turbo Pascal Runtime Library Version 5.5	*
; *	Date and Time Routines				*
; *							*
; *	Copyright (C) 1988,89 Borland International	*
; *							*
; *******************************************************

	TITLE	TIME

CODE	SEGMENT	BYTE PUBLIC

	ASSUME	CS:CODE

	PUBLIC	GetDate

GetDate		PROC	FAR

YearP		EQU	(DWORD PTR [BP+18])
MonthP		EQU	(DWORD PTR [BP+14])
DayP		EQU	(DWORD PTR [BP+10])
DayOfWeekP	EQU	(DWORD PTR [BP+6])

	PUSH	BP
	MOV	BP,SP
	MOV	AH,2AH
	INT	21H
	XOR	AH,AH
	LES	DI,DayOfWeekP
	STOSW
	MOV	AL,DL
	LES	DI,DayP
	STOSW
	MOV	AL,DH
	LES	DI,MonthP
	STOSW
	XCHG	AX,CX
	LES	DI,YearP
	STOSW
	POP	BP
	RET	16

GetDate		ENDP

	PUBLIC	SetDate

SetDate		PROC	FAR

Year		EQU	(WORD PTR [BP+10])
Month		EQU	(BYTE PTR [BP+8])
Day		EQU	(BYTE PTR [BP+6])

	PUSH	BP
	MOV	BP,SP
	MOV	CX,Year
	MOV	DH,Month
	MOV	DL,Day
	MOV	AH,2BH
	INT	21H
	POP	BP
	RET	6

SetDate		ENDP

	PUBLIC	GetTime

GetTime		PROC	FAR

HourP		EQU	(DWORD PTR [BP+18])
MinuteP		EQU	(DWORD PTR [BP+14])
SecondP		EQU	(DWORD PTR [BP+10])
Sec100P		EQU	(DWORD PTR [BP+6])

	PUSH	BP
	MOV	BP,SP
	MOV	AH,2CH
	INT	21H
	XOR	AH,AH
	MOV	AL,DL
	LES	DI,Sec100P
	STOSW
	MOV	AL,DH
	LES	DI,SecondP
	STOSW
	MOV	AL,CL
	LES	DI,MinuteP
	STOSW
	MOV	AL,CH
	LES	DI,HourP
	STOSW
	POP	BP
	RET	16

GetTime		ENDP

	PUBLIC	SetTime

SetTime		PROC	FAR

Hour		EQU	(BYTE PTR [BP+12])
Minute		EQU	(BYTE PTR [BP+10])
Second		EQU	(BYTE PTR [BP+8])
Sec100		EQU	(BYTE PTR [BP+6])

	PUSH	BP
	MOV	BP,SP
	MOV	CH,Hour
	MOV	CL,Minute
	MOV	DH,Second
	MOV	DL,Sec100
	MOV	AH,2DH
	INT	21H
	POP	BP
	RET	8

SetTime		ENDP

CODE	ENDS

	END
