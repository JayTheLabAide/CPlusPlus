/*
	For M. Ashok Kumar on SoloLearn
*/
#include <iostream>
#include <fstream>
#include <iomanip> //for easy dollar formatting (optional)
using namespace std; // <- this keeps you from having to put std:: everywhere


/*
	You can make a struct a little easier in C++ than in old C.
	Also, "objects" like structs and classes usually have upper-case names.
*/
struct Transaction{
	public: //structs are public by default, but this is a good reminder to yourself.
	/*
		Keep track of your string sizes in a way that's easy to look up. 
		This piece of data is shared across all members of the class (so you only have to store it in memory once).
	*/
	static const short NAMESZ = 100; //Max size of transaction name.
	
	/*
		There's no reason to have a character array and then a pointer to that array
		because arrays ARE pointers, and you can use their names like pointers.
	*/
	char txnName[NAMESZ]; //Transaction name.
	
	float amount; //Typically money amounts have decimals, so you'll want to use float or double.
	
	char pan[NAMESZ]; //"pan" number.
	
	/*
		Make a separate function for printing out data (this comes in handy very often)
	*/
	void printDetails(){
		cout<<fixed<<setprecision(2); //Will make "amount" variable print out with 2 decimal places for cents (doesn't change the value of the variable, just how it looks when printed out).
		cout<< this->txnName <<":\n$"<< this->amount <<"\nPAN: "<< this->pan <<endl; //Using "this->" specifies this function is using member variables
		//Note: It is much faster to use \n for new-lines until the end, then use endl (because of "flushing the output buffer")
	}
	
	/*
		Function for filling this struct
	*/
	void fillDetails(){
		cout<<"Enter name: ";
		/*
			cin.getline is good for c-strings because you can specify a max size, 
			which here we specify with the static constant we made, NAMESZ. We access such data shared across the
			whole class with the class name then the "scope resolution operator" which is ::
		*/
		cin.getline( this->txnName, Transaction::NAMESZ); 
		
		cout<<"Enter the amount: ";
		cin>>amount;
		cin.ignore(); //ignore the single '\n' left in the input buffer after the numeric input
		
		cout<<"Enter the PAN: ";
		cin.getline( this->pan, Transaction::NAMESZ);
		
		cout<<"Entered details:\n";
		this->printDetails(); //call this object's version of printTrDetails to echo back input.
	}
	
};


int main(){
	//Our Transaction struct for getting input and writing to file.
	Transaction taWrite;
	//Call our member function to fill this instance with data.
	taWrite.fillDetails();
	
	//Write our object to a file as binary data.
	//First open file in binary mode (use ofstream if just writing out).
	ofstream outFile("tranx1.dat", ios::app | ios::binary); //If we put this stuff in the constructor, we don't need to use .open()
	//Also keep in mind ios::app means we're outputting to the end of this file, so if we only read back in one file we might not see what we just wrote)
	/*
		Specify the address of the structure (as a character pointer),
		and use sizeof(ta) to get number of bytes (i.e. characters) to save starting at this address.
	*/
	cout<<"Saving data..."<<endl;
	outFile.write( (char*)&taWrite, sizeof(Transaction) );
	outFile.close();//close the file, we're done writing.
	cout<<"Data saved!"<<endl;
	
	//Read back all the data we've saved (useful since you're testing out ios::app with this program)
	cout<<"Reading back in saved data...\n"<<endl;
	ifstream inFile("tranx1.dat", ios::binary);
	Transaction taRead; //a temporary object we'll use for reading from the file
	//to read file we'll need to use a similar technique as we used to write it.
	int i = 0; //loop counter just used for labeling entries during output
	do{
		//Read in one record into our temporary struct
		inFile.read( (char*)&taRead, sizeof(Transaction) );
		//output this entry
		cout<<"\tEntry #"<< ++i <<":\n";
		taRead.printDetails(); //use our temporary struct to output it's own details
	
	}while ( inFile.peek()!=EOF );  //this continues as long as the next symbol in the file isn't the "end of file" marker

	//Once we get here, there's nothing left in tranx1.dat to read
	
	inFile.close(); //we can close this as soon as we're done copying from the file into our reading object
	
	return 0;
}