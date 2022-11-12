/* Maman 14 - Assembler Project 2021a
   By Andrey Diskin , 20/03/2021
   File name: extern_table.c */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern_table.h"




/* Adding new symbol to extern symbol list 
 * it added as new node to list */

void add_new_ext_symbol_node_list(ExtData_t** lst_ext_symbol, String_t symbol, int mem_location){

 ExtData_t *ext_node = malloc(sizeof(ExtData_t));

 strcpy(ext_node->symbol, symbol);

 ext_node->mem = mem_location;
 ext_node->Next = NULL;


  if (*lst_ext_symbol==NULL){
  *lst_ext_symbol = ext_node;
 }

  else {

   ExtData_t *pPos = *lst_ext_symbol;

  while (pPos->Next!=NULL)
   pPos = pPos->Next;

   pPos->Next = ext_node;
  }
 }




/* Freeing extern list with all data/nodes that it has */

void free_ext_lst(ExtData_t** lst_ext_symbol){


  ExtData_t* Next;
  ExtData_t* pPos;
  

 if (*lst_ext_symbol==NULL) 
  return;

  pPos = *lst_ext_symbol;
  Next = NULL;


  while (pPos!=NULL){
   Next = pPos->Next;


/* Freeing the node */

   free(pPos);
   pPos = Next;
 }

 *lst_ext_symbol = NULL;
}
