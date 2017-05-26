/*
to_string with format specifier
(wrapper function for sprintf)
-- concept Paul Conrad
===========================
Code by Jason Lillard, 2017
===========================
*/
#include <cstdio> //for sprintf
#include <string> //for strings
#include <iostream> //for outputting string objects
using namespace std;

//this also works if your format specifier is in a string
//string to_string(float f, string fmtspc ){
//	char str[20]{};
//	sprintf( str, fmtspc.c_str(), f );
//	return string(str);
//}

string to_string(float f, const char* fmtspc ){
	char str[20]{};
	sprintf( str, fmtspc, f );
	return string(str);
}

int main(){
	float pi = 3.14159;
	string s_pi = to_string(pi, "%.4f");
	string s_pi2 = to_string(pi, "%.3f");
	string s_pi3 = to_string(pi, "%.2f");
	string s_pi4 = to_string(pi, "%.1f");
	cout << s_pi <<endl;
	cout << s_pi2 <<endl;
	cout << s_pi3 <<endl;
	cout << s_pi4 <<endl;
}
