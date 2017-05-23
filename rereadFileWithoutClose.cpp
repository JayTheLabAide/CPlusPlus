/*
	Write a User-Input Vector to File, 
	And Read it Repeatedly Without Closing and Re-Opening The File
	===========================
	Code by Jason Lillard, 2017
	===========================
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector> //for dynamically resized array of strings (used here for user input, file output)
using namespace std;

//no subroutines in this one, just one big demo function

//MAIN
int main(){
	vector<string> strVect; //container to hold user input
	string fName; //string to hold file name from user
	ofstream outFile;
	ifstream inFile;
		
	bool validFileName = false;
	do{	
		//get file name from user
		cout<<"Enter a valid file name: ";
		getline(cin, fName, '\n');
		outFile.open( fName.c_str() );//even if you use C++11 Standard, 
				//using .c_str() for file name strings given to fstream is good practice, as
				//you may not always have access to compilers that use the newest standards.
				//Generally, first learn the new easy way to do something, then learn the old difficult way as a backup plan.
		
		if ( !outFile.fail() ) validFileName = true;
	}while(!validFileName);
	
	//get vector of strings from user
	string s_input="";
	bool exitSentryRead = false;
	do{
		cout<<"Enter a line to append to the file (or -1 to stop): ";
		getline(cin, s_input, '\n');
		if ( s_input.find("-1") != -1 ) exitSentryRead = true; //test for "sentry value" -1 (-1 from .find() means query not found)
		if (!exitSentryRead) strVect.push_back( s_input ); //if not sentry value, add input to the end of our string vector
	}while( !exitSentryRead); //do while input "-1" is not found 
	
	//write vector to file
	for( string forStr : strVect){ //enhanced for loop, goes through entire vector
		outFile<<forStr<<"\r\n"; //use \r\n instead of \n when writing to text files
	}
	//output is done, flush output buffer to file & close.
	outFile.close();
	
	
	//prompt user for number of times to print file contents
	bool validLoopMax = false;
	short loopMax;
	do{
		cout<<"How many times would you like to print the file contents? (1-20): ";
		cin>>loopMax; //get input from user
		if( !cin.good() ){ cin.clear(); cin.ignore(1000, '\n');} //if input failed, clear flags & ignore input buffer
		else if (loopMax > 1 && loopMax <=20) validLoopMax = true;; //range check for loopMax
	}while(!validLoopMax);
	
	//print entire file in a loop n times
	inFile.open( fName.c_str() );
	if ( !inFile.fail() ){ //if file could be opened
	
		for( int i = 0; i < loopMax ; i++){ //loop to print entire contents loopMax number of times
		
			while( inFile.peek() != EOF ){ //and while next char in stream isn't the End-of-File marker
				string s_temp;
				getline( inFile, s_temp); //get line from file
				cout<<s_temp<<"\n"; //no endl here -- don't flush until you're done
			}
			cout<<"\n";
			cout.flush(); //print everything to screen at once  (these two lines equivalent to cout<<endl )
			
			//RESET FILE READ MARKER
			inFile.clear(); //clear EOF flag inside fstream object
			inFile.seekg(0L, ios::beg ); //set "seek getter" to 0 bytes from the beginning of file (L just casts to long)
		}
		
		inFile.close(); //close your file!
	} 	
	/*
		Note: a better way to repeatedly read contents from files is to read them once, 
		fill an array or vector/list/tree etc. with those values, then just access that
		data structure as many times as you need to (with the file closed so other programs can use it).
		This clear+seekg tactic comes in handy, but shouldn't be used for exactly this sort of thing.
	*/
	return 0;
} //end of main
