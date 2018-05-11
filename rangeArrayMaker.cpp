/*
	This is based on the "range" function in PHP which
	accepts a start and end value, and returns an array
	including all values in the range from start to finish.
	
	In PHP the function works with multiple data types,
	but here is a version that only works with short ints.
	
	Array of character values, it is worth noting, can also
	be stored in short ints, and they will be effectively
	stored as a w_char array, or wide character string
	(which is used to store unicode characters, usually when
	you're dealing with input from the internet or the
	operating system).
*/

#include <iostream>
using namespace std;

//Returns an array based on range given.
//Assigns the determined size to sz if it is given.
short* range( short start, short end, unsigned * sz = 0);

//prints array as shorts
void printArr( short* arr, unsigned size){
	for(int i = 0; i < size; i++){
		cout<< *(arr+i) <<endl;
	}
}

int main(){
	cout <<	"Let's test our range function to quickly make a few arrays\n"
			"with ascending or descending values."
	<< endl;

	cout<<"\n\nTeens: "<<endl;
	unsigned teensArrSZ;
	short* teensArr = range(10, 19, &teensArrSZ);
	printArr( teensArr, teensArrSZ );
	
	cout<<"\nCountdown: "<<endl;
	unsigned cdArrSZ;
	short* cdArr = range(10, 0, &cdArrSZ);
	printArr( cdArr, cdArrSZ);
	
	cout<<"\nAlphabet: "<<endl;
	unsigned azArrSZ;
	short * azArr = range( 'a', 'z', &azArrSZ);
	
	//Instead of calling printArr, we'll use a custom
	//loop to make sure our values are interpreted as chars
	
	for( int i = 0; i < azArrSZ; i++){
		//If we wanted to output this as wide chars we could do:
		//wcout<< (wchar_t)azArr[i] <<endl;
		
		//But since we can safely interpret these as regular chars,
		//we can do this:
		cout<< (char)azArr[i] <<endl;
		
		//both ways should ultimately look the same in the console
	}
	
	return 0;
}

short* range( short start, short end, unsigned * sz){
	//determine size of array based on given range
	int size = end-start;
	if (size<0) size = -size; //make sure size > 0
	++size; //add one to size so range math works out
	
	if (sz) *sz = size;//assign sz if it is not null
	
	short * arr = new short[size]; //allocate array
	
	//Account for ascending or descending ranges as we fill array
	for(int i = 0; i < size; i++){
		if (start<end){ //if ascending
			arr[i] = start++; //use start as our counter, go up
		}
		else{ //if descending
			arr[i] = start--; //from start, go down
		}
	}
	//return pointer to dynamically created array
	return arr;
}
