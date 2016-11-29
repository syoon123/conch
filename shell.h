#ifndef SHELL
#define SHELL

int execute(char *line);

int redirector();

void checkRP(char *line);

void leftRedir(char *line); 

void rightRedir(char *line);

void rightDoubleRedir(char *line);

void twoRedir(char *line);

void ampRedir(char *line);

void parsePipe(char *line);

#endif

