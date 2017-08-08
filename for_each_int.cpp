/*
	for_each_int, example of a simplified variant of for_each in algorithm.h
	Uses: arrays, passing by reference, pointers, function pointers
	Also shows off a couple low-level techniques (manipulating bits) within functions to be called
	(though at least one of these is really only more efficient when done at the assembly level)
	====
	Code by Jason Lillard, 2017
*/

#include <cstdio> //for printf and puts
#include <cstdlib> //for rand and srand
#include <ctime> //for time(0) to seed rand
using namespace std;

//for_each_int:
//void function
//first param: pointer to start of region to affect
//second param: number of slots to affect
//third param: pointer to void function to call on each int, which accepts an int by reference (named num)
//PROTOTYPE OF FOR_EACH_INT, IMPLEMENTATION IS BELOW MAIN
void for_each_int( int* startLoc, int size, void (*func)(int &num) );
// function pointer syntax is:
// return_type (*pointer_name)( parameter list ... )
// where the parameter list is a specific order of data types, 
// such as (char, int, float), or (int*, int, bool)

//EXAMPLES OF FUNCTIONS TO USE WITH FOR_EACH_INT
// Note: while here the functions all use the same parameter name "num", that is not needed
//for your function pointer to work properly. What must match are the function's return type and parameter list.
void printInt(int &num){ //passing by reference only needed here to use with above for_each_int func
	printf("%d\n", num); //print a digit, num, then a newline
}

void randomize(int &num){ //set num to a random number (and seed rand if not yet done)
	static bool seeded = false; //static var here will keep state through func calls
	if (!seeded){ //if srand hasn't been called,
		srand(time(0)); // call it
		seeded=true; //then flag that it has been called
		}  
	num = rand(); //any random number
}

void resetInt(int &num){ //simply sets num to 0
	num ^= num; //Any number XOR itself is zero. 
	//Equivalent to "num = num ^ num", or "num = num xor num", or "num xor_eq num"
	//In g++, setting anything to 0 in c++ gets compiled down to this in assembly.
	//I think this is because logical operations between registers don't involve a call to memory,
	//but setting a number to some constant requires that constant be fetched from RAM.
	//NOTE: A better way of clearing an array is to use memset in cstdio.h. This is here to demo for_each_int
}

//function to perform single left shift (doubling) on integer
void shiftLeft(int &num){
	num = num<<1; // << here is left-shift operator (nothing to do with cout or ofstream)
}
//function to perform single right shift (halving) on integer
void shiftRight(int &num){
	num = num>>1;  // >> here is right-shift operator (nothing to do with cin or ifstream)
}

void negate(int &num){
	//"low-level" style negation. Probably does not compile down to more efficient code 
	// since using local variables means many needless MOV ops from stack to registers
	num = ~num; //invert each bit of num (one's complement)
	// equivalent to "num ^= 0xFFFFFFFF" or "num xor_eq 0xFFFFFFFF"
	num += 1;	//add one (turn one's complement to two's complement)
	//would likely be more efficient as: "num = -num"
	/*
	NOTE: floats and doubles do not use two's complement to store negative numbers,
	they only use the sign bit. This means that to change the sign of a float at a
	bit level, you must do:
	f_num = f_num xor 0x80000000;
	or
	f_num ^= 0x80000000;
	which, in binary, is just the sign bit as a 1 and everything else a zero. Using this
	with xor means if f_num's sign was 1, it's now 0, and if its sign was 0, it's now 1
	*/
}


//MAIN -- demo of for_each_int
int main(){
	const int ARRSZ = 5; //array size (constant)
	int i_array[ARRSZ]; //make an array for demonstration

	puts("Zeroed Out Array:");
	for_each_int(i_array, ARRSZ, resetInt ); //set each number to 0
	for_each_int( i_array, ARRSZ, printInt ); //print array
	
	puts("Randomized Array:");
	for_each_int( i_array, ARRSZ, randomize); //fill array with random numbers
	for_each_int( i_array, ARRSZ, printInt ); //print array
	
	puts("Left-Shifted Array ( x2 original values):"); 	
	for_each_int(i_array, ARRSZ, shiftLeft); //double array values
	for_each_int( i_array, ARRSZ, printInt ); //print array

	puts("Right-Shifted Array (undo left-shift, original values):"); 	
	for_each_int(i_array, ARRSZ, shiftRight); //double array values
	for_each_int( i_array, ARRSZ, printInt ); //print array
	
	puts("Right-Shifted Again Array ( 1/2 original values):"); 	
	for_each_int(i_array, ARRSZ, shiftRight); //double array values
	for_each_int( i_array, ARRSZ, printInt ); //print array
	
	puts("Negated Array (Two's Complements of given values):"); 	
	for_each_int(i_array, ARRSZ, negate); //double array values
	for_each_int( i_array, ARRSZ, printInt ); //print array

	return 0;
}


void for_each_int( int* startLoc, int size, void (*func)(int &num) ){
	for(int i = 0; i < size; i++) { //typical for loop header, using passed in size
		func( startLoc[i] ); //call to function we've named func (use like a normal function)
		//using startLoc as an array base pointer, and loop counter i as the index
		//This could also be done like this:
		//(*func)(  *(startLoc+i) ); //call to func, passing value at base+index (will be passed by reference)	
		//This function could also be made with num as a pointer instead of a reference,
		//but syntax for this is a little messy, and at least on g++ both will compile down
		//to the same assembly code, so you might as well use the one with easier syntax where possible
	}
}
/*
	NOTE: the function for_each in algorithm.h does not take a base pointer and a size,
	it instead takes an iterator the starting element, and an iterator to the last element.
	Because algorithm.h uses iterators made with templates, the functions which accept them
	can operate on various data types. If you understand templates and iterators adapting this
	into an equivalent of for_each in algorithm.h should only take a handful of changes.
*/

/*
	Bonus exercise:
	convert for_each_int into a function which returns an int,
	and turn void (*func) into int (*func) so func returns an int when called,
	then change for_each_int so that it returns the sum of all return values from int (*func).
*/
