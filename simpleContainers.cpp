/*
	Static and Dynamic Array Containers
===========================
Code by Jason Lillard, 2017
===========================
*/
#include <iostream>
using namespace std;

//let's make a few simple "container" structs.
//these will pop up all over the place in programming,
//as they are inherently more useful than raw arrays
//for a few very good reasons:
//1. they often know their own size
//2. they easily can prevent out-of-bounds access
//3. if dynamic memory is used, containers can de-allocate that memory in a destructor
//4. useful functions like printing, sorting, and searching can be build into the container itself

//Here we'll look build and examine 5 custom structs:
// ArrayStruct, SafeArray, SearchArray, DynamicArray, and DynamicMatrix

//let's get started:
//here is a very simple structure that cannot prevent out-of-bounds access, and doesn't
//use any kind of dynamic memory, member functions, constructors, or destructors.
struct ArrayStruct{ //this will be a very simple struct named arrayStruct
	//a shared constant like SIZE should be "static" so only one copy exists in memory
	static const size_t SIZE=15; //this variable will be saved inside our ArrayStructs
	char array[SIZE]{}; //Here we initialize our char array to 15 null terminators
}; //notice the semicolon at the end of the struct/class definition

/////////////////////////////////////////////////////////////////////////////////////////

//to make a slightly upgraded version of our arrayStruct, let's prevent out-of-bounds access
//with safe "setter" and "getter" functions required to access single elements
struct SafeArray{
	public: //our size constant can't be changed, so there's no harm making it public
		static const size_t SIZE=15;
	private: //"hide" our array from public access
		char array[SIZE]{};
	public: 
	//here are the safe "setter" and "getter" functions.
		//our public setter function
		void set( size_t index, char c ){ //returns nothing, but takes an unsigned integer and a char
			if (index < SIZE) array[index] = c;//if index is in bounds, set element to given char
		}
		
		//our public getter function:
		char get( size_t index ){//takes in an index between 0 and SIZE-1, and returns that element
			char result = EOF; //default result is EOF marker
			if (index < SIZE) result = array[index]; //if index is valid, return element
			return result; 
			//returning something like EOF, which wouldn't normally be stored in the array,
			//makes it easy to test the return result from get() to see if attempt failed.
		}
		
}; //end SafeArray. Note the semicolon.

/////////////////////////////////////////////////////////////////////////////////////////

//Now let's make a searchable verison of our safeArray. This time let's also make this
//blueprint for a "class" instead of for a "struct". "Access" in a struct is public by default,
//but access in a class is private -- which is better for "safe" or ecapsulated objects
class SearchArray{
	public:
		static const size_t SIZE=15; //safe to be public b/c it is a constant
	private:
		char array[SIZE]{}; //here we make our array just like before
	public:
		//our public setter function, now returns a bool
		bool set( size_t index, char c ){ //returns success or failure at saving 
			if (index < SIZE) { //if index is in bounds
				array[index] = c; //set element to given char
				return true; //indicate save was successful
			}
			//else, index was invalid; return "failure"
			return false;
		}
		
		//our getter function (dual-exit version)
		char get( size_t index ) const { //const here in our func header means no class members will be altered
			if (index < SIZE) return array[index]; //if index is valid, return element
			return EOF; //if index was invalid, return an EOF marker
		}
		
		//Now let's make a helpful function that you've likely made to search your own arrays
		//Our searching function, takes a char to search array for and returns the index where found or -1
		int searchChar( char c ) const { //(this is a const function: alters no members)
			//if any element matches, return index of that element
			for (int i = 0; i < SIZE; i++) if (array[i] == c) return i; 
			return -1; //otherwise return -1 to indicate "not found"
			//(because we may return a -1, we cannot use size_t as our return type)
		}
}; //end SearchArray, note the semicolon

/////////////////////////////////////////////////////////////////////////////////////////

//now let's make a class with a dynamic array, so we can resize it (like a string or vector)
class DynamicArray{
	private:
		//make size private since it can be changed
		size_t size; //not constant, changes from instance to instance
		char * arrayPtr; //pointer to hold dynamic character array
		
	public:
		//constructor -- with default argument to serve here also as the "parameter-less" constructor
		DynamicArray( size_t arraySize=15) { //constructor has no return type & same name as struct/class
			puts("DynamicArray Constructor Called! Building Object...");
			if (arraySize == 0 ) arraySize = 1; //force array to minimum size of 1
			//now allocate array
			size = arraySize; //set given size to our size_t variable
			arrayPtr = new char[size];
			for(int i = 0; i < size; i++) arrayPtr[i]=0; //initialize array to 0
		}
		//destructor
		~DynamicArray(){ //destructor has ~ then class name. Cannot have paramters!
			puts("DynamicArray Destructor Called! Deleting Object...");
			delete [] arrayPtr; //de-allocate memory when object falls out of scope
		}
		
		//our public setter function, returns a bool, single exit
		bool set( size_t index, char c){ //returns success or failure at saving 
			bool success = false;
			if ( index < size) { //if index is in bounds
				*(arrayPtr+index) = c; //set element to given char
				success = true; //success flag set to true
			}
			//return failure if index was invalid, true if element was set successfully
			return success;
		}
		
		//getter for size since now size is variable
		const size_t getSize() const{ return size;} //returns a const size_t, and is a const function (alters no members)
	
		//An option for our getter function: returns pointer to result, or null. 
		const char * getPtr( size_t index ) const { //const in our func header means no class members will be altered
			const char * result = NULL; //our result is null by default, set to an element if index is valid
			if ( index < size) result = (arrayPtr+index); //return address of result with (baseAddress+index)
			return result; //invalid access attempt recieves a null pointer
		}
		
		//A more sensible option for our getter function:
		//Return value or EOF (like our other classes)
		char get(size_t index) const {
			if ( index < size ) return *(arrayPtr+index);
			return EOF; //if index was out of bounds, return EOF
		}
		
		//here's something you can't do with the other containers: RESIZE YOUR DYNAMIC ARRAY
		bool resize(size_t newSize){ //returns true if successful
			//minimum size is 1. 
			//We could delete the array if newSize is zero, but that would require us
			// to test if arrayPtr is null in every other member function accessing the array
			if ( newSize == 0 ) return false;
			else if ( newSize == size ) return true; //if resize to current size, do nothing but return true
			//Here we'll make a new array and copy the elements over.
			//Resizing of dynamic memory can also be done with the cstdlib function "realloc"
			char* arrCopy = new char[newSize]; //make the new array
			
			//for each element in new array, either copy element from old array
			//(if it exists), or fill remainder of new array with zeros
			for (int i = 0; i < newSize ; i++){ 
				if ( i < size ) arrCopy[i] = arrayPtr[i]; //if element exists in old array, copy it
				else arrCopy[i] = 0; //else, initialize copy with 0 (a.k.a. null terminator or '\0')
			}
			//update our size variable
			size = newSize;
			//de-allocate old array
			delete [] arrayPtr;
			//set object's pointer to new resized array
			arrayPtr = arrCopy;
			
			//return success
			return true;
		}
		
		//simple public wrapper for recursive search function
		int search(char c){
			return recursiveSearch(0, c); //startIndex parameter is 0, forward search parameter
		}
		
		private: //private recursive search function (private b/c it's more complicated to use)
		int recursiveSearch(int startIndex, char c){ //startIndex will increment up with each call
			if (startIndex >= size) return -1; //base case: if we've reached end of array, return -1
			else if ( arrayPtr[startIndex] == c ) return startIndex; //success case: if we have a match, return index
			else recursiveSearch(startIndex+1, c); //continue recursive loop: if no match & not at end,
			//call self with our "startIndex" counter plus one. 
			//This could be ++startIndex, but NOT startIndex++
		}
		
		//To do for own study:
		//1. Print Elements Function (Decide if you want to print as ascii chars or as ints)
		//2. Random Fill Function (Useful for games, testing sorting functions)
		//2. Array-Based Sort Function (e.g. Bubble, Cocktail, Selection, Merge, Quick, Heap, etc.)
		//3. Shuffle Elements function -- sometimes useful for game design
		//4. Write to File -- its always good to practice using fstream
		
}; //end DynamicArray. Note the semicolon at the end of the class definition.

/////////////////////////////////////////////////////////////////////////////////////////

class DynamicMatrix{
	private:
		//A matrix is a 2D array. Since we already have a dynamicArray class,
		//we can build our matrix class out of an array of dynamicArray objects... dynamically.
		size_t width, height;
		DynamicArray* matrixPtr;
		
	public:
		DynamicMatrix(size_t width, size_t height){
			puts("DynamicMatrix Constructor Called! Building Object...");
			this->width = ( width > 0 ? width : 1 ); //ensure width is at least 1 (with ternary operator assignment)
			this->height = ( height > 0 ? height : 1);//ensure height is at least 1
			
			matrixPtr = new DynamicArray[height]; //create our array of arrays
			for(int r = 0; r < height; r++) 
				matrixPtr[r].resize(width); //resize each row to our desired width
		}
		
		~DynamicMatrix(){ //matrix destructor
			puts("DynamicMatrix Destructor Called! Deleting Object...");
			//since each object in our array has its own destructor,
			//we can just call delete[] on our matrix pointer
			delete [] matrixPtr;
		}
		
		//You may also swap these paramters to reflect an (x,y) coordinate scheme
		//Anything related to graphics/games/etc. will likely be easier to think of in terms of (x,y) or (col,row)
		char getAt(int row, int col){ //row, col. 
			//In the given row, call the dynamicArray's get(size_t) function w/given col
			return matrixPtr[row].get(col); //just like in a 2D array syntax, here access is in form (row, col)
		}
		
		void setAt(int row, int col, char c){
			matrixPtr[row].set(col, c); //setting using our "setter" func has similar syntax
			// to getting an element from this row and this column.
			//could also be:
			//(*(matrixPtr+row)).set(col, c);
		}
		
		
		//for a print function, we could output this matrix as either ascii chars or integers
		void printChars(){ //print as ascii chars
			for(size_t y = 0; y < height; y++){
				for (size_t x = 0; x < width; x++){
					printf("%c ", matrixPtr[y].get(x) ); //print char from row y, column x
				}
				putchar('\n');
			}
		}
		
		void printInts(){ //print as integers between 0-255
			for(size_t y = 0; y < height; y++){
				for (size_t x = 0; x < width; x++){
					printf("%3d ", matrixPtr[y].get(x) ); //print integer from row y, column x
				}
				putchar('\n');
			}
		}
		//To do for your own study:
		//1. Implement a function: int searchRow(size_t row, char query)
		//		This function returns the index found or -1 if not found in given row
		//2. Implement a function: bool searchMatrix(char query), or char* searchMatrix(char query)
		//		bool version: This function returns true if query is matched in any row.
		//		char* version: This function returns pointer to element if found or nullptr if not found
		//3. Randomly fill Matrix - useful for game design, testing sorting algorithms
		//4. Sort By Column (similar to "sort by price" or "sort by rating" on websites)
		//		This function sorts all the rows based on the values in one column
		//5. Write Matrix to file - probably can't be made by repeatedly calling a similar function in DynamicArray
		//6. Read Matrix from file, load values into current DynamicMatrix object
		
}; //end DynamicMatrix. Semicolon!

/////////////////////////////////////////////////////////////////////////////////////////

//MAIN BEGIN
int main(){
		//ArrayStruct
		puts("\n\tLet's investigate five simple, custom-built containers:\n"
			"ArrayStruct, SafeArray, SearchArray, DynamicArray, and DynamicMatrix\n"
			"\tArrayStruct:\n"
			"Our simple array structure can be filled similarly to an array, we just need to use\n"
			"our object's name, the dot operator \".\", then the usual array name and subscript\n"
			"arrStruct.array[i]");
		
		//let's first make our simplest container
		ArrayStruct arrStruct;//this is one "object" or one "instance of the class"
		//Now let's fill it with data by accessing the public array and SIZE members
		for (int i = 0; i < arrStruct.SIZE ; i++){ //SIZE accessed as non-static member through object name
			//we access members with the object name, the dot operator ".", and then the variable or function name
			arrStruct.array[i] = 'a'+i; //fill with first 15 letters of alphabet
			//notice array is accessed here with  [subscript]  notation
			//could have done as: *(arrStruct.array+i) = 'a'+i;
		}
		//now let's print elements from the same array
		puts("Now that the array is filled, let's print the contents:");
		for (int i = 0; i < ArrayStruct::SIZE ; i++){ //SIZE accessed as static member through class name
			printf("%c ", *(arrStruct.array+i) ); //print data as characters with "%c"
			//notice array here is accessed with  *(pointer)  notation
			//could have done as: printf("%c ", arrStruct.array[i] );
			if ( (i+1)%5==0) putchar('\n'); //every 5 elements, print newline
		}
		puts("\nLet's try unsafe access in ArrayStruct with public array (output has hex):");
		//notice we can still access elements outside of our array's bounds with ArrayStruct
		printf("arrStruct.array[-1]: 0x%x\narrStruct.array[ arrStruct.SIZE+2 ]: 0x%x\n",
				arrStruct.array[-1], arrStruct.array[ arrStruct.SIZE+2] ) ;
		puts("What is displayed at index -1 and index SIZE+2 is undefined\n"
			"and could even be different every time you run the program.\n");
		
		
		//SafeArray
		puts("\n\tSafeArray:");
		//let's make our SafeArray just like our ArrayStruct, fill it, print it, then try to access unsafe elements
		puts("Filling safe array...");
		SafeArray safeArr;
		for(int i = 0; i < SafeArray::SIZE ; i++){
			safeArr.set(i, 'Z'-i ); //using our setter function, let's fill array with last 15 letters of alphabet
		}
		puts("Printing safe array...");
		for (int i = 0; i < safeArr.SIZE ; i++){
			printf("%c ", safeArr.get(i) ); //print each character using our getter function
			if ( (i+1)%5==0)putchar('\n'); //every 5 elements, print newline
		}		
		printf("\nInvalid access attempt in SafeArray with safe getter function:\n"
				"Should each be 0x%x to indicate EOF marker\n", EOF);
		printf("safeArr.get(-1): 0x%x\nsafeArr.get(safeArr.SIZE+2): 0x%x\n",
				safeArr.get(-1), safeArr.get(safeArr.SIZE+2) );
		puts("Since we know what the return value is from an invalid access attempt,\n"
				"any time we call our gettter function we can test to see if that value\n"
				"indicating an error is what we recieved.");
				
				
		//SearchArray
		puts("\n\tSearchArray:");
		SearchArray searchArr;
		puts("Filling and printing searchable array...");
		for(int i = 0; i<SearchArray::SIZE ; i++){ //accessing static member with class name & scope operator
			//using ternary operator to fill array with half upper & half lower case
			searchArr.set( i, (i%2==0? i/2+'a' : i/2+'A') );  //calling .set( size_t, char) to set index i to given char
			//will fill array with "aAbBcCdD" etc.
			
			//let's print the array contents in the same loop for the sake of ease
			printf("%c ", searchArr.get( i ) ); //note that with "get" no subscript or pointer notation needed
		}
		printf("\nSearching for character '%c' in our SearchArray object:\n"
				"Index Result: %d\n", 'f', searchArr.searchChar('f') );
		printf("Searching for character '%c' in our SearchArray object:\n"
				"Index Result: %d\n", '&', searchArr.searchChar('&') );
		
		
		//DynamicArray
		{ //creating a code block to control when our dynamic array is deallocated
			puts("\n\tDynamicArray:");
			puts("Creating...");
			DynamicArray dynArr(26); //build with call to constructor, pass in size of array to allocate
			puts("Filling array...");
			const int ARRSZ = dynArr.getSize(); //here we use a getter to find out our array size.
			//efficiency tip: avoid placing function calls in loop headers. 
			//It takes fewer CPU cycles to call the function once & store it in a temporary variable
			for(int x = 0; x < ARRSZ ; x++){ 
				dynArr.set(x, (x%2==0? x+'a' : x+'A') ); //fill with "aBcDeFgH" etc
				printf("%c ", dynArr.get(x) ); //print element x as a char
				if(!((x+1)%13))putchar('\n'); //every 13 elements, print newline
			}
			
			//search

			printf("\nRecursively searching for character '%c' in our DynamicArray object:\n"
					"Index Result: %d\n", 'F', dynArr.search('F') );
			printf("Recursively searching for character '%c' in our DynamicArray object:\n"
					"Index Result: %d\n", '@', dynArr.search('@') );
			
			//ugly format string for printing 
			// [index: element as hex | as char]
			// (useful for seeing blank elements)
			const char * fmtstr = "[%2d:0x%x | %c] "; //const char pointer to a string literal
			
			//resize
			const size_t NEWSIZE_1 = 16;
			printf("Resizing array to size: %d\n", NEWSIZE_1);
			dynArr.resize( NEWSIZE_1 );
			puts("Printing remaining elements:");
			for(int x = 0; x < NEWSIZE_1; x++){
				printf( fmtstr, x, dynArr.get(x), dynArr.get(x) ); //print element x as hex and as char 
				if(!((x+1)%4))putchar('\n'); //every 4 elements, print newline
			}
			
			//getPtr
			puts("\nUsing our getPtr function, let's get pointers to the last and first element, then\n"
					" print out our array backwards using pointer notation.");
			const char * readPtr = dynArr.getPtr( dynArr.getSize()-1 ); //pointer acting as iterator, starting at end
			const char * arrayStrt = dynArr.getPtr( 0 ); //pointer to beginning of array, used to end backwards loop
			while ( arrayStrt <= readPtr) printf("%c ", *readPtr-- );
			readPtr = arrayStrt = NULL; //Nullify both of our pointers (since we're about to resize our dynamic array,
			//these pointers are about to become obsolete)
			
			//resize again
			const size_t NEWSIZE_2 = 24;
			printf("\nResizing array again to size: %d\n", NEWSIZE_2);
			for(int x = 0; x < NEWSIZE_2; x++){
				printf( fmtstr, x, dynArr.get(x), dynArr.get(x) ); //print index x, & element x as hex and as char 
				if(!((x+1)%4))putchar('\n'); //every 4 elements, print newline
			}
			
			puts("Leaving scope of our code block...goodbye local variables & objects!");
		} //destructor should be called by dynArr when it leaves this scope

		
		//Dynamic Matrix
		puts("\n\tDynamicMatrix:");
		//last one!
		{
			puts(	"When we build our dynamic matrix, we will see constructor messages\n"
					"For each row as it is allocated:");
			size_t width = 8, height = 12;
			//when we build our DynamicMatrix, it needs to know a width and height
			DynamicMatrix dynMatrix(width, height);
			//now we have a space we can fill with dynMatrix's getter function
			puts("Now let's fill the matrix with a nested for loop...");
			for(int y = 0; y < height; y++){ //2D array traversed here with x and y
				for (int x = 0; x < width; x++){
					dynMatrix.setAt(y, x, (x+1)*(y+1) ); //build basic multiplication table
				}
			}
			puts("And print contents as digits and characters...");
			//If we hadn't made our own print functions, we could have printed contents with getAt like this:
			
//			for(int row = 0; row < height; row++){ //2D array traversed here with row and col
//				for (int col = 0; col < width; col++){
//					//print basic multiplication table as digits
//					printf( "%3d ", dynMatrix.getAt( row, col ) ); 
//				}
//				putchar('\n'); //after printing each row, print a newline
//			}

			//but since we made internal print functions, let's use those.
			puts("As integers:");
			dynMatrix.printInts();
			puts("As characters, including newlines, tabs, etc.:");
			dynMatrix.printChars();
			
			puts("At end of block scope, objects' destructors will be called automatically.\n"
				"Note that our Matrix destructor is entered first, and from there each row\n"
				"is deleted and its own destructor is called. This happens in this order because\n"
				"Our Matrix \"has\" each DynamicArray object which together hold the data.\n"
				"If our Matrix \"was\" a DynamicArray (inherited from it), then the order of\n"
				"destructor calls would be different: first DynamicArray, then DynamicMatrix.\n"
				"Inheritence and Polymorphism are topics for another tutorial, though....");
		} //end of code block -- destructors should be automatically invoked here
		
		puts(	"That's it. Thanks for reading. Now you should be ready to\n"
		"study Inheritence, Polymorphism, and Abstract Data Structures!");
}//MAIN END
