//Tutorial, Code by Jason Lillard, 2017

/* <-- start of "block comment"

	C++ The Very Basics:
	
	The Pre-Basics:
		This is "block comment" and it begins with a
		/* 
		and ends with a
		*/
	// This line is not in the above comment, which ended with the "*/" above it.
	
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
			
		Program Control (jumping around)
		- if, else if, else (making decisions)
		- while and do-while loops (simple loops which go until a certain condition is met)
		- the "for" loop (A little more complicated, but just a loop that goes a set number of times)
	
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

//Now let's start typing some real code:

//We need iostream to display text to the "console" or "terminal" and get input from the users
//You're a long way from graphics, kid. Get used to the look of fixed-width characters.
#include <iostream> 

//We need cmath for pow() to do exponents, and sqrt() to do square roots.
// Actually there are other very complicated ways of doing those things, 
// but they're awful, so lets use these.
#include <cmath> 

//And here we need string for the objects called strings which can hold lines of text
#include <string>

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
	//And we can use the "*" symbol for multiplication.
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
	// you'll eventually come up with some clever uses for them.
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
	
	// SECTION 3: OUTPUT TO CONSOLE WINDOW AND INPUT FROM USER
	
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
	
	
	// Often times the point of a program is to accept user input and process it.
	// Let's make our area of a circle equation slightly interactive.
	
	// 4 STEPS TO GETTING INPUT:
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
	 The line "cout << "Enter a number:";" actually follows a usual formula of:
	 destination operator source,
	 similar to "x = 10". But cin is backwards, and is used like:
	 source operator destination
	 And cin, the user input, is the source.
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
	
	
	//SECTION 4: PROGRAM CONTROL - Conditionals
	// IF by itself
	/*
		Now, here's where our computer really becomes more than a calculator:
		conditional execution. This is one of the main reasons you create flow charts.
		The simplest methods of decision making are based on true and false.
	*/
	
	bool isDoorOpen = false; //here is a "bool" variable. They can hold either "true" or "false."
	
	//Here is our test. The important keyword here is "if"
	// after the "if" is our test within a pair of parenthesis.
	// VERY IMPORTANT NOTE: testing equality is done with ==, not with =.
	// A single equals sign sets the variable on the left to the value on the right,
	// which then becomes either "true" or "false" based on what you assigned.
	// DO NOT DO ASSIGNMENTS WITH "=" IN A TEST. While it will compile, it is never recommended.
	if ( isDoorOpen == false ) 
	{ //notice the curly braces, these make up the code block that happens ONLY IF the condition is true
		//here in the code block, since "isDoorOpen == false" is true, since we set it to false ourselves,
		//we will execute the code to open the door.
		cout<<"Opening door.."<<endl;
		isDoorOpen = true; //now our bool type variable is set to true
	}
	
	//The other type of conditional test involves inequalities, meaning less than or greater than
	// Let's set some variables for a simple business scenario where a conditional might be useful.
	int chickens = 27; //Note we use an integer type here since we don't want fractions of chickens.
	//But since these following values represent dollars,
	// we'll use floating types to hold the dollars and cents
	float chickenPrice = 1.50, farmFunds = 200.75; 
	
	if ( chickens < 30 ){ //if value held in variable "chickens" is less than 30,
		//do this stuff...
		cout << "Buying more chickens!"<<endl; //Inform user that chickens are being bought.
		farmFunds = farmFunds - (chickenPrice * 5 );  // Subtract price of 5 chickens from farmFunds
		chickens = chickens + 5; // Then set chickens to 5 more than its current amount.
		cout << "Current Chicken Population: "<<chickens<<endl; //output any numbers that changed
		cout << "Funds remaining: $"<< farmFunds <<endl; //so user knows what happened
	} //end block of code that executes when chickens < 30
	
		
	// IF with ELSE
	//Sometimes decisions have two parts to them, meaning if a certain condition is set,
	//one action is to be taken, but otherwise something else is to be done. 
	//That's where if and else comes in.
	
	short tinyNum = 4;
	short userGuess;
	
	cout << "Guess a number between 1 and 10: "; //notice no "endl" here since we want their
	// input on the same line, mostly because that just looks better after short prompts.
	cin >> userGuess; //now we use "cin" to get a number from the user and put it in variable userGuess
	
	//Now we use conditionals to determine if userGuess and tinyNum hold the same value
	if ( userGuess == tinyNum ){ //notice the "==" to test equality
		cout <<"Congrats, you either guessed correctly or cheated!"<<endl;
	}
	else{ //notice the "else" block doesn't have a test, it just happens if the block above doesn't happen
	
		cout <<"Wow, you didn't get the answer right? Did you even read the source code?"<<endl;
	}
	
	
	// IF, ELSE IF, ELSE
	// often times it is not enough to have simply "if this" and "if not this"
	// and we need a slightly more complicated form of decision making. That's where we get...
	
	cout<<"Okay, I'll give you one more guess. Pick a number between 1 and 10: ";
	cin >> userGuess; //get another number from user, put it in userGuess
	
	if ( userGuess < tinyNum ){
		cout<<"Too bad! Your guess was too low."<<endl;
	}
	// Here we use else if to test another condition *only after the above test fails*
	else if ( userGuess > tinyNum ){ 
		cout<<"So sad! Your guess was too high."<<endl;
	}
	else{ // if guess wasn't < or >, then it was == (meaning equal)
		//This final else block only is stepped into if all other tests return "false" 
		cout<<"Your guess was exactly right! Hacker."<<endl;
	}
	
	//Special Note: Remember the above collection of tests; these will be crucial for "binary 
	// search" algorithms which efficiently jump through a sorted list to find a specific value.
	// You will cover that after "arrays" of data, and how to sort and search them in various ways.
	
	
	//PROGRAM CONTROL - Loops
	//While
	/*
		Loops can be intimidating at first, but they work on the same basic idea as
		the "if" block. If the given test is true, the code block will be entered,
		and if not, then the block will be skipped. The difference between the if
		and the while blocks then comes down to how many times the blocks are
		executed. The if block by itself is either executed once or zero times.
		The while block continues to execute until either you shut down the program or
		computer, or you change a variable involved in the test so that the test
		returns a "false" result.
	*/
	
	//Let's simulate what Michio Kaku calls the lowest level of consciousness: the thermostat
	float roomTempFaren = 51.2; //let's assume our room temperature starts here
	while ( roomTempFaren < 72 ){
		cout<<"Room temp too low at "<<roomTempFaren;
		cout<<". Adjusting by 7 Degrees Fahrenheit."<<endl;
		//Notice that the above two outputs should appear on the same line
		roomTempFaren += 7; //this fancy notation is same as: roomTempFaren = roomTempFaren + 7;
	}
	cout<<"Room temp now suitable at "<<roomTempFaren<<" degrees Fahrenheit."<<endl;
	//The above block ran several times, and as long as (roomTempFaren < 72) was true
	// after the previous block's execution, the test returned true and the block executed again
	// Only after the test returned false as a result was the loop block skipped over.
	
	//This while loop will not be entered into now that roomTempFaren is too high:
	while (roomTempFaren < 10 ) {
		cout << "It's freezing in here!"<<endl;
	}
	// even though the while loop is like an "if" block, there is no "else" part to a while loop
	// If you want to enter a loop only if a condition is met, use if and else blocks around
	// a while block. For example (using our previous bool variable):
	
	if ( isDoorOpen ){ //this test is the same as "if (isDoorOpen == true)"
		cout<<"WARNING. DOOR OPEN. PLEASE TURN OFF AIR CONDITIONING."<<endl;
		//You might have noticed that at this point our brilliant program has opened
		//the door, cranked the air conditioning, and now scolded us for having the door open
	}
	else{ //This block is entered if isDoorOpen == false
		//(This will not execute as I wrote this code, since isDoorOpen was set to true)
	
		//Here we have our previous while loop block "nested" in our else block
		while ( roomTempFaren < 72 ){
			cout<<"Room temp too low at "<<roomTempFaren;
			cout<<". Adjusting by 7 Degrees Fahrenheit."<<endl;
			roomTempFaren += 7; 
		}
	
	}
	
	//Do-While
	/*
		Where the while loop is useful when you're not sure if the condition is even going
		to be true once, sometimes you know you want your loop's block to execute at least
		once, and then to keep executing until a certain condition is met. For example,
		getting user input and then testing it, and re-asking if the input was bad, is
		a very common use for a do-while loop.
		The essence of a do while loop is:
		
		do{
			//code here
		}while( testIsTrue );
		
		The do-while loop is the upside-down while loop, in a way.
		It is a "post-test" loop, meaning it runs its test after 
		it runs the code for the first time.
	*/
	//Testing user input with Do-While:
	
	// A string holds a sequence of characters. It can hold words or sentences.
	string userInput; //here's a string to hold our user input. 
	const string correctPass = "password"; //here is a const string that won't change
	
	do{ //do this stuff at least once:
	
		cout <<"Enter \"password\" to continue: "; //Here we use \" to put a quote symbol in a string
		cin >> userInput; //get input from console and store it in variable userInput
		
	//Here we use != to test if user input is "not equal" to correct password
	}while( userInput != correctPass ); 
		
	//This code will only execute when userInput == correctPass
	cout<<"You entered \"password\" correctly! Great job!"<<endl;
	
	
	//WARNING: A BOSS FIGHT APPROACHES AHEAD:
	/*
		I'll try to throw in a decent intro to the for loop in the 15 lines I have left.
		Basically: use the for loop when you know exactly how many times you want to loop.
		A naked for-ever loop block looks like this: for( ; ; ){ }
		Around those semicolons in the parenthesis go the 3 parts of the "for loop header"
		Part 1: The Initialization. This happens once. Usually it's "int i = 0"
		 Where "i" will be a counter used to keep track of times through the loop
		Part 2: The Test. Just like the test in a while loop. Often it's " i < size"
		 Where "size" is how many pieces of data are being looked at by the loop.
		Part 3: The Incrementation. This is most often where your counter is added to.
		 Most often times this is just "i++" which means set i to its current value + 1.
		The multiple parts to the for loop header make it look confusing, 
		but each part is something you've already done before:
		int i = 0		defining and initializing a variable
		i < size		testing a conditional statement
		i = i+1			setting a variable to a value (based on its current value)
	*/
	//For Loop
	int size = 5; // how many times our loop will go. (the "size" of our imaginary data array)
	//Data is almost always accessed starting at number 0, so get used to counting that way in your "for" loops
	for(int i = 0  ;  i < size  ;  i++ ){ // Go once for when i = 0, 1, 2, 3 and finally 4
		cout<<"Message "<<i+1<<":\n"; //print which "iteration" of the loop we're on, (1-5), and use a \n newline
		cout<<"Blast-off in "<< size-i <<"..."<<endl; //While i counts up, size-i will count down
	}
	cout<<"Ignition. We have blast off!"<<endl; //When code gets here, loop has finished
	
	//RETURN FROM MAIN:	
	//Finally, return 0 to show that no problems occurred during our program
	return 0;
}	// And don't forget to close int main() with this final curly brace
//		THE END 		//
