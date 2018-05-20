/*
	Here I attempted to break things using "goto," but C++ (or at least the
	g++ compiler) safely handles some of the most dangerous uses of goto:
	jumping out of a local scope without closing that scope and deallocating
	variables (i.e. restoring the previous frame pointer), and jumping from
	one function into the middle of another.
	Goto can, however be used somewhat responsibly since the biggest dangers
	of using it within assembly language are mitigated by our "higher-level
	language" compiler. These safe-guards may inhibit some of your solutions
	which use goto (especially if you're porting code from assembly language),
	but since there actually isn't any problem that can ONLY be solved by use
	of goto, these safe-guards which preserve local scope and your call stack
	are to be seen as your dearest friends, not as oppressive enemies.
	Similarly goto, while maligned, is actually significantly safer to use in
	C++ than many programmers assume, and so creative solutions with it could
	very well be worth exploring (even if they are technically unnecessary).
	===========================
	Code by Jason Lillard, 2018
*/
#include <cstdio>

int main(){

	//how does a for loop really work?
	//Maybe looking at it through labels will help.
	
	puts("Here are some basic count-downs done first with a basic for loop,\n"
		"And then with some treacherous labels and goto jumps.");
		
	//1. Initialization: int i = 5;
	//2. Test: repeat loop while i>=0. When i<0, jump over loop to step 6.
	//3. Code to execute: print the current counter value
	//4. Decrement: subtract 1 from counter i
	//5. Jump to step 2, our test.
	//6. End of loop
	for(int i = 5; i >= 0; --i){
		printf("Counting: %d\n", i);
	}
	
	//TEST #1:
	puts("And now for the same thing but terrible.");
	{ //using curly braces here to create a local scope for the counter variable
	
		//Step 1: counter initialization
		int i = 5;
		
		//label which determines the start of the loop	
		our_for_loop_start:
			
			/*
				Since the for loop is a "pre-test" loop, that means that
				we test if we're going to jump over the loop before we
				enter its code for the first time. Since this is a count down
				with a number that starts high and goes to 0, our test
				will jump over the loop once the counter is below 0.
				The "goto" keyword basically jumps to a line of code. It is
				limited by most compilers, though: for example you cannot jump
				out of one function into another (See Test #3 below).

				goto is best left unused completely, but if you must use it for
				some reason, use it within a single function to make/imitate
				structures like if/else-if/else, while, do-while, or switch-case
				blocks.
			*/
			//Step 2: test
			if (i<0) goto our_for_loop_end;
			
			//Step 3: code to execute (print counter)
			printf("Counting: %d\n", i);
			
			//Step 4: decrement counter
			--i;
			
			//Step 5: jump to step 2
			//here we always jump up to before our loop's test
			goto our_for_loop_start;
			
		//Step 6: the end.
		//This label determines the end of the loop	
		our_for_loop_end:
			
		; //empty expression, because here labels are technically attached to
		//expressions, not to line numbers (like they are in BASIC).
		//If we remove the empty expression after the label, and have no other
		//expressions after this part of the code, the program won't compile.
		
	} //end of created local scope for counter variable

	//end of main
	//return 0;
	/*
		If we have this return 0 here, our_for_loop_end will jump to this line.
		It would be safe here to leave out the empty expression and just link
		that label to return 0, but this whole mess is left here to show that
		the program will not compile unless you have some kind of expression
		after a label. If the only thing that makes sense in a particular
		context is to use an empty expression you can use that, but it is
		more likely any kind of final label in a function can precede a
		"return" keyword, even in a void function or in main where return 0 is
		optional.
	*/
}
	
	
////////////////////////////////////////////////////////////////////////////
//Test #2:

/*
	A few words concerning goto, local scope, and the stack, and where the
	stack currently starts (i.e. the frame pointer, which really defines
	what is in local scope and what isn't anymore):
*/

/*
	Fortunately(?) this test reveals that at least with the g++ compiler,
	this code will not even compile, since the line attempting to print
	the value outside of the code block is unable to access the variable.
	The given error is: "localFloat was not declared in this scope."
*/	

	/*
	puts("Testing what goto does to local scope:");
	
	{
		float localFloat = 3.14;
		printf("Variable in local scope: %f\n", localFloat);
		goto outOfScope;
		//Some code after our goto to try to force the block to remain open.
		localFloat *= 2;
	}
	
	outOfScope:
		printf("Variable outside local scope: %f\n", localFloat);
	*/

/*					
	In other compilers, using goto may do unexpected things to the scoping
	of local variables, allowing some things to remain on the stack even
	after the block in which they were made has been left.
	Using goto in assembly language is more dangerous since local
	scope is something more directly maintained by the coder
	based on what they push and pop from the stack, and what they save
	as their current "frame pointer" a.k.a. where they consider the stack
	to start.
	The "frame pointer" is really just the position of the stack pointer
	(which usually points to the next available slot) when the function started.
	Essentially, if you make local variables, they get made on the stack, 
	but you need to keep track of where the stack was before you did that,
	so when the func. is done you can move the stack pointer back to where it
	was, which has the effect of killing all the variables which existed in that
	local scope.
*/
////////////////////////////////////////////////////////////////////////////////
//TEST 3:
	
/*
	The following test, thankfully, also does not work (at least on g++).
	Basically We try to jump out of the middle of one function into the middle
	of another function, but g++ predicts this kind of thing will end in
	disaster, and forbids it by placing the funcBLabel out of scope from
	within funcA. This might seem incovenient, but disrupting the current
	local scope / stack frame by jumping from function to function is bound
	to cause more problems than it seeks to solve.
*/
/*
//Jumping from function to function test:

//OUTSIDE MAIN:
	
	//declare this function and label before we use it in funcA
int funcB(){
	funcBLabel:
	int x = 20;
	return x;
}

int funcA(){
	int x = 10;
	goto funcBLabel;
	return x;
}

//INSIDE MAIN:

	puts("Now let's test what happens when we use goto to jump from one"
		"function to another, and if this messes up our return values.");
		
	printf("Return value from funcA: %d\n", funcA() );
*/
////////////////////////////////////////////////////////////////////////////////
