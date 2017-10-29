/*
	Old tricks for using simple numbers 0-51 to card suits and faces.
	The values of these cards depend on the game being played, so no functions
	calculating those are here (e.g. for determining if one card number beats
	another in WAR, or if particular card is being treated as "wild," etc.)
	===========================
	Code by Jason Lillard, 2017
	===========================
*/
#include <iostream>
#include <cstdlib> //for srand and rand
#include <ctime> //for time(0)
using namespace std;

//constants for arrays
const unsigned SUIT_SZ = 4, FACE_SZ = 13, DECK_SZ = SUIT_SZ*FACE_SZ;

//C-Strings for Card Suits
const char * SUIT[ SUIT_SZ ] = {"Hearts", "Diamonds", "Clubs", "Spades"};

//C-Strings for Card Faces
const char * FACE[ FACE_SZ ] = {"Ace", "2","3","4","5","6","7","8","9","10",
		"Jack", "Queen", "King"};


//Functions
//Takes in a number 0-52, returns suit of card
const char * cardNumToSuit(short card ){
	return SUIT[ card / FACE_SZ ]; // 
}


//Takes in a number 0-52, returns face of card
const char * cardNumToFace(short card ){
	return FACE[ card % FACE_SZ ];
}

void shuffleDeck( short deck[] ){
	//for each card
	for( short i = 0; i < DECK_SZ ; i++ ){
		//randomly decide destination to put current card
		short destination = rand()%DECK_SZ;
		//then swap current card with one at destination
		short temp = deck[destination];
		deck[destination] = deck[i];
		deck[i] = temp;
	}
}

int main(){
	//print suits and faces just from numbers 0-51 in a loop
	cout<<"Card List:"<<endl;
	for(short i = 0; i < DECK_SZ ; i++){
		cout <<"Card Number "<<i<<" is the "
				<<cardNumToFace( i ) //use loop counter i to get face
				<<" of "
				<<cardNumToSuit( i ) //use looper counter i to get suit
				<<"."<<endl;
	}
	cout<<endl;
	
	
	//now let's create a deck and shuffle it
	short deck[DECK_SZ];
	
	//fill deck with numbers 0-51
	for (int i = 0; i < DECK_SZ ; i++) deck[i] = i;
	
	
	//seed random number generator with unix time + clock cycle timer
	srand( time(0) + clock() );
	
	//shuffle deck with our random swap function
	shuffleDeck( deck );
	
	//output shuffled deck
	cout<<"\n\nShuffled Deck:"<<endl;
		for(short i = 0; i < DECK_SZ ; i++){
		cout <<"Deck Index "<<i<<" is the "
				<<cardNumToFace( deck[i] ) //get face of card in shuffled array
				<<" of "
				<<cardNumToSuit( deck[i] ) //get suit of card in shuffled  array
				<<"."<<endl;
	}
	cout<<endl;
	
	//return from main
	return 0;
}
