/*
	Random Integers, Floats, Letter or Digit Characters, and Strings
	===========================
	Code by Jason Lillard, 2017
	===========================
*/
#include <iostream> //for output
#include <cstdlib> //for srand & rand and RAND_MAX
#include <ctime> //for time(0)
#include <string> //for two examples using strings
using namespace std;

//INITIALIZE RANDOM NUMBER GENERATOR (ONLY CALL ONCE)
void initRand(){ srand(time(0) );} //seed random number generator with the current "unix" time

//RAND INT WITHIN RANGE
int randInt( int min, int max){
	return (min+(rand()%(max-min+1)));
}
//POLYHEDRAL DICE SIMULATOR
int randXSidedDie( int sides ){
	return (1+(rand()%sides));
}

//RAND CHARACTERS 
//(Keep in mind that char data type stores ascii codes,
// which are numbers that can be added to and subtracted from
char randLowerCase(){
	return (char)((rand()%26)+'a'); //0+'a' returns 'a', 25+'a' returns 'z'
}

char randUpperCase(){
	return (char)( (rand()%26)+'A'); //0+'A' returns 'A', 25+'A' returns 'Z'
}

char randDigitChar(){
	return char((rand()%10)+'0'); //0+'0' returns '0', 9+'0' returns '9'
}

//RANDOM CHAR FROM A STRING
char randVowel(){
	string vowels = "aeiou"; //string to be chosen from randomly
	char result = vowels[rand()%vowels.length()]; //result is a char from a random index
	if ( rand()%2==0 ) result += ('A'-'a');  // 50% chance of upper case
	//half the time add to 'result' char the difference between
	//upper and lower case chars (i.e. make result upper case).
	return result;
}

//RANDOM STRING
const string S_DAY[7]={"MON","TUE","WED","THR","FRI","SAT","SUN"};
string randomDay(){
	//rand()%7 returns [0,7), which is the index range of our DAYS array
	return S_DAY[rand()%7];
}


//RANDOM FLOATING POINT VALUES
float randFloat(){
	//return fraction [0,RAND_MAX]/RAND_MAX
	return rand()/(float)RAND_MAX; //returns [0.0, 1.0]
}

float randDouble(){
	//return fraction [0,RAND_MAX]/RAND_MAX
	return rand()/(double)RAND_MAX;	//returns [0.0, 1.0]
}

//Random Ranged Float
float randFloat(float min, float max){
	//return min+(rand()/(float)RAND_MAX)*(max-min+1);
	return min+randFloat()*(max-min);
// min = offset, max-min = range
// offset+[0.0,1.0]*range
// randFloat()*range essentially gives a random percentage of the range
// eg. random percent = 80%, range = 200:  0.8 * 200 = 160
// then add min, the offset, to adjust random number up or down into desired range
}	
	


int main(){
	
	//Initialize RNG
	initRand();
	
	cout<<"Running Test Loops...\n";
	//comment statements in or out to test different generators
	
//	for(int i = 2; i <= 20; i++) {
//		for(int j = 0; j < 5; j++) {
//			cout << "Range "<<i*10<<" to "<<i*100<<": "<< randInt(i*10, i*100)<<"\n";
//			cout << "Sides: "<<i<<" Result: "<<randXSidedDie(i)<<"\n";
//			
//		}
//	}
	
	for(int i = 1; i <= 10; i++){
		cout<<"Random Ranged Float "<<-100<<" to "<<1000<<": "<< randFloat(-100, 1000)<<"\n"; 
		cout<<"Random Day: "<<randomDay()<<"\n";
		cout<<"Random Vowel: "<<randVowel()<<"\n";
		cout<< "Lower case : "<<randLowerCase()<<"\n";
		cout<< "Upper case : "<<randUpperCase()<<"\n";
		cout<< "Digit char : "<<randDigitChar()<<"\n";
		cout<<"Random Float : "<<randFloat()<<"\n";
		cout<<"Random Double : "<<randDouble()<<"\n";
		cout<<"Random Ranged Float "<<i*10<<" to "<<i*100<<": "<< randFloat(i*10, i*100)<<"\n"; 
	}
	
	//cout.flush();
	cout<<endl; //use "\n" for endlines until very end, 
	//so endl or flush can output everything all at once (much faster than using endl everywhere)
}
