; CS-2610 LAB ASSIGNMENT - 2			ASSIGNMENT-2.asm
; Objectives :- To encrypt a given input string.
; Inputs     :- String
; Outputs    :- Encrypted String.

%include "io.mac"

.DATA
	iword_msg	db	"Please enter an input string : ",0
	query_msg	db	"Would you like to terminate? (y\Y or \N)",0
.UDATA
	iword		resb	21		;Reserving 21 bytes for the input 						 string.
	response		resb  1 	;Reserving 1 byte for yes or no 							 response character.
.CODE
	.STARTUP
	start :
		PutStr	iword_msg	;Prompting for input string.
		GetStr	iword,21	;Taking input string.
		mov		EBX,iword	;Moving address of 1st bit of 							 iword to EBX.
	for_begin :
		mov		DL,[EBX]	;DL<-[EBX]
		cmp		DL,0		;Comparing whether null 								 character.
		je		break		;If null character break loop and 						 go to end.
		cmp		DL,'9'	;Comparing whether character is a 						 number of a letter of alphabet.
		jg		for_end	;If character go to end and print 						 as it is.
		cmp		DL,'4'	;Checking if less than '4'.	
		jg		else_part	;Jumping to else if >'4'.
		mov		AL,DL		;AL<-DL
		sub		AL,'0'	;AL<-AL-'0'
		mov		CL,2		;CL<-2.
		mul		CL		;CL<-CL*2
		add		AL,5		;AL<-AL+5
		add		AL,'0'	;AL<-AL+'0'
		mov		DL,AL		;DL<-AL
		jmp		end_ifelse	;Jumping end of if-else.
	else_part :
		mov		AL,DL		;AL<-DL.
		sub		AL,'4'	;AL<-AL-'4'
		add		DL,AL		;DL<-DL+AL.
	end_ifelse :
		cmp		DL,'9'	;Checking if DL is greater than 							 '9'.
		jle		for_end	;Jumping to end if less than or 							 equal to '9'.
		sub		DL,10		;DL<-DL-10 if DL>=10.
	for_end :
		PutCh		DL		;Outputting character.
		inc		EBX		;EBX<-EBX+1.
		jmp		for_begin	;Jump to beginning of for.
	break :
		nwln
		PutStr	query_msg			;Ask for termination.
		GetCh		[response]			;Input response.
		cmp		byte[response],'y'	
		je		terminate			;Terminate if 'Y' or 									 'Y'.
		cmp		byte[response],'Y'
		je		terminate
		nwln
		jmp		start				;Jump to start.
	terminate :
	.EXIT