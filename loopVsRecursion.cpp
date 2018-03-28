/*
	Recursion is a Kind of Loop
	Micro Demo
	------------------------------
	Code by Jason Lillard, 2018
*/

#include <iostream> //for output. We could do this with printf in C with stdio.h
using namespace std;

/*
	So all we're going to do here is count to 5. Nothing spectacular at all,
	because I'm assuming you're just learning loops and functions. So here's
	a void function. It doesn't return anything, so it's return type is "void".
	It's name is countToFive, and that is what we'll use to "call" the function
	later. The empty parenthesis are needed to surround the "parameter list",
	which is empty for this function.
*/
void countToFive(){
	//Here's a simple loop that prints the loop counter.
	//The counter starts at 1 and goes up. Once the counter is 6, the test i<=5
	//will evaluate as false and the loop's code will be skipped.
	for(int i = 1; i <= 5; i++) cout<<i<<endl;
	//Even though we don't return anything, we can still "return" from the func.
	return;
}


/*
	This is a recursive function which will do the same thing as countToFive,
	only this function will "loop" by calling itself a few times until a test
	evaluates to false, and then the code to call the function again will be
	skipped and the "loop" will terminate.
	
*/
void countUp(short r){
	cout<<r<<endl; //output our "counter"
	//if r is between 1 and 4...
	if (r>=1&&r<5) countUp( r+1 ); //call function again with r one higher
}

/*
	Here's something very common with recursive functions: a helper function
	that start's the recursive "loop." We don't need this, but this makes
	starting the recursion easier, as we don't have to use countUp in main
	with a call like countUp(1); We can now call countUp() with no "arguments"
	passed in to it. Since the "parameter list" of this countUp is different
	from the countUp we just made, C++ sees them as two separate functions.
	If we call countUp() it uses the function below, if we use countUp with
	an argument (like countUp(3); ) then the program will use the countUp
	we made higher up.
*/
void countUp(){ //the non-recursive countUp which doesn't call itself.
	//Start the recursion with a call to the recursive version of countUp:
	countUp(1);
}

//Now here are both the functions in action.
int main(){
	cout<<"Iterative count-up versus Recursive count-up\n"
		"Iterative:"<<endl;
	//Here's our call to our function which works iteratively
	countToFive();
	
	cout<<"Recursive:"<<endl;
	//And here's our call to our function which starts the recursive "loop"
	countUp();
	
	cout<<"There, that's it. What more do you need?"<<endl;
	
	//Now our main function returns the error code value of 0 to the O.S.
	return 0;
}
