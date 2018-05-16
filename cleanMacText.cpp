#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
	
	
	string fname;
	string fOutName = fname+"_pc";
	cout<<"File Name:";
	getline(cin, fname);
	
	ifstream inFile(fname.c_str() );
	
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
