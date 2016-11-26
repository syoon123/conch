#ifndef SHELL
#define SHELL

void prompt();
char ** split( char * line, char * delimiter );
int execute(char *args[]);
int redirector();
char * trimSpace(char *str);

#endif

