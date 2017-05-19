/*
	Reversing Arrays - early draft
	===========================
	Code by Jason Lillard, 2017
	===========================
*/
#include <iostream>
using namespace std;

//swap function used by all functions here
void swap(int &item1, int &item2){ int temp = item1; item1 = item2; item2 = temp;}
void swap(int *item1, int *item2){ int temp = *item1; *item1 = *item2; *item2 = temp;}

void reverseArray( int arr[], int size);

void recursiveRevArray( int arr[], int start, int end);
void recursiveRevArray( int* startPtr, int* endPtr);

int* returnReversed( int* arrPtr, int size);
int* returnNewReversed( int* arrPtr, int size);

int main(){
	//EVERYTHING IS UNTESTED
	//COPYPASTA AT OWN RISK
	return 0;
}

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

//rearranges original
void recursiveRevArray( int arr[], int start, int end){
	//swaps outer elements, moving inward until center is reached
	if (start<end){
		swap( arr[start], arr[end]);
		recursiveRevArray (arr, start+1, end-1);
	}
}

//rearranges original
void recursiveRevArray( int* startPtr, int* endPtr){
//swaps outer elements, moving inward until center is reached
	if (startPtr<endPtr){
		swap( startPtr, endPtr );
		recursiveRevArray (++startPtr, ++endPtr);
	}
}

int* returnReversed( int* arrPtr, int size){
	int *fwdPtr = arrPtr, *bkwPtr = (arrPtr+size-1);
	while ( fwdPtr < bkwPtr) swap( *fwdPtr++, *bkwPtr++);
	return arrPtr;
}


int* returnNewReversed( int* arrPtr, int size){
	int* revArrPtr = new int[size];
	int* fwdPtr = revArrPtr, *bkwPtr = (arrPtr+size-1);
	while ( fwdPtr < (revArrPtr+size) ) swap( *fwdPtr++, *bkwPtr++);
	return revArrPtr;
}


