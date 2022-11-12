/* Maman 14 - Assembler Project 2021a
   By Andrey Diskin , 20/03/2021
   File name: table_of_symbols.c */



#include <stdio.h>
#include "proj_commands.h"
#include "table_of_symbols.h"



/* Adding a new symbol to the list */


void add_new_symbol(SymbolNode_t** lst_symbol, String_t symbol, int mem, E_SYM_TYPE etype){
 SymbolNode_t* symbolNode = new_symbol_node();

/* Copying symbol name */

 strcpy(symbolNode->symbol, symbol);

/* Copying the memory address */

 symbolNode->mem = mem;

/* Copying the current symbol type  */

 symbolNode->etype = etype;

/* Setting not entry */

 symbolNode->entry_flag = false;


 if (*lst_symbol==NULL){
    
/* Setting as new symbol the table */

 *lst_symbol = symbolNode;
}

 else {
   SymbolNode_t *pPos = *lst_symbol;

/* End of the list */

 while (pPos->next_node!=NULL)
  pPos = pPos->next_node;

/* End of the list is the new symbol */

  pPos->next_node = symbolNode;

 }
}





/* Creating a new symbol node */

SymbolNode_t* new_symbol_node(){
  SymbolNode_t* pSymbolNode = (SymbolNode_t*)malloc(sizeof(SymbolNode_t));

  if(pSymbolNode==NULL){
	
/* Error if now enough memory */
   fprintf(stderr,"Error: malloc failed.");
   exit(1);
  }

/* Next pointer setted to null */

  pSymbolNode->next_node = NULL;
  return pSymbolNode;
}







/* Returns a pointer to symbol that found
 * Returns a NULL if not found */
 
 
SymbolNode_t* search_symbol(SymbolNode_t* lst_symbol, String_t symbol){
 SymbolNode_t *pPos = lst_symbol;

 while(pPos){
    
/* Comparing symbol list and synbol name that got */

 if(is_equal(pPos->symbol,symbol))
  return pPos;

  pPos = pPos->next_node;
 }
  return NULL;
}






/* Freeing the symbol table */

void free_symbol_table(SymbolNode_t** lst_symbol) {

  SymbolNode_t* next_node_tmp = NULL;
  SymbolNode_t* node = NULL;
  

/* If table of symbols is NULL */

  if (*lst_symbol==NULL) 
  return;

/* Pointer to the head of the list */

  node = *lst_symbol;
  next_node_tmp = NULL;

 while (node != NULL){
    
/* Freeing list by nodes */

 next_node_tmp = node->next_node;
 free(node);

/* Pointer to next node */

 node = next_node_tmp;

 }
 *lst_symbol = NULL;
}







