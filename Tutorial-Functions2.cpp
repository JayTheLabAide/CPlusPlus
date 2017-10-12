/*
	Functions Tutorial 2
	--------------------
	THIS VERSION IS INCOMPLETE -- SOME FUNCTIONS AREN'T YET TESTED IN MAIN
	You can implement these final tests yourself as an exercise, but I will
	try to finish this tutorial completely over the next week or two.
	--------------------
	Code by Jason Lillard
*/

#include <iostream>
#include <string>
#include <ctime> //for clock() to get # of clock cycles since program start
using namespace std;

/*
	I know the last tutorial was short, so I'll try to get a little more
	detailed in this one. Let's lay out some of the more advanced function
	topics, and go through them slowly. I won't get into handling files here,
	but these subjects usually taught in the second half of your first
	programming class will be the basis of everything else you can do which
	is complex or sophisticated which doesn't involve structs or classes
	(a.k.a "object-oriented programming").
	
1. Const Parameters or Return Types -- const just means read-only. Don't panic.
2. Arrays and Functions -- passing arrays to functions to output or process data
3. Functions and pointers -- passing, returning, and dynamic memory w/pointers
4. Local Static Variables -- functions with some long-term memory.
5. Recursion -- functions which call themselves a few times

Now, any one of these topics could fill a book, but I'll try to show some of the
simpler and more practical uses of some of these items, and where they come up,
I'll try to point you towards the more lengthy standard examples which you are
likely to find in any textbook.

*/

////////////////////////////////////////////////////////////////////////////////
//1.a

//Passing a constant parameter.
/*
We'll start with something fairly simple. In the last tutorial, we discussed
passing by reference, so that a variable could be altered directly. Sometimes,
passing by reference is done for a different reason, though. Sometimes the
thing you would otherwise pass by "value" (a.k.a. pass a copy of) is just
too big to copy, so you pass it by reference. However, you might still not want
the thing you're giving to your function to be changed by that function.
So here we get the somewhat paradoxical combination:
	passing by constant reference

If you have learned about vector containers, then you may have seen functions
which take a const data type which is a reference (indicated with "&")

Now, the vector header is big, and this tutorial is complicated enough, so let's
use a class you're probably much more familiar with, and which is essentially a
vector of charactors: the string class.
*/

//This function is void, so it doesn't return anything.
//The name of it is "printBigString," and that is the label we will use to call
// it from elsewhere in the program. You can rename it to whatever you want.
//The thing we give to the function is a string, which is const so we won't
// change it, but it is also has & to indicate it is a reference, not a copy
//The name the function will use internally to manipulate the string we give it
// is "bigUserString," but you could rename this whatever you want.
void printBigString( const string & bigUserString ){
	//use cout to output the reference variable
	cout << bigUserString <<endl; //Here we don't need const or & or anything.
	//Return nothing because this is a void function
	return;
}
//What is nice about using & instead of * where you can is that reference
//parameters are used exactly like those passed by value, how you're used to.
//And const parameters do not need the "const" keyword anywhere else.
//Use const data just like variable data, except don't try to change it.

////////////////////////////////////////////////////////////////////////////////
//1.b

//Returning a constant value
/*
It is difficult to imagine when returning a single constant piece of data
would be useful, but let's imagine something very simple which might actually
arise. Let's say you have one of the few acceptable global constants, such as
pi, though you have this stored as a double since that is how you will most
often be using it. However, sometimes you want this value as a float, but
you don't feel like typing out the static_cast<float>() syntax each time.
You don't want to waste space storing the same exact value twice, so you instead
come up with a function something like this:
*/

//Here is our global constant which we only want to store once:
const double D_PI = 3.141592654;

//Here is our silly helper function which static_casts our double to a float.
const float F_PI(){  //This function returns a constant float.
	//We can return a non-const float and it will be treated as const
	return static_cast<float>(D_PI);
}

////////////////////////////////////////////////////////////////////////////////
//2

//Passing an Array to a Function

/*
	I'm going to assume that you are only just now learning what arrays are,
	so I'll say a couple of words about them which may give you some perspective
	that will help you learn about them.
	I made reference to "labels" earlier in referring to function names.
	That word is used to refer to a few of different things at the
	assembly level, and the three major things are lines of instructions, 
	functions (which are also lines of instructions), and data (which in some
	old systems are literally kept inbetween lines of instructions).
	What does that have to do with arrays? Well, the data part comes into play
	here. Sometimes in assembly you have one piece of data after a label.
	Example:
		.data
			myIntroString:
			.asciz "Run! Orange zombies have taken over the world!\n"
		
	But sometimes you don't want to make a new label for every little piece of
	data, you just want to use one label to refer to a big giant block of data.
	So you do something like this:
		.data
			zombieHealthLevels:
			.word 100, 100, 100, 100, 100, 100, 100, 100,
					200, 200, 200, 200, 400, 400, 800 
			
	Well, that's great for assembly programmers, but what good is that to us
	here in the high-level language of C++? This is where arrays come in.
	If we want many different variables of the same data type all kept in one
	place, then	we can make an array and give them one label.
	To create the above example in C++, we could use a couple of different
	methods. Some of them require much less keyboarding to accomplish.
	
	Possibly Shortest Example (C++11 Only):
	int zombieHealthLevels[] = {
	100, 100, 100, 100, 100, 100, 100, 100, 200, 200, 200, 200, 400, 400, 800 };
	
	Another, slightly more sane way, would be something like this:
	const int ZOMBIES = 15;
	int baseHealth = 100;
	int zombieHealth [ ZOMBIES ]; //here we make 15 integers to hold our data
	//And here we use loops to fill different sections of the array with data
	int i = 0; //start counter here, use same one for all loops (don't reset)
	for(  ; i < 8; i++) zombieHealth [ i ] = baseHealth;
	for(  ; i < 12; i++) zombieHealth[ i ] = baseHealth*2;
	for(  ; i < 14; i++ ) zombieHealth[i] = baseHealth*4;
	zombieHealth[ZOMBIES-1] = baseHealth*8; //could also use zombieHealth[i]
*/

//Now, let's get to an actual function that uses an array
//This function takes in an array and its size, and returns
//the difference between the highest and the average values
double diffHighAvg( double bigData[], unsigned int size){
	//Our Function will return a double.
	//Within the parenthesis, when the function is used, the first item
	//given must be an array of doubles. The second item must be an unsigned
	//integer -- because we cannot calculate stats for an array with a negative
	//size. That would lead to nonsense results.
	
	//This will keep track of our running total. ALWAYS INITIALIZE TO 0
	double accumulator = 0; //this must be a double to hold fractional results 
	//This variable will keep track of the current "high score"
	double maxVal = bigData[0]; //ALWAYS INITIALIZE TO FIRST ELEMENT'S VALUE

	for(unsigned int i = 0; i < size ; i++){
		accumulator += bigData[ i ]; //Add current value to running total
		//Test for new high score:
		//If current value being examined is the new high score,
		//set maxVal to that value
		if ( bigData[i] > maxVal )  maxVal = bigData[i]; 
		
	}
	//At this point we have 2 pieces of useful data:
	// 1. The full sum of the data, held in our accumulator
	// 2. The "high score" or maximum value within the array
	//Now we can finish our function's purpose and calculate the difference
	//between the highest value and the average value.
	double average = accumulator / size; 	// avg = sum/totalNumber
	return maxVal - average; //Our return statement can be an equation.
}

////////////////////////////////////////////////////////////////////////////////
// 3.a

//Functions that take in pointers

//The easiest, most useful example, is a function that swaps two values
void swap_ints( int * ptr1, int * ptr2){
	//First, we copy the value held at the first address
	int temp = *ptr1; // the * "dereferences" the value instead of the address
	*ptr1 = *ptr2; //then over-write the first value with the second value
	*ptr2 = temp; //Then we set the 2nd value to the 1st, held in temp.
	return; //Then return nothing because values were altered at their origin.
}

////////////////////////////////////////////////////////////////////////////////
// 3.b
//Here is an example often over-looked as an "advanced" topic, because
//once you understand it, it is simple. First seeing the "const" keyword,
//though, is itself intimidating, and if you put it in the wrong place then
//the compiler yells at you and so most people just don't bother to learn it
//until much later, through struggling with other sorts of compiler errors.

void printCStr(const char * cstr){ //Here we receive a pointer to a char array
/*
	Here, since we are not going to change any of the characters being pointed
	to, we use a pointer to a constant character. Recall that constant data
	cannot be changed -- it is read-only. Pointers to constant variables treat
	the data as read-only, and cannot be made to change data they access.
	
	The pointer itself is not constant, though. We can demonstrate this
	by changing the address held by the pointer itself with the ++ or --
	operators. If the pointer itself was constant, we couldn't change where
	it points to and so the ++ or -- operators would not work.
*/

	while ( *cstr != '\0' ){ //while cstr isn't pointing to a null-terminator
		cout << *cstr; //print the character at the address being held by cstr
		cstr++;//increment the pointer so it now points to the next char address
	}
	//When the code reaches here, cstr is pointing to a null terminator
	// (which was not printed out)
	
	//Then return nothing from our void function
	return; 
}

/*
	Advanced Note:
	
	This while loop could have been written as:
	
	while ( *cstr ) cout << *cstr++;
	
	The while(*cstr) part is explained below the next example, but note that
	the cout<<*cstr++; line first prints out the data pointed to, then
	increments the pointer to point to the next character. 
	
	Here is a very nifty table from:
	http://www.cplusplus.com/doc/tutorial/pointers/
	Which lays out the different combinations of ++ * and pointers:
	
*p++  //same as *(p++): increment pointer, and dereference unincremented address
*++p  //same as *(++p): increment pointer, and dereference incremented address
++*p //same as ++(*p): dereference pointer, and increment the value it points to
(*p)++ // dereference pointer, and post-increment the value it points to 

*/


////////////////////////////////////////////////////////////////////////////////
//3.c
//Returning a pointer to existing memory

/*
	Those are two easy examples of passing in a pointer to a function, but
	now let's return one. The tricky part to note is that the return type
	needs a "*" symbol to indicate that we are returning a pointer.
*/

//This function returns a pointer to the first space ' ', tab '\t',
// carriage return '\r' or newline '\n'
char * findSpace( char * cstr ){
	
//Advanced Note: A safer, read-only version of this function header would be:
//const char * findSpace ( const char * cstr) {


	//This function returns a char *, meaning a pointer to a character
	//And while it may be slightly confusing, this function takes in
	//a char * which points to the beginning of a c-string.
	//The same kind of pointer is used to keep track of both things,
	//so make sure when you're using these kinds of functions you know
	//when to use char* as a "null-terminated" c-string and when to use
	//it as a single character. The standard is that variables named "c" are
	//used as characters, and those named "cstr" or "str" are used as c-strings.
	
	
	char * result = 0; //This will be our return value. We set it first
	// at 0 to indicate the "null" address. Setting a pointer to null
	// is like putting the safety on so you won't accidentally blast
	// data into a random location in your memory.
	// Sometimes people will add a line by their include directives up top
	// to "#define NULL 0" (which causes a compiler warning) or they'll 
	// "#include <cstdlib>" to get NULL as a constant to point to address 0.
	
	
	//Boring linear search. Check every item and when you find it stop checking.
	
//while we haven't reached the end of the c-string or set result to something...
	while( *cstr != '\0' && !result ){ 
		//Check if the current character is anything we're looking for
		//(This switch block looks weird but it's just smushed onto one line.)
		switch ( *cstr ){
			case ' ': case '\t': case '\r': case '\n': result = cstr; default:;
		}
		/*
			Notice though that result and cstr don't have * in front.
			This is because we want to set our address pointer "result"
			equal to the address held by the pointer "cstr"
			Also compare this to the test in our while loop, where cstr
			is being "dereferenced" to check if the value at that location
			is the character '\0', but our "result" pointer is not being
			dereferenced, meaning we are testing whether the pointer itself
			is holding an address to location 0 or someplace else.
			
			If pointers confuse you, remember these simple facts:
			
			1. Every variable (or constant) has an address in memory.
			2. Pointers hold memory addresses.
			3. Pointers can grab the data from the address they're pointing to.
			4. Pointers also have their own addresses.
		*/
	}
	return result; //whether result is null or a found space, return it
}

/*

Also, the word "null" is used in two contexts, so let's clear this up now:
1. Null-Terminators are written as '\0' and designate the end of a c-string.
The ascii value of a null-terminator is actually 0.
2. Null Pointer or Null Address is held by a pointer and points to address 0
which does not hold a character or anything, because address 0 is used as
a safety address where nothing can be written to or read from.

Advanced Note:

Knowing that both of these "null"s are actuall equal to zero can help
you write shorter conditional tests. For example, if we wanted to use just 
the first test in our while loop above, the test would look like this:

while (*cstr != '\0')

But that test uses 8 more characters than we need. We could have written:

while (*cstr)

Which is the same as: 

while (*cstr != 0)

Which is the first version, only using the ascii code for the
null-terminator instead of the "control character" for it.

Testing for a null address can be done with the same logic.
If you want to know that a pointer is not pointing to null, just do:

if ( cstr )

And if cstr is pointing to a non-zero address, then the test will return true.
If none of this about the shorter tests made sense yet, don't worry. Testing
for '\0' or for NULL is actually more clear and generally better practice.
Just consider this part trivia that you can come back to after some practice
with pointers and c-strings and logical/boolean tests.
*/


////////////////////////////////////////////////////////////////////////////////
//3.d

//Returning a pointer to new memory

/*
	I should not be the one teaching you this, because it can be dangerous.
	So let's get the important part out of the way so you make it less dangerous
	
	EVERY NEW NEEDS A DELETE. EVERY SINGLE ONE.
	
	Data in a program is usually stored in the "code" section, or "the stack"
	Those things are nice, but they're somewhat rigid (from the c++ level)
	and we cannot easily create a bunch of new variables there while our program
	is in the middle of running. But where can we get extra space if we need it?
	The heap. Now, at this point you don't actually need to know what the
	instruction block, stack, and heap are all about, but if you want to make
	new variables while the program runs, you need the keyword that grabs
	up space on the heap. That word, is "new"
	
							DON'T STOP READING YET
							
	What did I say before?
	
	EVERY NEW NEEDS A DELETE. EVERY SINGLE ONE.
	
	Before I even show you the proper syntax, you need to know that any time
	you use "new" to eat up RAM on the heap, you need to use "delete" when you
	are done with that memory. What happens if you don't? 
	
						MEMORY LEAKS = PROGRAM CRASH
								
	Almost every time you've been playing a video game that crashed, it was
	because some asshole programmer decided to have way too many "new"s and
	no god damned "delete"s and the program maxxed out its available RAM so the
	whole thing got shut down by the operating system for being a danger to
	itself and others.
	
	Okay, now I'll show you how to do this with a single variable before
	I do it with an array of variables in the actual function below.
	
	//To make a new int ("dynamically" on the heap):
	int myInt = new int;
	
	//To free up that memory (to avoid "memory leaks"):
	delete myInt;
	
	
	Why would you use this with a single variable? Well, you wouldn't.
	You might do it with a single object that could get very big, like string
	or vector, but most	of those kinds of objects actually use "new" and 
	"delete" inside their own code, so there isn't much benefit in also using
	"new" and "delete" to make a string or vector.
	(This is because a string or vector is usually about the same small size at
	a "shallow" level, and the "deep" part of them -- the actual data -- is
	a region of varying size on the heap, elsewhere in memory. Putting the small
	part on the heap as well isn't usually necessary or beneficial.)
*/

//Because I get sick of typing int, float, char, and double all the time,
//let's make an array of bool variables. Sometimes such a thing is called
//a "bit mask" -- but bools actually take up more than a bit, so don't use 
//them to hold bit data. Instead: bitset from c++11, or char as an unsigned byte

//We are going to return a pointer to our new memory block on the heap
bool * makeHeapFlags( unsigned size ){ //use unsigned so size won't be negative
	
	bool * flags; //first, we make a bool * named flags
	flags = new bool[size];//then we make a new array of bools of the given size
	return flags; //After our flag array is made on the heap, return its address
}

//And because I want to stress that EVERY NEW NEEDS A DELETE, let's make
//a function which un-makes our flag array on the heap

void killHeapFlags( bool * & boolPtrRef ){ //A reference to a pointer to a bool
	//Remember when I said earlier that pointers themselves have addresses?
	//Well that comes into play here. The reason we pass a reference to
	//a bool * is so that we can set the value of that pointer itself
	//after we call delete on the memory block being pointed to.
	
	//First delete the array we made with "new" in makeHeapFlags
	delete [] boolPtrRef;//Notice dynamic arrays are deleted with an extra "[]"
	
	//Then set the original pointer to null (since it was passed by reference)
	boolPtrRef = 0;
	
	//Void function, return nothing:
	return;
}

////////////////////////////////////////////////////////////////////////////////
// 4.a
// Static Variables to keep track of initialization

//Sometimes we want a function to remember whether it has run before or not.
//There are times when something must be set up once and then every other time
//the function can skip that set-up step. Once use of an initializer flag
//is for random numbers. Here's a similar set-up for a clock-cycle timer
//This function depends on the "clock()" function linked to by "#include <ctime>
//clock() returns the number of CPU clock cycles since the start of the program.

unsigned long long clockTimer(){ //this function returns a giant integer type
	//Here is our flag which will keep track of first run vs later runs
	//it is static because we don't want the function to forget it
	static bool isSetUp = false;
	//Here's the variable which will remember the # from first call to clock()
	static unsigned long long cycleAtFirstCall; //No starting value here.
	if ( isSetUp==false ){ // if we have not run our set-up code yet:
		//set our static variable for starting time
		cycleAtFirstCall = clock();
		//set our static bool flag for set-up having finished
		isSetUp=true;
	}
	//And every time this func. is called, we return the elapsed time:
	//(The first time this func is called this number will be fairly small.)
	return clock() - cycleAtFirstCall; //return newTime - oldTime
}
//(Note on timer math: Since now > then, "now - then" will always be positive)


////////////////////////////////////////////////////////////////////////////////
// 4.b
//Static Variables to act as an accumulator across function calls

//Instead of keeping track of a variable that is only ever set once,
//Let's make a function which acts as an accumulator thanks to its static
//variable. We will also use a default argument on this function, so the
//user can reset the accumulator when desired, but they don't have to bother
//with telling our function to NOT reset the accumulator every time.

double keepTrack( double add = 0, bool reset = false ){
	//Here we'll make a static double to keep track of a running total
	static double total = 0; //ALWAYS INITIALIZE ACCUMULATORS TO 0
	//Note: The initialization of a static variable only happens once.
	
	if (reset) total = 0; //if reset is true, reset the total
	
	total += add; //add the given value to our accumulator named "total"
	
	return total; //return our accumulator's current value
}

/*
	How to use this function (from main or wherever):
	//Ex. 1
	keepTrack( myDouble ); 		//call function with a number to add to total
	//Ex. 2
	double currentTotal = keepTrack(); //Call function with no arguments to get
									//the current value held by the accumulator
	//Ex. 3
	keepTrack( myDouble, true ); //call function to reset acc. then add myDouble
	
	//Ex. 4
	double firstVal = keepTrack( myDouble, true ); 
	//reset accumulator, add myDouble to accumulator, 
	//and set firstVal to the number returned by keepTrack,
	//(which is just a copy of myDouble)
*/



////////////////////////////////////////////////////////////////////////////////
// 5
// Recursion to print elements of an array in reverse

/*
	Recursion is a very simple concept which gets very ticky to implement.
	"Recursion" is what we call it when a function calls itself.
	Recursion, as you can imagine, can be very dangerous.
	The most common problem from recursion (whether you mean to be doing
	something recursively or not) is that the function never stops calling
	itself and the program crashes.
	
	( Advanced note: the program crashes because too many return addresses
	get "pushed" onto the "stack" and none of them ever get "popped" off from
	returning from any functions. The error message you get from this is:
	"stack overflow error"
	Which is where the famous help site gets its name from. )
	
	So eventually a recursive function needs a "base case" where it stops
	calling itself. Usually you use a simple if statement to determine whether
	you have arrived at this base case.
	Recursion seems difficult to flowchart, but it works mostly like a loop
	does:
		1. You need an exit condition (called a base case in recursion)
		2. You need to be changing something so eventually the test 
			to stop calling itself will become true. Usually this is done
			with a +1 or -1 to one of the parameters passeed into the function.
*/

//Here's one of my favorite examples:
//Using recursion to print a string backwards


//Recursive function which basically calls itself until start++ == end
//This function takes a pointer to the starting character and
//to the ending character.
void printReverse( const char * strt, const char * end){
	//Here's where we test for our base case.
	//If start >= end, we don't call ourselves again
	if (strt < end){
		//Here's the "recursive call" to ourselves
		printReverse( strt+1, end ); //notice we add 1 to the pointer (not ++ )
	}
	//Then we print the current character by "dereferencing" our pointer.
	cout<< char(*strt) ; //use char's "constructor" so you only print one char
	//NOTE: If you don't use the char() function to "construct" a char, then 
	//cout tries to print the entire c-string, and you don't get a reversal,
	//you get chaos.
	
	/*
		The first time that cout<<char(*strt) runs will be when we are at
		the base case, which is when strt has been added to so many times
		that now strt == end. Since start has been moving up, and end has
		been staying still, and now they are equal, that means strt within
		this specific function call is the final character in the string.
		So when we print, the first character that comes out is last one 
		in the string.
		
		Let's say our pointers start holding addresses 100 and 104
		first call to printReverse gets: strt = 100, end = 104
		2nd call gets: strt = 101, end = 104
		3rd call gets: strt = 102, end = 104
		4th call gets: strt = 103, end = 104
		5th call gets: strt = 104, end = 104
		then, in 5th call: cout << *strt; // which is char @ address 104
		then, in 4th call: cout << *strt; // which is char @ 103
		then, in 3rd call: cout << *strt; // which is char @ 102
		then, in 2nd call: cout << *strt; // which is char @ 101
		then, in 1st call: cout << *strt; // which is char @ 100
		
		and finally, in our helper function: 
		cout<<endl;
		
		And here's the "helper" function:
	*/
}

//Here's what we actually call in main, and instead of giving it two pointers,
//we just give it the usual arguments of cstr pointer and length.
//Helper function which just calls the recursive function
void printReverse( const char * cstr, unsigned len ){
	printReverse( cstr, cstr+len-1 ); //give a pointer to the start and
	//a pointer to the end, which is determined by adding the array length
	//to the "base address" held by the pointer, then subtracting 1
	cout<<endl;	//After each char gets printed in reverse, print a newline
}

////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////MAIN START////////////////////////////////
int main(){
	
	//Test of 1.a
	//Notice that our "intro" string itself doesn't have to be const to be
	//passed to a function expecting a const. The function will just treat our
	//data as if it were read-only even though it can be re-written elsewhere.
	string intro =
	"Hello and welcome to the overly-ambitions Functions Tutorial 2\n"
	"Which can't help but introduce the entire second half of your intro\n"
	"programming class in one big-ass tutorial source file. Hope it helps.\n";

	//Calling printBigString
	printBigString( intro );

	////////////////////////////////////////////////////////////////////////////
	//Test of 1.b
	//We can use our F_PI function to get a local copy of our const float
	//(The only reason you would do this is to get a copy "on the stack" of
	// local variables which are accessed slightly faster than global constants)
	const float F_STACKPI = F_PI();
	
	//We can also use a const to initialze a variable which we will change later
	float f_piSquared = F_STACKPI;
	
	//Here we square our variable's value.
	//This line is equivalent to: f_piSquared = f_piSquared * f_piSquared;
	f_piSquared *= f_piSquared;
	//if we tried to do STACKPI *= STACKPI; we would get a compiler error
	//because STACKPI is read-only and cannot be changed.
	
	cout<< "Global Const Double Pi: " << D_PI <<endl;
	cout<< "Function-Returned Const Float Pi: " << F_PI() <<endl;
	cout<< "Local Const Float Initialzed With Function Pi: " << F_STACKPI <<endl;
	cout<< "Local Variable Float Initialized With Local Const Float Pi^2: "
			<< f_piSquared <<endl;
			
	//Alright, now I'm sick of pi. Let's go chew on something else.

	////////////////////////////////////////////////////////////////////////////
	//Test of 2	
	
	cout<<"\nLet's test our function which takes in an array that I've called\n"
			"diffHighAvg, which takes in an array and its size, and return\n"
			"the difference between the highest value and the average value."
			<<endl;
			
	unsigned const ARRSZ = 5;
	double myArray[ARRSZ]; //here's where we make our array of 5 variables
	//which are stored in order starting at the address held by "myArray"
	
	cout<<"\nLet's try to fill this array with values:"<<endl;
	for(int i = 0; i < ARRSZ; i++){
		bool accepted = false;
		do{
			cout<<"Enter value number "<<i+1<<": ";
			//This cin will store vals at index 0, 1, 2, 3, then 4 as this loops
			cin>> myArray[i]; 
			//Input Verification
			if (!cin.good()){ //if input failed
				cin.clear(); //clear "fail" flag (do first)
				cin.ignore(1024, '\n'); //ignore input buffer (do second)
			}
			else accepted = true; //otherwise, input was good.
			
		} while (!accepted); //end input-verification do-while loop
				
	} //end array-traversing "for loop"
	
	
	//now let's get that difference, stored in a new double variable
	double diff = diffHighAvg( myArray, ARRSZ); //give function array and size
	//and let's output it
	cout<<"\nThe difference between the high and average in this array was: "
		<<diff<<endl;
	
	////////////////////////////////////////////////////////////////////////////
	//Test of 3.a
	cout<<"\nNow here's a little test of our tiny swap function:"<<endl;
	{ //here I make a code block just to keep these variables in a "local scope"
		int x = 64, y = 2048;
		cout<<"X is: "<<x<<" and Y is: "<<y<<endl;
		swap_ints( &x, &y); 
		//since this function expects two pointers (which hold memory addresses)
		//we can use the & symbol as the "address symbol" (not as AND) to give
		//our function the address of x and the address of y. Now when the
		//function works with its values, it will be working on the same values
		//that appear here in main instead of just working on copies of those
		//values we passed into the function.
		//(This is an example of passing by reference instead of passing by
		// value, even though we're using pointers here and not references.
		// At the assembly level, references all become pointers, so the only
		// way to pass by reference at that level is to use pointers.)
		cout<<"After swap, now X is: "<<x<<" and Y is: "<<y<<endl;
	
	}
	
	////////////////////////////////////////////////////////////////////////////

	//TODO: WRITER DEMO/DRIVERS FOR OTHER FUNCTIONS TO DEMONSTRATE USE
	
	////////////////////////////////////////////////////////////////////////////
	//Test of 3.b
	//printCString
	
	////////////////////////////////////////////////////////////////////////////
	//Test of 3.c
	//findSpace
	
	////////////////////////////////////////////////////////////////////////////
	//Test of 3.d
	//makeHeapFlags
	
	//killHeapFlags
	
	////////////////////////////////////////////////////////////////////////////
	//Test of 4.a
	//clockTimer (static function for tracking duration)
	
	////////////////////////////////////////////////////////////////////////////
	//Test of 4.b
	//keepTrack (static accumulator function)
	
	////////////////////////////////////////////////////////////////////////////
	//Test of 5
	string toReverse = "Do you believe in subliminal messages?";
	//Here we'll use a string class even though our function needs a c-string.
	//We can get around this limitation by calling the .c_str() function
	//on a string to get a const char * to the beginning of the string
	//And we can also use the .size() function of a string to get its length.
	printReverse( toReverse.c_str() , toReverse.size() );
	
	
	
}
/////////////////////////////////////MAIN END////////////////////////////////
