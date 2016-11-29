#ifndef PARSE
#define PARSE

void prompt();

char ** split( char *line, char *delimiter );

char * trimSpace(char *str);

void parse(char *line);

void parsePipe(char *line);

#endif
