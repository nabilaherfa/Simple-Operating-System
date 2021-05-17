#ifndef SHELL_H
#define SHELL_H

void eksekusi(char* progName, char parentIndex);
int cd(char* c, int idx);
int strNCompare(char* string1, char* string2, int size);
int searchPath(char* dirCall, int parent);
void run_program(char* c);

#endif