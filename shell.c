#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "shell.h"

/*******************************************************
PROMPT: prints current dir and delimiter 
Takes as input: none
Returns: none
*******************************************************/

void prompt() {
  char cwd[256];
  getcwd(cwd, sizeof(cwd));
  printf("%s", cwd);
  printf("$ ");
}

/*******************************************************
SPLIT: splits str on delimiter 
Takes as input: input string, delimiter
Returns: array of pointers to strings
*******************************************************/
 
char ** split( char * line, char * delimiter ) {
  char ** ret = (char **) malloc (1000);
  int i = 0;
  char * input = malloc(256);
  input = line;
  while ( input != NULL ) {
    ret[i] = strsep( &input, delimiter );
    ret[i] = trimSpace(ret[i]);
    i++;
  }
  ret[i] = NULL;
  return ret;
}

/*******************************************************
TRIMSPACE: removes extra white space from a given string
Takes as input: input string
Returns: output string
*******************************************************/

char * trimSpace(char *str){
    char *end;
 
    while(isspace(*str)){
      str++;
    }
    if(*str == 0)
        return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace(*end)){
      end--;
    }
    *(end+1) = 0;
    return str;
}

/*******************************************************
EXECUTE: forks child that executes cmd, waits for child
Takes as input: *args is array of char pointers
                args[0] = cmd, args[1]...args[n] = rest
                (kind of like linked list)
Returns: 1 if successful, 0 otherwise
*******************************************************/
int execute( char *args[] ) { 
  if ( !(strcmp(args[0], "exit")) ) {
    printf("Exiting SeaShell...\n");
    exit(0);
  }

  if ( !(strcmp(args[0], "cd" )) ) {
    printf("Changing directory...\n");
    if (args[1] == NULL || args[1] == "fts_open" ){
      chdir(getenv("HOME"));
    }
    else {
      chdir(args[1]);
    }
    return 0;
  }

  int pid = fork();

  if (pid == -1) {
    char *error = strerror(errno);
    printf("Process Error: %s\n", error);
    return 0;
  }
    
  else if (pid == 0) {
    execvp(args[0], args);
    char * error = strerror(errno);
    printf("Command Error for %s: %s\n", args[0], error);
    return 0;
  }

  else {
    int cstat;
    waitpid(pid, &cstat, 0);
    return 1;
  }
  return 1;
}

      



