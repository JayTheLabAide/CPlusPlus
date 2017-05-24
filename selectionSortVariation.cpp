/*
	Selection Sort Variation
	
	Premise:
	With two helper functions, swap and indexOfMaxVal, 
	selection sort can be reduced to just a few lines
	(which might be a little easier to understand than what
	the textbooks usually have as their example selectionSort)
	
	===========================
	Code by Jason Lillard, 2017
	===========================
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;


//selection sort prototype (function below main)
void selectionSort(int arr[], int size);

//short utility functions (no prototypes):

//USED IN SELECTION SORT
void swapInts(int &x, int &y){ int t = x; x = y; y = t;} //swap -- set x to y and y to x using temp variable t 

//USED IN SELECTION SORT
int indexOfMaxVal(int arr[], int size){ //return index of highest value in array
	//input validation
	if (arr==0 || size < 1) return -1; //if ptr is null or size is invalid, return -1
	//simplified computation
	else if (size==1) return 0; //if array is only one element, that's the largest element, return index 0
	
	//else, scan for highest value and also highest index (value can be found w/o index, index can't be found w/o value)
	int maxVal = arr[0]; //current highest value (before any comparisons)
	int maxIndex = 0; //current index of highest element (before any comparisons)
	for (int i = 1; i < size; i++){ //go through each element in range
		if (arr[i]>maxVal) { //if any element's value > maxVal,
			maxVal=arr[i]; // save that current element's value in maxVal
			maxIndex=i; //and then save the current element's index (this may be our return result)
		}
	}
	//After every element has been checked to find the max, return what index we found it at: maxIndex.
	return maxIndex;
}

//FUNCTIONS USED FOR DEMO PURPOSES (NOT NEEDED IN SELECTION SORT)
//Seed rand
void initRand(){ srand(time(0) );} //seed random number generator with the current "unix" time

//rand int within range
int randInt( int min, int max){ //ONLY USE AFTER CALLING initRand() or srand(time(0))
	return (min+(rand()%(max-min+1)));
}
//fill entire array with random values
void fillArray(int* arr, int size){ //NEEDS randInt(int, int)
	const int MIN = -9999, MAX = 9999; //change range of random numbers here
	for (int i = 0; i < size ; i++){
		*(arr+i) = randInt(MIN, MAX); //*(arr+i) equivalent to arr[i]
	}
}

void printArray(int* arr, int size){
	for (int i = 0; i < size ; i++){
		printf("%7d ", *(arr+i) ); //printf in cstdio. 
		//"%7d" means right-aligned, fieldwidth 7, d means digit.
		// *(arr+i) equivalent to arr[i]
		if ( (i+1)%10==0 ) cout<<"\n"; //every 10 elements, print newline
	}
	cout<<"\n"<<endl;//print 2 newlines and flush output buffer
}

//================================================================================================================
//MAIN
int main(){
	
	//first, always seed your random number generator
	initRand();
	//make test array
	const int ARRSZ = 20;
	int myArray[ ARRSZ ];
	//fill test array with random numbers using helper function
	fillArray( myArray, ARRSZ); 
	//print randomly filled array using helper function
	cout<<"Unsorted Array:\n";
	printArray( myArray, ARRSZ);
	
	//sort array using selectionSort
	cout<<"Sorted Array:\n";
	selectionSort(myArray, ARRSZ);
	//print sorted array using helper function
	printArray( myArray, ARRSZ);
	//if array isn't sorted, you broke something
	return 0;
}
//END MAIN
//================================================================================================================

//THE HEADLINE ACT: SELECTION SORT
void selectionSort(int arr[], int size){
	for(int i = size-1; i >= 1; i--){ //step backwards through each index in the array (except the first)
		//swap highest valued element with element at index i
		swap( arr[i], arr[ indexOfMaxVal(arr,i+1) ] );  //$$$$ See explanatory note below function
		//^^^^ this could be broken into 2 lines:
		// int indexOfMax = indexOfMaxVal(arr,i+1);
		// swap( arr[i], arr[indexOfMax];
	}
}
/*
	$$$$ Explanatory Note:
	//i is index (so it has to start at size-1), but indexOfMaxVal takes an array and size, so pass i+1
	//Here we call indexOfMax with decreasing size because once we find the highest valued element
	//and put it at the end of our current range, it is considered sorted, so we can leave it out
	//and find the next-highest-valued element, place that at the end of the unsorted range, and keep looping
	//until only one element is left, and that doesn't have to be swapped with anything.
	//After this for loop breaks and the last element is left unswapped, the array is sorted.
	
	//Advanced Notes:
	This selection sort might look special, but it doesn't use recursion (just plain iteration)
	and still has worst-case time complexity of O(n^2), like all selection sorts, which have to go through the whole
	array of n elements n number of times to do every comparision. 
	If that's confusing, remember this: indexOfMaxVal goes through the whole array, 
	and selectionSort goes through the whole array, calling indexOfMaxVal once for each element.
	That means roughly arraySize * arraySize number of operations, meaning O(n*n) time, or O(n^2)

	HeapSort works through a similar algorithm: by finding the largest value in a range and swapping it with the last element 
	in the range, then shrinking the range for the next iteration. HeapSort can use the still-unsorted region as the "heap"
	to find the next-largest value. It also finds the max index faster than our linear search function indexOfMaxVal does,
	which is why it is superior to selection sorts (but also more complicated to implement).
*/
