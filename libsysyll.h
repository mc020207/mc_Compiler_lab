#ifndef __SYLIB_H_
#define __SYLIB_H_

#include<stdio.h>
#include<stdarg.h>
#include<sys/time.h>
/* Input & output functions */
long long getint(),getch(),getarray(long long a[]);
void putint(long long a),putch(long long a),putarray(long long n,long long a[]);
/* Timing function implementation */


#define _SYSY_N 1024

__attribute((constructor)) void before_main(); 
__attribute((destructor)) void after_main();
void _sysy_starttime(int lineno);
void _sysy_stoptime(int lineno);
void starttime();
void stoptime();

#endif
