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
  char cwd[1000];
  getcwd(cwd, sizeof(cwd));
  int i = 0;
  while(cwd[i] != '\0')
  {
    i++;

  }
  cwd[i] = '$';
  cwd[i+1] = ' '; 
  cwd[i+2] = '\0';
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
TRIMSPACE: removes extra white space from inside and 
            around a given string
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

/*******************************************************
PARSEPIPE: Splits the input on "|" and performes proper
            redirection, passing commands to individual
            forked processes for execution
Takes as input: input string
Returns: none
*******************************************************/

void parsePipe(char *line){ 
  char *line2 = (char *)malloc(256);
  line2 = strsep(&line, "|");
  line2 = trimSpace(line2); 
  line = trimSpace(line);
  int fs[2];
  pipe(fs);
  int f1 = dup(STDOUT_FILENO);
  int f2 = dup(STDIN_FILENO);
  int stat;
  int pid = fork();
  if (pid == 0){
    close(fs[0]); 
    dup2(fs[1], STDOUT_FILENO); 
    close(fs[0]);
    execute(line2);
    exit(0);
  }
  else{
    wait(&stat);
    dup2(fs[0], STDIN_FILENO);
    close(fs[1]);
    execute(line);
    dup2(f2, STDIN_FILENO);
  }
  //free(line2);
}
