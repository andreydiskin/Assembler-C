/* Maman 14 - Assembler Project 2021a
   By Andrey Diskin , 20/03/2021
   File name: machine.types.h */


#ifndef _MACHINE_TYPES_H_
#define _MACHINE_TYPES_H_

/* The types */

typedef char bool;
typedef char* String_t;
typedef const char* CString_t;



/* Macros */

#define STATUS_FLAG_SUCCESS 0
#define STATUS_FLAG_ERROR -1



/* Booleans */

#define false 0
#define true 1



/* Machine Parameters */

#define MAX_READ_BUFF 256
#define MAX_BUFF_LINE_LENGTH 80
#define MAX_LBL_SIZE 31
#define PROGRAM_ADDRESS	100
#define MEM_MAX_SIZE 4096





/* The commands */
#define CMD_MOV "mov"
#define CMD_CMP "cmp"
#define CMD_ADD "add"
#define CMD_SUB "sub"
#define CMD_LEA "lea"
#define CMD_CLR "clr"
#define CMD_NOT "not"
#define CMD_INC "inc"
#define CMD_DEC "dec"
#define CMD_JMP "jmp"
#define CMD_BNE "bne"
#define CMD_JSR "jsr"
#define CMD_RED "red"
#define CMD_PRN "prn"
#define CMD_RTS "rts"
#define CMD_STOP "stop"
#define CMD_ENTRY ".entry"
#define CMD_EXTERN ".extern"
#define CMD_DATA ".data"
#define CMD_STRING ".string"



typedef enum {
 ARE_A = 0,
 ARE_R = 1,
 ARE_E = 2
 } 

E_ARE;



#define ITER_LVL_1 1
#define ITER_LVL_2 2


/* Addressing mode 
 * types for a memory block */

typedef enum {
 ADDRESSING_MODE_IMMEDIATE = 0,
 ADDRESSING_MODE_DIRECT 	= 1,
 ADDRESSING_MODE_RELATIVE = 2,
 ADDRESSING_MODE_REG = 3
 }

 E_ADDRESSING_MODE;



#define FUNC_SHIFT 4
#define OPCODE_SHIFT 8
#define ARE_SHIFT 12


/* Data
 * code 
 * or extern the symbol */


typedef enum {
 SYM_TYPE_DATA = 0,
 SYM_TYPE_CODE = 1,
 SYM_TYPE_EXT = 2
 }

 E_SYM_TYPE;


/* The right range of nums */

#define MAX_NUM_VAL 2047
#define MIN_NUM_VAL -2048



typedef enum {
 ROW_HANDLE_REGULAR = 0,
 ROW_HANDLE_STR = 1
 } 

 E_ROW_HANDLE;




#define B_IMMED				0x1
#define B_DIREC				0x2
#define B_RELAT				0x4
#define B_REGIS				0x8



#endif
