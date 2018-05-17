#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

int main(){
	
	
	string fname;
	cout<<"This program goes through a .cpp or .txt file and makes a copy\n"
		"with all invisible characters removed except for spaces and newlines."
		<<endl;
	cout<<"Enter file to convert:";
	getline(cin, fname);
	
	ifstream inFile(fname.c_str() );
	
	string fOutName = "_pc_"+fname;
	ofstream outFile(fOutName.c_str() );
	
	
	char c;
	while( inFile ){
		c = inFile.get();
		if ( isprint(c) || isspace(c) || c=='\r'){
			outFile<<c;
		}
	}
	cout<<"Cleaned-up copy has been made!\n\nCopy name: "<<fOutName<<endl;
	return 0;
}
