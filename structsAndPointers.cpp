/*
  Intro/Tutorial/Demo:
  Structs With Pointers
  WE GOIN IN DEEP FAM, BRACE YOSELVES
===========================
Code by Jason Lillard, 2017
===========================
*/
#include <cstdio> //used for output & formatting instead of iostream & iomanip
#include <string> //for example 1, showing that strings are objects just like structs are
#include <cstring> //used for memset (just to make one horizontal break)
//struct doesn't need a library, it is part of the c language.
using namespace std;

struct SimpleStruct{float data;}; //a struct containing a single float as a member

struct FPtrStruct{float* fPtr;}; //a struct containing a pointer to float as a member

int main(){
	puts( 	"\n\n\tStructs And Pointers\n"
			"Structs and pointers can get complicated, and much of your first advanced c++\n"
        	"college classes will be devoted to topics like pointers to structs,\n"
        	"structs with pointers to dynamic arrays, pointers to dynamic arrays of structs,\n"
        	"and dynamic structs with pointers to other dynamic structs\n"
			"(which covers data structures like Linked Lists, Trees, and Graphs).\n"
        	"I cannot hope to exhaustively teach all of those things here, but hopefully\n"
        	"this intro will give you enough to experiment with to discover more possibilities.\n");

         
    //print horizontal break (variation 1)
	for(int i=0;i<32;i++)putchar('=');putchar('\n');
    
	
  //let's start with the simplest: a pointer to a struct, class, obj.
  	{
  		//let's make a string and use its constructor (just to warm up to using struct & class constructors)
		string str( "First: strings are instances of a class.\nWe can make string pointers set to the addresses of strings." );
		
	    string* strptr; //this makes a pointer to a string object 
	    strptr = &str; //we set our string pointer to the address of our string instance "str"
	    
		//concat string using operator+=
	    *strptr += ",\nTheir functions and operator overloads can be accessed through the pointer as well."; 
	    
	    puts( strptr->c_str() );//using our object pointer, print the string's data returned from its accessor
	    //notice that when we access an object's data or functions through a pointer, we have to use the -> "arrow operator" 
  	}

	
	//print horizontal break (variation 2)
	puts(string(32, '=').c_str() ); //construct a string with 32 '=' symbols, then get that string's c_string to print with puts

	
  	{
  	puts("structs we make can be pointed to by struct pointers, just like we can with strings.");
  	SimpleStruct sStruct; //create a simpleStruct instance named sStruct
  	SimpleStruct* structPtr; //create a pointer to a simpleStruct named structPtr
  	structPtr = &sStruct; //set structPtr to hold address of our simpleStruct instance
  	//let's set data in sStruct, then access it through the pointer to it. 
  	sStruct.data = 3.1416;
  	printf("sStruct's data accessed through the object itself (sStruct.data): %.4f\n" //"%.4f means a float with fixed setprecision 4
    		"Accessed through the pointer (structPtr->data): %.4f\n",
    		sStruct.data, structPtr->data ); //notice that using the pointer we have to use the -> "arrow operator" 
	} //enclosing block used to clean up variables & so I can re-use the names.
	
  	
	{//print horizontal break (variation 3)
	//use memset to fill cstring horizbreak with '=' chars, then print with puts
  		char horizbreak[33]{}; memset(horizbreak, '=', 32); puts(horizbreak); 
	} //(these braces aren't needed, just used to clean up temp variables that won't be needed anymore)

	
  	{
	puts("Here we'll use a pointer to a struct to dynamically allocate an array of structs.\n");
	const size_t ARRSZ = 30;
	SimpleStruct* structPtr = new SimpleStruct[ARRSZ];
	//let's fill the data of these structs with a simple sequence
	puts("Filling objects' data with numbers...");
	//and let's use a few different ways of accessing the data, just because we can.
	structPtr->data = 1; //first term (set using array ptr, which points to index 0)
	structPtr[1].data = 2; //second term (set using array ptr + subscript notation)
	//now for the other terms, let's make a pointer to use as an "iterator" to access the other elements
	SimpleStruct* iter = (structPtr+2); //initializing iterator with base array address + index
	for( int i = 2  ; i < ARRSZ; i++, iter++ ){ //pointer incrementation here for ease (not required, could be in loop)
			iter->data = (iter-2)->data  +  (iter-1)->data; //terms 3 and up are made from adding previous two terms.
			//note that because we're using an iterator, we don't need to use our loop counter
			//to access elements (e.g. iter[i] = iter[i-1]+iter[i-2] )
		}//this sequence, btw, is the Fibbonacci Series (except I skipped the extra 1 at the beginning.)
  	//the sequence itself is not especially useful to us here, but the algorithm for making it
  	//forces us to access multiple elements as we build the series, which makes it good for demo purposes
  
  	//print array of data 
  	puts("Our dynamically allocated Fibbonacci Series:");
  	for(int i = 0; i < ARRSZ; i++){
		printf("%7.0f ", structPtr[i].data ); //print out data using subscript notation (& loop counter)
		if ( (i+1)%5==0)putchar('\n'); //every 5 elements print newline
	}//end for loop
  	
  	//WARNING: dynamic memory doesn't get deleted just because it falls out of scope
  	puts("\nNow deleting dynamic array of objects & nullifying array pointer...");
  	delete [] structPtr;
  	structPtr = NULL;
  	}
  	
  	{//print horizontal line break (variation 4)
		char hb[33]{}; char*c=hb; while(c<hb+32)*c++='='; puts(hb);
	}
	
	//using a struct with a pointer inside
	{
		puts("Now lets use a struct containing a pointer to point to a local variable...");
		float localFloat = 2.7182818; //a regular float (math constant "e", Euler's number, btw)
		FPtrStruct objWithPtr; //a struct containing a pointer to a float
		objWithPtr.fPtr = &localFloat; //here we assign the object's pointer to our local variable's address
		printf( "Local Variable's Value accessed through object's held pointer (*objWithPtr.fPtr):\n"
				"%f\n", *objWithPtr.fPtr ); //the * deref's fPtr, not the struct itself. Works like "objWithPtr.*fPtr"
		puts(	"This is the easy version of an object with a pointer, even though the * symbol before\n"
				"the struct name instead of the pointer name makes this syntax a little strange\n"
				"A pointer in a struct can also be used to dynamically allocate an array.\n"
				"The syntax for this is even more strange. All of this takes a while to memorize.\n"
				"If this is your first time working with pointers and structs, you may want to\n"
				"take a break here.");
	}
	
	{ //print horizontal line break (variation 5)
		char*hb=new char[32];char*it=hb;while(it<hb+32)*it++='=';it=hb;while(it<hb+32)putchar(*it++);
		putchar('\n'); delete[]hb;
	}
	
	//using a struct with a pointer inside to dynamically allocate an array
	{
		puts("Using a struct with a pointer to dynamically allocate an array:");
		FPtrStruct objWithPtr; //a struct with a pointer we'll use for dynamic allocation
		const size_t ARRSZ = 32;
		puts("We create the array with: objWithPtr.fPtr = new float[32]");
		//dynamic allocation in a struct still uses "new datatype [ size ]" format
		objWithPtr.fPtr = new float[ARRSZ]; //access pointer in object with "dot operator" i.e. "."
		puts("We access elements inside with: objWithPtr.fPtr[i]");
		for(int i = 0; i < ARRSZ; i++) objWithPtr.fPtr[i] = 1<<i; //fill with 32 powers of 2 
		//Uses right bit-shift, x<<i = x multiplied by 2 i number of times
		
		//now let's print out the array using the slightly more complicated syntax
		puts("We can also access elements inside with: *(objWithPtr.fptr+i)");
		for (int i = 0; i < ARRSZ; i++){
			printf("%-12.0f ", *(objWithPtr.fPtr+i) );
			if ( (i+1)%4==0)putchar('\n');
		}
		puts("Oh, look. We blew up our float.\n"
				"I didn't even know those could overflow. Oh well, moving on...\n"
				"Don't forget to delete the array & nullify the pointer.\n"
				"the command \"delete []\" still works, and we use \".\" to access the ptr:\n"
				"delete [] objWithPtr.fPtr");
		puts( "objWithPtr.fPtr = NULL");
		delete [] objWithPtr.fPtr; //delete the array, or "de-allocate" it from memory. Frees the memory for reuse.
		objWithPtr.fPtr = NULL; //nullify pointer to keep from accessing de-allocated memory
	}

	
	{ //draw horizontal line break (variation 6)
		//use ascii codes in hex, labels, and goto, because MUAHAHAHAHAHAHAHAHAHA
		//(only do this kind of code obfuscation if you don't even care about understanding your own code)
		char i=0;putStart:putchar(0x3D);if(++i>31)goto putEnd; goto putStart; putEnd:putchar(0x0A);
	}

	
	{
		puts(	"Last example for today: dynamically allocating any array of structs\n"
				"which each contain a dynamically allocated array of structs.\n"
				"This may seem insane, but the idea is essentially the same as a\n"
				"dynamic 2D array, or a vector of vectors, which you've likely seen before\n");
		
		//first we have to make our pointer to our dynamic array of objects (1D array)
		//let's make this array 8 rows x 16 columns
		const size_t ROWS = 8, COLS = 16;
		puts("First, use the struct pointer to allocate our rows:");
		FPtrStruct* structPtr = new FPtrStruct[ROWS];
		//now, at this point we still don't actually have any float variables
		//we can print or set or anything like that. We just have a bunch of objects
		//which each have a pointer to a float. That pointer, though, will be used
		// to make a separate array inside of each of our objects. This will give us our 2D array.
		puts("Then use the struct pointer to access each float pointer to make a float array.");
		for (int r = 0; r < ROWS; r++){ //for each row
			structPtr[r].fPtr = new float[COLS]; //make an array of floats
			//structPtr[r] accesses our FPtrStruct array
			// .fPtr accesses the float pointer in struct index [r]
			// = new float[COLS] allocates a new array of floats to be held by the float pointer
		}
		puts(	"Now we can actually populate our matrix\n"
				"(and output in the same loop to save space here):");
		//currently this 2D array -- or "matrix" -- is uninitialized. Let's fill it
		//with something simple since we're almost at 200 lines of code for this tutorial.
		for(int y = 0; y < ROWS; y++){
			for(int x = 0; x < COLS; x++){
				//ASSIGN
				//we can't use structPtr[y][x] to access elements,
				//but we can use syntax that is fairly similar:
				//structPointer[row].arrayPointer[col]
				structPtr[y].fPtr[x] = (y+1)*(x+1); //make simple multiplication table
				//notice in this syntax we have to access our float ptr after our struct ptr
				//OUTPUT
				//we can also access elements with pointer arithmetic syntax 
				//if we hate ourselves:	*((*(structPointer+row)).arrayPointer+col)
				printf("%3.0f ",  *((*(structPtr+y)).fPtr+x)  ) ; //notice the horrendous syntax. Don't use it.
			//	printf("%3.0f ",  structPtr[y].fPtr[x]  ) ; //this is enough to remember
			}
			putchar('\n'); //after printing each column in the row, print newline
		}
		
		puts("After we're done with our dynamic 2D array using structs, we\n"
				"have to call delete [] on each of our float arrays (in a loop),\n"
				"then call delete [] on our struct array.");
		for( int row = 0; row < ROWS; row++){
			delete [] structPtr[row].fPtr; //delete the float array in our current row
			structPtr[row].fPtr = NULL; //(probably not needed here since we're deleting whole matrix, 
			//but setting array ptr to null after freeing dynamic memory is a good habit)
		}
		//delete the array of structs
		delete[] structPtr;
		structPtr = NULL;
		//all clean, and now none of the de-allocated elements can be accidentally accessed.
	}	

		
	{ //draw horizontal line break (variation 7)
		puts("================================"); //thought I'd save the best for last, huh? Nope.
	}
	
	//outro
	puts(	"When all of this gets too easy for you, then it is time for you\n"
			"to move on to studying Linked-Lists and Binary Search Trees.\n"
			"Thanks for reading! -- Keep up the hard work!\n\n");
	return 0;		
}
