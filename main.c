#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "shell.h"
#include "parse.h"

int main() {
  chdir(getenv("HOME"));
  system("clear");
  printf("Conch v1.0\n");
  printf("By Winston Venderbush and Sarah Yoon\n\n");
  printf("Welcome to SeaShell\n");
  printf("-------------------\n\n");
  char *line;
  while ((line = readline(prompt())) != NULL) {
    if (line[0]!=0){
      add_history(line);
      parse(line);
    }
  }
  printf("\n");
  free(line);
  return 0;
}
