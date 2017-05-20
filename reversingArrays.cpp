/*
	Reversing Arrays - early draft
	===========================
	Code by Jason Lillard, 2017
	===========================
*/
#include <iostream>
using namespace std;

//swap function used by all functions here
void swap(int *item1, int *item2){ int temp = *item1; *item1 = *item2; *item2 = temp;}
//void swap(int &item1, int &item2){ int temp = item1; item1 = item2; item2 = temp;}

//print array
void print(int arr[], int size){ for(int i = 0; i < size; i++)cout<<arr[i]<<"\n"; cout<<endl;}

//func 1
void reverseArray( int arr[], int size);
//func2
void recursiveRevArray( int arr[], int start, int end);
//func3
void recursiveRevArray( int* startPtr, int* endPtr);
//func4
int* returnReversed( int* arrPtr, int size);
//func5
int* returnNewReversed( const int* arrPtr, int size);


int main(){
	//ARRAY FOR TESTING
	const size_t ARRSZ = 7; //use size_t instead of ints, noobs
	int arr1[ARRSZ]; //static int array
	//fill array with simple sequence
	for (int i =0; i<ARRSZ; i++){
		arr1[i] = i+1;
	}
	
	//print regular array
	cout<<"Regular Array:\n";
	print(arr1, ARRSZ);
	
	//testing func 1
	cout<<"Testing func1, reverseArray(int[], int):\n";
	reverseArray(arr1, ARRSZ);
	print (arr1, ARRSZ);
	
	//testing func 2
	cout<<"Testing func2, recursiveReverseArray(int[], int, int):\n";
	recursiveRevArray(arr1, 0, ARRSZ-1);
	print (arr1, ARRSZ);
	
	//testing func 3
	cout<<"Testing func3, recursiveReverseArray(int*, int*):\n";
	recursiveRevArray( arr1, arr1+ARRSZ-1); //note int[] arr1 can be passed like an int*
	print (arr1, ARRSZ);
	
	//testing func 4
	cout<<"Testing func4, returnReversed(int*, int):\n";
	int* revArrayPtr = returnReversed(arr1, ARRSZ);
	cout<<"Original after call to returnReversed(int[], int):\n";
	print (arr1, ARRSZ);
	cout<<"int* returned from returnReversed, pointing to reversed original:\n";
	print (revArrayPtr, ARRSZ);
	
	//testing func 5
	cout<<"Testing func5, returnNewReversed(int*, int):\n";
	int* revArrayCopy = returnNewReversed (arr1, ARRSZ);
	cout<<"Original after call to returnNewReversed:\n";
	print (arr1, ARRSZ);
	cout<<"int* returned from returnNewReversed, pointing to reversed copy:\n";
	print (revArrayCopy, ARRSZ);
	
	return 0;
}

//func1
//overwrites original
void reverseArray( int arr[], int size){
	//makes a reversed copy, then overwrites original
	// (uses more memory than swap-based algorithms)
	int revArr[size] = {};
	for (int i = 0, j = size-1  ; i < size  ; i++, j-- ){
		revArr[j] = arr[i]; // index j counts down as i counts up
	}
	//copy reversed array over original array
	for (int i = 0; i < size ; i++ ){
		arr[i] = revArr[i];
	}
}

//func2
//rearranges original - uses swap
void recursiveRevArray( int arr[], int start, int end){
	//swaps outer elements, moving inward until center is reached
	if (start<end){ //if counters point to same element or have passed each other, array is reversed
		//swap elements
		swap( &arr[start], &arr[end]);
		//recursively pass array with "incremented" & "decremented" counters to this function
		recursiveRevArray (arr, start+1, end-1);
	}
}

//func3
//rearranges original - uses swap
void recursiveRevArray( int* startPtr, int* endPtr){
//swaps outer elements, moving inward until center is reached
	if (startPtr<endPtr){//if pointers point to same element or have passed each other, array is reversed
		//swap elements
		swap( startPtr, endPtr );
		//recursively pass incremented & decremented pointers to this function
		recursiveRevArray (++startPtr, --endPtr); 
	}
}

//func4 
//rearranges original, returns pointer to original - uses swap
int* returnReversed( int* arrPtr, int size){
	int *fwdPtr = arrPtr, *bkwPtr = (arrPtr+size-1);
	//swaps outer elements, moving inward until center is reached
	while ( fwdPtr < bkwPtr) swap( fwdPtr++, bkwPtr--);
	return arrPtr; //return pointer to original array
}

//func5
//returns reversed copy, preserves original
int* returnNewReversed( const int* arrPtr, int size){
	int* revArrPtr = new int[size]; //ptr to hold new array
	int* fwdPtr = revArrPtr; //ptr for traversing & writing to new array
	const int* bkwPtr = (arrPtr+size-1); //read-only ptr for scanning old array
	while ( fwdPtr < (revArrPtr+size) ) *fwdPtr++ = *bkwPtr--; //copy to fwdPtr forwards as bkwPtr scans backwards
	return revArrPtr; //return new array
}


