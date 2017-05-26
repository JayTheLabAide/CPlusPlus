/*
  Intro/Tutorial/Demo:
  Simple Structs and Classes
===========================
Code by Jason Lillard, 2017
===========================
*/
#include <cstdio>
using namespace std;

//this creates a simple "object" called simpleStruct
struct simpleStruct{
  int data; //members of a struct are "public" by default, which means
    //no functions are needed to access the data inside the struct
}; // <-- note that struct and class definitions end in a semicolon
    //after the closing curly brace

//this creates a simple object that only has a function as a member
struct simpleLibrary{
  //this function is public by default
  void print(){ printf("Hello from a Simple Library instance!\n"); }
  //if you are making even a simple library, make as many functions "static" as possible
  //"static" members only have one copy shared across all instances of the class, and if public 
  //then they can be accessed without even making an instance of the struct or class 
  static void printStatic(){ printf( "Hello from the Simple Library's Static Function!\n");}
}; //don't forget that semicolon!

class encapsulatedData{ //classes are nearly the same as structs, but members are "private" by default
  private: //only accessible from outside through member functions
    int privateData;
  public: //accessible anywhere an instance of the object is
    void setData(int data){ privateData = data;} //function to "mutate" object's data
    int getData(){ return privateData; } //function to "access" object's data
}; //classes need semicolons too

int main(){
  //create two "instances" of simpleStruct 
  simpleStruct mySimpleStruct_A, mySimpleStruct_B;
  //we can "mutate" and "access" a different variable named "data" in each struct.
  mySimpleStruct_A.data = 5; //note the way we access data, with the name of the instance, a dot, then the variable name
  mySimpleStruct_B.data = -7; //instance name . variable name. (Don't use the class name to access non-"static" variables)
  printf("\n\nData in struct A: %d\nData in struct B: %d\n", mySimpleStruct_A.data, mySimpleStruct_B.data);
  //we can also increment, decrement, etc. variables in a struct or class. 
  mySimpleStruct_A.data++;
  mySimpleStruct_B.data--;
  printf("Incremented data in struct A: %d\nDecremented data in struct B: %d\n", mySimpleStruct_A.data, mySimpleStruct_B.data);

  //we can also initialize data within our struct without using a special "constructor" function call
  //this "list initializion" syntax is the same for initializing an array of data
  simpleStruct ss3 = {42};
  printf("List-Initialized data in struct \"ss3\": %d\n", ss3.data );
  
  //using the simpleLibrary:
  //run the static print function saved in our library class
  printf("Calling our library structure's static function with \"%s\":\n", "simpleLibrary::printStatic()");
  simpleLibrary::printStatic(); //note the :: needed to acesss a static member (function or variable)
  //make an instance of the library (needed for non-static member functions)
  simpleLibrary libraryInstance1, libraryInstance2;
  printf("Calling Library Instance 1's print function:\n");
  libraryInstance1.print(); //run the print function saved in our library object
  printf("Calling Library Instance 2's print function:\n");
  libraryInstance2.print();
  printf(
         "\nAs you can probably tell, function collections are easier to use when\n"
          "the functions are all declared \"static\", as this allows us to use\n"
        "those functions without creating any instances of the library class.\n\n"
        );
  
  printf("Testing our encapsulatedData class:\nSetting data using \"setData(int)\":\n");
  encapsulatedData myData1, myData2;
  //setting our object's data:
  myData1.setData(64);
  myData2.setData(128);
  printf("Accessing our encapsulated data with \"getData()\"\n"
         "myData1: %d\nmyData2: %d\n", myData1.getData(), myData2.getData() );
  
  printf("Setting myData2 using the result from myData1's getData function:\n");
  myData2.setData( myData1.getData() );
  printf("myData1: %d\nmyData2: %d\n", myData1.getData(), myData2.getData() );
  printf("Final Notes: Code that attempts to access private members in our encapsulatedData class\n"
         "without using the \"getter\" function will not compile. Also, if we wanted to prevent users\n"
         "from setting our data to zero or a negative number, then we could test incoming data within\n"
        "our \"setter\" function. Public data, as in our simpleStruct objects, could be set to anything,\n"
         "which can result in convenient coding, but can also result in data being set to invalid values\n"
        "(which might lead the program to crash or behave unpredictably).\n\n");
  
  return 0;
}
