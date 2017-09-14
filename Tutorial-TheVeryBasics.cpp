//Tutorial, Code by Jason Lillard, 2017

/* <-- start of "block comment"

	C++ The Very Basics:
	
	The Pre-Basics:
		This is "block comment" and it begins with a
		/* 
		and ends with a
		*/
	// This line is not in the above comment.
	
	// A comment can also start with a "//" and you will see this often here.
	// If I want to use these I have to put them at the start of (every) line;
	// which is fine sometimes, but sometimes you just want to type without 
	// worrying	about adding them in the middle of typing your other thought.
	// Also, they add visual clutter, which really never helps.
	
	/*  <-- starting a new block comment
	
	Now, for the real coding stuff:
	The Very Basics:
		"Boilerplate"
		- The keywords you need to properly turn this text file into a "source" file
		
		Math (Everything a computer does ultimately comes down to math)
		- Making variables and giving them values
		- Addition and subtraction, multiplication,
		- division (special notes on division)
		- pow() sqrt() and other "math.h" functions
		
		Input and Output from the Console
		- output text and numbers with "cout" 
		- input numbers with "cin"
		
		TO BE ADDED LATER:		
		Program Control (jumping around)
		X if, else if, else (making decisions)
		X while loop (a simple loop which goes until a certain condition is met)
		X the "for" loop (A little more complicated, but just a loop that goes a set number of times)
	
*/

// SECTION 1: BOILERPLATE:

/*
	FIRST THING IN EVERY PROGRAM:
	These are "the includes" and they come first. The "#" symbol before them isn't used
	often in C++ (even though it is used incessently on social media). They are for
	a thing you don't need to know much about at this moment, called the "pre-compiler."
	Which "includes" you use depends on what you need done, but basically they each
	contain a bunch of apps that we can use to make things easier on ourselves. Instead
	of "apps" though, here they're named "functions" or -- if we wanna be really
	old school -- "subroutines." 
	TLDR: "Includes" have code that's already written for us, so it makes stuff much easier.
*/

//We need iostream to display text to the "console" or "terminal" and get input from the users
//You're a long way from graphics, kid. Get used to the look of fixed-width characters.
#include <iostream> 

//We need cmath for pow() to do exponents, and sqrt() to do square roots.
// Actually there are other very complicated ways of doing those things, 
// but they're awful, so lets use these.
#include <cmath> 

//There are lots of other "includes" that come with the compiler
// (which is the thing that turns your program from text into a program that runs).
// Here is the list of standard includes: http://www.cplusplus.com/reference/
// Explore that list often, as it is your book of spells. You won't understand
// everything you come across, especially at first, but all that experience adds up.

/*
	SECOND THING IN EVERY PROGRAM:
		"using namespace std;"
		The "std" here stands for "standard." It does not stand for other things.
		the "namespace" means that when we use functions like pow() in our code,
		we want the "standard" ones from the C++ everyone uses, and not some
		set of our own functions which use the same names. For literally everything
		in your intro C++ classes, you will be using the standard namespace.
		Oh yeah, and "using" means we're using it.
*/
using namespace std; // <-- NOTCE THE WEIRD SHAPE AT THE END OF THIS STATEMENT
// This the semi-unfortunately named "semi-colon." It's in winky faces.
// Only people like me who think of themselves as writers use it, normally.
// Here you will use it after nearly every single line you type.
// FYI: It's under your pinky. Unless you use an AZERTY keyboard, then who the hell knows.


/* 
	AT LAST:
THE REAL MOST ACTUAL THING NEEDED IN EVERY PROGRAM
(Actually this is just in a comment, the real main is below):

int main()
{
	
}

This is "main". EVERY PROGRAM STARTS AT MAIN. You can have
a c++ project with thousands of .cpp files in them, but when
you turn the thing into a program and run it, it starts here.
Sometimes when you start a new C++ project, the parenthesis
have a bunch of stuff in them. You don't need that stuff.
(If you really wanna know: they make it so your program can
take extra commands when you start it from the console. 
You don't need those yet; not for a while.)
After those parenthesis is the "code block." More on that below.
The "int" means that our main program "returns an integer" to
whatever program started running our main program. What program
started our program? The Operating System. That is, after all,
just another program running on your computer, even if it is a
very important program. Main usually returns 0 to show that
nothing went wrong. When numbers are returned from main, they
are usually error codes that show the program ended because of a problem.
*/

int main()	// don't forget the parenthesis! They show that main is a function.
{
	// The thing above this line is an "opening curly brace"
	// It starts a "block" of code. Blocks show when things
	// like functions begin and end. You need them.
	// The { opens a block and the } closes it.
	// They are not [] and they are not ()
	// Those both have different meanings in C++
	
	//SECTION 2: MATH
	// Hey kids, do you like video games? Great, here's some algebra to do.
	
	//Making Variables and Giving Them Values
	int x = 10;
	/*
		There's that word "int" again. Here it is also short for "integer."
		In computer science, "integer" types can't hold fractions. They can,
		however, hold numbers from (depending on your computer)	-2^32 to
		(2^32)-1
		Why is there one less positive number than negative number?
		Because bits.
		That's why. In short: you need a single bit for the negative sign,
		and as a result there's one number technically possible to make
		which isn't really interpreted as a distinct number: -0
		This is a little funny, and also slightly annoying, because
		we lose a combination of bits which could be used for a number. 
		Think of it like daylight savings time: It's stupid.
		
		x = 10
		The meaning of this should be obvious. There is a thing called x
		and now it is equal to 10. What is a little less obvious, is that
		the thing we are "setting" equal to something else always goes
		on the left side. We sometimes call this the "destination,"
		of our data. The right-hand side of the equals sign is our "source"
		With the notable early exception of "cin" -- which you'll see later -- 
		the format for most lines of code will be:
		destination operation source
		Although another combination is also common:
		destination source1 operation source2
		For example, something like:
	*/
	int y = 7 + 17;	
	// Oh look, we're at addition.
	// So, the important thing about this line, other than that + works how you'd expect,
	// is that + has "higher precedence" than "=", which means it happens first.
	// So what happens is first 7+17 is calculated, then integer "y" is set to
	// equal the result, 24. That "precedence" thing will become important quickly,
	// especially once we add in multiplication and division. (Think PEMDAS from gradeschool)
	
	//We can also set a variable to the values of another variable, or an equation
	int totalCats = x * y + 1; //NOTE: there is no "int" now before x or y
	// We can also give our variables descriptive names where it makes sense. Or not.
	
	
	//Division Error 1:
	// Don't divide by zero. The universe won't end, but your program might actually crash.
	// Some programs like Excel will be user-friendly and tell you anything/0 = 0, and
	// will give you a warning about your silly equation. C++ is not as user-friendly.
	// Attempting something like "int sandwiches = 4/0 " will lead to an "exception"
	// that your program doesn't "catch" or deal with, so your program shuts down.
	
	//Division (and "float" variables to hold both scientific notation and fractions)
	float z = 2.5; //float is a "data type" like int.
	// They are actually the same number of bits, but the computer interprets them differently
	// depending on which format it is expecting to read -- but that is not currently important.
	
	//Division Error 2:
	// 1/2 is equal to 0. Why? Because of "integer division." 
	// Remember I said that integers can't hold fractions, so any
	// result you try store in an integer, or even make WITH integers
	// in the code (like with 1/2 ) will try to be stored in a format
	// which only deals in whole numbers. Having to worry about integer
	// division is stupid, but like a lot of stupid things in computer science,
	int notHalf = 1/2; // Because 0.5 cannot be stored in an int, this variable "notHalf" equals 0
	float alsoNothalf = 1/2; // trying to store 1/2 in a float still won't work, because of
	// that "precedence" thing, 1/2 is calculated as problem involving integers, and the
	// result is 0. Then, that bad integer result is converted to a float to store in "alsoNotHalf"
	float reallyHalf = 1.0/2; // Yeah, that's dumb. I know it is. But this makes sure that
	// your 1 is made in a format that holds fractions, and then since 2 is in an
	// operation involving a float, it gets "promoted" to a float, and then 1.0/2.0 returns 0.5
	float alsoReallyHalf = 1/2.0; //Either number can be a float, but at least one has to be.
	// There are other ways of promoting or converting one int to a float, but don't sweat that now.
	
	//Higher Math With <cmath>
	// The two functions from cmath you're likely to use the most are "pow" and "sqrt"
	// pow is a function, like main, and you "call" it by using its name followed by
	// parenthesis. pow takes a couple values between its parenthesis, so it knows
	// what you want to raise to some power, and what power you want to raise it to.
	// Now is also a reasonable time to introduce "const" or constant numbers. They don't change.
	const float PI = 3.141592654; // Constant numbers are usually written in all capital letters
	//Now lets make some use of pow()
	int radius = 42;
	float circleArea = PI * pow(radius, 2); 	// area = pi*r^2
	// Two standard points about this example:
	// 1. It's faster to multiply something by itself when you want to square it. E.g. radius*radius
	// 2. Even though in my comment I used " ^2 " to show "raised to the second power", that is
	// not what that means to the C++ compiler. ^ is a logical operation called "Exclusive Or"
	// Why? Because bits. Also logic.
	// But that isn't going to raise anything to any power. It will just encrypt/corrupt numbers.
	
	//Q: How do we know any of what you're telling us is true?
	//A: Let's output some of our values, and move away from math for now.
	
	//First, let's check our circleArea calculation.
	//According to Windows Calculator, I should get 5,541.769441656
	cout << "Circle Area is: " << circleArea <<endl;
	// On my computer, this program came up with "5541.77"
	/*
		Sit down, children. It's time for another block-quote lecture.
		Q: What the hell is this "<<" I have to worry about now?
		A: That's called the "insertion operator." I know, it's gross.
		This thing also shows up as the "left bit shift operator" because bits.
		
		Q: Okay, but what's kowt?
		A: The keyword is pronounced "see out" and it stands for Console Output.
		Because you are outputting. To the console.
		
		Q: Why is one thing in quotes and the other things not in quotes?
		A: So the thing in quotes is called a "string literal" because it is a
		sequence, or string, of characters which we want displayed literally like that,
		as we wrote it in the code. 
		One other thing without quotes is our variable, circleArea, which holds the result
		of our equation. When used like it is here, without quotes, and between the <<
		operators, cout converts the number to characters to print on screen.
		The last thing on the line is  "endl" which is lower-case ENDL, not END1
		This stands for "end line" and is like hitting Enter on the keyboard.
		
		Q: Why doesn't 5541.77 have commas like it should?
		A: Because C++ doesn't really offer an easy way of doing that.
		
		Q: Why did it round .769441656 to .77 ?
		A: Since fractions can't be stored precicely in a float (because bits) the
		cout assumes that numbers which are really close to round numbers are actually
		those round numbers, and so it outputs the clean version and hides the nastiness.
		
		Q: I want it to show me the whole result though.
		A: That's not a question.
		
		Q: How do I get it to show me the whole result?
		A: If you must know, you can use #include <iomanip> at the top of your program,
		on its own line around "#include <cmath>" and "#include <iostream>" and then use 
		something like:
		cout << fixed << setprecision(15) << "Circle Area is: " << circleArea <<endl;
		Here the "fixed << setprecision" being set before you output circleArea will mean
		that circleArea will display 15 digits after the decimal point.
		
	*/
	
	//INPUT
	// Often times the point of a program is to accept user input and process it.
	// Let's make our area of a circle equation slightly interactive.
	
	// 4 STEPS:
	// 1. Output a prompt to the user to tell them what you want
	cout << "Enter a number for the radius of a circle in meters:"; //Do science in metric.
	float userRadius; //Here we make a variable to hold what we get from the user through cin
	
	// 2. Get input from user using "cin >> " and the variable where we want to store the input.
	cin >> userRadius;  // notice now the >> is going the other way. This is the "extraction operator"
	/*
	 When our program gets to the line with cin, it will try to pull in some characters from
	 the console's "input buffer" aka place where it stores what you type.
	 If nothing is already sitting in the input buffer, the program will wait until the user
	 types something in, and then presses Enter
	 You may also recall I mentioned cin has its source and destination backwards.
	 Where "cout<<"Enter a number:"" actually follows a usual formula of:
	 destination operator source,
	 like x = 10, but cin is backwards, and is used as:
	 source operator destination
	 where cin, the user input, is the source.
	 In summary, do cout << pointed out away from your document, and cin >> pointed into it.
	*/
	
	// 3. Do calculations WITH USER INPUT 
	// (which means do this AFTER your lines where you get the input)
	//Now that we have our radius from the user, let's calculate the area (without pow)
	float userArea = PI*userRadius*userRadius; // area = pi*r^2
	
	// 4. Show results
	// Notice now we have two "string literals" in our output, and two variables.
	// This is fine to do, just make sure you separate strings and variables with a "<<"
	cout << "A circle with a radius of "<<userRadius<<" has an area of "<<userArea<<endl;
	
	
	//Sorry kids, ran out of time to work on this. Hopefully this will help with the first
	//few assignments before I can update it with the other basic essentials. TTYL
	
	//PROGRAM CONTROL - Conditionals
	// IF by itself
	
	// IF with ELSE
	
	// IF, ELSE IF, ELSE
	
	//PROGRAM CONTROL - Loops
	//While
	
	//Do-While
	
	//For Loop
	
	
	//Return 0 to show that no problems occurred during our program
	return 0;
}
