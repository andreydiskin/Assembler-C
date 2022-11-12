/* Maman 14 - Assembler Project 2021a
   By Andrey Diskin , 20/03/2021
   File name: extern_table.h */



#include "machine_types.h"

#ifndef _EXTERN_TABLE_
#define _EXTERN_TABLE_



/* Linken-list of node of exteren data */

typedef struct ExtData_t {



/* Symbol name */

 char symbol[MAX_LBL_SIZE+1];



/* Symbol address */

  int mem;


/* Pointer to the next symbol */

  struct ExtData_t *Next;

 } 

  ExtData_t;



/* Adding new symbol to extern symbol list 
 * it added as new node to list */

void add_new_ext_symbol_node_list(ExtData_t** lst_ext_symbol, String_t symbol, int mem_location);


/* Freeing extern list with all data/nodes that it has */	
	
void free_ext_lst(ExtData_t** lst_ext_symbol);	

#endif
