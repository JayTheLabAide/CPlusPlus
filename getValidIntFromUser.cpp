/*
	Get Valid Int From User, Multiple Examples
	"Kitty-Cat Proof" User Input (Garbage Input Does Not Throw Program Into Infinite Loop)
	===========================
	Code by Jason Lillard, 2017
	===========================
*/

#include <iostream>
#include <cstdio> //for BUFSIZ (optionally use limits library)
#include <string>
using namespace std;

int getValidInt(); //get any valid integer from user
int getValidInt(int min, int max); //get integer within specified range
int getValidInt(string prompt ); //output given prompt, get any valid integer
int getValidInt(string prompt, int min, int max); //output given prompt, get int in range

int main( ) {
	
	cout << "\t____getValidInt Tester____\n";
	
	cout << "First: Testing getValidInt()...\n";
	//output prompt within function calling getValidInt()
	cout << "Input garbage to test validation, enter a number to continue: ";
	int i_input = getValidInt(); //get input, store in temporary variable
	cout << "Input Accepted: "<< i_input <<endl;
	cout << endl; //extra endline
	
	cout << "Second: Testing getValidInt(int min, int max)...\n";
	//output prompt within function calling getValidInt(int, int)
	cout <<"Input garbage to test validation, enter a number between -16 and 1024: ";
	//getting input (within a cout statement) and outputting without using a temp variable
	cout << "Input Accepted: "<< getValidInt( -16, 1024 ) <<endl <<endl; 
														//extra endline 
	
	cout <<"Third: Testing getValidInt(string prompt)...\n";
	//using temp variables for prompt and input
	int i_input2;
	// myPrompt is a string; it is not output here, it is output within getValidInt(string, int, int)
	string myPrompt = "Input garbage to test validation, enter a number to continue: ";
	//passing prompt and range to getValidInt (within a cout statement),
	//outputting int returned from function without using another temp variable
	cout << "Input Accepted: "<< getValidInt( myPrompt ) <<'\n' << endl;
														//extra endline 
	
	//More Advanced: Using C Language I/O (cStrings, cstdio input/output )
	puts("Fourth: Testing getValidInt(string prompt, int min, int max)..." );
	//using const integers for range
	const int MIN = 1, MAX = 999999;
	char cStrPrompt[50] = {}; //blank c-string to build prompt
	//use sprintf to build cString prompt with ints (works like printf but saves into cString)
	sprintf( cStrPrompt, "Enter a number between %d and %d: ", MIN, MAX); 
	//output accepted int with printf. 
	printf("Input Accepted: %d\n", getValidInt ( cStrPrompt, MIN, MAX) );
	//"%d" format specifier becomes return value from getValidInt(string, int, int)
	//cString is automatically "promoted" to string when passed by value to func expecting string
	putchar('\n'); //extra endline
	
	puts("Tests Complete! Press Enter to Quit...");
	getchar(); //get char from stdout, do nothing with it
	
	return 0;
}

int getValidInt(){
	bool valid = false;
	int num;
	do{
		cin>>num; //GET INPUT
		if ( !cin.good() ){ // if cin detects bad input (i.e. letters, over/underflowed values)
			cout<<"ERROR: Invalid Input!"<<endl;
			cin.clear(); //clear the bad input flags (doesn't delete anything from stream!)
			cin.ignore(BUFSIZ, '\n'); //ignore everything in the input buffer
			//optionally use cin.ignore(numeric_limits<streamsize>::max(), '\n'); //must #include <limits>
		}
		else{
			valid = true; //a valid integer was input (no range check)
			cin.ignore(BUFSIZ, '\n'); //clear any garbage after valid int. 
			//WARNING: This cin.ignore also prohibits multiple inputs on a single line
		}
	}while(!valid);
	return num;
}

int getValidInt(int min, int max){
	bool valid = false;
	int num;
	do{
		cin>>num; //GET INPUT
		if ( !cin.good() ){ // if cin detects bad input (i.e. letters, over/underflowed values)
			cout<<"ERROR: Invalid Input!"<<endl;
			cin.clear(); //clear the bad input flags (doesn't delete anything from stream!)
			cin.ignore(BUFSIZ, '\n'); //ignore everything in the input buffer
			//optionally use cin.ignore(numeric_limits<streamsize>::max(), '\n'); //must #include <limits>
		}
		else{
			cin.ignore(BUFSIZ, '\n'); //clear any garbage after valid int. 
			//WARNING: This cin.ignore also prohibits multiple inputs on a single line
			
			//RANGE CHECK:
			if ( num >= min && num <= max ) valid = true;
			else cout<<"ERROR: Input Out of Range!"<<endl;
			
		}
	}while(!valid);
	return num;

}
int getValidInt(string prompt ){
	bool valid = false;
	int num;
	do{
		cout<<prompt; //OUTPUT PROMPT
		cin>>num; //GET INPUT
		if ( !cin.good() ){ // if cin detects bad input (i.e. letters, over/underflowed values)
			cout<<"ERROR: Invalid Input!"<<endl;
			cin.clear(); //clear the bad input flags (doesn't delete anything from stream!)
			cin.ignore(BUFSIZ, '\n'); //ignore everything in the input buffer
			//optionally use cin.ignore(numeric_limits<streamsize>::max(), '\n'); //must #include <limits>
		}
		else{
			valid = true; //a valid integer was input (no range check)
			cin.ignore(BUFSIZ, '\n'); //clear any garbage after valid int. 
			//WARNING: This cin.ignore also prohibits multiple inputs on a single line
		}
	}while(!valid);
	return num;
}


int getValidInt(string prompt, int min, int max){
	bool valid = false;
	int num;
	do{
		cout<<prompt; //OUTPUT PROMPT
		cin>>num; //GET INPUT
		if ( !cin.good() ){ // if cin detects bad input (i.e. letters, over/underflowed values)
			cout<<"ERROR: Invalid Input!"<<endl;
			cin.clear(); //clear the bad input flags (doesn't delete anything from stream!)
			cin.ignore(BUFSIZ, '\n'); //ignore everything in the input buffer
			//optionally use cin.ignore(numeric_limits<streamsize>::max(), '\n'); //must #include <limits>
		}
		else{
			cin.ignore(BUFSIZ, '\n'); //clear any garbage after valid int. 
			//WARNING: This cin.ignore also prohibits multiple inputs on a single line
			
			//RANGE CHECK:
			if ( num >= min && num <= max ) valid = true;
			else cout<<"ERROR: Input Out of Range!"<<endl;
		}
	}while(!valid);
	return num;	
}
