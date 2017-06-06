/*
	Swap Anything in Memory
	(Without Templates or Overrides)
	===========================
	Code by Jason Lillard, 2017
	===========================
*/

#include <cstdio>
using namespace std;
//swap anything without templates or overrides
void swapMem( void * x, void * y, size_t byteSize); //give pointer to first data block, second data block, and size (in bytes) to swap
void swapByte(char * x, char * y); //swap one byte (as a char)

int main(){
	float f1 = 3.141592654;
	float f2 = f1*f1;
	
	printf("%f, %f\n", f1, f2);
	puts("Calling swapMem with float.");
	swapMem ( &f1, &f2, sizeof(float) );
	printf("%f, %f\n", f1, f2);
	
	double d1 = 1234.56789;
	double d2 = d1*d1;
	
	puts("Calling swapMem with double.");
	printf("%f, %f\n", d1, d2);
	swapMem ( &d1, &d2, sizeof(double) );
	printf("%f, %f\n", d1, d2);
	
	unsigned long ul1 = 654321;
	unsigned long ul2 = 456789;
	
	puts("Calling swapMem with unsigned long");
	printf("%d, %d\n", ul1, ul2);
	swapMem( &ul1, &ul2, sizeof(unsigned long) );
	printf("%d, %d\n", ul1, ul2);
	
	size_t ARRSZ = 10;
	int * i_arr1 = new int[ARRSZ];
	int * i_arr2 = new int[ARRSZ];
	for(int i = 0; i < ARRSZ; i++){
		*(i_arr1+i) = (i+1);
		*(i_arr2+i) = 10*(i+1);	
	}
	
	for(int i = 0; i < ARRSZ; i++) printf("Array 1, i:%d val:%d\n", i, i_arr1[i] );
	for(int i = 0; i < ARRSZ; i++) printf("Array 2, i:%d val:%d\n", i, i_arr2[i] );
	
	puts("Swapping int array with swapMem");
	swapMem ( i_arr1, i_arr2, sizeof(int)*ARRSZ );
	
	for(int i = 0; i < ARRSZ; i++) printf("Array 1, i:%d val:%d\n", i, i_arr1[i] );
	for(int i = 0; i < ARRSZ; i++) printf("Array 2, i:%d val:%d\n", i, i_arr2[i] );
}

//SWAP ANY NUMBER OF BYTES IN MEMORY
void swapMem ( void * x, void * y, size_t byteSize){
	char * c_x = (char*)x;
	char * c_y = (char*)y;
	for(int i = 0; i < byteSize; i++) {
		swapByte ( c_x++ , c_y++ );
	}
}
//SWAP A SINGLE BYTE IN MEMORY
void swapByte (char * x, char * y){
	char t = *x;
	*x = *y;
	*y = t;
}
