
;To implement mmap() and fork()                             
         


%include "io.mac"

.DATA
    file_name       db             "input.txt", 0           ;Input file name
    n               dd               0                      ;Variable that holds total num of integers
    x               dd               0
    y               dd               0                      ;Dummy variables
   
    

.UDATA
    file_desc       resd            1                       ;Variable that holds file descriptor
   

.CODE
    .STARTUP
   
   
     call            create_and_open_file    ; File created and opened
     mov             [file_desc], EAX  
     
     GetInt [n]
     mov EBX, [n]
     mov [x],EBX
     call write_into_file                     ;Taking n as input and storing it in the file and then modifying  file pointer 
     call lseek
     
     
     num_save_loop:
     
    	GetInt          [x]              
    	call            write_into_file         ; Written n integers into the file
    	call            lseek 
   
    	dec EBX
    	cmp EBX,0
    	je num_save_done
    	jmp num_save_loop
    
    num_save_done:
    
    call            close_file              ;Closing file
    call            open_file               ; File opened for mmaping
    mov             [file_desc], EAX        ; File descriptor saved
     
    call            mmap2                   ; Mmaping the file into memory
                 
           
   
  
    call            fork                    ;Forking a child process
    cmp             EAX, 0                  ; Checking if process is child or parent
    je              child                   ; Jumping to child in case of child process
    
    parent:
    
    call           wait_for_child           ; First child output be displayed 
    call           insertion                  ; then parent process is continued
    jmp            return_from_parent     ; Jumping to end
    

 child:
    
    call           print_sum   
    jmp            return_from_child      ; Jumping to end
    
    
return_from_child:    
return_from_parent:
     
    call close_file            ; close the file before terminating


.EXIT

print:                         ;Prints the n numbers in the file
	push EAX
	push EBX
	push ECX
	push EDX

   	mov EAX,1
  
  	print_loop:
  	
     		cmp EAX,[n]
     		jg print_loop_end
     		IMUL ECX,EAX,4
     		call lseek_custom
     		call read
     		PutInt [x]
     		nwln
     		inc EAX
     		jmp print_loop
     
     
    	print_loop_end:
 
  	pop EDX
 	pop ECX
 	pop EBX
 	pop EAX
 	
 ret
 
insertion:                  ;Does insertion sort on the n numbers in the file

	push EAX
	push EBX
	push ECX
	push EDX


 
 	mov EAX,2
 
 	loop_i:
   		cmp  EAX,[n]
   		jg    loop_i_end
   		IMUL  ECX,EAX,4
   		call lseek_custom
   		call read
   		mov EDX,[x]
   
   		mov EBX,EAX
   		dec EBX
   			loop_j:
      				cmp EBX,0
      				je  loop_j_end
      
      				IMUL ECX,EBX,4
      				call lseek_custom
      				call read
      				mov ECX,[x]
      				
      				cmp ECX,EDX
      				jle  loop_j_end
      				
      				mov ECX,EBX
      				inc ECX
      				IMUL ECX,ECX,4
      				call lseek_custom
      				call write_into_file
      				dec EBX
     
      				jmp loop_j
      
    			loop_j_end:
    
    		inc EBX
    		IMUL ECX,EBX,4
    		call lseek_custom
    		mov [x],EDX
    		call write_into_file
    		
    		inc EAX
    		jmp loop_i
    
 	loop_i_end:
 

   	call print
 
 
  	pop EDX
 	pop ECX
 	pop EBX
 	pop EAX
 	
 	ret
      
print_sum:           ;Prints the sum of n numbers in the file

push EAX
push EBX
push ECX
push EDX

   	mov EDX,0
   	mov [y],EDX
   	mov EBX,[n]
   	add EBX,1
   	loop_start:
   	
     		cmp EBX,1
     		je output_end
     		dec EBX
     		IMUL ECX,EBX,4
     		call lseek_custom
     		call read
   		mov EDX,[x]
     		ADD  [y],EDX
     		jmp  loop_start
     
     
     
   
     	output_end:
     	PutInt [y]
     	nwln
     
 
 pop EDX
 pop ECX
 pop EBX
 pop EAX
 
 ret
 
 
read:        ;Reading 4 bytes from the location pointed by file pointer
 push EAX
 push EBX
 push ECX
 push EDX
 
 mov EAX,3
 mov EBX,[file_desc]
 mov ECX,x
 mov EDX,4
 int 0x80
 
 pop EDX
 pop ECX
 pop EBX
 pop EAX
 ret
 
lseek:        ;Moving file pointer to the end of file
 push EAX
 push EBX
 push ECX
 push EDX
 
 mov EAX,19
 mov EBX,[file_desc]
 mov ECX,0
 mov EDX,2
 int 0x80
 
 pop EDX
 pop ECX
 pop EBX
 pop EAX
 ret
 
 lseek_custom:    ;Moving file pointer [ECX] bytes from the beginning of file
 
 push EAX
 push EBX
 push EDX
 
 mov EAX,19
 mov EBX,[file_desc]
 mov EDX,0
 int 0x80
 
 pop EDX
 pop EBX
 pop EAX
 
 ret


create_and_open_file:       ;Creates and opens file with no access restrictions
 
 push EBX
 push ECX
 push EDX
 
    mov             EAX, 8
    mov             EBX, file_name
    mov             ECX, 0x1FF
    int             0x80
    
 pop EDX
 pop ECX
 pop EBX

    ret





write_into_file:            ;Writes the value in x to the location pointed by file pointer     

 push EAX
 push EBX
 push ECX
 push EDX
 
    mov             EAX, 4
    mov             EBX, [file_desc]
    mov             ECX, x
    mov             EDX,4
    int             0x80
    
 pop EDX
 pop ECX
 pop EBX
 pop EAX
    ret




close_file:                  ;Closes file corresponding to file_desc
 push EAX
 push EBX
 push ECX
 push EDX
 
    mov             EAX, 6
    mov             EBX, [file_desc]
    int             0x80
    
 pop EDX
 pop ECX
 pop EBX
 pop EAX
    ret







open_file:             ;Opens a file corresponding to file_name

 push EBX
 push ECX
 push EDX
 
    mov             EAX, 5
    mov             EBX, file_name
    mov             ECX, 2
    mov             EDX, 1FFH
    int             0x80
    
 pop EDX
 pop ECX
 pop EBX

    ret






mmap2:     ;mmap the opened file to current process

    mov             EAX, 192
    mov             EBX, 0           ;address
    mov             ECX, 4096          ;system page size
    mov             EDX, 0x1           ;protection: PROT_EXEC | PROT_WRITE | PROT_READ
    mov             ESI, 0x2           ;flags: MAP_ANONYMOUS | MAP_PRIVATE
    mov             EDI, [file_desc]
    mov             EBP, 0        ;offset in file from which it should be mapped to the memory
    int             0x80

    ret






fork:          ;fork the current process
 

    mov             EAX, 2
    int             0x80

    
    ret





wait_for_child:   ;waitpid till the child processes are terminated
 
    mov            EAX, 7
    mov            EBX, -1
    mov            ECX, 0
    mov            EDX, 0
    int            0x80

    ret





    






   
     
   


