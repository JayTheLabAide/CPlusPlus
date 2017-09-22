/*
	Simple turn-based game program skeleton/tutorial
	--------------------------------------
	Code by Jason Lillard, 2017
*/
#include <iostream> //for simple input/output
#include <fstream> //to record scores
using namespace std;

//Our player "object" to hold info about any given player
struct Player{
	string name; //player's name
	int score; //player's score
}; // <-- don't forget this semicolon at the end of a struct definition

//Function "prototype" for our function to handle anybody's turn
//This function is fully defined below our "main" function
//The * in the parentheses means that we pass a player "pointer" to this func.
void gameTurn( Player * current);

//function to save scores after game finishes
void saveScores(Player p1, Player p2, Player p3);

////////////////////////////START MAIN//////////////////////////////////////////
int main(){

	//Make two (or more) players
	Player p1;
	Player p2;
	Player p3;
	
	//Make pointer to current player, set it (point it) to player 1
	//The & symbol means "address of" the player object.
	Player * current = &p1; //pointers hold the addresses of existing objects
	
	cout<<"Welcome to the nothing game."<<endl; //title/intro
	//Get player names (and use . to get variables inside player objects)
	//like player.name or player.score
	//(This is slightly different with pointers, where we use -> instead of .)
	cout<<"Enter player one's name: ";
	cin>>p1.name;
	cout<<"Enter player two's name: ";
	cin>>p2.name;
	cout<<"Enter player three's name: ";
	cin>>p3.name;
	 
	//SET ALL PLAYER SCORES TO ZERO (if we don't, they start with garbage vals)
	p1.score = 0;
	p2.score = 0;
	p3.score = 0; 
	 
	//GAME LOOP START
	cout<<"Game beginning:"<<endl;
	bool quit = false;
	while (!quit){ //while quit is false (while user doesn't want to quit)
	
		//STEP 1
		//"current" player takes their turn, pass pointer to gameTurn function
		gameTurn( current ) ;
		
		//STEP 2
		//check win condition
		if ( current->score > 1000 ){ //if somebody has reached the win goal
			cout<< current->name <<" surpassed 1000 points! They win!"<<endl;
			//output victory message and break from loop
			break;
		}
		
		//STEP 3 (OPTIONAL)
		//offer player to quit (This could get annoying, you should re-work it)
		cin.ignore(100, '\n'); //clear any junk input waiting to be read in
		cout<<"Quit now?(Y/N): "; //show quit prompt
		char qInput; //make variable to hold input
		qInput = cin.get(); //get one character from user (could be '\n')
		if ( qInput == 'y' || qInput == 'Y' ) quit = true; //if yes, set q. flag
		
		//STEP 4
		//switch current player (rotate, P1 to P2 to P3 back to P1 )
		if (current == &p1) current = &p2; //if pointing @ player 1, point @ p2
		else if (current == &p2 ) current = &p3; //if pointing @ player 2, point @ p3
		else current = &p1; //else, pointing @ p3, point @ p1

	} //END GAME LOOP
	
	//SAVE SCORES
	saveScores( p1, p2, p3); //give function all 3 players (not just current)
	
	//GAME IS OVER, OUTPUT CLOSING MESSAGE
	cout<<"\n\n\t\tGAME OVER"<<endl;

	return 0;
}
////////////////////////////END MAIN////////////////////////////////////////////

//FUNCTION DEFINITIONS
void gameTurn( Player * current){
	
	//Since we are using a player pointer, if we want to access the player's
	//name or score, we have to use the "arrow operator", hyphen + greater than
	// examples: current->name or current->score
	
	cout << "It is "<< current->name <<"'s turn now."<<endl;
	cout << "Current Score: "<< current->score <<endl;
	cout<<"Enter a number to add to the score: ";
	int toAdd; //variable to hold input
	cin >> toAdd; //get user input (or your game will be very boring)
	
	//check if int was entered (game freaks out if not)
	if ( !cin.good() ) { //if not good
		cin.clear(); //clear the "bad" flag (which makes cin.good equal false)
		cin.ignore(100, '\n'); //clear the rest of the input waiting to be read
		toAdd = -1000; //punish player for not entering a valid integer
	}
	
	current->score += toAdd; // set score to "toAdd" more than its current val.
	// (if toAdd is negative, this will still work correctly. 
	// Adding a negative number is the same as subtracting)
}

void saveScores(Player p1, Player p2, Player p3){
	ofstream writer ("results.txt", ios::app); //open text in "append" mode
	//so we can write to the end of it (instead of overwriting previous results)
	// Run this game multiple times and see the results.txt file grow in size
	if (writer){ //if file was able to be opened/created
		//save the data to it
		writer<< p1.name << "\r\n" <<p1.score << "\r\n"; //"\r\n" is like endl,
		writer<< p2.name << "\r\n" <<p2.score << "\r\n"; //it works better with
		writer<< p3.name << "\r\n" <<p3.score << "\r\n"; //files than endl does.
		//close our output file
		writer.close();
	}
	cout<<"Scores saved!"<<endl;
}
