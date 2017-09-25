/*
	Better I/O For C++. Language: C
	A weekend project trying to make IO less of a headache.
	Currently incomplete, but still serves an example of how to make
	your own C library that can link to a C++ program. Just add this
	and BetterIO.c to your project and link to the header with:
	#include "BetterIO.h"
	---------------------------
	Code by Jason Lillard, 2017
*/
#ifndef BETTERIO_H
#define BETTERIO_H

//BetterIO Library Functions
char get(); //get one string from stdin
void getEnter(); //wait for user to press enter
unsigned getStr(char * cstr); //get string until newline from stdin, returns chars read
char put(char c); //print one char to console
void putN(const char * cstr, unsigned len); //put given number of characters to console out
void putCN(char c, unsigned len); //put given character to screen len number of times
void putStr(const char * cstr); //print null-terminated c-string to console
void putLn(const char * line); //print newline-terminated c-string to console
void clearIn(); //clear stdin's error flags and input stream
int isDigit(char c);//returns if char is a digit
int isSign(char c);//returns if char is '-' or '+'
int isLower(char c); //returns whether or not char is lower case
int isUpper(char c); //returns whether or not char is upper case
unsigned getDigitStr(char * cstr);//get optional sign then digits, store in cstr
unsigned getNumStr(char * cstr);//get from stdin as long as digits are read, store in cstr
unsigned strToInt(const char * cstr); //convert signed cstring to integer
void intToStr(int val, char * cstr); //writes value as c-string with digit chars to given location
unsigned strLen(const char * cstr); //number of characters before '\0'
unsigned lineLen(const char * cstr); //number of characters before '\n'
void swap( char * c1, char * c2); //swap values of two chars
void reverse(char * cstr, unsigned len); //reverse cstring
void newLine(); //put '\n'
//copy len number of chars to src from dest. returns pointer to last char written
char * copy(char * dest, const char * src, unsigned len); 

//copy c len number of times at dest. returns pointer to last char written
char * copyChar(char * dest, char c, unsigned len); 

int getInt(); //returns an int from the user (scanf call)
float getFloat(); //returns a float from the user (scanf call)

//print an array (not optimal, as doesn't use a field for spacing, just prints given number of spaces)
void putIntArr( int * arr, unsigned size, unsigned perLine, unsigned spacing);

#endif
