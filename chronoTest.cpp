/*
    Counting milliseconds with chrono,
    with ample use of the "auto" datatype because
    the chrono library is written by crazy people.
    ==============================================
   Code by Jason Lillard, 2017
    ==============================================
	
*/

#include <chrono> //in c++11 standard
#include <iostream> //for output
#include <iomanip> //to format fractions for output
using namespace std;

double passedTime(){ //returns fraction of a second which has passed
	using namespace chrono;

	static auto last = high_resolution_clock::now();
	auto elapsed =  high_resolution_clock::now() - last;
	last = high_resolution_clock::now();
	auto temp = duration_cast<duration<double>>(elapsed);
	return  temp.count();
}


int main(){
    cout<<fixed<<showpoint<<setprecision(7);
    
    cout<<"Fraction of second passed: "<<endl;
    cout<<"First call: "<< passedTime()  <<endl;
    cout<<"Second call: "<< passedTime()  <<endl;
    cout<<"Third call: "<< passedTime() <<endl;
    cout<<"Fourth call: "<< passedTime()  <<endl;
}
