#include <iostream>
#include <string>
#include <cstdio> //for BUFSIZ
#include <cstdlib> //for exit(0)
using namespace std;


//function to return menu string
string getMenuString(){
	return	"\n\tMenu-Driven Program Collection:\n"
			"A or 1: Function 1\n"
			"B or 2: Function 2\n"
			"C or 3: Function 3\n"
			"D or 4: Function 4\n"
			"E or 5: Function 5\n"
			"Q or 0: Quit\n"
			" Please Enter A Selection: ";
}

//function containing switch case
void handleInput(char input); //passing input by value is fine here

//simple implementation of cctype's "tolower" function
char toLower(char c) { if ( c >= 'A' && c <= 'Z' ) c += ('a'-'A'); } //add diff between lower & upper case

//prototypes for assorted functions (called within handleInput(char) )
void func1(); void func2(); void func3(); void func4(); void func5();
//custom quit function (used to escape main's while(true) loop)
void quit();

//MAIN
int main(){
	
	char c_input; //character to hold input
	
	while(true){ //infinite loop (program is exited through handleInput(char) and quit() )
	
		cout << getMenuString(); //print menu
		cin>> c_input; //get input
		cin.ignore(BUFSIZ, '\n'); //ignore everything past first character //BUFSIZ in cstdio
		handleInput(c_input); //pass input to handleInput
	}
	return 0;
}
//END MAIN


//FUNCTION IMPLEMENTATIONS

void handleInput(char input){ 
	switch ( toLower(input) ) { //convert input to lower case (to simplify testing for 'a' or 'A')
		case 'a': case '1': // a, A, or 1
			func1(); 
		break;
		
		case 'b': case '2': // b, B, or 2
			func2(); 
		break;
		
		case 'c': case '3': // c, C, or 3
			func3(); 
		break;
		
		case 'd':  case '4': // d, D, or 4
			func4(); 
		break;
		
		case 'e':  case '5': // e, E, or 5
			func5(); 
		break;
		
		case 'q':  case '0': // q, Q, or 0
			quit();
		break;
		
		default: //function was passed invalid character as argument
			cout<<"ERROR: Invalid Input!"<<endl;
	}
}

void func1(){
	cout<<"\nIn Function 1!"<<endl;
}
void func2(){
	cout<<"\nIn Function 2!\n"<<endl;
}
void func3(){
	cout<<"\nIn Function 3!\n"<<endl;
}
void func4(){
	cout<<"\nIn Function 4!\n"<<endl;
}
void func5(){
	cout<<"\nIn Function 5!\n"<<endl;
}
void quit(){
	cout<<"\n\nGoodbye!"<<endl;
	exit(0); //requires cstdlib
}
