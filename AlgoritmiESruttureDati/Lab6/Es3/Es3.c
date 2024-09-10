#include <stdio.h>
#include <string.h>
#include "character.h"

#define MAX_COMMAND_LENGTH 30

typedef enum {c_stop, c_new, c_new_from_file, c_print_char} command;

command menu();
int runCommand(character **car, command c);

int main(void){
    character *car = NULL;
    int flag = 1;

    while(flag != 0){
        command c = menu();
        flag = runCommand(&car, c);
    }

    return 0;
}

command menu(){
    char command[MAX_COMMAND_LENGTH];

    printf("1. Add new characters read from a file [new char file];\n");
    printf("2. Add a new character from keyboard [new char];\n");
    printf("3. Print the list of characters [print char];\n");
    printf("4. Stop the program [stop];\n");
    printf("Insert the command you want to execute: ");
    scanf(" %s ", &command);

    if(strcmp(command, "new char file") == 0)
        return c_new_from_file;
    else if(strcmp(command, "new char") == 0)
        return c_new;
    else if(strcmp(command, "print char") == 0)
        return c_print_char;
    else if(strcmp(command, "stop") == 0)
        return c_stop;
}

int runCommand(character **car, command c){
    char filename[MAX_NAME_LENGTH];

    switch(c){
        case c_new_from_file:
            printf("Insert the name of the file from which to read the characters: ");
            scanf(" %s ", &filename);
            *car = insertFromFile(*car, filename);
            return 1;
        case c_new:
            return 1;
        case c_print_char:
            listTravR(*car);
            return 1;
        case c_stop:
            return 0;
        default:
            printf("Invalid command.\n");
    }

    return -1;
}
