.MODEL SMALL    ; Program uses a minimum of 64K of memory for code
.STACK 100H     ; Bytes of stack spaces for the Program


.DATA

MSG1 DB "ENTER A CHARACTER : ", "$"
MSG2 DB 0DH, 0AH, "ENTERED CHARACTER : "
CHAR DB ?, "$"


.CODE

MAIN PROC
        
        MOV AX, @DATA
        MOV DS, AX
        LEA DX, MSG1
        MOV AH, 09H
        INT 21H

                
        ; ENTER THE LETTER

        MOV AH, 01H
        INT 21H
        ADD Al, 00H
        MOV CHAR, Al      ; STORE FOR PRINTING

        LEA DX, MSG2
        MOV AH, 09H
        INT 21H


        ; TERMINATE

        MOV AH, 4CH
        INT 21H

MAIN ENDP
END MAIN


; MASM Q6.ASM && LINK Q6.OBJ && Q6.EXE
