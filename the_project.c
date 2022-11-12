/* Maman 14 - Assembler Project 2021a
   By Andrey Diskin , 20/03/2021
   File name: the_project.c */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "creation_of_files.h"
#include "assembler_action.h"



/* Freeing the list */

void free_list(SymbolNode_t** lst_symbol, ExtData_t** lst_ext_symbol){
  free_symbol_table(lst_symbol);
  free_ext_lst(lst_ext_symbol);
 }



int main(int argc, char *argv[]){

/* Symbol List */

 SymbolNode_t* lst_symbol=NULL;

/* Extern list */

 ExtData_t* lst_ext_symbol=NULL;

/* Assembler file */

 int i;
 char assembly_path[MAX_READ_BUFF];

/* Checking minimum number
 * of parameters */

 if(argc < 2){
  fprintf(stderr, "Invalid command to run assembler program.\n");
  exit(0);
 }



/* Working on each assembly file */

  for(i = 1;i < argc;++i){
    
/* Memory array */

 bool flag_ok = true;
 int j=0;
 int program_data_img[MEM_MAX_SIZE];
 int instruction_counter = 0, data_counter = 0;

/* Initial data and list */

  sprintf(assembly_path,"%s.as",argv[i]);
  free_list(&lst_symbol,&lst_ext_symbol);

 for(j=0; j<2; j++){
  int select_iter = (j == 0 ? ITER_LVL_1 : ITER_LVL_2);

 if (start_compilation(assembly_path, select_iter, program_data_img, &lst_symbol, &lst_ext_symbol, &instruction_counter, &data_counter)==-1){
  fprintf(stderr, "FAILED\n");
  flag_ok = false;
  break;
 }
}

 if(flag_ok==false){
		
/* Going to the next assembly file and stopping the current */

 continue;
}

/* Creating object file */

 generate_ob_file_output(argv[i],program_data_img, instruction_counter, data_counter);

/* Create externals file */

 generate_ext_file_output(argv[i],lst_ext_symbol);

/* Create entries file */

 generate_ent_file_output(argv[i],lst_symbol);

 fprintf(stdout, "SUCCESS\n");
}
  free_list(&lst_symbol, &lst_ext_symbol);
  return 0;
}

