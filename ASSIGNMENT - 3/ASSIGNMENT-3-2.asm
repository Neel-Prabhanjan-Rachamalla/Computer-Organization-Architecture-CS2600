; ACKERMAN FUNCTION		ASSIGNMENT-3-2.asm
; OBJECTIVE : To implement Ackermann function using recursion in stack.

%include "io.mac"

.UDATA
	m		resd		1
	n		resd		1
	result	resd		1

.CODE
	.STARTUP
		GetLInt	[m]
		mov		EAX,[m]
		push 		EAX
		GetLInt	[n]
		mov		EAX,[n]
		push		EAX
		call		Afunc
		mov		[result],EAX
		PutLInt	[result]
		nwln
	.EXIT

Afunc :
		enter 	0,0
		
	if1 :
		mov		ECX,[EBP+12]
		cmp		ECX,0
		jne		if2
		mov		EAX,[EBP+8]
		inc 		EAX
		jmp		return
	
	if2 :
		mov		ECX,[EBP+8]
		cmp		ECX,0
		jne		if3
		mov		EDX,[EBP+12]
		dec		EDX
		push		EDX
		inc 		ECX
		push		ECX
		call		Afunc
		jmp		return
	
	if3 :
		mov		ECX,[EBP+12]
		mov		EDX,[EBP+8]
		dec 		EDX
		push		ECX
		push		EDX
		call 		Afunc
		mov		ECX,[EBP+12]
		dec		ECX
		mov		EDX,EAX
		push		ECX
		push		EDX
		call 		Afunc
	
	return :
		leave
		ret 		8