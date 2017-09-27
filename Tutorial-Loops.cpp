/*
	Intro to loops. Chicken-themed for some reason.
	Also includes a rough implementation of the dice game Craps.
	I was kind of all over the place with this one.
	--------------------------------------------
	Code by Jason Lillard, 2017
*/

#include <iostream> //for cout and cin
#include <random> //for default_random_engine, uniform_int_distribution -- C++11 STD!
#include <ctime> //for clock and CLOCKS_PER_SEC (to generate seed for our random engine)
using namespace std;

int main(){
	//First, let's start our timer that we'll use for random numbers later.
	unsigned long timer_start = clock();
	
	/*
		Alright, so before we start with loops, 
		here's what an if block looks like:
		
		if ( test ){ 		//if "test" is true
							//do this stuff
		}					//end of if block
		
		
		And here is, the simplest loop:
		
		while( test ) { 	//if "test" is true
							//do this stuff then
							//do something that might change "test" to false					
		}					//end of while block
		
		
		If we want to make an infinite loop (which is sometimes useful)
		we can put the keyword "true" in the loop test area, and it won't stop.
		
		For example:
		
		while(true){
			//read in controller input
			//calculate elapsed time since last update
			//update physics/game state using elapsed time
			//redraw screen
		}	//end of while block
		
		Most often times, though, we want our loops to end after a set number
		of times, or when a certain situation has finally occurred.
	*/

	//In my opinion, the simplest of the "while" loops is the counting loop
	//even though the "for" loop is actually better for that (once you learn it)
	
	//Step 1 of a counting while loop:
	//Initialize Counters
	int chickens = 0;	//this will keep track of how many times we've looped
	const int BIRDHOUSES = 10;		//this will be the maximum times we loop
	//You won't always want to use a "const" number for your maximum loop
	//count, but it is a good idea in part because you know the max number won't
	//keep growing and therefore keep the loop going forever (which can happen)
	
	//Step 2 of a counting while loop:
	//The "while loop header" with our test, aka "conditional statement"
	//This loop will go while the number in the counter is less than the max
	while (chickens < BIRDHOUSES) {  //while chickens is less than # of houses
	
		//Step 3 of a counting while loop:
		//In a counting loop, you will often output your counter's value
		//in one way or another every time the loop goes around. 
		cout<< "Only " << chickens << " number of chickens!"<<endl;
		cout<<"Houses still empty!\nACQUIRE CHICKEN"<<endl;
		
		//Step 4 of a ANY loop:
	//Do something that will eventually make the test in the loop header false
		chickens++; //acquire chicken. (chickens++ means chickens = chickens+1 )
		//Since our loop is based on counting, the thing that we do which makes
		//our test false (eventually) is that we get more chickens.
		//When the number of chickens becomes equal to the number of birdhouses,
		//our loop will stop going once it gets to the test and fails it.
		
		//Step 5 of ANY Loop:
	}	//<------ end of while loop block. Closing curly brace.
	
	//When code gets here, loop is done here
	//Step 6:
	//Output results of loop. There must have been some reason you made it.
	cout<<"BIRDHOUSE FILLED. "<< chickens << " CHICKENS LIFTED!"<<endl;
	
	
	//Alright, got that down? Now I'm going to put a loop in a loop.
	//This is (roughly) how counting loops can be used to draw a pattern
	//on the screen. Here we'll draw 9 lines of 'X', each 12 characters wide
	
	//Step 1: Initialize counters
	int x = 0, y = 0, MAX_X = 12, MAX_Y = 9;//x will be our inner loop & y outer
	
	//Step 2: Outer loop header
	while (y < MAX_Y){ //This test is just like our above test. Counter < Max
	
		//Step 3: Re-initialize your inner loop counter. (AKA zero it out)
		x = 0; //If you forget this, the inner loop will only draw one line
	
		//Step 3: Inner loop header 
		while (x < MAX_X){
			//Step 4: Print one character to the screen
			cout<<'X'; 	// DON'T USE AN ENDL OR YOU'LL BREAK THE LINE
			//(This is how we draw one line of text left to right)
		
			//Step 5: Increment INNER loop counter.
			//Don't think we can skip this step just because we're "nested"
			x++;
			
		}	//<--- end of while (x < MAX_X);
		
		//Step 6: Once the inner loop has drawn its line of text, NOW do endl
		cout<<endl;
		
		//Step 7: Increment OUTER loop counter.
		y++;
		
	}//<---- end of while (y < MAX_Y)

	//Step 8: Loop is over, perhaps output results.
	cout<<"Here is the henhouse what done houses the chickens."<<endl;
	
	
	//Sometimes clever things are done with counting loops, in that
	//the loops have headers, but don't need any bodies.
	//For example, here we have our decrement (opposite of increment) in the
	//header of the test loop itself.
	while( 0 < --chickens );
	//It looks strange, but this loop WILL eventually end, because
	//before each time the test runs, the -- sets chickens to chickens - 1
	//and so eventually chickens will equal zero
	cout<<"Warning: " << chickens << " chickens left." <<endl;
	cout<<"WAT. WHO DONE FLIMFLAMMED ME CHICKENS?"<<endl;
	
	/*
		New Challenger Approaching:
		DO WHILE LOOP
		
		So the do-while loop has exactly one more word than the while loop.
		Can you guess which word it is? Yeah. You can operate a computer,
		so you should be able to guess which one.
		
		Here's the basic do-while loop structure:
		
		do{			//literally "do" then our opening curly brace
					//loop's code stuff.
					//more stuff which will eventually make following test fail
		}while( test );		//a test which runs after the loop's code is run
		
		This loop jumps back to the start after the test if the test is true
		The standard answer for when you want to use this loop is,
		"When you know you want the code in the loop to run at least once."
		If you design your while loops well, you can avoid ever using a
		do-while loop, but sometimes a do-while loop is much easier to make.
	*/
	
	//A fairly simple, common example:
	//VERIFY USER INPUT WITH DO-WHILE
	//Making sure you get a number from the user
	int userInt; //the variable to hold our number from the user
	bool inputGood = false; //our flag to control whether we loop again or not
	const int MIN_INPUT=1, MAX_INPUT = 100; //constants for our accepted range
	
	do{	//<--- do-while loop begins here
		//output prompt at least once, and for every time we loop
		cout<<"Enter a number between "<<MIN_INPUT<<" and "<<MAX_INPUT<<": ";
		//try to get input from user using cin, store result in userInt
		cin>>userInt;
		//WARNING: DON'T SKIP THE FOLLOWING TEST (or input loop could FREAK OUT)
		if (!cin.good() ){ //if cin.good() == false   (means input was a char)
			cin.clear(); //clear the "flag" that cin had an issue
			cin.ignore(1000, '\n'); //ignore the rest of the input stream
		}
		else{ // if cin.good() == true:
			//Test if number was in range, set our exit flag based on test
			inputGood = (userInt >= MIN_INPUT && userInt <= MAX_INPUT);
		}
		
	}while(!inputGood); //repeat while inputGood == false
	//Output a message that "echoes out" input, shows input was successful
	cout<<userInt<<" accepted as bet!"<<endl;
	
	
	//BOSS BATTLE APPROACHING:
	
	//DO-WHILE For making a game:
	
	//With RNG code from http://www.cplusplus.com/reference/random/
	//And http://www.cplusplus.com/reference/ctime/clock/
	//Make our C++11 random number generator
	default_random_engine RNG; //we'll name it RNG
	//seed our RNG with elapsed time (now - then)
	RNG.seed( clock() - timer_start );
	uniform_int_distribution<int> range(1,6); //make our "distribution" for D6
	
	//Now with our RNG set up, let's simulate a single game of "Craps"
	int sum = range(RNG) + range(RNG); //roll 2 die with range(RNG)
	int point = -1; //This will be the sum we will try to re-roll if we don't
			//automatically win or lose on the first roll
	bool gameOver = false; //set our flag for when we leave our do-while loop
	int passBet = userInt; //And let's use input from prev example as our bet
	int payOut = 0; //our eventual win (if any)
	
	cout<<"Oh well. I'll win 'em back right quick.\n"
		<<"Here, watch me play a game of what I call Craps...\n"
		<<"We'll bet "<<passBet<<" of the chickens from my other property.\n"
		<<"Let's roll!"<<endl;
		
	do{ //Since do-while is a "post-test" loop, this code runs at least once:
	
		cout<<"The total was "<<sum<<"!"<<endl;
		if (point == -1)
		{ //FIRST ROLL
			//Determine if first roll resulted in win, loss, or "point" set
			if (sum==7||sum==11){
				cout<<"We won on the first roll! I knew I was good at this\n";
				payOut = passBet * 2;
				gameOver = true;
			}
			else if (sum==2||sum==12){
				cout<<"Darn our luck. We lost on the first roll!";
				gameOver = true;
			}
			else{ //point established
				cout<<"Now we gotta get that one again.\n"
					<<"Let's max out our odds bet and here we go..."<<endl;
				point = sum; //Save our sum which we will need to re-roll
				//game is not over yet
				//re-roll die
				sum = range(RNG)+range(RNG); //get 2 die rolls
			}
		}
		else{ //SUBSEQUENT ROLLS -- POINT ESTABLISHED
			
			//first let's check if we lost
			if (sum == 7 ){
				cout<<"7! Our pass bet done lost!"<<endl;
				gameOver = true;
			}
			//now let's check if we won
			else if (sum == point){
				cout<<point<<" rolled! Our pass bet won!"<<endl;
				//Determine payouts (notice fractional payouts get truncated)
				if (sum==4||sum==10) payOut = passBet * 2;
				else if (sum==5||sum==9) payOut = (int)passBet * (3/2.0); 
				else if (sum==6 || sum == 8) payOut = (int)passBet*(6/5.0);
				gameOver=true;
			}
			else{ //else, keep rolling
				cout<<"Aint nothin' we lookin' fer..."<<endl;
				//re-roll die
				sum = range(RNG)+range(RNG); //get 2 die rolls
			}
			
		} //end of if block to process turns past the first
	
	} while (!gameOver); //repeat loop while gameOver == false
	
	//At this point our while loop is over, here's what happens afterwards:
	cout<<"Our payouts was a full "<<payOut<<" chickens!"<<endl;
	if (payOut > 0 ) cout<<"See? I'm like, a smart guy. Best brain."<<endl;
	else cout<<"We got robbed! Totally unfair. Sad."<<endl;
	
	
	//If you survived that, here's a simple example to finish off
	//our current session of running around like chickens with our heads cut off
	
	//FOR LOOP
	//Here, we'll do 2 counting loops using one accumulator to sum some numbers.
	//First, the while loop that we know.
	short A = 0;	// our Accumulator
	short X = 1; 	// our counter
	short Y = 5;	//our max
	
	while (X <= Y) {
		A = A + X; //add X to A, store in A
		X++;	//add 1 to X
	}
	//At this point X is 6
	
	//Now, our for loop will do the same thing as our while, going from 6 to 10
	//First is the "initialize" and normally you initialize your counter,
	//but we already did that, so here we're going to initialize our max
	for ( Y = Y*2 ;  X <= Y ;  X++ ){ //Notice our test is the same, so is X++
		A = A + X;	//Add X's value to our accumulator
	}
	//Output our sum of numbers from 0 to 10, stored in A
	cout<<"Now what am I going to do with my field full of "<< A <<" sheep?"
		<<endl;
	
	//return from main
	return 0;
}//end main's code block
