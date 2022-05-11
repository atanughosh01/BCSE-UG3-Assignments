                                           System Programming Assignment - 3

# Names, Rolls and Email-ids of Group Members


|       |           Name            |            Roll             |              Email-id               |
|:-----:|:-------------------------:|:---------------------------:|:-----------------------------------:|
|   1.  |       Atanu Ghosh         |        001910501005         |      2001atanughosh@gmail.com       |
|   2.  |       Sagnik Ganguly      |        001910501030         |      sagnikg2013@gmail.com          |
|   3.  |       Arpan Nandi         |        001910501013         |      arpannandi12@gmail.com         |
|   4.  |       Ayush Choudhury     |        001910501027         |      hazard8474@gmail.com           |
|   5.  |       Arjun Mallick       |        001910501021         |      arjunmallick99@gmail.com       |



<br>
<br>

# PassTwoAssembler (PASM)

An implementation of a simple yet fast two-pass assembler in C language with tries for fast in-memory opcode fetch.



<br>

## Supports

* Parsing assembler scripts
* Generation of intermediate file
* Generation of object file
* Generation of symbol tables
* Loader creating .exe files


### Instructions for executing this project

Write the source assembly in the source file named `file.pasm` and then run the following command:

```
$ make test
```
The above command takes care of assembling the source code, linking and executing the binary.



<br>

## Limitations

* The [opcodes.csv](./opcodes.csv) file contains the supported opcodes, more opcodes has to be supported and some have yet undefined lenghts.
* There is no support for macros
* There is no support for some assembler directives such as `EXTERN` , `ORG` and `LTORG`.
* There is yet no support for multiple control sections.

