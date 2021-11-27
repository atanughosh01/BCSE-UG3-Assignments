.MODEL SMALL    ; Program uses a minimum of 64K of memory for code
.STACK 100H     ; Bytes of stack spaces for the Program


.DATA

MSG1 DB "|| STARTING THE LOOP ||","$"
LMSG DB 13,10, "LOOPING...., ENTER Q TO QUIT : ","$"


.CODE

MAIN PROC

        MOV AX, @DATA
        MOV DS, AX
        LEA DX, MSG1
        MOV AH, 09H
        INT 21H

LOOP1:
        MOV AH, 09H
        LEA DX, LMSG
        INT 21H
        MOV AH, 01H
        INT 21H
        CMP AL, 'Q'
        JNZ LOOP1


        ;TERMINATE

        MOV AH, 4CH
        INT 21H

MAIN ENDP
END MAIN


; MASM Q9.ASM && LINK Q9.OBJ && Q9.EXE
