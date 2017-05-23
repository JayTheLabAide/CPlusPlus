/*
	Creating, Destroying, and Resizing Arrays
	With Pointers and Functions (c-style & c++)

===========================
Code by Jason Lillard, 2017
===========================

*/

#include <iostream> //for size_t
#include <cstdio> 
using namespace std;

int* createArray(int size);
void fillArray(int* arr, int size);
void printArray(int* arr, int size);
void destroyArray(int *&arr); //reference to pointer (to alter val. of original pointer)

int* cStyleCreateArray(int size);
int* cStyleCreateBlankArray(int size);
int* cStyleResizeArray(int* oldArrPtr, int newSize);
void cStyleDestroyArray(int *&arr);

int main(){
	const size_t ARRSZ = 7; //use size_t for array sizes, noobs
	int* arrPtr = createArray(ARRSZ); //allocate array with function
	fillArray( arrPtr, ARRSZ); //fill array with linear sequence
	printArray( arrPtr, ARRSZ); //print simple array
	destroyArray(arrPtr); //delete & nullify arrPtr
	destroyArray(arrPtr); //repeated call doesn't crash if arrPtr is set to null (address 0) 

	const size_t ARRSZ_2 = 20;
	int* cStyleArr = cStyleCreateArray(ARRSZ); //start with size 1
	printArray(cStyleArr, ARRSZ); //print uninitialized array
	//delete old array
	cStyleDestroyArray( cStyleArr );
	
	//make new array with old pointer
	cStyleArr = cStyleCreateBlankArray( ARRSZ );
	//print 0-initialized array (made using calloc)
	printArray(cStyleArr, ARRSZ);
	
	//now fill blank array
	fillArray(cStyleArr, ARRSZ);
	printArray(cStyleArr, ARRSZ);
	
	//resize array (ptr may be pointing to new place, re-set ptr to returned value)
	cStyleArr = cStyleResizeArray( cStyleArr, ARRSZ_2);
	//print with unitialized, expanded data
	printArray(cStyleArr, ARRSZ_2);
	
	fillArray( cStyleArr, ARRSZ_2);
	printArray( cStyleArr, ARRSZ_2);
	
	cStyleDestroyArray( cStyleArr ); //delete old array
	cStyleDestroyArray( cStyleArr ); //redundant call for demo purposes
}

int* createArray(int size){
	if (size<1) return 0; //return null
	return new int[size];
}

void fillArray(int* arr, int size){
	for (int i = 0; i < size ; i++){
		*(arr+i) = 1+i;
	}
}

void printArray(int* arr, int size){
	for (int i = 0; i < size ; i++){
		//cout<< left<<setw(5)<<*(arr+i) <<" "; //works, just don't wanna use it
		printf("%-5d", *(arr+i) ); //printf in cstdio. 
		//"%-5d" means left-aligned, fieldwidth 5, d means digit.
		// *(arr+i) equivalent to arr[i]
		if ( (i+1)%10==0 ) cout<<"\n"; //every 10 elements, print newline
	}
	cout<<"\n"<<endl;//print 2 newlines and flush output buffer
}

void destroyArray(int *&arr){ //reference to pointer (to alter val. of original pointer)
	delete [] arr; //de-allocate memory
	arr = 0; //set pointer to null
}


/*
	c-style memory allocation functions 
	malloc, calloc, and realloc all return type-less
	"void pointers" which must be cast into the desired type 
*/
int* cStyleCreateArray(int size){
	return (int*)malloc(size);
}

int* cStyleCreateBlankArray(int size){
	return (int*)calloc(size, sizeof(int) ); //calloc also needs size of data type
}

int* cStyleResizeArray(int* oldArrPtr, int newSize){
	return (int*)realloc( oldArrPtr, newSize*sizeof(int) ); //realloc needs total new byte size (newSize*sizeof( datatype ))
}

void cStyleDestroyArray(int *&arr){
	free(arr);
	arr = 0;
}
