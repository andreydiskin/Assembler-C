/* Maman 14 - Assembler Project 2021a
   By Andrey Diskin , 20/03/2021
   File name: assembler_action.c */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assembler_action.h"
#include "machine_types.h"
#include "proj_commands.h"


/* Macros of punctuation marks */

#define COLON ':'
#define SEMICOLON ';'
#define COMMA ','



/* Checking if letter */

bool check_letter(char c) {

  return ('a'<=c && c<='z')||('A'<= c && c<='Z');
}



/* Checking if digit */


bool check_digit(char n) {

  return '0'<=n && n<='9';

}



/* Checking if number */

int check_num(String_t val_num_as_str)
{
   int i; 
   int num_use;
   

   if (strlen(val_num_as_str)== 0) 
      return false;

   if (5< strlen(val_num_as_str)) 
      return false;

/* The first character should be sign/digit */

   if (val_num_as_str[0]!='-'&&val_num_as_str[0]!= '+' && !check_digit(val_num_as_str[0]))
      return false;

/* The other characters should be digits */
   for (i = 1; i < strlen(val_num_as_str); i++){
     if (!check_digit(val_num_as_str[i]))
      return false;
    }

/* Checking number validation */
   num_use = atoi(val_num_as_str);

   if (check_number_on_range(num_use) == false){
    return false;
}
    return true;
}


/* Getting next value for parsing*/

int get_next_value_parser(String_t assembly_code_line, String_t parsed_val, int ParseMode, bool special_flag)
{
  unsigned place_in_line = 0;
  static unsigned index = 0;
  static String_t code_line;
  
  

  if (assembly_code_line!=NULL) {
  
     code_line = assembly_code_line;
     index = 0;
   }

/* Parsing a string in quotes */

  if (ParseMode==ROW_HANDLE_STR) {

    while (true) {

/* Case if 
 *(special_flag && code_line[index]==0) */

  if (code_line[index]==0) {
     break;
    }
        

/* Case if 
 *(special_flag && code_line[index]=='\n') */

  if (code_line[index]=='\n') {
     break;
    }


/* Case if 
 *(special_flag && code_line[index]=='\"') */

  if (code_line[index]=='\"') {
     break;
    }

   parsed_val[place_in_line++] = code_line[index++];
 }
        
   parsed_val[place_in_line] = 0;

   return place_in_line;
}


/* Before val_data_parsed */

   parsed_val[place_in_line] = 0;

/* Until getting relevant data - skipping */

   while (true) {
    
  if (code_line[index]==' ') {
     index++;
     continue;

 }

  if (code_line[index]=='\n') {
     return 0;
 }


  if (code_line[index]==0) {
        
     return 0;
 }


  if (code_line[index]=='\t') {
     index++;
     continue;
 }

   break;
 }


    while (true) {
    
  if (code_line[index]==' '||code_line[index]=='\t'||code_line[index]=='\n'|| code_line[index]==0) {
     break;
  }

/* Value of String */

  if (code_line[index]=='\"'){

    if (place_in_line==0){
     parsed_val[place_in_line] = '\"';
     place_in_line++;
     index++;
     break;
    }
  }

    if (code_line[index]==COMMA){
        
     if (place_in_line==0) {
            
      parsed_val[place_in_line] = COMMA;
      place_in_line++;
      index++;
      break;
   }
      else {

      break;
   }
 }

 /* Checking for label */

   if (code_line[index]==COLON) {
     parsed_val[place_in_line] = COLON;
     place_in_line++;
     index++;
     break;
   }

/* If there is a comment in the assemberly code it should be ignored
 * so there is a checking here */

/* If it's special_flag */

    if (code_line[index]==SEMICOLON) {
        
     if (place_in_line == 0) {
       parsed_val[place_in_line] = SEMICOLON;
       place_in_line++;
       index++;
       break;
   }
 }

  parsed_val[place_in_line] = code_line[index];
  place_in_line++;
  index++;
 }

  parsed_val[place_in_line] = 0;
  return place_in_line;
}



/* Swapping the data between two variables */

void swap_data(int* a, int* b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}



/* Setting information in the memory */

void set_mem_block_func_opcode_are(int* mem_block, CmdData_t* cmd_data, E_ARE are_val) {
  *mem_block = (cmd_data->function_code<<FUNC_SHIFT)|(cmd_data->opcode_code<< OPCODE_SHIFT)|(are_val<< ARE_SHIFT);
}



/* Checking if str is a register name */

bool check_register(String_t val) {
  return (strlen(val) == 2) && (val[0]=='r') && (val[1]>='0') && (val[1]<='7');
}




/* Getting the number of blocks in memory that is
 * needed for the command but it can't be data/String */

int get_num_of_mem_blocks(CmdData_t* cmd_data) {
  return 1 + (cmd_data->src_addressing_mode!=0)+(cmd_data->dest_addressing_mode!=0);
}




/* Checking if the number is on the right range */


bool check_number_on_range(int num) {
  return MIN_NUM_VAL<= num && num<=MAX_NUM_VAL;
}




/* Checking validation of a symbol name */

bool check_lbl_symbol_is_func_machine_name(const String_t lbl_symbol) {
  String_t* arr_invalid_lbl_name = get_commands();
  int i;
  for (i=0; i<CMD_DATA_SIZE; i++){
   if (is_equal(arr_invalid_lbl_name[i], lbl_symbol))
    return false;
  }
    return !check_register(lbl_symbol);
}




/* Setting ARE to the memory */


void set_are(int* mem, const E_ARE eare_val) {
  *mem = (eare_val<<ARE_SHIFT);
}







/* Handling the relevant operand  */

int handle_operand(const int pos_at_file, E_OPER_HANDLER eoper_handler, String_t val, int* program_data_img, int mem_inst_counter, CmdData_t* cmd_data,SymbolNode_t* lst_symbol,  ExtData_t** lst_ext_symbol,int iter_number,String_t fn) {

     int delta;
     int place_at = (eoper_handler==OPER_HANDLER_SRC) ? 2 : 0;
     int operands_to_use = (eoper_handler==OPER_HANDLER_SRC) ? cmd_data->src_addressing_mode : cmd_data->dest_addressing_mode;
    String_t operand_str = (eoper_handler==OPER_HANDLER_SRC) ? "src" : "dest";
    
    

  if ((eoper_handler==OPER_HANDLER_SRC)||(cmd_data->src_addressing_mode==0)) {
    delta = 1;
 }

  else {
    delta = 2;
 }

  if (val[0]=='#') {
   if ((operands_to_use & B_IMMED)==0) {
   fprintf(stderr, "%s operand is not valid - command \'%s\' cannot use immediate addressing mode - line %d\n", operand_str, cmd_data->cmd_name, pos_at_file);
   return -1;  
 }

   if (!check_num(&val[1])){
     fprintf(stderr, "\'%s\' is not a number. - line %d\n",&val[1], pos_at_file);
     return -1; 
 }

  program_data_img[mem_inst_counter] |= (ADDRESSING_MODE_IMMEDIATE<<place_at);
  program_data_img[mem_inst_counter+delta] = (atoi(&val[1]) & 0xfff)|(ARE_A<<ARE_SHIFT);
}  

  else if (check_register(val)) {
    if ((operands_to_use & B_REGIS)==0){
      fprintf(stderr, "%s operand is not valid - command \'%s\' cannot use register addressing mode - line %d\n", operand_str, cmd_data->cmd_name, pos_at_file);
      return -1; 
 }

  program_data_img[mem_inst_counter] |= (ADDRESSING_MODE_REG<<place_at);
  program_data_img[mem_inst_counter + delta] = (1<<(val[1] - '0')) | (ARE_A<<ARE_SHIFT);
}

    else if (val[0]=='%') {
      if ((operands_to_use & B_RELAT)==0) {
       fprintf(stderr, "%s operand is not valid - command \'%s\' cannot use relative addressing mode - line %d\n", operand_str, cmd_data->cmd_name, pos_at_file);
       return -1;  
  }

    program_data_img[mem_inst_counter] |= (ADDRESSING_MODE_RELATIVE<<place_at);
      if (iter_number==ITER_LVL_1) {
        program_data_img[mem_inst_counter + delta] = 0;
    }
      else {
/* Searching symbol on lst */

     SymbolNode_t* node = search_symbol(lst_symbol, &val[1]);
      if (!node) {
/* If the symbol not exist */

      fprintf(stderr, "The symbol \'%s\' has not defined - line %d\n", &val[1], pos_at_file);
      return -1;       
  }

      if (node->etype != SYM_TYPE_CODE){
       fprintf(stderr, "your code is trying to use a relative addressing mode on extern symbol - line %d\n", pos_at_file);
       return -1;  
  }

  program_data_img[mem_inst_counter + delta] = ((node->mem - (mem_inst_counter + 1))&0xfff)|(ARE_A << ARE_SHIFT);
  }
}

/* Handling the direct addressing mode */

    else {
     if ((operands_to_use & B_DIREC)==0){
      fprintf(stderr, "%s operand is not valid - command \'%s\' cannot use direct addressing mode - line %d\n", operand_str, cmd_data->cmd_name, pos_at_file);
      return -1;  
  }

/* Setting a new value */

  program_data_img[mem_inst_counter] |= (ADDRESSING_MODE_DIRECT<<place_at);

/* Adding an additional word */

  if (iter_number==ITER_LVL_1){
  program_data_img[mem_inst_counter + delta] = 0;
 }
   else { 
    
/* Looking for a symbol on lst_symbol
 * to get its address */

  SymbolNode_t* node = search_symbol(lst_symbol, val);

  if (!node) {
     fprintf(stderr, "The symbol \'%s\' has not defined - line %d\n", val, pos_at_file);
     return -1;       
  }
   program_data_img[mem_inst_counter + delta] = (node->mem & 0xfff) | (ARE_R << ARE_SHIFT);
  if (iter_number == ITER_LVL_2 && node->etype == SYM_TYPE_EXT){
    add_new_ext_symbol_node_list(lst_ext_symbol, node->symbol, mem_inst_counter + delta);
    program_data_img[mem_inst_counter + delta] = (ARE_E << ARE_SHIFT);
   }
  }
 }
 return 0;
}





/* Compiling the assembly code
 * and creating machine code by the function */

int start_compilation(String_t assembly_file_name, int iter_number, int* program_data_img, SymbolNode_t** lst_symbol, ExtData_t** lst_ext_symbol, int* instruction_counter, int* data_counter) {
  
  int mem_space_needed;
  int l_data_instruc = *instruction_counter;
  int l_instruct_count = PROGRAM_ADDRESS;
  int pos_at_file = 0;
  int status_flag = STATUS_FLAG_SUCCESS;
  FILE *file_as;
  char assembly_code[255];
  char val_data_parsed[MAX_BUFF_LINE_LENGTH + 1];
  CmdData_t* cmd_data;

  
 if(iter_number==ITER_LVL_1){
  fprintf(stdout,"\n%s\n===============================\n", assembly_file_name);
 }

/* Access to the assembly file */

 file_as = fopen(assembly_file_name, "r");

 if (file_as == NULL){
  fprintf(stderr, "The file %s not found (skipping into the next file).\n",assembly_file_name);
  return -1;
 }
    
 if (iter_number==ITER_LVL_1){
  fprintf(stdout,"Starting to compile ..\n");
 }

/* Reading the assembly code lines 
 * by steps */

 while(fgets(assembly_code, sizeof(assembly_code), file_as)) {

  bool lbl_exist = false;
  int val_data_parsed_length;
  char lbl_symbol_name[MAX_BUFF_LINE_LENGTH+1];

 pos_at_file++;

/* Check validation of the length */

 if (strlen(assembly_code)>MAX_BUFF_LINE_LENGTH){
  fprintf(stderr, "Invalid line because line is longer than maximum - line %d\n",pos_at_file);
  status_flag = STATUS_FLAG_ERROR;
  continue;
}

val_data_parsed_length = get_next_value_parser(assembly_code, val_data_parsed, ROW_HANDLE_REGULAR,false); 

/* Should ignore if empty*/

 if (val_data_parsed[0]==0){
  continue;
}

/* Should ignore the comments */

 if (is_equal(val_data_parsed,";")){
  continue;
}

 if (val_data_parsed[val_data_parsed_length-1]==COLON){

/* Handling the label */

 if (iter_number == ITER_LVL_1){

/* Copying the name of the label
 */

  strcpy(lbl_symbol_name, val_data_parsed);
  lbl_symbol_name[val_data_parsed_length-1] = 0;

/* Setting the flag for indication */

  lbl_exist = true;

/* Checking if the lbl lenght is valid */

 if (!check_symbol(lbl_symbol_name)){
   fprintf(stderr, "The label \'%s\' is invalid - line %d\n", lbl_symbol_name, pos_at_file);
   status_flag = STATUS_FLAG_ERROR;
   continue;
}

/* Searching this in symbol lst 
 * and if exist in the symbol lst so it's duplicated */

  if (search_symbol(*lst_symbol,lbl_symbol_name)){
   fprintf(stderr, "Symbol \'%s\' has already defined - line %d.\n", lbl_symbol_name, pos_at_file);
   status_flag = STATUS_FLAG_ERROR;
   continue;
 }
}

/* Parsing the next val */

   val_data_parsed_length = get_next_value_parser(NULL,val_data_parsed, ROW_HANDLE_REGULAR,true);
}
 
/* Handling a String line */

  if (is_equal(val_data_parsed,".string")){
   if (lbl_exist){

/* Adding a new symbol to lst symbol */

   add_new_symbol(lst_symbol,lbl_symbol_name,l_data_instruc,SYM_TYPE_DATA);
 }

   get_next_value_parser(NULL,val_data_parsed,ROW_HANDLE_REGULAR, false);

  if (!is_equal(val_data_parsed, "\"")){
     fprintf(stderr, "string should start with \" - line %d\n", pos_at_file);
     status_flag = STATUS_FLAG_ERROR;
     continue;
 }

   val_data_parsed_length = get_next_value_parser(NULL,val_data_parsed,ROW_HANDLE_STR,false);
  
  if (iter_number==ITER_LVL_2){
   int i;

    for (i = 0; i < val_data_parsed_length + 1; i++)
     program_data_img[l_data_instruc+i] = (val_data_parsed[i]&0xfff)|(ARE_A<<ARE_SHIFT);
  }

    get_next_value_parser(NULL,val_data_parsed, ROW_HANDLE_REGULAR,true);

  if (!is_equal(val_data_parsed, "\"")){
    fprintf(stderr, "string should end with \" - line %d\n", pos_at_file);
    status_flag = STATUS_FLAG_ERROR;
    continue;
 }
            
    get_next_value_parser(NULL,val_data_parsed,ROW_HANDLE_REGULAR,true);

  if (val_data_parsed[0]!=0){
     fprintf(stderr, "too many parameters \'%s\' - line %d\n",val_data_parsed,pos_at_file);
     status_flag = STATUS_FLAG_ERROR;
     continue;
 }
            
     l_data_instruc += val_data_parsed_length + 1;
     continue;
 }       
       
/* Handling a data row line */

 if (is_equal(val_data_parsed,".data")){
  bool status_loop = true;

 if (lbl_exist && iter_number == ITER_LVL_1){
  add_new_symbol(lst_symbol,lbl_symbol_name, l_data_instruc,SYM_TYPE_DATA);
 }

 while (status_loop){           	
/* Parsing next val */

  get_next_value_parser(NULL,val_data_parsed,ROW_HANDLE_REGULAR,false);

/* If it's a number */

 if (val_data_parsed[0]==0){
  fprintf(stderr, "number is missing - line %d.\n", pos_at_file);
  status_flag = STATUS_FLAG_ERROR;
  status_loop = false;
 }

 if(status_loop){
  if (check_num(val_data_parsed)==false){
   fprintf(stderr,"should get a number but got \'%s\' - line %d\n", val_data_parsed,pos_at_file);

   status_flag = STATUS_FLAG_ERROR;
   status_loop = false;
 }

  if(status_loop){
   if (iter_number==ITER_LVL_2){

/* Adding data to program_data_img */

  program_data_img[l_data_instruc]=(atoi(val_data_parsed)&0xfff)|(ARE_A<<ARE_SHIFT);

}

  l_data_instruc++;
  get_next_value_parser(NULL,val_data_parsed,ROW_HANDLE_REGULAR,false);
						
  if (val_data_parsed[0]==0){
   status_loop = false;
  }

  else if (is_equal(val_data_parsed,",")){

/* Getting next number */

}
  else {

   fprintf(stderr,"looking for \'%s\' - line %d\n",val_data_parsed, pos_at_file);
   status_flag = STATUS_FLAG_ERROR;
   status_loop = false;
   }
  }
 }
}
   continue;
}


/* Handling Entry */

  if (is_equal(val_data_parsed, CMD_ENTRY)){
   SymbolNode_t* data_node = NULL;

  if (iter_number==ITER_LVL_1){
   continue;
}

/* Getting the name of the symbol */

  get_next_value_parser(NULL,val_data_parsed,ROW_HANDLE_REGULAR,false);

/* Searching val_data_parsed
 * the symbol in lst_symbol */

  data_node = search_symbol(*lst_symbol,val_data_parsed);

  if (!data_node){
    fprintf(stderr,"cannot find symbol \'%s\' - line %d\n",val_data_parsed,pos_at_file);
    status_flag = STATUS_FLAG_ERROR;
    continue;
  }


   if (data_node->etype==SYM_TYPE_EXT){
    fprintf(stderr,"error on symbol \'%s\' - defined as entry and as extern. - line %d\n", val_data_parsed, pos_at_file);
    status_flag = STATUS_FLAG_ERROR;
    continue;      
  }
    data_node->entry_flag = true;
    continue;
 }

/* Handling Extern */

   if (is_equal(val_data_parsed,CMD_EXTERN)){
    SymbolNode_t* data_node = NULL;
    get_next_value_parser(NULL, val_data_parsed,ROW_HANDLE_REGULAR,false);

/* Checking symbol */

   if (!check_symbol(val_data_parsed)){
     fprintf(stderr, "\'%s\' is not a valid symbol - line %d\n", val_data_parsed,pos_at_file);
     status_flag = STATUS_FLAG_ERROR;
     continue;
  }

/* If a symbol exists already */

     data_node = search_symbol(*lst_symbol,val_data_parsed);

   if (data_node){
     if (data_node->etype!=SYM_TYPE_EXT){
     fprintf(stderr, "symbol \'%s\' already exists as relocatable - line %d\n",val_data_parsed,pos_at_file);
     status_flag = STATUS_FLAG_ERROR;
     continue;
   }
 }

    else {
            
/* Adding the symbol to lst if all fine */

     add_new_symbol(lst_symbol,val_data_parsed,0,SYM_TYPE_EXT);
  }

     get_next_value_parser(NULL,val_data_parsed,ROW_HANDLE_REGULAR,false);

    if (val_data_parsed[0]!=0){
       fprintf(stderr,"too many parameters \'%s\' - line %d\n",val_data_parsed,pos_at_file);
       status_flag = STATUS_FLAG_ERROR;
       continue;
     }
       continue;
   }

/* Adding a label if necessery */

    if (lbl_exist){
     add_new_symbol(lst_symbol,lbl_symbol_name,l_instruct_count,SYM_TYPE_CODE);
   }
       cmd_data = get_command_full_info(val_data_parsed);

     if (!cmd_data){
       fprintf(stderr,"unknown command \'%s\' - line %d\n",val_data_parsed,pos_at_file);
       status_flag = STATUS_FLAG_ERROR;
       continue; 
   }

/* Setting the data in the memory */

    set_mem_block_func_opcode_are(program_data_img + l_instruct_count, cmd_data, ARE_A);
    mem_space_needed = get_num_of_mem_blocks(cmd_data);

    if (!handle_src_in_cmd(cmd_data, val_data_parsed, pos_at_file, program_data_img,l_instruct_count,lst_symbol, lst_ext_symbol,iter_number,assembly_file_name)){
		
    status_flag = STATUS_FLAG_ERROR;
    continue;
  }

    if (!handle_dest_in_cmd(cmd_data, val_data_parsed,pos_at_file,program_data_img,l_instruct_count,lst_symbol, lst_ext_symbol,iter_number,assembly_file_name)){
		
    status_flag = STATUS_FLAG_ERROR;
    continue;
  }

/* Increase the l_instruct_count */

    mem_space_needed = get_num_of_mem_blocks(cmd_data);
    l_instruct_count += mem_space_needed;
    get_next_value_parser(NULL,val_data_parsed,ROW_HANDLE_REGULAR,false);

    if (val_data_parsed[0]!=0){
      fprintf(stderr, "too many parameters \'%s\' - line %d\n",val_data_parsed,pos_at_file);
      status_flag = STATUS_FLAG_ERROR;
      continue;
    }
  }

    if (iter_number==ITER_LVL_1){
     SymbolNode_t* node = *lst_symbol;

     while (node){
        
      if (node->etype==SYM_TYPE_DATA)
        node->mem += l_instruct_count;
        node = node->next_node;
      }
    }

    *instruction_counter = l_instruct_count;
    *data_counter = l_data_instruc;

    return status_flag;
}


/* Handle dest command to the memory */

bool handle_dest_in_cmd(CmdData_t* cmd_data, char* val_data_parsed, const int pos_at_file, int* program_data_img, const int l_instruct_count, SymbolNode_t** lst_symbol, ExtData_t** lst_ext_symbol, const int iter_number, char* assembly_file_name){

/* Checking if needed */

  if (cmd_data->dest_addressing_mode!=0){
	
/* Getting an operand */

  get_next_value_parser(NULL,val_data_parsed,ROW_HANDLE_REGULAR,false);

  if (val_data_parsed[0]==0){
   fprintf(stderr,"missing destination operand - line %d\n", pos_at_file);
   return false;
  }
		
  if (handle_operand(pos_at_file,OPER_HANDLER_DST,val_data_parsed,program_data_img,l_instruct_count,cmd_data, *lst_symbol,lst_ext_symbol,iter_number,assembly_file_name)==-1){
   return false;
  }
 }

    return true;
 }




/* Checking symbol */

int check_symbol(String_t lbl_symbol_name){

  int i;
  int lbl_symbol_length = strlen(lbl_symbol_name);
  

/* If not empty */

  if (lbl_symbol_length==0||lbl_symbol_length>MAX_LBL_SIZE) 
   return false;

/* If the first character
 * isn't a letter so there is an error */

  if (!check_letter(lbl_symbol_name[0]))
   return false;

/* Checking chars with problems */

  for (i = 1; i < lbl_symbol_length; i++){
   if (check_digit(lbl_symbol_name[i])==false&&check_letter(lbl_symbol_name[i])==false){
     return false;
   }
  }

/* Checking symbol lbl_symbol_name 
 * if it's a name of a machine functionality */

   if (check_lbl_symbol_is_func_machine_name(lbl_symbol_name)==false){
    return false;
   }

    return true;
 }



/* Handle src command to the memory */

bool handle_src_in_cmd(CmdData_t* cmd_data, char* val_data_parsed, const int pos_at_file, int* program_data_img, const int l_instruct_count, SymbolNode_t** lst_symbol, ExtData_t** lst_ext_symbol, const int iter_number, char* assembly_file_name){

/* Checking if needed */

   if (cmd_data->src_addressing_mode!=0){
    get_next_value_parser(NULL, val_data_parsed,ROW_HANDLE_REGULAR,false);

   if (val_data_parsed[0]==0){
    fprintf(stderr, "missing source operand - line %d\n", pos_at_file);
    return false;            
  }

/* Starting handle the operand */

   if (handle_operand(pos_at_file,OPER_HANDLER_SRC,val_data_parsed,program_data_img,l_instruct_count,cmd_data, *lst_symbol,lst_ext_symbol,iter_number,assembly_file_name)==-1){
    return false;
  }

    get_next_value_parser(NULL,val_data_parsed,ROW_HANDLE_REGULAR,false);

   if (!is_equal(val_data_parsed,",")){
    fprintf(stderr, "command \'%s\' must have source and dest operands - line %d\n", cmd_data->cmd_name, pos_at_file);
    return false;
   }
  }
    return true;
 }





