#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "shell.h"
#include "parse.h"

int main() {
  chdir(getenv("HOME"));
  //system("clear");
  printf("Welcome to SeaShell!\n");
  printf("---------------------------\n\n");
  char * history;
  while (1) {
    prompt();
    char line[100];
    if (fgets(line, sizeof(line), stdin) == NULL) {
      printf("\nExiting SeaShell...\n");
      return 0;
    }
    *strchr(line, '\n') = 0;
    parse(line);

  }
  return 0;
}
