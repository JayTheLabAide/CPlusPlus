/*
	Better I/O For C++. Language: C
	A weekend project trying to make IO less of a headache.
	Currently incomplete, but still serves an example of how to make
	your own C library that can link to a C++ program. Just add this
	and BetterIO.h to your project and link to the header with:
	#include "BetterIO.h"
	---------------------------
	Code by Jason Lillard, 2017
*/
#include <stdio.h> //cstdio is the foundation of this library's i/o
#include "BetterIO.h"

char get(){ return (char)getchar(); }
unsigned getStr(char * cstr){ 
	unsigned len = 0;
	while ( (*cstr=get())!='\n'){len++;cstr++;}
	*cstr=0;
	return len;
}
void getEnter(){ while (getchar()!='\n');} //wait for user to press enter
char put( char c ){ return (char) putchar(c); }
void putN(const char * cstr, unsigned len){ 
	unsigned i = 0;	while (i++ < len) putchar( *cstr++ );
}
void putStr( const char * cstr){ while( put( *cstr++ )); }
void putLn(const char * line) { while( put( *line++ )!='\n'); }
void clearIn(){ clearerr(stdin); fflush(stdin); }
int isDigit(char c){ return (c>='0'&&c<='9');}
int isSign(char c){ return ((c=='-')||(c=='+'));}
int isLower(char c){return (c>='a'&&c<='z');} 
int isUpper(char c){return (c>='A'&&c<='Z');}

unsigned getDigitStr(char * cstr){
	unsigned len = 0;
	while ( isDigit(*cstr=get()) ){len++;cstr++;}
	*cstr=0;
	return len;
}
unsigned getNumStr(char * cstr){
	unsigned len = 0;
	*cstr = get();
	if ( isSign(*cstr) || isDigit(*cstr) ){
		len++;cstr++;
		while ( isDigit(*cstr=get()) ){len++;cstr++;}
	}
	*cstr=0;
	return len;
}
unsigned strToInt(const char * cstr){ //numbers too big overflow strangely.
	short sign=1;
	if ( *cstr == '-' ) { sign = -1; cstr++; }
	else if ( *cstr=='+') { cstr++; }
	//then
	int sum = 0;
	while ( isDigit( *cstr ) ){
		sum *= 10; //shift current result left
		if (sum < 0) { //if number overflowed
			sum /= 10; //put it back
			break; //stop converting
		}
		sum += *cstr - '0'; //push new digit
		cstr++; //inc reader
	}
	return sum*sign;
}

unsigned strLen(const char * cstr){
	unsigned len = 0; while(*cstr++)len++; return len;
}	
unsigned lineLen(const char * cstr){
	unsigned len = 0; while(*cstr++!='\n')len++; return len;
}
void swap( char * c1, char * c2) //swap values of two chars
{
	char c3 = *c1;
	*c1 = *c2;
	*c2 = c3;
}

void reverse(char * cstr, unsigned len){
	if (cstr && len){
		char * end = cstr+len-1;
		while (cstr < end){ swap( cstr++, end--);}
	}
}

void intToStr(int val, char * cstr){ // -- possibly not breaking when intended to
	long lVal = val; //promote
	char * revStart = cstr;
	if (cstr){
		if (lVal == 0) *cstr++ = '0';
		else
		{
			if (lVal < 0 ) {
				*cstr++ = '-';
				revStart++;
				lVal = -lVal; //this is why we use long (lowest int val can't be negated in int)
			}
			//copy digits from lVal to cstr, starting with lsd
			while (lVal){
				*cstr++ = '0'+lVal%10;
				lVal/=10;
			}
		reverse(revStart, cstr-revStart);
		}//end if != 0 
	*cstr=0;	
	}//end if cstr
}//end intToStr

//copy len number of chars to src from dest. returns pointer to last char written
char * copy(char * dest, const char * src, unsigned len){
	unsigned i = 0;
	while( i < len)
	{
		*dest++ = *src++;
		i++;
	}
	return --dest;
}

//copy c len number of times at dest. returns pointer to last char written
char * copyChar(char * dest, char c, unsigned len){
	unsigned i = 0;
	while( i < len)
	{
		*dest++ = c;
		i++;
	}
	return --dest;
}

int getInt() //returns an int from the user (scanf call)
{
	int input;
	scanf("%d", &input);
	return input;
}

float getFloat() //returns a float from the user (scanf call)
{
	float input;
	scanf("%f", &input);
	return input;
}
void newLine(){
	put('\n');
} //put '\n'

void putCN(char c, unsigned len) //put given character to screen len number of times
{
	unsigned i = 0;	while (i++ < len) put(c);
}

void putIntArr( int * arr, unsigned size, unsigned perLine, unsigned spacing){
	unsigned i = 0;

	while (i < size){
		//replace following two lines with call to put in right-aligned field
		printf("%d", *(arr+i) );
		putCN(' ', spacing);
		if ((1+i)%perLine==0) newLine();
		i++;
	}
}
