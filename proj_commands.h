/* Maman 14 - Assembler Project 2021a
   By Andrey Diskin , 20/03/2021
   File name: proj_commands.h */


#include "machine_types.h"


/* Macros */


#ifndef _PROJ_COMMANDS_H_
#define _PROJ_COMMANDS_H_
#define ARE_A_STR 'A'
#define ARE_E_STR 'E'
#define ARE_R_STR 'R'
#define CMD_DATA_SIZE 16


typedef struct CmdData_t {

/* The name of the command */

String_t cmd_name;


/* The value of the operation code */

int opcode_code;



/* The value of function code */

int function_code;



/* Valid src addressing mode */

int src_addressing_mode;


/* Valid dst addressing mode */

int dest_addressing_mode;




} 

CmdData_t;





/* Checking if two strings are equal or not equal */

bool is_equal(const String_t str1, const String_t str2);



/* Returns an array with all the commands */

String_t* get_commands();



/* Returns the operation code value of command
 * Returns -1 if not found the opcode */

int get_command_opcode_val(String_t cmd_name);



/* Identifying the needed command */

bool identify_command(const String_t cmd);




/* Returns the func value of command
 * Returns -1 if not found the func value */

int get_command_func_val(String_t cmd_name);





/* Command info search received the name of command */
 
CmdData_t* get_command_full_info(String_t cmd);








#endif
