; CS-2610 LAB ASSIGNMENT - 1		ASSIGNMENT-1.asm

; Objectives :- To find the sum of given n numbers.
; Inputs	 :- n , n-numbers
; Outputs	 :- n , sum of n-numbers

%include "io.mac"		;Including io.mac file.

.DATA
	sum	dd	0		;Initializing sum to 0.
.UDATA
	n	resd	1		;Reserving double word for variable n.
.CODE
	.STARTUP
		GetLInt	[n]		;Taking n as input.
		mov		ECX,[n]	;ECX <- n
	repeat_sum :
		GetLInt	EDX		;Taking a number as input in EDX.
		add 		[sum],EDX	;sum <- sum + EDX
		dec		ECX		;ECX <- ECX - 1
		cmp		ECX,0		;Comparing if ECX==0.
		jne		repeat_sum	;Jump to 'repeat_sum' if ECX!=0.

		PutLInt	[n]		;Printing n.
		nwln				;New line.	
		PutLInt	[sum]		;Printing sum.
		nwln
	.EXIT