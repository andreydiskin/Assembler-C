/* Maman 14 - Assembler Project 2021a
   By Andrey Diskin , 20/03/2021
   File name: table_of_symbols.h */



#include <stdlib.h>
#include <string.h>
#include "machine_types.h"

#ifndef _TABLE_OF_SYMBOLS_H_
#define _TABLE_OF_SYMBOLS_H_




/* Symbol node structure */

 typedef struct SymbolNode_t {

/* Symbol */

 char symbol[MAX_LBL_SIZE+1];

/* Memory */

 int mem;

/* Type of the symbol */

 E_SYM_TYPE etype;

/* Entry flag with indicating boolean value */

 bool entry_flag;

/* Next node */

 struct SymbolNode_t* next_node;
}

 SymbolNode_t;





/* Adding a new symbol to the list */

void add_new_symbol(SymbolNode_t** lst_symbol, String_t symbol, int mem, E_SYM_TYPE etype);



/* Creating a new symbol node */

SymbolNode_t* new_symbol_node();



/* Returns a pointer to symbol that found
 * Returns a NULL if not found */

SymbolNode_t *search_symbol(SymbolNode_t* lst_symbol, String_t symbol);



/* Freeing the symbol table */

void free_symbol_table(SymbolNode_t** lst_symbol);




#endif
