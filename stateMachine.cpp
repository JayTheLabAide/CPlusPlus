/*
	Simple State Machine 
	inspired by Robert Nystrom's "Game Programming Patterns"
	---------------------------------------------------------
	code by Jason Lillard 2018
	---------------------------------------------------------
	This state machine resembles a simple platformer, only it's just text.
	The jump is like Ghosts&Goblins where one button press starts a jump
	that always goes the same length of time.
	There is a talk/interact state that is toggled with A if the
	actor is standing still. Talking doesn't really do anything though.
	This "game" assumes that the player will never fall into a hole.
	Basically, this game is horrible, but the essence of the state machine
	being implemented to control a character in real time is
	demonstrated here, and you can make it not horrible with some
	understanding and a bit of effort.
*/

//This demo will use windows.h for real time keyboard input.
//If you are using a unix-based machine try the "curses library"
#include <windows.h> //for GetKeyState(int)
#include <cstdio> //for system("cls") to clear the console screen
#include <ctime> //for clock to keep track of passing time
#include <iostream>//for regular cout (but not cin)
using namespace std;

//THE WINDOWS-SPECIFIC FUNCTION, TO TELL IF A KEY IS BEING PRESSED
bool isKeyDown( short letter ){ 
	//We use short for letter so we can use VK codes like VK_LEFT or VK_SPACE
	//GetKeyState is in windows.h
	//you will have to use a different method on unix-based machines.
	return (0x8000 & GetKeyState(letter)); 
}


//A "forward declaration" of State so it exists when we make our Actor,
//which has a State, which takes a reference to an Actor... yeah, so this:
class State; 

//Now our hella-generic game object class which only has a state
//In a real game Actor would have x, y coordinates, money, health points, etc.
struct Actor {
	State * state;
};

/*
Here are the numbers representing the various inputs. Powers of 2 are used so
that we can do logical operations like | to store multiple flags in one int.
If this seems strange, just remember numbers in binary are a bunch of ones and
zeros, and those can also be used as true or false. So every time input comes
in, it will look (in binary) like 0 0 1 0 , which means only our "B Button" was
pressed. If the user is pressing right and jump, our input nibble will look like
this: 1 0 1 0. In this way we can easily store and test for single or multiple
keypresses as we see fit. By the way, this form of storing input goes at least
as far back to the 8 buttons of the NES controller: 4 directions, A, B, select,
and start, which could have all flags stored within one byte.

*/
enum InButton { IN_NO_BUTTON=0,
		IN_A_BUTTON = 1,
		IN_B_BUTTON = 2, 
		IN_L_DIR = 4,
		IN_R_DIR = 8
};

/*
State Diagram / Plan:

	A standing character can begin running, jumping, or talking
		-run with direction buttons
		-talk with A
		-jump with B
		
	A running character can't talk, but can stand or jump
		-jump with B
		-release direction to stand
		
	A talking character can only cancel talking by pressing A
		-stand with A
		
	A jumping character stays jumping for 5 frames
		-run when frame count limit is reached
*/

//Our abstract base class for State objects. Actor will use a State pointer
//to store the addresses of all the various State child class instances.
class State{
	private:
		unsigned frameCount; //for animations or limiting duration of a state
	public:
		
		State(){
			frameCount=0;
		}
		
		//A getter for our frame count, and two setters based on our needs,
		// one to increment the frame count, and one to reset back to 0
		// (which we probably don't really need because the state just dies)
		unsigned getFrameCount(){ return frameCount;}
		void incFrameCount(){ ++frameCount;}
		void resetFrameCount(){ frameCount=0;}
		
		//update frame count and any other time-related events
		virtual void update( Actor& actor ) = 0;
		
		//process input to handle requests to change state or activate
		//some feature of this specific state
		virtual void handleInput( Actor& actor, unsigned short input ) = 0;
		
		//basically a toString function so we can see which state we're in
		virtual const char * name() = 0;
};

//I thought I might need these enums, but I didn't. You might use them later.
/*
enum STATE{
	ST_STANDING, ST_RUNNING, ST_JUMPING, ST_TALKING
};
*/

//STANDING STATE
class StateStanding : public State {
	//how many frames after entering Standing state before Actor can talk
	static const unsigned TALK_DELAY = 3;
	//private constructor (only usable by the factory function makeState() )
	StateStanding(){}
	
	public:
	//Prototypes of our pure virtual functions we inherited which must be made.
	virtual void update(Actor & actor);
	virtual void handleInput(Actor & actor, unsigned short input);
	virtual const char * name(){return "Standing";}
	//"Factory" to construct instances using dynamic memory.
	//We don't inherit these because they all have different return types.
	//Though it might make sense to inherit a State* makeState function.
	static StateStanding* makeState();
	
};

//States are made with a "factory model" where we use a private constructor and
//a static function which controls construction to ensure States will be
//dynamically allocated, since the states "delete this" to kill themselves
//once they remove themselves from an Actor.
StateStanding* StateStanding::makeState(){
	return new StateStanding();
}

//RUNNING STATE
class StateRunning : public State {

	StateRunning(){}
	
	public:
	void update(Actor & actor);
	void handleInput(Actor & actor, unsigned short input);
	virtual const char * name(){return "Running";}
	static StateRunning* makeState();	
};

StateRunning* StateRunning::makeState(){
	return new StateRunning();
}

//JUMPING STATE
class StateJumping : public State {
	static const unsigned short FRAME_LIMIT = 12;
	StateJumping(){}
	public:
	void update(Actor & actor);
	void handleInput(Actor & actor, unsigned short input);
	virtual const char * name(){return "Jumping";}
	static StateJumping* makeState();
};

StateJumping* StateJumping::makeState(){
	return new StateJumping();
}

//TALKING STATE
class StateTalking : public State {
	static const unsigned short FRAME_DELAY = 3;
	StateTalking(){}
	public:
	void update(Actor & actor);
	void handleInput(Actor & actor, unsigned short input);
	virtual const char * name(){ return "Talking";}
	static StateTalking* makeState();
};

StateTalking* StateTalking::makeState(){
	return new StateTalking();
}


//MAIN
int main(){
	//Our movie reference, I mean character.
	Actor Gary;
	//Start off Gary with some state or the thing crashes. Trust me.
	Gary.state = StateStanding::makeState();
	
	//Game loop variables: exit flag and time variables
	bool quit = false;
	time_t lastDraw = clock(); //to keep track of when the last refresh happened
	time_t redrawTime = CLOCKS_PER_SEC/10; //the number on the right is the fps.
	//In my experience, the console can push 30fps, but for text 10fps is fine.
	
	//THE GAME LOOP
	do{
		//If enough time has passed, do the update and redraw stuff
		if ( clock()-lastDraw >= redrawTime){
			
			//Keep track of all buttons held down using inFlags,
			// our enums for inputs, and the or-equals operator |=
			unsigned short inFlags = IN_NO_BUTTON;
			if ( isKeyDown('Z') ) inFlags |= IN_A_BUTTON;
			if ( isKeyDown('X') ) inFlags |= IN_B_BUTTON;
			if ( isKeyDown( VK_LEFT ) ) inFlags |= IN_L_DIR;
			if ( isKeyDown( VK_RIGHT ) ) inFlags |= IN_R_DIR;
			if ( isKeyDown( VK_ESCAPE) ) quit = true;
			
			//If user didn't press escape
			if(!quit){
				//Use Gary's state to process the user input... for Gary
				Gary.state->handleInput( Gary, inFlags );
				
				//Update current state (mostly frame counts)
				Gary.state->update(Gary);
				
				/*
					We could have also made a function within Actor which
					passed "this" to the input and update functions so the
					syntax here would look more like:
					Gary.handleInput(inFlags);
					Gary.update();
					The State object needs access to the object that called it,
					though, so that it can change the Actor's variables, or even
					change its State pointer. For that reason, however we use
					Actor to call state functions, to change attributes about
					the actor itself we need to pass in that Actor by reference.
				*/
				
				//Draw current state to screen
				system("cls");//clear screen
				cout<<"Gary's No-Good Stupid Adventure To Nowhere\n\n"
					"Press Z, X, or Left or Right Arrow Keys"
					" to change state.\n"
					"Gary is "<< Gary.state->name();
				
				/*
					Dirty hack to output direction because its not saved in the
					State or Actor classes as it probably should be:
				*/
				
				if (inFlags & IN_L_DIR) cout<<" Left";
				else if (inFlags & IN_R_DIR) cout<<" Right";
				
				cout<<endl;
				cout<<"\n\nPress Escape to Quit"<<endl;
				
				//update our timer of when we last refreshed the screen
				lastDraw=clock();
			}
	
		}
	//end of game loop which goes until player presses Escape key
	}while(!quit);
	
	cout<<"\n\nGoodbye"<<endl;
	
	return 0;
}
// END MAIN


//FUNCTION DEFINITIONS (had to be down here because the classes all refer
//to each other, which means they all need to be declared & prototyped etc.
//ahead of time so the definitions down here can see all the different 
//State child classes)

void StateStanding::update(Actor & actor){
	
	incFrameCount();
}
void StateStanding::handleInput(Actor & actor, unsigned short input){
	
	/*
		Since we're not worried about multiple buttons being
		pressed at once, we can use a simple switch block here
	*/
	bool stateChanged = false;
	switch(input){
		case IN_A_BUTTON:
			//actor.state = new StateTalking();
			if ( getFrameCount() > TALK_DELAY){
				actor.state = StateTalking::makeState();
				stateChanged=true;
			}
			break;
		case IN_B_BUTTON:
			//actor.state= new StateJumping();
			actor.state = StateJumping::makeState();
			stateChanged=true;
			break;
		case IN_L_DIR:
		case IN_R_DIR:
		// input will not equal either case if L and R are pressed together
			//actor.state = new StateRunning();
			actor.state = StateRunning::makeState();
			stateChanged=true;
			break;
		default: break;
	}
	if (stateChanged) delete this;
}
	
void StateRunning::update(Actor & actor){
	incFrameCount();
}
void StateRunning::handleInput(Actor & actor, unsigned short input){
	
	bool stateChanged = false;
	
	if ( input & IN_B_BUTTON ){
		//actor.state = new StateJumping();
		actor.state = StateJumping::makeState();
		stateChanged = true;
	}
	else if ( (input & IN_L_DIR) ^ (input & IN_R_DIR) ){
		//if only one direction is being pressed, keep running
		stateChanged = false;
	}
	else{
		//stand
		//actor.state = new StateStanding();			
		actor.state = StateStanding::makeState();			
		stateChanged = true;
	}
	
	if (stateChanged) delete this;
}

void StateJumping::update(Actor & actor){

	incFrameCount();
	
	if ( getFrameCount() > FRAME_LIMIT){
		//actor.state = new StateRunning();
		actor.state = StateRunning::makeState();
		delete this;
	}	
}
void StateJumping::handleInput(Actor & actor, unsigned short input){
	//dgaf about your input
	//you are committed to this jump
}

void StateTalking::update(Actor & actor){	
	incFrameCount();
}

void StateTalking::handleInput(Actor & actor, unsigned short input){
	
	if ( getFrameCount() > FRAME_DELAY && input == IN_A_BUTTON){
		//actor.state = new StateStanding();
		actor.state = StateStanding::makeState();
		delete this;
	}
}
