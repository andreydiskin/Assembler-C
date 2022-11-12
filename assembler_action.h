/* Maman 14 - Assembler Project 2021a
   By Andrey Diskin , 20/03/2021
   File name: assembler_action.h */



#include "table_of_symbols.h"
#include "proj_commands.h"
#include "machine_types.h"
#include "extern_table.h"

#ifndef _ASSEMBLER_ACTION_H
#define _ASSEMBLER_ACTION_H


/* What of the operands
 * to handle at specific time */

 typedef enum {

   OPER_HANDLER_SRC = 0,
   OPER_HANDLER_DST = 1
 }
   E_OPER_HANDLER;
 

int check_symbol (String_t symbol_name);


/* Checking if number */

int check_num (String_t val_num_as_str);


/* Getting next value for parsing*/

int get_next_value_parser (String_t assembly_code_line, String_t parsed_val, int ParseMode, bool special_flag);



/* Checking if the number is on the right range */

bool check_number_on_range(int num);



/* Setting information in the memory */

void set_mem_block_func_opcode_are(int* mem_block,CmdData_t* cmd_data,E_ARE are_val);



/* Setting ARE to the memory */

void set_are(int* mem,const E_ARE eare_val);



/* Handling the relevant operand  */

int handle_operand(const int pos_at_file,E_OPER_HANDLER eoper_handler,String_t val_data_parsed,int* program_data_img,int instruction_counter,CmdData_t* cmd_data,SymbolNode_t* lst_symbol,ExtData_t** lst_ext_symbol,int iter_number, String_t fn);



/* Checking validation of a symbol name */ 

bool check_lbl_symbol_is_func_machine_name(const String_t lbl_symbol);


/* Checking if str is a register name */

bool check_register(String_t str);



/* Handle src command to the memory */

bool handle_src_in_cmd(CmdData_t* cmd_data, char* val_data_parsed, const int pos_at_file, int* program_data_img, const int l_instruct_count, SymbolNode_t** lst_symbol, ExtData_t** lst_ext_symbol, const int iter_number, char* assembly_file_name);


/* Handle dest command to the memory */

bool handle_dest_in_cmd(CmdData_t* cmd_data, char* val_data_parsed, const int pos_at_file, int* program_data_img, const int l_instruct_count, SymbolNode_t** lst_symbol, ExtData_t** lst_ext_symbol, const int iter_number, char* assembly_file_name);


/* Compiling the assembly code
 * and creating machine code by the function */

int start_compilation(String_t assembly_file_name, int iter_number, int* program_data_img, SymbolNode_t** lst_symbol, ExtData_t** lst_ext_symbol, int* instruction_counter, int* data_counter);



/* Getting the number of blocks in memory that is
 * needed for the command but it can't be data/String */

int get_num_of_mem_blocks(CmdData_t* cmd_data);



#endif
