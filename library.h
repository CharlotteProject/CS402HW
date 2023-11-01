#ifndef _READFILE_H_
#define _READFILE_H_

extern int read_int(char x[], int option, int* var);
extern int read_float();
extern int read_string(char x[], int option, char y[]);
extern int open_file(char* inputfile);
extern void close_file();

#endif