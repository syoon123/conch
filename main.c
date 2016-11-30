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
  printf("Welcome to SeaShell!\n");
  printf("---------------------------\n\n");
  printf("%s", prompt());
  char *line;
  while ((line = readline(prompt())) != NULL) {
    if (line[0]!=0){
      add_history(line);
      parse(line);
    }
  }
  *strchr(line, '\n') = 0;
  free(line);
  return 0;
}
