/*
	Breaking Out of Loops: Linear Search Done Six Ways
	===========================
	Code by Jason Lillard, 2017
	===========================
*/
#include <iostream> //used only for demo output. Not needed in any search functions.
using namespace std;

//best way: smart use of variables in loop test
int linearSearch1( int arr[], int size, int query);
//good way: use of an extra flag in loop test
int linearSearch2( int arr[], int size, int query);
//multiple-return way (not always acceptable)
int linearSearch3( int arr[], int size, int query);
//break way (not always acceptable)
int linearSearch4(int arr[], int size, int query);
//goto way, terrible way (always unacceptable, but still works)
int linearSearch5( int arr[], int size, int query);
//goto way 2, worst way (always unnacceptable, but still works)
int linearSearch6( int arr[], int size, int query);

int main(){
	const size_t SIZE = 10;
	int  testArr[SIZE] = {9, 1, 8, 2, 7, 4, 6, 5, 0, 3};
	cout<< "Searching for 7 in testArr..."<<endl;
	cout<<"linearSearch1 Result: "<<linearSearch1(testArr, SIZE, 7)<<"\n";
	cout<<"linearSearch2 Result: "<<linearSearch2(testArr, SIZE, 7)<<"\n";
	cout<<"linearSearch3 Result: "<<linearSearch3(testArr, SIZE, 7)<<"\n";
	cout<<"linearSearch4 Result: "<<linearSearch4(testArr, SIZE, 7)<<"\n";
	cout<<"linearSearch5 Result: "<<linearSearch5(testArr, SIZE, 7)<<"\n";
	cout<<"linearSearch6 Result: "<<linearSearch6(testArr, SIZE, 7)<<"\n";
	cout<<endl;
	return 0;
}

//best way: smart use of variables in loop test
int linearSearch1( int arr[], int size, int query){
	//No extra "found" flag used. No "break". Single-entry, single-exit.
	int foundAt = -1;
	for (int i = 0; ( i < size && foundAt==-1 ) ; i++){
		if (arr[i] == query){
			foundAt = i; //once foundAt is set to something besides -1,
			// loop test will be false, loop will terminate
		}
	}
	return foundAt; //return index where match was found, or -1 if not found
}

//good way: use of an extra flag in loop test
int linearSearch2( int arr[], int size, int query){
	//Uses flag "found" to determine when to exit loop
	bool found = false; //loop will continue while found is false
	int foundAt = -1; //default result is -1, which means "not found" (invalid index)
	for (int i = 0; ( i < size && !found ) ; i++){
		if (arr[i] == query){
			found = true; //set flag to exit loop at next test (doesn't leave instantly)
			foundAt = i; //save result
		}
	}
	return foundAt; //return index where match was found, or -1 if not found
}

//multiple-return way (not always acceptable)
int linearSearch3( int arr[], int size, int query){
	//Sometimes acceptable: uses multiple return statements
	// Violates "single-entry, single-exit" principle
	for (int i = 0; i < size; i++) if (arr[i]==query) return i; //if found, return result instantly
	return -1; //if i was never returned, return -1 to indicate "not found"
}

//break way (not always acceptable)
int linearSearch4( int arr[], int size, int query){
	int foundAt = -1; //default result is -1, which means "not found" (invalid index)
	for (int i = 0; i < size ; i++){
		if (arr[i] == query){
			foundAt = i; //save result
			break; //instantly break out of the loop (also works in while loops)
		}
	} 
	//break jumps to this point:
	return foundAt; //return index where match was found, or -1 if not found
}

//goto way, terrible way (always unacceptable, but still works)
//DO NOT USE IN ASSIGNMENTS -- based on low-level programming, here for demo purposes
int linearSearch5(int arr[], int size, int query){
	//WORST WAY -- modern use of "goto" and labels are forbidden 
	// 1. goto creates hard-to-flowchart "spaghetti code"
	// 2. it's tough to keep track of all the unique labels
	// 3. jumps can seriously mess up the stack, and result in functions returning to incorrect places
	int* ptr = arr, *end = &arr[size-1]; //pointers to first and last element
	//while ptr isn't past the last element, compare query to value pointed to by ptr
	while( ptr <= end) if ( *ptr++==query ) goto success; //if found, jump to success
	return -1; //success label was never jumped to, return -1 for "not found"
	success: return (--ptr-arr); //if success label reached: 
	//return distance between ptr and array beginning (found index)
}

//goto way 2, worst way. Multiple return statements, bootleg while loop.
//the "while" loop in linearSearch5 is eliminated using assembly-style goto-label loops
int linearSearch6(int arr[], int size, int query){
	int* ptr = arr, *end = &arr[size-1]; //first and last element
	LS6_while_start: //while loop start
	if ( ptr > end) goto LS6_while_end; //loop test, if ptr is past end, break loop
	if ( *ptr++==query ) goto LS6_success; //query test, if element is match, jump to success
	goto LS6_while_start; //end of loop, jump to beginning
	LS6_while_end: return -1; //after loop. No match found, return -1
	LS6_success: return (--ptr-arr); //if success is reached, return index where match was found
}

