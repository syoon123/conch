#ifndef SHELL
#define SHELL

void prompt();

char ** split( char *line, char *delimiter );

int execute(char *line);

int redirector();

char * trimSpace(char *str);

void parse(char *line);

void checkRP(char *line);

void leftRedir(char *line); 

void rightRedir(char *line);

void rightDoubleRedir(char *line);

void twoRedir(char *line);

void ampRedir(char *line, int flag);

void parsePipe(char *line);

#endif

