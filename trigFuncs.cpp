/*
	Short example of how to use the trig functions in C++

	Code by Jason Lillard, 2018
*/

#include <cmath> //for trig function functions
#include <iostream> // for input and output
using namespace std;

//FUNCTION PROTOTYPE
//helper function to get float inputs w/0 breaking
float getFloat(const char * prompt, float min, float max);

//BEGIN MAIN
int main(){
	//OUTPUT INTRO AND PROMPT
	cout<<"Tangent thing.\n"
			"Determine the height of a thing with your distance from its base\n"
			"and the angle from the ground to the top of the thing."<<endl;
	//GET INPUTS, DO MATH
	float x = getFloat("How far away is the thing?: ", 0, 1e10);
	
	float theta = getFloat("At the given distance away, what is the angle in degrees\n"
		"from the ground to the top of the thing?: ", 0.01, 89.99 );
		
	theta *= M_PI/180.0; //convert from degrees to radians for math functions
	
	//OUTPUT RESULTS ( & DO THE LAST BIT OF MATH)	
	cout<<"The thing's height is " << x*tan(theta) <<" units tall"<<endl;

	return 0;
}
//END OF MAIN

//HELPER FUNC DEF.
float getFloat(const char * prompt, float min, float max){
	bool valid = false; //assume input failed
	float result; //allocate some space to store result
	do{
		cout<<prompt; //output the prompt
		cin>>result; //get in the input
		
		//test the input
		if (!cin.good()){ //check cin.good() to make sure no letters were input
			cin.clear(); //clear all flags
			cin.ignore(1028, '\n'); //ignore rest of input buffer
		}
		else if (result>=min&&result<=max){ //check range
			valid = true; //if range is good, set valid to true
		}
		//after all that, if input isn't true, output an error message
		if(!valid) cout<<"Invalid input!"<<endl;
		
	}while(!valid); //repeat until input is deemed valid
	
	return result;	//return validated input
	
}
