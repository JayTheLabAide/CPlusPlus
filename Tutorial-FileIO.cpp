/*
	File Input/Output Tutorial by Jason Lillard, 2017
	
	So, the important thing to remember about computers is that almost
	all of the data you deal with is basically just a stream of bytes.
	If "stream" still sounds too technical, just think of it as an array,
	collection, sequence, or list of bytes. Each byte is 8 bits, and sometimes
	we work with data on a bit-by-bit level, but most often we deal with bytes.
	The console input from the keyboard goes into the "input buffer," which is
	just a stream of bytes (each representing one character). The same is true
	of the "output buffer" used by cout: it is just a stream of bytes.
	The internet? A stream of bytes (broken into chunks called "frames" 
	and "packets"). Even your hard-drive and RAM are just streams of bytes.
	And you already know how to deal with streams of bytes through cin and cout,
	so now you will deal with streams of bytes through ifstream and ofstream.
	
	If you visit http://www.cplusplus.com/reference/istream/istream/ then the
	first thing you will see at the top is a diagram showing that iostream
	and ifstream both are based partly on the "istream" class, which introduces
	functions like ".operator>>()" which you know as ">>", and also introduces
	functions like .get(), .getline(), and .ignore(). If you are suspecting that
	"cin" is an istream object, you are absolutely right.
	Further down the page you'll see even more functions from "ios" like
	.good(), .clear(), and .fill(). All of these are all used regularly dealing
	with input from the console, and .eof() and .read() technically work when
	dealing with console input, but they're much more often used with files.
	
	You don't need to remember which things are from istream and which are from
	ios, but the important thing to remember here is that dealing with streams
	of bytes from a file in C++ is really very similar to dealing with streams
	of bytes from the "stdin" input buffer, which you've already been doing.
*/

////////////////////////////// CODE START //////////////////////////////////////

#include <iostream> //for cin and cout objects
#include <fstream> //for ifstream and ofstream objects
//#include <string> //for easy writing & reading from text files
#include <vector> //for an easily expanding container similar to an array

using namespace std; //using the standard library versions of these functions

////////////////////////// FUNCTION PROTOTYPES /////////////////////////////////

// USED IN INPUT METHOD 5
//Counts number of floats in a text file (sorta).
//Really counts how many times inFile>>f works (explained later).
unsigned countFloats( ifstream & inFile );

//USED IN INPUT METHOD 6
//Fill a float vector with a text file full of floats
void fillFloatVector( ifstream & inFile, vector<float> & fVect);

////////////////////////////// START MAIN //////////////////////////////////////
int main(){

	cout<<"\t\tFILE I/O TEST USING SEVERAL TECHNIQUES"<<endl;

	// PART 1: OUTPUT TO FILE 
	/*
		For the most part, outputting to a file is the same as outputting to
		the console. The only thing to keep in mind is that if you want your
		.txt files to look normal in notepad, then instead of using endl or
		'\n' to make a newline, you have to use "\r\n" which is a "carriage-
		return" plus a "line feed" aka newline. You can think of this as
		"carriage-return, line-feed" or you can come up with some kind of
		memonic to remember RN, like "right now" or "real newline"
		Also notice that while '\n' is a single char and goes in single-quotes,
		"\r\n" is two chars, making it a c-string that goes in double-quotes.
	*/
	
	const char * FNAME = "FIOData.txt"; //First, here's our file name c-string
	
	cout<<"CREATING OR REMAKING "<< FNAME <<" WITH OFSTREAM"<<endl;
	
	ofstream outFile; //Now we make our ostream object, and name it outFile
	
	outFile.open( FNAME ); //open our text file so we can fill it with data.
	// NOTE: if we wanted to open this file to add on to the end of it,
	// we would have to open it like this:
	// outFile.open("data.txt", ios::app);
	// The ios::app flag indicates we want to "append" to the end of file
	// If we leave out the ios::app flag, then if data.txt already exists
	// it will be destroyed and created all over from scratch.
	
	
	// Save a bunch of circle areas (pi*radius^2, where our counter i is radius)
	for( int i = 1; i <= 10; i++) {
		outFile << 3.14156*i*i; //write one number to the file
		outFile << "\r\n"; //output "carriage return, newline" instead of endl
	}
	
	// CLOSE THE FILE!!!
	outFile.close();
	
	cout<<FNAME<<" WRITTEN SUCCESSFULLY!\n"<<endl;
	
	////////////////////////////////////////////////////////////////////////////
	
	//Stupid counter used in lazy output message;
	int methodCounter = 1;
	const char * METHODMSG = "NOW TESTING INPUT METHOD #";
	
	// PART 2: INPUT FROM A FILE
	/*
		There are a bunch of ways to do this so I'll show you every way
		I know of that seems to be consistent. Learn all the different ways,
		because once in a while a compiler will complain about the easy ways
		and you'll have to do things the tough way.
	*/
	
	cout<<"OPENING FILE WITH IFSTREAM FOR FIRST TIME..."<<endl;
	
	
	//Now we'll open this file and read in the contents a few different ways.
	//Let's print the file to the screen, too.
	ifstream inFile; //create our ifstream object named inFile
	inFile.open( FNAME ); //open the file to read in the data already there.
	
	cout<<"FILE OPENED!\n"<<endl;
	//INPUT, METHOD ONE:
	//Quick and dirty, kind of stupid because it skips all whitespace:
	// One character at a time with >> and <<
	
	//Announce which test we're running, increment test counter
	cout<< METHODMSG << methodCounter++ <<endl;
	cout<<"(Using char c, inFile>>c and cout<<c. FULLY ERASES NEWLINES/SPACES!)"
			<<endl;
	
	//Our temporary variable "c" to hold one character (we need this)
	char c;
	while ( inFile >> c )  cout << c ; //while inFile>>c succeeds, output char c
	cout<<'\n'<<endl;
	/*
		NOTE: if this doesn't compile and gives you an error saying something
		like "ifstream::operator>> doesn't return a bool" then try input method
		three, below, which uses inFile.eof() to test for the end of file marker
	*/
	
	//RESET THE FILE, METHOD ONE:
	//Just close and open it again.
	inFile.close();
	inFile.open( FNAME );
	
	
	//INPUT METHOD TWO:
	// Also quick and dirty, slightly less stupid:
	// One character at a time with get(char) and put(char)
	
	//Announce which test we're running, increment test counter
	cout<< METHODMSG << methodCounter++ <<endl;
	cout<<
	"(Using inFile.get(c) and cout.put(c). FULLY PRESERVES SPACES, NEWLINES!)"
			<<endl;
	
	//make our temp variable c
	//char c	//(commented out because we just made this in the last example)	
	while (  inFile.get(c)  )  cout.put(c); //while get(c) works, put(c)
	cout<<endl;

	//RESET THE FILE, METHOD TWO:
	// It's easier to close and open the file, but also slower than this way:
	inFile.clear(); //clear the EOF (end of file) flag 
	
	// The function seekg(long) moves or "seeks" the g or "getter".
	inFile.seekg(0); //put the "file read marker" to byte 0 (start of the file)
	//NOTE: .clear() is needed before seekg(0) for C++ earlier than C++11.
	
	
	//INPUT METHOD THREE:
	// Read in numbers from a file and convert them to variables like float
	
	//Announce which test we're running, increment test counter
	cout<< METHODMSG << methodCounter++ <<endl;
	cout<<
"(Using float f, inFile>>f, while(!inFile.eof() ). ERASES NEWLINES/SPACES!)"
			<<endl;
	
	float f; //temp variable to hold input
	
	//Try to read in from inFile into our float
	inFile>>f;
	
	while ( !inFile.eof() ){ //if the end of file flag wasn't set by inFile>>f
		cout<<f<<endl; //that means f has a float, so output with cout
		// NOTE: since this method of reading the file erases "whitespace"
		// characters like spaces and newlines, be sure to add endl to outputs.
		
		inFile>>f; //then try to read again
		//When inFile>>f fails, the !inFile.eof() test will then also fail
	}
	cout<<endl;
	
	//RESET THE FILE, METHOD TWO AND A HALF:
	inFile.clear(); //clear EOF flag
	inFile.seekg( 0L, ios::beg ); //set getter to 0 bytes from beginning
	// The 0L is equivalent to (long)0 or static_cast<long>(0), which just
	// specifies that the number being passed in is a long and not an int
	// to set the marker to the end, use: inFile.seekg(0, ios::end);
	
	// BONUS:
	// Use inFile.tellg() to learn which byte is currently being pointed to by
	// the file read marker.
	// If you want to know a file's byte size, you can use these two lines:
	// inFile.seekg( 0L, ios::end );	//first put file marker at last byte
	// long size = inFile.tellg();		//now tell me what byte we're on
	
	
	//INPUT METHOD FOUR:
	// Read in numbers from file, put into a giant array
	
	//Announce which test we're running, increment test counter
	cout<< METHODMSG << methodCounter++ <<endl;
	cout<<"(Using a big array of floats. ERASES NEWLINES/SPACES!)"<<endl;
	
	const unsigned FLOATS = 100; //decide on a size of our array (make const)
	float tooManyFloats[FLOATS]; //make an array of too many floats
	
	unsigned index = 0; //create counter to help us fill array
	// while we haven't filled the array and while >> succeeds in storing floats
	
	
	while ( index < FLOATS && inFile >> tooManyFloats[index] ){
		//output the float we just read into our array
		cout << tooManyFloats[index] <<endl;
		//increment our counter to fill the next slot in our array
		index++;
	} 
	
	
	//ASIDE: now our variable "index" holds the number of elements read in
	//so we should save this number in case we need it again
	const unsigned FLOATSREAD = index;
	
	//Now we can close the file and use our array instead, to do things like...
	inFile.close();
	cout<<"PRINTING ARRAY IN REVERSE:"<<endl;
	// ...going through our array in reverse and printing it backwards
	// (start at FLOATSREAD-1 ; repeat while i isn't negative ; decrement i )
	for( int i = FLOATSREAD-1; i >= 0 ; i-- ) {
		cout << tooManyFloats[i] <<endl;
	}
	cout<<endl;

	//REOPEN FILE BECAUSE I CLOSED IT TO PROVE A POINT
	inFile.open( FNAME );


	//INPUT METHOD FIVE:
	// Count numbers in file, create perfectly-sized array, read in #s to array
	
	//Announce which test we're running, increment test counter
	cout<< METHODMSG << methodCounter++ <<endl;
	cout<<
	"(Using countFloats(ifstream&) and dynamic memory. ERASES NEWLINES/SPACES!)"
	<<endl;
	
	// 1. COUNT NUMBERS
	//First, use a loop, or a simple function like I made here, to count
	//the number of floats within the file.
	unsigned numFloats = countFloats( inFile );
	
	// 2. CREATE PERFECTLY-SIZED ARRAY
	//use a float pointer to "dynamically allocate" an array of floats
	float * fptr;
	fptr = new float[numFloats]; //make a new array of floats, size = numFloats
	
	//Now the array doesn't waste any space. Also, we can use the pointer
	//just like the name of an array, and output everything like before.
	
	// 3. READ IN #S TO ARRAY
	//since we know how many times >> will work, we don't need to check .eof()
	for(int i = 0; i < numFloats; i++){ 
		inFile >> fptr[i];
	}
	
	// 4. CLOSE OUR FILE AGAIN
	inFile.close();
	
	// 5. OUTPUT DYNAMIC ARRAY
	for( int i = 0; i < numFloats; i++){
		cout << fptr[i]<<endl;
		//[ADVANCED]: this could also be done with "pointer arithmetic" like so:
		// cout << *(fptr+i) <<endl;
	}
	cout<<endl;
	
	// 6. DE-ALLOCATE DYNAMIC ARRAY
	// IMPORTANT NOTE ABOUT DYNAMIC ARRAYS:
	// EVERY NEW NEEDS A DELETE. EVERY. SINGLE. ONE.
	delete [] fptr;
	
	
	//INPUT METHOD SIX:
	// Read in numbers from file, push into a vector
	
	//Announce which test we're running, increment test counter
	cout<< METHODMSG << methodCounter++ <<endl;
	cout<<
"(Using fillFloatVector(ifstream&, vector<float>&). ERASES NEWLINES/SPACES!)"
			<<endl;
	
	//Create vector of floats
	//(use "template argument" <float> to specify the data type of the vector)
	vector<float> fVect;
	
	//Open the file and use our handy function to fill the vector from it.
	inFile.open( FNAME );
	fillFloatVector(inFile, fVect);
	
	//Now close the file a final time since we saved the data into our vector
	inFile.close();
	
	//Use the vector's "member function" .size() to learn the # of floats saved.
	unsigned vectSize = fVect.size();
	
	//Then output the vector just like an array
	for(int i = 0; i < vectSize; i++){
		cout << fVect[i] <<endl; // the [] notation works with vectors too
	}
	cout<<endl;
	
	cout<<"FILE I/O TEST TERMINATING. FAREWELL."<<endl;
	return 0;
}
///////////////////////////////// END MAIN /////////////////////////////////////


////////////////////////////// FUNCTION DEFINITIONS ////////////////////////////


//Counts number of floats in a text file (sorta).
//Really counts how many times inFile>>f works.
unsigned countFloats( ifstream & inFile ){
	//reset file (just in case)
	inFile.clear();
	inFile.seekg(0);
	//make our counter and temporary variable
	unsigned int counter = 0;
	float f;
	//while floats are successfully read in with >>, increment our counter
	while (inFile>>f) counter++;
	//after >> fails, return current count
	
	//But first, BE KIND PLEASE REWIND
	inFile.clear();
	inFile.seekg(0);
	
	return counter; 
}


//Fill a float vector with a text file full of floats
void fillFloatVector( ifstream & inFile, vector<float> & fVect){
	/*
		The stuff that is different here, like using inFile.peek()!=EOF
		and .good(), doesn't need to be used with vectors. Those are just
		used here to show one more way of dealing with file I/O.
		
		NOTE: if .peek() does return an EOF (end of file) marker, the .eof()
		flag IS NOT SET. This means that on one hand using .peek() is easier
		because you won't have to call .clear() once you find EOF. The downside
		is that if you're using .peek() to read the next character, you can't
		also use .eof() because it will return FALSE like you didn't reach an
		EOF character yet. I have only ever needed to use this method when
		having problems with the last value in a file being read in twice for
		mysterious reasons. You normally won't have to use this technique.
	*/
	
	//reset file (just in case)
	inFile.clear();
	inFile.seekg(0);
	//make our temporary variable
	float f;
	bool valid = true;
	
	//while peek() tells us the EOF marker isn't next, and last read worked
	while( inFile.peek() != EOF  &&  valid ){
		
		inFile>>f; //try to read in a float
		
		//Save in our flag whether file read was successful
		valid = inFile.good();
		
		//if read was successful, push float to back of vector
		if (valid) fVect.push_back(f);
		
	} //end while loop
	
	//On some compilers this loop could also be done as:	
	//while(inFile>>f) fVect.push_back(f);
	
	//BE KIND PLEASE REWIND
	inFile.clear();
	inFile.seekg(0);
	
	return; //return from void function
}
