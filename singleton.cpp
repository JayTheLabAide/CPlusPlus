/*
	Have you ever wondered, "How do I make sure that only ONE instance
	of this class is ever made (since multiple instances will break stuff) ?
	
	Well, the solution is: The Singleton Class
	
	It's not really a special type of thing that needs a new header file
	or special library or anything, you just have to make it in a certain way
	and then people will say, "Ah, yes. I see you have a Singleton class here."
	
	===========================
	Code by Jason Lillard, 2017
	===========================
*/

#include <iostream>

using namespace std;



class SingletonThing{

	private:

	string myData;
		
	// Make constructors private!! (our getThing func uses it)
	SingletonThing(){
		myData = "Now I have a secret.";
	}
	//copy constructor also private (should never be invoked)
	SingletonThing(const SingletonThing &rhs){}
		
	public:
	//Destructor is OK to make public.	
	~SingletonThing(){} //Ours does nothing

	//Make our public "factory" which will only ever return
	//the same reference to the only SingletonThing made
	static SingletonThing & getThing(); //defined below, outside of class
	
	
	//A normal member function to do stuff
	void doThing(){//this function can access member data like our myData string
		cout<<"SingletonThing is doing its thing."<<endl;
		cout<<"Its secret is: "<< myData <<endl;
	}

};

//Singleton's getThing function, sometimes called "getInstance"
SingletonThing & SingletonThing::getThing()
{
	static SingletonThing thing; //only singleton thing ever made
	return thing; //return reference to the thing we made
}
	
	
int main(){

	//Since getThing returns a reference to our class, make a reference
	//type in main to recieve what comes back from the function
	SingletonThing & singleRef = SingletonThing::getThing();
	
	//Now use our reference to the only SingletonThing in existence
	//to call member function "doThing" 
	singleRef.doThing();

	return 0;
}
