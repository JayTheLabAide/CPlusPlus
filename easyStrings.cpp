/*
	Code by Jason Lillard, 2017
	---------------------------
	Here are some easy functions to get strings and c-strings (char arrays)
	so that getting input is a little more uniform for each data type.
	
*/

#include <iostream> //for cin, cout, cin.getline
#include <string> //for strings, getline
using namespace std;

//these are all "void" functions, meaning they don't "return" anything

//C-STRING FUNCTIONS (FOR CHARACTER ARRAYS)
//TO USE IN MAIN: getString( myCharArray );
void getString ( char * cstr ){ 
	//use cin.getline to get a line, store it in cstr
	//stop line at 100 chars or '\n', whichever comes first
	cin.getline( cstr, 100, '\n'); 
	//might need, depending on context:
	//cin.ignore( 1000, '\n'); //ignore "delimiter" left in the input stream
}

//TO USE IN MAIN: getString( myCharArray, arraySize);
void getString( char * cstr, unsigned int len){ 
	//use cin.getline to get a line, store it in cstr
	//stop line at "len" number of chars or '\n', whichever comes first
	cin.getline( cstr, len, '\n');
	//might need, depending on context:
	//cin.ignore(1000, '\n'); //ignore the "delimiter" left in the input stream
}


//STRING FUNCTION (FOR STRING OBJECTS)
//TO USE IN MAIN: getString( myString );
void getString( string &str){
	//use string's getline to get a string from cin, 
	//store the string in str, and stop at newline
	getline(cin, str, '\n');
}



int main(){
	 //make a 100-char long c-string, (empty curly braces set all values to 0)
	char cstring[100]{}; //NOTE: empty braces to zero-initialize array only works on c++11
	cout<<"Enter a long string: "; //prompt
	getString (cstring); //get input
	cout<<"Your long string: "<<cstring<<endl; //echo input
	
	char shortStr[7];
	cout<<"Enter a short string: "; //prompt
	getString (shortStr, 7); //get input
	cout<<"Your short string: "<<shortStr<<endl; //echo input
	
	//this is a string "object", which is just a container
	// for our char array. Strings also can be resized, unlike c-strings
	// (strings are easier. Use these when you can)
	string strObject; 
	cout<<"Enter any kind of string: "; //prompt
	getString( strObject ); //get input
	cout<<"Here was your string: "<<strObject<<endl;//echo input
	
}
