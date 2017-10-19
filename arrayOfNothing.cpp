/*
	Allocate useless memory,
	then use it just 'cause.
	---------------------------
	Code by Jason Lillard, 2017
*/
#include <iostream>
using namespace std;

//Create array of an empty structure
struct Nothing{};


int main(){
	//Allocate 200 bytes with array of empty structs
	Nothing arr[200];
	
	//our data to write to our "arr" block
	int num = 1234567;
	
	//Pointer to first byte of our value to read
	char * reader = (char *)&num;	
	
	//Pointer to first byte of destination for data
	char * writer = (char *)arr;
	
	//Loop to write our data to our array area
	for( int i = 0; i < sizeof(int); i++){
		//Write one byte from where we're reading, 
		//then increment each pointer
		*writer++ = *reader++;
		
	}
	//Cast our address of arr to an int ptr,
	//then dereference that int pointer
	cout << *(int*)arr <<endl; //Outputs 1234567
	
	return 0;
}
