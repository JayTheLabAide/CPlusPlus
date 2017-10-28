/*
	(Hopefully) Simple Array Tutorial
	===========================
	Code by Jason Lillard, 2017
	===========================

	Bonjour à tous! Here's another attempt at a tutorial that will hopefully
	make it a little easier to create and use arrays.
	
	As I've said in the Functions2 Tutorial, arrays are very much like
	variables, but instead of using a single name -- or "label" -- to specify
	only one piece of data, we're going to use a label to specify the
	start of many pieces of data. You can think of an array as just a list
	of things (though you'll learn much later that the term "list" tends
	to refer to "linked-lists," which are more complicated than arrays).
	
	
	In ARM assembly language, making one variable looks something like this:
	
	myVar:
		.word 1234567

	//(FYI ".word" just means 4-byte data type, roughly the same as int)
		
	And making an array would be almost exactly the same, we would just have
	a few different values separated by commas after our label:
	
	myArr:
		.word 123, 234, 345, 456, 567, 678, 789, 890

	And we would use that one label to give us the starting point for
	this list of numbers. This label is referred to as the "base address"
	or "base pointer."
	
	[Advanced Note]: The base pointer is used in "pointer arithmetic" and
	is why array indices start at 0. For a simple array, the pointer arithmetic
	is "baseAddress + index * sizeof(dataType)" where sizeof(dataType) is the
	byte size of something like char (1), float (4) or long (8).
	
	
	Now, if you're only just learning about arrays, if you wanted to make this
	set of data in C++ you would probably do something like this:
	
	int myVar1 = 123, myVar2 = 234, myVar3 = 245; // etc.
	
	But that takes way too much keyboarding. So, fortunately, in C++ we can
	use a similar trick to assembly language, where we can use one label
	to refer to many different pieces of data:

	
	int myArr[] = {123, 234, 345, 456, 567, 678, 789, 890};  //C++ 11 only!!!
	
	
	Or, we can specify a size for the array when we make one:
	
	const int SIZE = 8;
	int myArr[SIZE] = {123, 234, 345, 456, 567, 678, 789, 890}; 
	
	
	We could also make our array first, and then fill it in one piece of
	data at a time. To do this, we'll use the [] symbols and specify which
	list item we want. For a size 8 array, our possible list items will be
	0 through 7. 
	
	Three important notes about this:
	
	1. The numbering for arrays doesn't start at 1! It starts at 0! Always!
	
	2. The numbering for arrays doesn't end at SIZE!! (8 in this example)
	
	3. The numbering for arrays DOES end at SIZE-1 !!! (7 in this example)
	
	
*/


//Let's do some actual coding now

#include <iostream> //for simple input/output
#include <cstdlib> //for rand() and srand(), random numbers
#include <ctime> //for clock() and time(0)
using namespace std;

int main(){
	
	//Alright, I needed something to build that wouldn't be in an assignment,
	//so none of you kids will be cheating off of me, so here's what we're going
	//to make:
	
	cout<<"\t\tWELCOME TO THE COW RACE SIMULATOR"<<endl; // Don't judge me.
	
	//Let's start with something we know how to do, and which is better
	//done earlier than later:
	
	const int COWS = 8;
	
	cout << "Today we will be racing "<< COWS
			<< " real-life, virtual cows for your viewing pleasure,"<<endl;;
	
	/*
		We'll get to use this COWS constant for all sorts of things related to
		our array. Also, since our array is a "static" (meaning unchanging) 
		array, we don't want this number representing its static size to change.
		Ideally, this size constant (and almost any number you use when handling
		arrays) should be unsigned, so no negative numbers are even possible to
		be stored and accidentally used to access the memory before the start
		of the array. The exception to this rule is when you are returning
		a value from a function to search an array, because conventionally
		if you return 0 or greater, this means you found what you were looking
		for at that part of the array, and if you return -1 then it means you
		didn't find it anywhere in the array. 
	*/
	
	
	//Now let's decide how far we'll be racing these cows:
	// Distance to finish line:
	//(Note: Because of how I designed this, you can change this number up
	// or down and it won't break the output to the screen )
	const int TOTALYARDS = 100; //We'll chase them up a football field.
	
	cout<<"across our speciality racetrack "<<TOTALYARDS<<" yards long!"<<endl;
	
	// This array will hold the current X coordinate,
	// or yards traveled, for each cow.
	int cowX[ COWS ]; 
	
	//This array will hold the names of each cow:
	string cowNames[ COWS ]; // We can make arrays of strings just like ints
	
	// Now let's give each cow a name, and access its place in the array
	// using the [] braces and index numbers between 0 and COWS-1
	cowNames[0] = "Knight";
	cowNames[1] = "Rookie";
	cowNames[2] = "Bishop";
	cowNames[3] = "The King";
	cowNames[4] = "Queenie";
	cowNames[5] = "Barbie";
	cowNames[6] = "Kelly";
	cowNames[7] = "G.I. Joe";

	// In C++11, this array can be made and initialized at the same time like:
	//	string cowNames [ COWS ] = { "Knight", "Rookie", "Bishop", "King",
	// 		"Queenie", "Barbie", "Kelly", "G.I. Joe" };
	
	//Let's print this whole array in a loop
	for(int i = 0; i < COWS ; i++){
		// Access each element in the array with our
		// loop counter variable "i" inside "[]" symbols:
		cout<<"Cow "<< i+1 <<": "<< cowNames [ i ] <<endl; 
		// Note that here for human counting we use i+1 (which starts at 1),
		// but for computer counting to access our array we use i (which 
		// starts at 0).
	}
	/*
	 From these cout statements, our program output here should be:
	 
		Cow 1: Knight
		Cow 2: Rookie
		Cow 3: Bishop
		Cow 4: The King
		...yadda yadda you get the idea...
		Cow 8: G.I. Joe
	*/
	
	
	//Now let's make it interesting. We'll ask the user to guess a winner.
	bool decisionMade = false;
	int userGuess;
	do{
		cout<<"Which do you think will win? (1-"<<COWS<<"): "; 
		cin>>userGuess;
		
		if( !cin.good() ){ //if a number wasn't entered
			cin.clear(); //clear "bad" flag
			cin.ignore(BUFSIZ, '\n'); //and ignore rest of buffer
		}
		else if ( userGuess >= 1 && userGuess <= COWS) {
			//A decision has been made.
			decisionMade = true;
			cin.ignore(); 	// ignore the '\n' char left in the input buffer
							// from reading in a number with cin>>
		}
	
	}while( decisionMade == false ); //repeat until decision is made
	
	// At this point userGuess is between 1 and 8. We have to keep this in mind
	// later because it doesn't align with our array counting, which goes from
	// 0 to 7.
	
	cout<<"Alright. Let's bet it all on cow #"<< userGuess
			 <<", "<< cowNames[ userGuess-1 ] << "!" << endl;
	// Because of the difference between the human and computer counting, if we
	// want to echo out which cow the user chose, we need to access array index
	// userGuess-1 in our cowNames array of strings.
	
	cout<<"<Press Enter To Continue> ";
		while (cin.get()!='\n');  //This empty loop eats through the input
		//buffer by calling cin.get() as it runs its test over and over again.
		// As a result, the user can put in a bunch of nonsense, and as soon as
		// they press enter at the end they'll be able to continue.
	
	
	//Cow Race Algorithm:
	// 1. Set each cow's x to 0
	// 2. For each cow:
	// 	2a. Generate a number between 1 and MAXSPD
	// 	2b. Add this number to the cow's x position
	//	2c. Print a representation of the cow's progress on the track
	// 3. For each cow:
	//	3a. Check if any cow's new position is greater or equal to totalYards,
	//  	3a1. If so, output winner message (may display multiple times)
	// 4. If no cow has won, jump back up to step 2.
	
	// As you can see there, I mention a constant I haven't made yet. Let's
	// create that now.
	const int MAXSPD = 4; //Cow's max speed is ~4 yards per second...
	// At least according to about 15 seconds of research and math.
	
	// So, hypothetically, the luckiest cow in the world, running at top speed
	// for every cycle, will complete the race in totalYards/MAXSPD cycles,
	// or 100/4, or 25 cycles. So buckle in, this cow race is gonna get real.
	
	
	// 1. Set each cow's x to 0
	for(int i = 0; i < COWS; i++ ) cowX[ i ] = 0;
	// Don't do the same thing to their names. I like their names.

	//Now we're going to make our "track" which we will copy and
	//draw over for each cow for each cycle.
	
	string track = "["; 	//starting line
	track.append( 77, '_'); //the track (77 characters of '_')
	track.append("||"); 	//the finish line
	
	const int SCREENWIDTH = track.length(); //let's get our "screen width"
	//for printing our output (a.k.a. the length of the track)
	//cout<<"Track string length is :"<<track.length()<<endl; //length is 81
	//We will scale our current yards to the screen width. That way we can
	//have extreme track lengths and the output will always look the same,
	//even if it takes longer for the cows to run the race.
	
	//Let's seed our random number generator with the current CPU clock cycle
	// count of our current function, main, plus the current unix time
	srand( clock() + time(0) );
	
	bool winner = false; //We will use this flag to quit our loop
	do{  // while(!winner)
	
		//Let's first "clear the screen" by spamming newline characters.
		for (int i = 0; i < 300 ; i++) cout<<'\n';
		//And then "flushing the screen buffer"
		//aka printing it to the screen with cout.flush()
		cout.flush();
	
		// 2. For each cow:
		for(int i = 0 ; i < COWS; i++){
			// 2a. Generate a number between 1 and MAXSPD
			int cowVelocity = 1 + rand()%MAXSPD;
			// rand() % MAXSPD would give us numbers between 0 and 3
			// so we add 1 to get numbers between 1 and 4
			
			// 2b. Add this number to the cow's x position
			// "x position += x velocity" moves our cow
			cowX[ i ] += cowVelocity; 
		
			// 2c. Print a representation of the cow's progress on the track
			
			//First, let's make a copy of our track string, so we can edit it.
			string trackCopy = track;
			
			//Then let's decide on our symbol for each cow. Since we only have
			// 8 cows in this version, I'll use digits chars '1' through '8'
			char cowSymbol = '1'+i; //This will give me characters '1' through
			// '8' because the ascii value for '1' will first have 0 added, then
			// 1, 2, 3, etc. so we'll get characters '1','2','3','4' etc. to '8'
			// If you have a bunch of cows, pick a different symbol like @ or $
			// or maybe 'R', since that kind of looks like an animal.
			// Or, you know... 'C'... for Cow.
			
			//Now let's paint our current NPC onto the map,
			// and remember to scale the current map coordinates by our "screen
			// width" so we can see the whole race at once
			int cowScreenPosition; //screen coordinate X
			
			cowScreenPosition = cowX[i] / (float)TOTALYARDS * (SCREENWIDTH-1);
		//Let's break that down.
		// cowX[i]/totalYards gives us what percentage of the race the cow has
		// finished. Multiplying that percentage by the screen width shows us
		// how far across the screen to draw this cow.
		// Here are a few example X values:
		// When cowX is 0, 0/100 will be 0, and that * (SCREENWIDTH-1) will be 0
		// When cowX is 50, 50/100 will be 0.5, that * (SCREENWIDTH-1) = 40
		// When cowX is 100, 100/100 will be 1, and that * (SCREENWIDTH-1) = 80
			
			// Now let's draw our cow symbol on our track with our screen pos.
			trackCopy[  cowScreenPosition ] = cowSymbol; 
		
			//Ok, and now we can actually paint our representation:
			cout << trackCopy <<endl;
			
		} //end of For Each Cow, step 2.
		
		//Now that we've moved each cow and drawn it to the screen, let's check
		//their x positions to see if we have a winner yet.
		
		// 3. For each cow:
		for(int i = 0 ; i < COWS; i++){
			// 3a. Check if any cow's new position is 
			// greater or equal to totalYards
			if ( cowX[ i ] >= TOTALYARDS ){
				//3a1. If so, output winner message (may display multiple times)
				cout<< cowNames[i] << " has crossed the finish line!"<<endl;
				winner=true; //set our winner flag so the race ends
			}
		}
		
		//Give user a chance to see the map, then have them press enter
		//before we begin the next cycle of moving and drawing.
		
		cout<<"<Press Enter To Continue> ";
		while (cin.get()!='\n');  //Use our tricky while loop to wait for '\n'
		
	// 4. If no cow has won, jump back up to step 2.
	}while(!winner);
	
	//Now let's see if our user guessed correctly and output the result
	cout<<"\n\nYou bet on "<< cowNames [ userGuess-1 ] <<", and your cow ";
	if (cowX [ userGuess-1 ] >= TOTALYARDS ) cout<<"WON!";
	else cout<<"LOST!";
	cout<<endl;
	
	//In this game a tie always goes to the user, because checking for a tie
	//is more complicated than this array example really needs to be.
	
	cout<<"\n\nHope you learned something at the cow races today. "
			"I know I didn't."<<endl;
			
	return 0;
}

