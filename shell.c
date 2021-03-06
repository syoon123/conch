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
CHECKRP: Checks input string from terminal for redirects
          piping, or other necessary markers and passes 
          to other functions to handle accordingly
Takes as input: input string
Returns: none
*******************************************************/

void checkRP(char *line){
  if (strstr(line, ">>")){
    rightDoubleRedir(line);
  } 
  else if (strstr(line, "2>")){
    twoRedir(line);
  }
  else if (strstr(line, "&>")){
    ampRedir(line);
  }
  else if (strchr(line, '>')){
    rightRedir(line);
  }
  else if (strchr(line, '<')){
    leftRedir(line);
  }
  else if (strchr(line, '|')){
    parsePipe(line);
  }
  else {
    execute(line);
  }
}

/*******************************************************
LEFTREDIR: Splits the input on "<" and performes the
            proper redirection before passing the
            command for execution
Takes as input: input string
Returns: none
*******************************************************/

void leftRedir(char *line){
  char * line2 = (char *)malloc(256);
  line2 = strsep(&line , "<");
  line2 = trimSpace(line2); 
  line = trimSpace(line); 
  int f1 = open(line, O_RDONLY, 0666);
  int f2 = dup(STDIN_FILENO); 
  dup2(f1, STDIN_FILENO); 
  execute(line2);
  dup2(f2, STDIN_FILENO);
  close(f1);
}

/*******************************************************
RIGHTREDIR: Splits the input on ">" and performes the
            proper redirection before passing the
            command for execution
Takes as input: input string
Returns: none
*******************************************************/

void rightRedir(char *line){ 
  char *line2 = (char *)malloc(256);
  line2 = strsep(&line, ">");
  line2 = trimSpace(line2); 
  line = trimSpace(line); 
  int f1 = open(line, O_WRONLY | O_TRUNC | O_CREAT, 0644);
  int f2 = dup( STDOUT_FILENO );
  dup2(f1, STDOUT_FILENO);
  execute(line2); 
  dup2(f2, STDOUT_FILENO);
  close(f1);
}

/*******************************************************
RIGHTDOUBLEREDIR: Splits the input on ">>" and performes the
            proper redirection before passing the
            command for execution
Takes as input: input string
Returns: none
*******************************************************/

void rightDoubleRedir(char *line){ 
  char *line2 = (char *)malloc(256);
  line2 = strsep(&line, ">>");
  line2 = trimSpace(line2);
  line = line + 1;
  line = trimSpace(line); 
  int f1 = open(line, O_APPEND | O_WRONLY | O_CREAT, 0644);
  int f2 = dup( STDOUT_FILENO );
  dup2(f1, STDOUT_FILENO);
  execute(line2); 
  dup2(f2, STDOUT_FILENO);
  close(f1);
}

/*******************************************************
TWOREDIR: Splits the input on "2>" and performes the
            proper redirection before passing the
            command for execution
Takes as input: input string
Returns: none
*******************************************************/

void twoRedir(char *line){ 
  char *line2 = (char *)malloc(256);
  line2 = strsep(&line, "2>");
  line2 = trimSpace(line2);
  line = line + 1;
  line = trimSpace(line); 
  int f1 = open(line, O_WRONLY | O_TRUNC | O_CREAT, 0644);
  int f2 = dup( STDERR_FILENO );
  dup2(f1, STDERR_FILENO);
  execute(line2); 
  dup2(f2, STDERR_FILENO);
  close(f1);
}

/*******************************************************
AMPREDIR: Splits the input on "&>" and performes 
            the proper redirection before passing the
            command for execution
Takes as input: input string
Returns: none
*******************************************************/

void ampRedir(char *line){
  char *line2 = (char *)malloc(256);
  line2 = strsep(&line, "&>");
  line2 = trimSpace(line2);
  line = line + 1;
  line = trimSpace(line); 
  int f1 = open(line, O_WRONLY | O_TRUNC | O_CREAT, 0644);
  int ferr = dup(STDERR_FILENO);
  int fout = dup(STDOUT_FILENO);
  dup2(f1, STDERR_FILENO);
  dup2(f1, STDOUT_FILENO);
  execute(line2); 
  dup2(ferr, STDERR_FILENO);
  dup2(fout, STDOUT_FILENO);
  close(f1);
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
}

/*******************************************************
EXECUTE: forks child that executes cmd, waits for child
Takes as input: line is a string, the input from the
                terminal
Returns: 1 if successful, 0 otherwise
*******************************************************/
int execute(char *line){

  char **cmds = (char **)malloc(1000);
  char **args = (char **)malloc(256);

  cmds = split(line, ";");
  int i;
  for (i=0; cmds[i] != NULL; i++) {    
    args = split(cmds[i], " ");
  }

  if ( !(strcmp(args[0], "exit")) ) {
    printf("Exiting SeaShell...\n");
    exit(0);
  }

  if ( !(strcmp(args[0], "cd" )) ) {
    if (args[1] == NULL){
      args[1] = "~";
    }
    if ( !(strcmp(args[1], "~")) ) {
      chdir(getenv("HOME"));
    }
    else {
      if (!(chdir(args[1]) == 0)){
        printf("Failed to change directory!\n");
      }
    }
    free(args);
    free(cmds);
    return 0;
  }

  int pid = fork();

  if (pid == -1) {
    char *error = strerror(errno);
    printf("Process Error: %s\n", error);
    exit(0);
    free(args);
    free(cmds);
    return 0;
  }

  else if (pid == 0) {
    execvp(args[0], args);
    char * error = strerror(errno);
    printf("Command Error for %s: %s\n", args[0], error);
    exit(0);
    free(args);
    free(cmds);
    return 0;
  }

  else {
    int cstat;
    waitpid(pid, &cstat, 0);
    free(args);
    free(cmds);
    return 1;
  }
  free(args);
  free(cmds);
  return 1;
}





