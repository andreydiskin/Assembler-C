/* Maman 14 - Assembler Project 2021a
   By Andrey Diskin , 20/03/2021
   File name: proj_commands.c */



 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include "proj_commands.h"



/* Checking if two strings are equal or not equal */

bool is_equal(const String_t str1, const String_t str2){
   return strcmp(str1, str2)==0;
 }



/* Returns an array with all the commands */

String_t* get_commands(){

 static String_t arr[] = {
/* Names of the commands */
 CMD_MOV, 
 CMD_CMP, 
 CMD_ADD, 
 CMD_SUB,
 CMD_LEA, 
 CMD_CLR, 
 CMD_NOT, 
 CMD_INC,
 CMD_DEC, 
 CMD_JMP, 
 CMD_BNE, 
 CMD_JSR,
 CMD_RED, 
 CMD_PRN, 
 CMD_RTS, 
 CMD_STOP
 };
 return arr;
}








/* Returns the operation code value of command
 * Returns -1 if not found the opcode */


int get_command_opcode_val(String_t cmd_name){
  CmdData_t* data_cmd = get_command_full_info(cmd_name);
 if(data_cmd==NULL)
  return -1;
	
  return data_cmd->opcode_code;
}





/* Identifying the needed command */


bool identify_command(const String_t cmd) {

  CmdData_t* data = get_command_full_info(cmd);

  if(data==NULL){
   fprintf(stderr, "Unknown command \'%s\'\n", cmd);
   return false;
  }
   return true;
 }






/* Returns the func value of command
 * Returns -1 if not found the func value */



int get_command_func_val(String_t cmd_name){
  CmdData_t* data_cmd = get_command_full_info(cmd_name);
  if(data_cmd==NULL)
   return -1;
	
   return data_cmd->function_code;
 }



/* Command info search received the name of command */


CmdData_t *get_command_full_info(String_t cmd){

  static CmdData_t cmd_data[] = {
   {
    CMD_MOV,
    0,
    0,
    B_IMMED | B_DIREC | B_REGIS, 
    B_DIREC | B_REGIS 
   },

   {
    CMD_CMP, 
    1, 
    0, 
    B_IMMED | B_DIREC | B_REGIS, 
    B_DIREC | B_IMMED | B_REGIS 
   },

   {
    CMD_ADD,
    2, 
    10,	
    B_IMMED | B_DIREC | B_REGIS, 
    B_DIREC | B_REGIS
   },

   {
    CMD_SUB,
    2, 
    11, 
    B_IMMED | B_DIREC | B_REGIS, 
    B_DIREC | B_REGIS
   },

   {
    CMD_LEA,
    4, 
    0, B_DIREC, 
    B_DIREC | B_REGIS
   },

   {
    CMD_CLR,
    5, 
    10,
    0,
    B_DIREC | B_REGIS
   },

   {
    CMD_NOT,
    5,
    11,
    0,
    B_DIREC | B_REGIS
   },

   {
    CMD_INC,
    5,
    12,
    0,
    B_DIREC | B_REGIS
   },

   {
    CMD_DEC, 
    5, 
    13, 
    0, 
    B_DIREC | B_REGIS
   },

   {
    CMD_JMP,
    9, 
    10, 
    0, 
    B_DIREC | B_RELAT
   },

   {
    CMD_BNE, 
    9, 
    11, 
    0, 
    B_DIREC | B_RELAT
   },

   {
    CMD_JSR, 
    9, 
    12, 
    0, 
    B_DIREC | B_RELAT
   },

   {
    CMD_RED, 
    12, 
    0, 
    0, 
    B_DIREC | B_REGIS 
   },

   {
    CMD_PRN, 
    13, 
    0, 
    0,
    B_IMMED | B_DIREC | B_REGIS 
   },

   {
    CMD_RTS, 
    14, 
    0, 
    0, 
    0
   },

   {
    CMD_STOP, 
    15, 
    0, 
    0, 
    0 
   }
  };

 int i;

 for (i = 0; i < CMD_DATA_SIZE; i++){
   if (is_equal(cmd_data[i].cmd_name, cmd))
    return &cmd_data[i];
    } 
    return NULL;
}




