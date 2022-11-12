/* Maman 14 - Assembler Project 2021a
   By Andrey Diskin , 20/03/2021
   File name: creation_of_files.h */

#include "extern_table.h"
#include "table_of_symbols.h"

/* Macros */

#ifndef _CREATION_OF_FILES_H
#define ARE_LOCATION 0x3
#define _CREATION_OF_FILES_H


void generate_ent_file_output (const String_t assembly_path,SymbolNode_t* lst_symbol);


void generate_ext_file_output (const String_t assembly_path,ExtData_t* lst_ext_symbol);


void generate_ob_file_output (const String_t assembly_path,int* program_data_img,int instruction_counter,int data_counter);





#endif
