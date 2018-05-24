/*
	A function to simplify the creation of menus
*/
#include <iostream>
#include <string> //used in menu func for prompts
#include <iomanip> //not needed for menu func
using namespace std;
////////////////////////////////////////////////////////////////////////////////
//BEGIN MAKEANDRUNMENU.H


/*
	Now we'll make a template function which takes in two arguments
	as template parameters: the data type of the function pointer,
	and the data type of the parameter.
	
	All of the functions in this menu will be acting on a single piece of data,
	which is passed into makeMenu by reference, then passed to each other
	function by reference. This way different menu options can all display or
	alter the same piece of data.
	
*/

template <class FT, class DT>
void makeAndRunMenu( FT funcPtrArr[], DT& data, 
		string funcNames[], unsigned short options){
			
	short choice;
	bool quit = false;
	do{
		//output all numbered options
		for(int i = 0; i < options; i++) cout << i+1<<": "<<funcNames[i]<<endl;
		cout<<"\nOr Q to quit: ";
		
		//first check if q or Q was input
		if (cin.peek()=='q'||cin.peek()=='Q'){
			quit = true; //jump out of menu
		}
		else{ //if not quit
				
			//if q or Q wasn't entered, read in number as a menu choice.
			cin>>choice;
			cin.ignore();
			
			if(!cin.good()){ //if characters, were input
				cin.clear(); //clear "bad" flag
				cin.ignore(1028, '\n'); //ignore rest of input
			}else if (choice > 0 && choice <= options){
				//adjust choice from human counting to computer counting
				--choice;
				//run the function held in the array, pass in the data
				funcPtrArr[choice]( data );
				
			}
			else{
				//they screwed up somehow (probably num too big)
				cout<<"\nERROR: Invalid Selection"<<endl;
			}
		} //end if not quit
	
	}while(!quit);
	return;
}
//END MAKEANDRUNMENU.H
////////////////////////////////////////////////////////////////////////////////


/*
	USAGE
*/

/*
	Here's the first part of our usage of our function, where we make typing
	everything out a little easier for ourself by declaring a type of function
	pointer called "funcType" which will be able to hold the
	addresses of void functions which take a float by reference.
*/
typedef    void (*funcType)(float & data);

/*
	Now here are a bunch of functions we can use in our menu
*/

//Shows a float with some formatting.
void showFloat(float & f){
	cout<<setprecision(2)<<fixed<<showpoint;
	cout<<"Current Float: "<<setw(20)<<f<<endl;
}
//Sets the float passed in
void setFloat(float & f){
	bool valid = false;
	float temp;
	do{
		cout<<"Enter a new value for float: ";
		cin>>temp;
		if(!cin.good()){
				cin.clear();
				cin.ignore(1028, '\n');
		} else {
			valid = true;
		}
	}while(!valid);
	//temp is valid, so save it to f
	f = temp;
}
//Sets the float passed in back to zero.
void resetFloat(float & f){
	f=0;
	cout<<"Float has now been reset."<<endl;
}
/*
	Here's our main, where we make our array of strings for menu options,
	our array of functions for menu options,
	our data which we'll give by reference to each menu function,
	and finally our call to makeAndRunMenu with all relevant data
*/
int main(){
	unsigned short CHOICES = 3;
	//the names which will be shown in the menu
	string funcNames[CHOICES] ={"Show Float", "Set Float", "Reset Float"};
	//here we make an array of our function pointers using the type we
	//made with typeDef, and we give it several function names.
	funcType funcs[CHOICES] = {showFloat, setFloat, resetFloat};
	//here's the data which will be shared across all funcs in the menu func.
	float data;
	//now we pass in our func pointer data type, our data data type,
	//the array of functions, the data, the array of names, and number
	//of menu items.
	makeAndRunMenu<funcType, float>( funcs, data, funcNames, CHOICES);
	//One more output to show we made it out of the menu function.
	cout<<"Goodbye."<<endl;
	return 0;
}
