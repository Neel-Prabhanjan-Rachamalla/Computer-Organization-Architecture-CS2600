;ENCRYPTION		ASSIGNMENT-2

%include "io.mac"

.DATA
	query		db		"Do you want to continue or terminate? Y/N?",0
	input		db		"5791368024"
	
.UDATA
	string 	resb		21

.CODE
	.STARTUP
	
		GetStr	string,21
		mov		EBX,input
		mov		ECX,string
	
	encry :
		mov		AL,[ECX]
		cmp		AL,0
		je		end2
		cmp		AL,'9'
		jg		end
		cmp		AL,'0'
		jl		end
		sub		AL,'0'
		xlatb
	end	:
		PutCh		AL
		inc		ECX
		jmp		encry
	end2 	:
		nwln
	
	.EXIT