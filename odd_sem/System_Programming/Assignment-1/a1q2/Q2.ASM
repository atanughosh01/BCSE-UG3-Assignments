.MODEL SMALL    ; Program uses a minimum of 64K of memory for code
.STACK 100H     ; Bytes of stack spaces for the Program


.DATA

UPPER DB "ENTER A LETTER IN UPPERCASE : ", "$"
LOWER DB 0DH, 0AH, "SAME LETTER IN LOWERCASE : "
CHAR DB ?, "$"


.CODE

MAIN PROC
        
        MOV AX, @DATA
        MOV DS, AX
        LEA DX, UPPER
        MOV AH, 09H
        INT 21H


        ; ENTER THE LETTER

        MOV AH, 01H
        INT 21H
        ADD AL, 20H      ; CONVERT TO LOWERCASE BY ADDING 32
        MOV CHAR, AL     ; STORE THE LOWERCASE CHARACTER

        LEA DX, LOWER
        MOV AH, 09H
        INT 21H


        ; TERMINATE

        MOV AH, 4CH
        INT 21H

MAIN ENDP
END MAIN


; MASM Q2.ASM && LINK Q2.OBJ && Q2.EXE
