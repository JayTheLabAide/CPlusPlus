/*
	Wait until user presses enter
	(With an empty while loop)
	Perhaps the world's easiest useful function.
	---------------------------
	Code by Jason Lillard, 2017
*/

#include <iostream>

using namespace std;

void waitUntilEnter(){ //when function is called, code will jump here
	while ( cin.get()!='\n'); //this test will run over and over again until
	//a newline is encountered in the "input buffer"
} //once newline is encountered, function will end and jump back to line 21

int main(){
	cout<<"Spam nonsense then press enter eventually"<<endl; //output our prompt
	
	waitUntilEnter(); //"call" our function defined above. AKA jump to line 12.
	//after function is called, program will resume here.
	
	cout<<"Very good."<<endl;
	return 0;
}
