#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "shell.h"

int main() {
  system("clear");
  printf("Welcome to SeaShell!\n");
  printf("---------------------------\n\n");
  while (1) {
    prompt();
    char line[100];
    if (fgets(line, sizeof(line), stdin) == NULL) {
      printf("\nExiting SeaShell...\n");
      return 0;
    }
    *strchr(line, '\n') = 0;

    char ** cmds = (char **) malloc (1000);
    cmds = split(line, ";");
    int i;
    for (i=0; cmds[i] != NULL; i++) {
      char ** command = (char *) malloc (256);
      command = split(cmds[i], " ");

      execute(command);
    }
  }
  return 0;
}
