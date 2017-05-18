/*
	Rounding Floats (And Doubles) 
	Gives demonstration and function for rounding the actual stored value of a float or double.
	Warning: Some values cannot be rounded precisely (see demo & explanation below, also research
	limits of floating-point precision given different bit sizes).
	===========================
	Code by Jason Lillard, 2017
	===========================
*/
#include <iostream>
#include <iomanip> //for fixed, setprecision
#include <cmath> //for pow() in final 2 examples
using namespace std;

//FUNCTION PROTOTYPE (function only used in last example)
double roundDouble(double, int);


int main(){
	//the automatic way of rounding (used here to better demonstrate hard-coded rounding)
	cout<<fixed<<setprecision(12); //#include <iomanip>
	cout<<"\t____Rounding Demonstrations____\n";
	cout<<"Using float, int...\n";
	{
	float pi = 3.14159265359;
	cout<<"\nRounding pi to 2 decimal places...\n";
	// 1. value attempts to round up in the hundredth's place (by adding 0.005)
	float pi_plus = pi+0.005; 
	// 2. value is scaled up by 100 (to get two decimal digits left of the decimal point)
	// 3. value is cast to, and stored in, an int. This truncates all decimal digits remaining
	int pi_temp = (int)(100*pi_plus);
	// 4. value is promoted back to a float and divided by 100.0, restoring saved decimal digits to proper place
	float pi_rounded = pi_temp/100.0;
	cout<< setw(12)<<"Pi: "<<pi<<"\nPi Rounded: "<< pi_rounded <<"\n" 
		"As you can see, floating-point numbers can't always be precisely rounded.\n"
		"This is especially obvious with 32-bit floats,\n"
		"But we'll have better luck with 64-bit doubles (if you're allowed to use them)...\n"<<endl;
	}
	
	double pi = 3.14159265359;
	cout<<"Using double, long...\n\n";
	
	{
	cout<<"Rounding pi to 4 decimal places...\n";
	//some of these steps can be combined.
	long pi_temp = (long)(10000*(pi+0.00005));
	double pi_rounded = pi_temp/10000.0;
	cout<< setw(12)<<"Pi: "<<pi<<"\nPi Rounded: "<< pi_rounded <<"\n"<<endl;
	}
	
	
	{
	cout<<"Rounding pi to 8 (or any number of) decimal places..."<<endl;
	short roundPlace = 8;
	long scale = 1; for (int i=0;i<roundPlace;i++)scale*=10; //long scale = pow(10, roundPlace)
	cout<<"Round Place: 8\nScale number, 10^roundPlace: "<<scale<<endl;
	double add = 0.5/scale;
	cout<<"Add number, 0.5/scale: "<<add<<endl;
//	long pi_temp = (long)(scale*(pi+add));
//	double pi_rounded = (double)pi_temp/scale;
	cout<< "Final step using calculated \"scale\" and \"add\" values:\n"
	"double pi_rounded = ( (long)(scale*(pi+add))) / (double)scale";
	double pi_rounded = ( (long)(scale*(pi+add))) / (double)scale; //using no pi_temp var
	cout<<"\n"<<setw(12)<<"Pi: "<<pi<<"\nPi Rounded: "<< pi_rounded <<"\n"<<endl;
	}

	{
	cout<<"Rounding pi to 7 decimal places in one line...\n"
		"double pi_rounded = ( (long)(pow(10,7)*( pi + (0.5/pow(10,7) ))) ) / pow(10,7) "
		"\nNote: multiple calls to pow to calculate scale & add make this inefficient.\n"
		"Ideally, use temporary variables to limit number of function calls.\n"
		"Also note that since pow() returns a double, our \"scale\" portion\n"
		"now doesn't need to be cast to a double in the denominator.\n";
		
	double pi_rounded = ( (long)(pow(10,7)*(pi+(0.5/pow(10,7)) ) )) / pow(10,7);
	cout<< setw(12)<<"Pi: "<<pi<<"\nPi Rounded: "<< pi_rounded <<"\n"<<endl;
	}
	
	{
	cout<<"\nRounding pi to 5 decimal places using a function...\n";
	cout<<setw(12)<< "Pi: "<<pi<<"\nPi Rounded: "<< roundDouble(pi, 5) <<"\n"<<endl;
	}
}

double roundDouble(double num, int places){
	double scale = pow(10,places);
	//Alternatively, do exponentiation in a for loop (slower, but eliminates #include <cmath>):
	//double scale = 1; for (int i=0;i<places;i++)scale*=10;
	return (( (long)(scale*(num+(0.5/scale) )  )) / scale ) ;
}
