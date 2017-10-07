/*
	INTRO TUTORIAL ON FUNCTIONS
	---------------------------
	Code by Jason Lillard, 2017

*/
#include <iostream>
using namespace std;

/*
	What it is, fam? So, today we're going to talk about functions.
	Now, you already know at least one function: int main()
	While int main is a special function, it is ultimately just a function.
	
	Other functions you've probably used come from the math library, such
	as pow(int, int), sqrt(int), abs(int), sin(int), cos(int) or tan(int).
	
	Technically, even cin and cout are used as functions, but since they
	are used in a way that is quite different than usual functions,
	they are only so helpful in teaching how to make your own functions.
	
	So now, let's make a few functions above main (so we can use them below,
	in main) and then we'll do something a little strange -- we'll make
	function "prototypes" above main so we can use the functions in main,
	but we'll actually specify what the function's code is BELOW main.

*/

// First we'll make a function with the same "return type" as main: int
int getInteger(){//this function will get an integer from the user and return it
	int input;	//make the integer we're going to return
	cout<<"Input an integer: "; //output a prompt to user
	cin>>input;		//use cin to get an int from the user, store in "input"
	return input; //return value saved in input
}
// This kind of function (sometimes with a bit more complexity) is very
// useful in a program where you have to get many different numbers from the
// user. This can be used as many times as you need to, with code like:
// int myInteger = getInteger(); //here we are making a new variable, and
//filling it with the value that is "returned" by our getInteger function.

////////////////////////////////////////////////////////////////////////////////

//Now let's make something just as easy, but which doesn't return anything.
//NOTE: "void" is the return type here. Now, usually the word "void" is used
//to refer to far off outer space, where nothing much exists. Here, it means
//"nothing," as in nothing is returned from the function.
void printError(){
	cout<<"I don't know what you did, but it was wrong."<<endl;
	return; //Here we simply return, we don't send any value back from this.
}
//This function we would use within main to output an error, like this:
/*
	int myNum;
	cout<<"Enter a number to divide 100 by:";
	cin>>myNum;
	if ( myNum == 0 ) printError(); //if user tries to divide by 0, print error
	else cout<< 100.0/myNum <<endl; //if myNum isn't 0, output the result
*/
////////////////////////////////////////////////////////////////////////////////

// Functions can also call other functions. This should be obvious, since
// your main function is the place you have already been calling functions from

//Here is our first function that will be "called" from our second function
void callMe(){
	cout<<"So nice of you to call!"<<endl;
}

//Our second function will first say "Hello?" and then call the first func.
void callThem(){
	cout<<"Hello?"<<endl; 
	//To "call" our function, we just use the function name (after we have
	//already declared it above) and follow the name with parentheses.
	callMe();
}

////////////////////////////////////////////////////////////////////////////////

// Functions can also accept "arguments" within the parenthesis, like the
// functions in the cmath library do (since you need numbers to do math)

void printInteger( int toPrint ){
	cout << toPrint <<endl;
}
//We'll demonstrate this within main by giving it different integers to print

////////////////////////////////////////////////////////////////////////////////

//For this last function, we will declare a "prototype" here, and fully
//define the function below main. This seems silly to do with such a small
//program, but learning how to turn your function "headers" into prototypes
//definitely comes into handy as you get into "object oriented" programming.

//Also special with this function is the "&" symbol, which means that instead
//of passing a copy of a value, we are going to pass the actual variable itself
//that exists somewhere else -- and we can change it here and the change will
//show up where the variable was made. For our toPrint function, for example,
//if we tried to modify the value of toPrint, it wouldn't change the value
//back in main  (or wherever we were when we called toPrint(int) ).

void integerX2( int & valToDouble ); //semicolon & no curly brace = prototype

//Look below to find where integerX2 is defined

///////////////////////////////////// START MAIN //////////////////////////////
int main(){

	cout<<"Alright, let's try to use a couple of these functions now."<<endl;
	
	//First let's call our function which calls another function
	callThem(); //Notice even functions which take no "arguments" need the
	//parentheses in the "function call" within main.
	
	//Now let's test our getInteger, printError, and printInteger functions
	int myInt = getInteger();  //use our get integer function to fill this int
	
	//check for errors, output error message if needed
	if (myInt == 0 ){
		printError(); //call our error message function
		return 1; //Returning something other than 0 from main means "ERROR"
		//NOTE: Some teachers will not allow more than one "return" in a func.
		//because this violates a "structured programming" rule that all
		//functions should be "single-entry, single-exit" (to make it easier
		//for the programmers to keep track of the program flow).
	}
	
	
	//now let's print our number a few times in a loop
	for(int i = 0;  i < 10  ;  i++ ){
		//print what myInt currently equals
		printInteger( myInt ); //pass a copy of myInt "by value" to printInteger
		
		//Then double it so next time we print myInt, it's different
		integerX2( myInt ); //pass myInt "by reference" to double its value here
	}

	cout<<"Yay! We doubled it a bunch! Hopefully it didn't overflow..."<<endl;

	return 0; //And now you know what the "return 0;" is all about.
}
////////////////////////////////////////////////////////////////////////////////

//THE DEFINITION FOR OUR PROTOTYPE (given above, line 101):
void integerX2( int & valToDouble ){
	valToDouble = valToDouble*2;
	//We can leave out the "return" keyword in void functions
	//because they don't return anything. And since we are modifying our
	//value "by reference" with the & symbol, we don't need to return a value.
}
