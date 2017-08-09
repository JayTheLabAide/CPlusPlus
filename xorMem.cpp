/*
	XOR Anything in Memory
	(Without Templates or Overrides For Each Data Type)
	===========================
	Code by Jason Lillard, 2017
	===========================
*/

#include <cstdio> //for demo output
using namespace std;

//WARNING: ALL FUNCTIONS WILL FAIL SILENTLY IF PASSED NULL POINTERS

//FUNCTION 1
//xor one space of memory with another, store over first space
void xorMem( void * x, void * y, size_t byteSize); //give pointer to first data block, second data block, and size (in bytes) to xor

//FUNCTION 2
//xor one space of memory with another, store result at a third space (arrays x and y left unaltered)
void xorMem( void * x, void * y, void * z, size_t byteSize); //give pointer three data blocks, and size (in bytes) to xor
// ALLOCATE MEMORY IN Z BEFORE CALLING XORMEM OR YOU MIGHT DESTROY YOUR OWN DATA SOMEWHERE ELSE

//FUNCTION 3
//xor one space of memory of any size with a key of any size
void xorMemByKey( void * x, size_t memByteSize, void * y, size_t keyByteSize);


//BEGIN MAIN
int main(){
	//three features of xor will help us test this:
	//1. Any number xor all 1s = the one's complement (or ~, bitwise not) of the number
	//2. Any number xor itself = 0, (each bit set to 1 gets xor'ed with 1, setting it to 0, and similarly each 0 xor 0 = 0
	//3. Numbers/Characters encrypted with a key using xor can be unencrypted using the same key
	
	//our arrays for testing
	const int ARRSZ = 7;
	int arr1[ARRSZ], arr2[ARRSZ], arr3[ARRSZ];
	printf("Array 1 starting values, 1-%d\n", ARRSZ);
	for(int i = 0; i < ARRSZ; i++){
		arr1[i] = 1+i; //fill array1 with 1 through ARRSZ
		arr2[i] = 0xFFFFFFFF; // fill array2 with all bits set to 1
		printf("arr1[%d]=%d\n", i, arr1[i] ); //print arr1[i]
	}
	puts("All bits in Array 2 set to 1 (hex F = binary 1111 ):");
	for(int i = 0; i < ARRSZ; i++){
		printf("arr2[%d]=0x%x\n", i, arr2[i] ); //print arr2[i]
	}
	
	puts("Testing function 1 by getting \"one's complement\" (negative minus 1) of Array 1\n"
			"by xor-ing it with Array 2. (Result stored in Array 1):");
	//TESTING FUNCTION 1
	xorMem( arr1, arr2, ARRSZ*sizeof(int) );  //byteSize = arraySize * sizeof(dataType)
	for(int i = 0; i < ARRSZ; i++){
		printf("arr1[%d]=%d\n", i, arr1[i] ); //print arr1[i]
	}
	
	//TESTING FUNCTION 2
	puts("Testing function 2 by undoing one's complement in Array 1,\n"
			"but storing the result in Array 3");
	xorMem( arr1, arr2, arr3, ARRSZ*sizeof(int) ); //uses same key in arr2 to get one's complement with xor
	puts("Arr1:");
	for(int i = 0; i < ARRSZ; i++){
		printf("arr1[%d]=%d\n", i, arr1[i] ); //print arr1[i]
	}
	puts("Arr3:");
	for(int i = 0; i < ARRSZ; i++){
		printf("arr3[%d]=%d\n", i, arr3[i] ); //print arr3[i]
	}

	char KEY[] = "sEcReT!"; //encryption string to use as our "key" array
	const size_t KEYLEN = 7; //not counting null terminator. Whether you do or not is optional.
	//TESTING FUNCTION 3
	printf("Testing function 3 by encrypting and decrypting Array 1 with key:\"%s\":\n", KEY);

	
	xorMemByKey( arr1, ARRSZ*sizeof(int), &KEY, KEYLEN*sizeof(char) ); //pass address of KEY here since it isn't a pointer
	// note sizeof(char) is 1, but this proper calling procedure is shown here
	// in case your key isn't of type char
	puts("Array 1 Encrypted:");
	for(int i = 0; i < ARRSZ; i++){
		printf("arr1[%d]=%d\n", i, arr1[i] ); //print arr1[i]
	}
	
	xorMemByKey( arr1, ARRSZ*sizeof(int), KEY, KEYLEN*sizeof(char) );
	
	puts("Array 1 Decrypted:");
	for(int i = 0; i < ARRSZ; i++){
		printf("arr1[%d]=%d\n", i, arr1[i] ); //print arr1[i]
	}
	
	puts("Now using a single char set to 0xff as a key to get one's complement\n"
			"of Array 1, instead of using the entirety of Array 2:");
	char CHARKEY = 0xff;
	xorMemByKey ( arr1, ARRSZ*sizeof(int), &CHARKEY, 1); //charkey is only 1 byte
	for(int i = 0; i < ARRSZ; i++){
		printf("arr1[%d]=%d\n", i, arr1[i] ); //print arr1[i]
	}
	
	//FUNCTION 1
	puts("Finally, zero-ing out each array by xor-ing it with itself\n"
			"This can't be done with a key for Array1 or Array3,\n"
			"but since Array2 has each byte identical, it can be zeroed with a key:");
	
	puts("Before xor self:");
	for(int i = 0; i < ARRSZ; i++){
		printf("arr1[%d]=%d\n", i, arr1[i] ); //print arr1[i]
	}
	for(int i = 0; i < ARRSZ; i++){
		printf("arr2[%d]=%d\n", i, arr2[i] ); //print arr2[i]
	}
	for(int i = 0; i < ARRSZ; i++){
		printf("arr3[%d]=%d\n", i, arr3[i] ); //print arr3[i]
	}
	const size_t BYTESZ = ARRSZ*sizeof(int); //we really should be using a constant for this
	xorMem(arr1, arr1, BYTESZ );
	
	xorMemByKey( arr2, BYTESZ, &CHARKEY, 1 ); //remember CHARKEY is 0xff, and each element of arr2 is 0xffff_ffff
	
	xorMem(arr3, arr3, BYTESZ );
	
	puts("After xor self (each bit is \"bleached\"):");
	for(int i = 0; i < ARRSZ; i++){
		printf("arr1[%d]=%d\n", i, arr1[i] ); //print arr1[i]
	}
	for(int i = 0; i < ARRSZ; i++){
		printf("arr2[%d]=%d\n", i, arr2[i] ); //print arr2[i]
	}
	for(int i = 0; i < ARRSZ; i++){
		printf("arr3[%d]=%d\n", i, arr3[i] ); //print arr3[i]
	}
	
	
	
	return 0;
	
}

//FUNCTION IMPLEMENTATIONS

//FUNCTION 1
void xorMem ( void * x, void * y, size_t byteSize){
	
	if ( !(x&&y) ) return; //silently fail if any pointers are null
	
	char * c_x = (char*)x; //cast void pointer x to a local char pointer
	char * c_y = (char*)y; //cast void pointer y to a local char pointer
	for(int i = 0; i < byteSize; i++) { //for each byte of array (i.e. for each char)
		*c_x ^= *c_y; // x = x xor y
		c_x++; c_y++; //increment pointers
	}
}

//FUNCTION 2
void xorMem( void * x, void * y, void * z, size_t byteSize){ //give pointer to first data block, second data block, and size (in bytes) to xor

	if ( !(x&&y&&z) ) return; //silently fail if any pointers are null
	
	char * c_x = (char*)x;
	char * c_y = (char*)y;
	char * c_z = (char*)z;
	
	// notice malloc returns a void pointer to allocated memory block.
	for(int i = 0; i < byteSize; i++) {
		*c_z = *c_x ^ *c_y; // z = x xor y
		c_x++; c_y++; c_z++;//increment pointers
	}
}


// Misuse warning: You won't have much luck making ransomware out of this alone -- the operating system will prevent
// you from encrypting anything marked as read-only, and most important programs are access-protected.
// If you are not careful messing around with this, though, you could very well encrypt something and
// lose the key, effectively corrupting your data. 
// I suggest you not use any important documents for your encryption tests.
void xorMemByKey(void * x, size_t memByteSize, void * y, size_t keyByteSize){
	if ( !(x&&y) ) return; //silently fail if pointers are null
	
	//character pointers to process memory blocks
	char * c_x = (char*)x; 
	char * c_y = (char*)y;
	
	for ( size_t memByte = 0 ; memByte < memByteSize; memByte++ ){ //for each byte of what we're encrypting
		c_x[ memByte ] ^= c_y[ memByte%keyByteSize]; //xor with a byte from the key
		// memByte is simple counter
		// memByte%keyByteSize will scroll through given key repeatedly as memByte is incremented
		// e.g. if the key is only 4 bytes, memByte%4 will always give you 0 through 3,
		// which are the valid indices you can access at c_y, your key
	}
}
