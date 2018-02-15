/*
	Blues Hero
	
	Give beats per minute and key,
	program tells you proper chords for a blues progression
	and prints them out in proper tempo.
	------------------------------------
	Code by Jason Lillard, 2018
*/
#include <iostream> //for input/output
#include <string> //for string objects
#include <ctime> //for clock()

using namespace std;

const short CHORDS = 12;
const string circle5ths[CHORDS]={"C","F","Bb","Eb","Ab","Db","F#","B","E","A","D","G"};

void printChordMenu();
string get4th(string chord);
string get5th(string chord);

int main(){

	cout<<"\t\tWelcome to Blues Hero!\n";
	
	short bpm; //variable to hold beats per minute
	cout<<"Enter tempo (beats per minute, e.g. 120):";
	cin>>bpm; //get input
	cin.ignore(1000,'\n'); //ignore space left over after reading in a number
		
	
	short keyIndex;
	cout<<"Pick a key, 1-12"<<endl;;
	
	printChordMenu(); //print menu displaying all the keys
	
	cin>>keyIndex; //get key from user
	keyIndex-=1; //decrement by 1
	string key= circle5ths[keyIndex];
	string root =key;
	root+="7";
	string fourth = get4th( circle5ths[keyIndex] );
	fourth+="7";
	string fifth = get5th( circle5ths[keyIndex] );
	fifth+="7";
	cout<<"For a blues in "<<key<<", the root chord is "<<root<<endl;
	cout<<"The 4th is "<< fourth <<endl;
	cout<<"The 5th is "<< fifth <<endl;
	
	cin.ignore(1000,'\n');
	cout<<"Press enter to start in-time display, press Ctrl+Z to stop"<<endl;
	while(cin.get()!='\n'); //wait for enter
	
	
	unsigned long last = clock(); //start time
	float bps; //variable to hold beats per second
	bps = 60.0/bpm;
	//cout<<"BPS: "<<bps<<endl;
	long clocksBetweenBeats = CLOCKS_PER_SEC*bps;
	short measure = 1;
	cout<<"Clocks between beats: "<<clocksBetweenBeats<<endl;
	
	while(true){ //loop forever (until Ctrl+Z closes program)
		//R 4 R R
		//4 4 R R
		//5 4 R 5
		
		if ( (clock()-last)>=clocksBetweenBeats*4 ){//every 4 beats show chord
			last = clock();
			switch(measure){
				//4th
				case 2: case 5: case 6: case 10:
					cout<<fourth<<'\t';
					cout.flush();
				break;
				
				//5th
				case 9: case 12:
					cout<<fifth<<'\t';
					cout.flush();
				break;
				
				//root
				default:
					cout<<root<<'\t';
					cout.flush();
				break;
			}
			//increment measure
			++measure;
			if (measure>12){
				cout<<endl;
				measure=1; //reset if 12 bars have passed
			}
			if (measure == 1 || measure == 5 || measure == 9) cout<<endl;
			
		}
	}
	
}

string get4th(string key){
	string chord="Invalid Key";
	for(int i = 0; i < CHORDS; i++){
		if (key==circle5ths[i]){
			int index4th = (i+1)%CHORDS;
			return circle5ths[index4th];
		}
	}
	return chord;
}


string get5th(string key){
	string chord="Invalid Key";
	for(int i = 0; i < CHORDS; i++){
		if (key==circle5ths[i]){
			int index5th = (i-1);
			if (index5th<0)index5th=CHORDS+index5th;
			return circle5ths[index5th];
		}
	}
	return chord;
}

void printChordMenu(){
	for(int i = 0; i < CHORDS; i++){
		cout<<i+1<<": "<<circle5ths[i]<<endl;
	}
}
