.MODEL SMALL    ; Program uses a minimum of 64K of memory for code
.STACK 100H     ; Bytes of stack spaces for the Program


.DATA

MSG DB "PRINTING CHARACTERS FROM A TO Z",13,10,"$"


.CODE

MAIN PROC

        MOV AX, @DATA
        MOV DS, AX
        LEA DX, MSG
        MOV AH, 09H
        INT 21H

        MOV DL, 'A'
        MOV CX, 1AH     ; Stores 26 in CX

LOOP1:
        MOV AH, 02H
        INT 21H
        INC DL
        DEC CX
        JNZ LOOP1


        ;TERMINATE

        MOV AH, 4CH
        INT 21H

MAIN ENDP
END MAIN


; MASM Q10.ASM && LINK Q10.OBJ && Q10.EXE
