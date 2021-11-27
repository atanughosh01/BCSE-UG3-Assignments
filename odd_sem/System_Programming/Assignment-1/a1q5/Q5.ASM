.MODEL SMALL    ; Program uses a minimum of 64K of memory for code
.STACK 100H     ; Bytes of stack spaces for the Program


.DATA

MESSAGE DB "TERMINATING....", 0DH, 0AH, "TERMINATED !", "$"


.CODE

MAIN PROC
        
        MOV AX, @DATA
        MOV DS, AX
        LEA DX, MESSAGE
        MOV AH, 09H
        INT 21H


        ; TERMINATE

        MOV AH, 4CH
        INT 21H

MAIN ENDP
END MAIN


; MASM Q5.ASM && LINK Q5.OBJ && Q5.EXE
