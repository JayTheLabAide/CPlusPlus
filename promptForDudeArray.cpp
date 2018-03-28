/*
	Example of using prompt functions to fill structs
	-------------------------------------------------
	Code by Jason Lillard, 2018
	-------------------------------------------------	
*/

#include <iostream>
#include <string>

using namespace std;

/*
	A fancy variable type to hold a name, phone number, and bank balance for each dude
*/
struct Dude {
	string name;
	string phoneNum;
	string bankBal;
};

/*
	Helper function to output a string and get a string from user
*/
string prompt(string output){
	string result;
	cout<<output;
	getline(cin, result);
	return result;
}


void fillDude( Dude & d){
	/*
		Fill a dude using 3 calls to prompt(), once for each value
		in a Dude struct.
		This first value has some simple error checking, namely it
		complains if your name has any numbers in it, or if your
		name was blank.
	*/
	bool validName = true;
	do{
		d.name = prompt("Enter dude's name: ");
		for(int i = 0; i < d.name.length() ; i++){
			if ( d.name[i] >= '0' && d.name[i] <= '9' ) {
				cout<<"YOUR NAME CAN'T HAVE NUMBERS!"<<endl;
				validName=false;
				d.name="";
			}
		}
		
	}while (d.name.length() == 0 );
	
	
	//simple prompt for phone number (no error checking)
	d.phoneNum = prompt("Enter dude's number: ");
	//simple prompt for bank balance (no error checking)
	d.bankBal = prompt("Enter dude's bank balance: ");
}

//Helper function to print each stat for a particular dude
void printDude( Dude d){
	cout<<"Dude's Name: "<<d.name<<endl;
	cout<<"Dude's number: "<<d.phoneNum<<endl;
	cout<<"Dude's balance: "<<d.bankBal<<endl;
}

int main(){
// Some other uses of prompt
//	string name = prompt("Hello, what is your name?:");
//	cout<<"Your name is "<<name<<endl;
//	cout<< prompt("What is your message?") <<endl;
//
//	string names[10];
//
//	for(int i = 0; i < 10; i++){
//		names[i] = prompt("Enter name: ");
//	}
//	for(int i = 0; i < 10; i++){
//		cout<< names[i] <<endl;
//	}


	//Real demo:
	//size of dude array
	const unsigned DUDESZ = 3;
	//array of Dude objects of size DUDESZ, named "dudes"
	Dude dudes[DUDESZ];

	//call fillDude once for each dude, on each dude
	for(int i = 0; i < DUDESZ ;i++){
		cout<<"Dude #"<<i+1<<endl;
		fillDude( dudes[i] );
	}
	
	//After all dudes are filled, spit 'em back out
	for (int i = 0; i < DUDESZ; i++){
		cout<<"Dude #"<<i+1<<endl;
		printDude( dudes[i] );
	}

	return 0;
}
