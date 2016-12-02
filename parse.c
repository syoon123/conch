#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "parse.h"
#include "shell.h"

/*******************************************************
PROMPT: returns current dir and delimiter for prompt
Takes as input: none
Returns: char array containing the prompt and delimiter
*******************************************************/

char * prompt() {
  static char cwd[1000];
  getcwd(cwd, sizeof(cwd));
  int i = 0;
  while(cwd[i] != '\0')
    i++;
  cwd[i] = '$';
  cwd[i+1] = ' '; 
  cwd[i+2] = '\0';
  // char *pcwd = &cwd[0];
  // pcwd = strrchr(pcwd, '/'); //single file path, decided not to include
  // pcwd = pcwd + 1;
  return cwd;
}

/*******************************************************
SPLIT: splits str on delimiter 
Takes as input: input string, delimiter
Returns: array of pointers to strings
*******************************************************/

char ** split(char *line, char *delimiter) {
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
TRIMSPACE: removes extra white space from around a given 
           string
Takes as input: input string
Returns: "trimmed" output string
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
PARSE: Handles parsing multiple commands and passes 
        them to check for redirection or piping
Takes as input: input string
Returns: none
*******************************************************/

void parse(char *line){
  char * line2 = (char *) malloc (256);
  line2 = strsep(&line, ";");
  if (line){
    checkRP(line2);
    checkRP(line);
  }
  else {
    checkRP(line2);
  }
  free(line2);
}


