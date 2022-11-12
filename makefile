OBJECTS = the_project.o proj_commands.o assembler_action.o table_of_symbols.o extern_table.o creation_of_files.o
HEADERS = assembler_action.h machine_types.h proj_commands.h table_of_symbols.h extern_table.h creation_of_files.h
CFLAGS  = -Wall -ansi -pedantic

assembler: $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) -o $@

#create *.o files
%.o: %.c $(HEADERS)
	gcc $(CFLAGS) -c $< -o $@

#clean *.o files	
clean:
	rm -f *.o
	rm -f assembler

                                                                                                                 
              
