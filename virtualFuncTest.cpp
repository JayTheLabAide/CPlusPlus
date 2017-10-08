/*
	Virtual Functions (With Polymorphic Pointers) Example
	-------------------------------------------------------------------
	Very short example of the difference between virtual functions and
	standard functions when dealing with inheritance and pointers to
	parent classes. Basically, if you want a parent pointer pointing to
	a child object to call the child class's version of the function,
	then you need to declare the function virtual, otherwise that
	function call through the parent pointer will always call the
	parent class's version of the function.
	-------------------------------------------------------------------
	Code by Jason Lillard, 2017
*/
#include <iostream>

using namespace std;
// Base Class
class parent{
	int num =5;
	
public:
	int getNum(){
		return num;
	}
	
	virtual int numAgain(){ //declare function as virtual in parent class
		return num;
	}
	
};

//Inheriting Class
class child : public parent { // <-- here's where inheritance is set
	int myNum=10;
public:
	// "virtual functions get overloaded, others get overwritten"
	int getNum(){
		return myNum;
	}
	
	virtual int numAgain(){ //this "virtual" keyword is optional
		return myNum;
	}
	
};


int main(){
	//make a parent and child object
	parent myParent;
	child myChild;
	cout << "Function Redefinitions Accessed Through Objects Themselves:"<<endl;
	cout << "myParent.getNum(): "<< myParent.getNum() <<endl; //prints 5, from base class
	cout << "myChild.getNum(): "<< myChild.getNum() <<endl; //prints 10, from child class
	
	cout <<"Functions Accessed Through a Polymorphic Pointer:"<<endl;
	parent* pPtr = &myParent;
	cout << "Parent pointer to parent class: (*ptr).getNum(): "<< (*pPtr).getNum() <<endl; //prints 5, from base class
	pPtr = &myChild;
	cout << "Parent pointer to child class: (*ptr).getNum(): " <<(*pPtr).getNum() <<endl; //prints 5, ALSO FROM BASE CLASS
	
	cout << "Virtual Functions Accessed Through a Polymorphic Pointer:"<<endl;
	pPtr = &myParent;
	cout << "Parent pointer to parent class, virtual function: (*ptr).numAgain(): "<<(*pPtr).numAgain() <<endl; //prints 5, from base class
	pPtr = &myChild;
	cout << "Parent pointer to child class, virtual function: (*ptr).numAgain(): "<<(*pPtr).numAgain() <<endl; //prints 10, OVERLOADED FUNCTION
	
	return 0;
}
