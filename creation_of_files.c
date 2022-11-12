/* Maman 14 - Assembler Project 2021a
   By Andrey Diskin , 20/03/2021
   File name: creation_of_files.c */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "machine_types.h"
#include "proj_commands.h"
#include "creation_of_files.h"


/* Creating the entries file output */

void generate_ent_file_output (const String_t assembly_path,SymbolNode_t* lst_symbol){
 
 char file_ent_name[MAX_READ_BUFF];
 SymbolNode_t* pNode;
 FILE *fp = NULL;

 sprintf(file_ent_name, "%s.ent",assembly_path);
 pNode = lst_symbol;

  while (pNode){
   if (pNode->entry_flag){
        
/* If used */

   if (fp==NULL){
    fp = fopen(file_ent_name,"w");
  }
    fprintf(fp, "%s %04d\n",pNode->symbol,pNode->mem);
 }
    pNode = pNode->next_node;
}
   if(fp) { fclose(fp); }
}


/* Creating the externals file output */

void generate_ext_file_output (const String_t assembly_path,ExtData_t* lst_ext_symbol){

  char file_ext_name[MAX_READ_BUFF];
  ExtData_t* node;
  FILE *fp;


  sprintf(file_ext_name,"%s.ext",assembly_path);

/* Empty if if no externals */

  if (lst_ext_symbol==NULL)
   return;

   fp = fopen(file_ext_name,"w");
   node = lst_ext_symbol;

  while (node){
    
/* Create name address line */

  fprintf(fp, "%s %04d\n",node->symbol, node->mem);
  node = node->Next;
 }
  fclose(fp);
}





/* Creating the object file output */


void generate_ob_file_output (const String_t assembly_path,int *program_data_img,int instruction_counter,int data_counter) {

  char file_ob_name[MAX_READ_BUFF];
  FILE *fp;
  int i;
  

  sprintf(file_ob_name, "%s.ob",assembly_path);

/* File opening */

  fp = fopen(file_ob_name,"w");

  if(fp==NULL){
    fprintf(stderr,"failed to create %s file\n",file_ob_name);
    exit(1);
  }

   fprintf(fp,"%d %d\n",instruction_counter - PROGRAM_ADDRESS, data_counter - instruction_counter);
    
  for (i = PROGRAM_ADDRESS; i < data_counter; i++){
    int val = (program_data_img[i] >> ARE_SHIFT) & ARE_LOCATION;
    char c_are_result = 0;

    fprintf(fp, "%04d %03X ", i,program_data_img[i] & 0xfff);

  if(val==ARE_A){
   c_are_result = ARE_A_STR;
  }

  else if(val==ARE_R){
    c_are_result = ARE_R_STR;
  }

  else if(val==ARE_E){
    c_are_result = ARE_E_STR;
  }
   fprintf(fp, "%c\n",c_are_result);
 }
    
   fclose(fp);
}










