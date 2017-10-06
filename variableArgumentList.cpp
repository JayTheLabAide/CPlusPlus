/*
	Variable Length Arguments With Template Functions
	
	Use of a template function helps us here because va_arg needs
	a data type, and template functions	are by far the easiest way
	to pass a data type as an argument. cstdarg works without
	templates, but we can make our functions verstile more easily with it.
	--------------------------------------------------------------
	Code by Jason Lillard, 2017
*/

//variable length arguments in c++
#include <iostream> //for cout
#include <cstdarg> //for va_list, va_start, va_arg, and va_end
#include <iomanip> //for fixed, setprecision
using namespace std;

//If this is put in its own file, keep it in a .h because it is a template func.
//(va_arg requires a data type as an argument)
template <class T>	//this is how we will get our data type to print
void printStuff(size_t numArgs, ... ){
	
	va_list varList;	//create our variable list
	//use va_start to initialize varList with set number of items
	va_start (varList, numArgs);
	//call va_arg to get the next item
	//from given list of given type
	for(int i = 0; i < numArgs ; i++){
		//since cout will take nearly any data type, we can try to
		//output anything given to it (even though that may fail)
		cout<< va_arg(varList, T) <<endl; //notice va_arg needs a data type, T
		
	}
	cout<<endl; //extra break
	//deallocate(?) list with va_end. (Maybe optional?)
	va_end(varList);
}

//Useless structure for demo purposes:
//Even though structures like "Broken" can be passed to a template function,
//cout doesn't recognize what a "Broken" is, so will not be able to print it.
struct Broken{ int num; };


////////////////////////////////////START MAIN//////////////////////////////////
int main(){
	//first, let's print a variable list of floats
	float f1=1.414, f2=2.718, f3=3.1416, f4=4.20;
	
	//according to the compiler, we should
	//always pass double to va_arg instead of float
	// printStuff<float>(4, f1, f2, f3, f4); //ERROR! FAILS AT RUN-TIME!
	printStuff<double>(4, f1, f2, f3, f4); //Notice template parameter <double>
	
	//If we want to format our list, we can set iomanip properties before
	//we call printStuff, and they should still be in effect for printStuff
	cout<<fixed<<setprecision(4);
	printStuff<double>(4, f4, f3, f2, f1);//Let's print it backwards just 'cause
	
	//Now let's make a bunch of individual ints to print
	int i1 = 2, i2 = 4, i3 = 8, i4 = 16, i5 = 32, i6 = 64;
	//Our call to printstuff<int> will try to print everything as an int
	printStuff<int>(6, i1, i2, i3, i4, i5, i6);
	
	//Now let's print some c-strings
	const size_t STRS = 4; //our array size
	const char * cstr[STRS] = {"Bonjour", "tout","le","monde"}; //our array
	//Notice we are passing type const char *
	printStuff< const char * >( STRS, cstr[0], cstr[1], cstr[2], cstr[3] );
	
	
	//STUFF THAT WON'T WORK:
	
	// Note that we cannot pass the base pointer to our array
	// as if it were a list of arguments (even though an array is like a list)
	
	// printStuff< const char * >( STRS, cstr ); //ERROR! FAILS AT RUN-TIME
	
	
	//If we try to make something that cout doesn't recognize,
	//and use it with printStuff, then the program won't compile
	
	// Broken b1={100}, b2={200}, b3={300};
	// printStuff<Broken>(3, b1, b2, b3); //ERROR! FAILS AT COMPILE-TIME!
	
	return 0;
} //end main
