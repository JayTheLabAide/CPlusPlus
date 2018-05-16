#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
	
	
	string fname;
	cout<<"File Name:";
	getline(cin, fname);
	
	ifstream inFile(fname.c_str() );
	
	string fOutName = fname+"_pc";
	ofstream outFile(fOutName.c_str() );
	
	
	while( inFile ){
		char c;
		inFile>>c;
		if ( isprint(c) || isspace(c) ){
			outFile<<c;
		}
	}
	
	return 0;
}
