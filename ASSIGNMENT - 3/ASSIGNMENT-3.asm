; CS-2610 LAB ASSIGNMENT - 3			ASSIGNMENT-3.asm
; Objectives :- To perform recursive Ackerman's function.
; Inputs     :- Two whole numbers m,n.
; Outputs    :- Ackerman's function(m,n).

%include "io.mac"

.UDATA
	m		resd	1			; Reserving 1 double word for m.
	n		resd	1			; Reserving 1 double word for n.
	result	resd	1			; Reserving 1 double word for result.

.CODE
	.STARTUP
		GetLInt	[m]			; Inputting m.
		GetLInt	[n]			; Inputting m.
		mov		EAX,[m] 
		push		EAX			; Pushing m value to stack via EAX register.
		mov		EAX,[n]
		push		EAX			; Pushing n value to stack via EAX register.
		call		Afun			; Calling Ackermann's function.
		mov		[result],EAX
		PutLInt	[result]		; Outputting the result.
		nwln
	.EXIT

Afun:							; Ackermann's Function.
		enter		0,0
		mov		ECX,[EBP+12]	; ECX <- first parameter (i.e. m).
		cmp		ECX,0			; Checking if m==0.
		jne		elif			; Jumping to elif if m!=0.
		mov		EAX,[EBP+8]		; EAX <- second parameter (i.e. n).
		inc		EAX			; EAX <- EAX + 1
		jmp		return		; Jumping to return.
	elif:
		mov		ECX,[EBP+8]		; ECX <- second parameter (i.e. n).
		cmp		ECX,0			; Checking if n==0.
		jne		recur			; Jumping to recur if n!=0.
		mov		ECX,[EBP+12]	; ECX <- first parameter (i.e. m).
		dec		ECX			; ECX <- ECX - 1
		push		ECX			; Pushing (m-1) value to stack via ECX register.
		push		1			; Pushing 1 value to stack.
		call		Afun			; Calling Ackermann's function.
		jmp		return		; Jumping to return.
	recur:
		mov		ECX,[EBP+8]		; ECX <- second parameter (i.e. n).
		dec		ECX			; ECX <- ECX - 1
		mov		EDX,[EBP+12]	; ECX <- first parameter (i.e. m).
		push		EDX			; Pushing (n-1) value to stack via EDX register.
		push		ECX			; Pushing (m) value to stack via ECX register.
		call		Afun			; Calling Ackermann's function.
		mov		EDX,EAX		; EDX <- EAX
		mov		ECX,[EBP+12]	; ECX <- first parameter (i.e. m).
		dec		ECX			; ECX <- ECX - 1
		push		ECX			; Pushing (m-1) value to stack via ECX register.
		push		EDX			; Pushing (n) value to stack via EDX register.
		call		Afun			; Calling Ackermann's function.
	return:
		leave					; Release EBP.
		ret 8					; Clean stack.