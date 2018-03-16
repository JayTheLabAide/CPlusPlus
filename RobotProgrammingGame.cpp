/*

    Robot Programming Game! (i.e. an input queue demo)  
-------------------------------------------------------------------------------
    Code by Jason Lillard, 2018.
    Based on the "Command" pattern in "Game Programming Patterns" by
    Robert Nystrom and the old game series "The Island of Doctor Brain,"
    which featured a much better version of this kind of minigame.

*/

#include <iostream>//for basic input/output
#include <ctime>//for time(0) and clock()
#include <cstdlib>//for srand, rand
#include <string>//for command names
using namespace std;

////////////////////////////////////////////////////////////////////////////////
/*
 * This is the base class for anything in our "game" that moves 
 * (which here is only the player, but could easily include mobile enemies)
 * Every GameActor has an x y coordinate with setters and getters
 */
class GameActor{
private:
	short x, y;
public:
	GameActor(){ x=y=0;}			~GameActor(){}
	short getX(){return x;} 		short getY(){return y;}
	void setX(short x){this->x=x;}	void setY(short y){this->y=y;}
};

////////////////////////////////////////////////////////////////////////////////
//A star of this show: The "Command" class, a function turned into an object
class Command { //an abstract base class representing a character action
private:
	//no private members are usually needed in abstract classes
public:
	Command(){} //default constructor (needed even in abstract classes)
	virtual ~Command(){} //virtual destructor, best for abstract classes
        //This is the function which does the action
	virtual void execute( GameActor * ga ) = 0; 
        //function to describe current action (for output purposes)
        virtual string getName()=0;
};

////////////////////////////////////////////////////////////////////////////////
/*
    Here we have our concrete implementations of our base Command class.
 * These each only govern movement, but we could add more for using items
 * or attacking enemies and so on.
 * 
 * Note that both of the pure virtual methods, execute and getName, are
 * implemented by necessity in each of the child classes of Command
 */
class MoveRight : public Command{
public:
	virtual void execute(GameActor * ga){
            if(!ga)return;
            ga->setX( ga->getX()+1);
	}
        virtual string getName(){
            return string("Right");
        }
};

class MoveLeft : public Command{
public:
	virtual void execute(GameActor * ga){
            if(!ga)return;
            ga->setX( ga->getX()-1);
	}
        virtual string getName(){
            return string("Left");
        }
};

class MoveDown : public Command{
public:
	virtual void execute(GameActor * ga){
            if(!ga)return;
            ga->setY( ga->getY()+1);
	}
        virtual string getName(){
            return string("Down");
        }
};

class MoveUp : public Command{
public:
	virtual void execute(GameActor * ga){
            if(!ga)return;
            ga->setY( ga->getY()-1);
	}
        virtual string getName(){
            return string("Up");
        }
};

////////////////////////////////////////////////////////////////////////////////

class CommandQueue{ //A basic linked-list queue for command objects
private:
	
	struct CNode{ //a private inner class, nodes for our linked list
		Command* cmd; //the node data, our command object
		CNode* next; //the link to the next node in the queue
	};

	//actual private members of the queue
	unsigned size; //current size of queue (number of nodes)
	CNode* head; //node which is next to be executed (or undone)
	CNode* tail; //where we add the new nodes (back of the line)


public:
	
	static const unsigned MAXSIZE = 16; //maximum size of queue

	//constructor
	CommandQueue(){
		size=0;
		head=tail=0;
	}
	
	//destructor
	~CommandQueue(){ clear(); }
	
        //returns current number of elements in queue
	unsigned getSize(){return size;}
	
        //displays names of each element, from head to tail
        void print(){
            CNode* reader = head;
            while(reader){
                cout<< reader->cmd->getName()<<'\n';
                reader=reader->next;
            }
            cout.flush();
        }
        
	//Peek: copy Command* from head, leave in queue
	Command* peek() const { return head->cmd;} 
	
	//Get: take Command* from head then delete from queue ("dequeue")
	Command* get(){
		if (!size) return 0;
                --size;
		//save our resulting command
		Command* result = head->cmd;
		//use temp variable to hold dequeued node
		CNode* deleter = head;
		//move the front of the line forward to next element
		head=head->next;
		//delete the dequeued node
		delete deleter;
		//give the command from the front of the queue
		return result;
	}
	
	//Put: add to tail ("enqueue")
	void put( Command * cmd ){
		//if queue is empty
		if (!size){
			//set head and tail to the new command node
			head = tail = new CNode();
			head->cmd=cmd;
			//increment size of queue
			++size;
		}
		//if queue is not full
		else if(size<MAXSIZE){
			//allocate new node
			CNode* toAdd = new CNode();
			//set node's data to the command being enqueued
			toAdd->cmd=cmd;
			//point back of queue to the added element
			tail->next = toAdd;
			//point the back of our queue to what we just added
			tail=tail->next;
			//increment the size of the queue
			++size;
		}
	}
	
	//Clear: delete all nodes from queue
	void clear(){
		//Make a node pointer to traverse the queue
		CNode* reader=head;
		//continue as long as reader points to something
		while( reader ){
			//keep track of the node to delete with this temp variable
			CNode* deleter = reader;
			//move our reader forward
			reader = reader->next;
			//delete the current node
			delete deleter;
		}
		//after everything has been deleted, clear the size & pointers
		size=0;
		head=tail=0;
	}
};

////////////////////////////////////////////////////////////////////////////////

void keepOnMap( GameActor * ga, unsigned mapHeight, unsigned mapWidth ){
	if (ga->getX()<0)ga->setX(0);
	else if (ga->getX()>=mapWidth)ga->setX(mapWidth-1);
	
	if (ga->getY()<0)ga->setY(0);
	else if (ga->getY()>=mapHeight)ga->setY(mapHeight-1);
}

////////////////////////////////////////////////////////////////////////////////

void fillMap( char ** matrix, unsigned height, unsigned width, char fill){
    for(int y = 0; y < height; y++){
        for( int x = 0; x < width; x++){
                *(*(matrix+y)+x)=fill;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void printMap( char ** matrix, unsigned height, unsigned width){
    for(int y = 0; y < height; y++){
        cout<<"\t\t";
        for (int x = 0; x < width; x++){
            cout<< *(*(matrix+y)+x);
        }
        cout<<'\n';
    }
    cout<<endl;
}

////////////////////////////////////////////////////////////////////////////////

Command * pickInput(){
    Command * result;
    //output prompt for choosing input
    //(this could be adapted into an event listening function)
    cout<<"Add another command to the queue or start your robot\n"
            "1. Up\n2. Down\n3. Left\n4. Right\n5. Start Robot"<<endl;
    char choice;
    cin>>choice;
    //return one of our command child classes within this parent class pointer
    switch(choice){
        case '1':
            result = new MoveUp();
            break;
        case '2':
            result = new MoveDown();
            break;
        case '3':
            result = new MoveLeft();
            break;
        case '4':
            result = new MoveRight();
            break;
        case '5':
        default:
            //start robot will happen when choice is '5' or invalid
            result=0;
            break;
    }
    return result;
}

////////////////////////////////////////////////////////////////////////////////

int main(){
    //player object
    GameActor player;

    //input command queue
    CommandQueue cq;

    //map info, allocation
    unsigned MAPSZ = 5;
    char ** map = new char *[MAPSZ];
    for(int i = 0; i < MAPSZ; i++) map[i]=new char[MAPSZ];

    //key and positions
    short keyX, keyY, doorX, doorY;
    //level
    short level = 1;
    //character tiles
    const char C_FLOOR = ',';
    const char C_PLAYER = '@';
    const char C_DOOR = 'E';
    const char C_KEY = 'k';
    const char C_MINE = '_';
    //seed rng
    time_t lastTime = clock();
    srand(time(0)*lastTime);

    bool quit = false;
    while(!quit){
        //reset level for new game
        level=1;
        //flag to determine if game win state has been reached
        bool levelWon, levelLost;
        //output into and menu key
        cout<<"Robo Programmer (Input Queue Demo)\n"
                "Input your robot's program, then run it!\n\n"
                "Your robot: "<<C_PLAYER<<"\tLandmine: "<<C_MINE
                <<"\tKey: "<<C_KEY<<"\tExit: "<<C_DOOR<<
                "\n(Note: If You Cannot See The Exit,"
                " Your Robot Is Standing On It)"<<endl;
        //main level loop
        while (level>0 && level <= 10){
            unsigned mines = 1+level/2;
            short * minesX = new short[mines];
            short * minesY = new short[mines];

            //level header
            cout<<"Level "<<level<<endl;
            levelWon=false;
            levelLost=false;
            //randomize key position
            keyX=rand()%MAPSZ;
            keyY=rand()%MAPSZ;
            //set door an increasing distance away from the key
            doorX = (keyX+2+rand()%level)%MAPSZ;
            doorY = (keyY+2+rand()%level)%MAPSZ;
            //set player in random place
            player.setX( rand()%MAPSZ );
            player.setY( rand()%MAPSZ );
            //clear player's key inventory
            bool hasKey=false;

            //place mines around other map items
            for(int i = 0; i < mines; i++){
                short x, y;
                bool onPlayer, onKey, onDoor;
                do{
                    x=rand()%MAPSZ;
                    y=rand()%MAPSZ;
                    onPlayer = (x==player.getX() && y==player.getY());
                    onKey = (x==keyX && y==keyY);
                    onDoor = (x==doorX && y==doorY);
                    //put somewhere new as long as on something else
                }while( onPlayer || onKey || onDoor );
                minesX[i]=x;
                minesY[i]=y;
            }

            //prepare and print map
            //fill with floor/background tile
            fillMap(map, MAPSZ, MAPSZ, C_FLOOR);
            //place key tile
            map[keyY][keyX]=C_KEY;
            //place door tile
            map[doorY][doorX]=C_DOOR;
            //place player tile
            map[player.getY()][player.getX()] = C_PLAYER;
            //draw mine tiles
            for(int i = 0; i < mines; i++){
                map[ minesY[i] ][ minesX[i] ] = C_MINE;
            }

            //output map header
            cout<<"Starting Map:"<<endl;
            //print map
            printMap(map, MAPSZ, MAPSZ);

            //fill queue with inputs
            Command * cmd;
            do{
                //call our function which shows menu for input, returns Command*
                cmd = pickInput();
                //if the command queue is full, stop adding instructions
                if (cq.getSize()>=CommandQueue::MAXSIZE){
                    cout<<"ERROR: Robot's Instruction RAM is Full!"<<endl;
                    break;
                } else if ( cmd ){//if a command was chosen...
                    //...enqueue it into our CommandQueue
                    cout<<"Adding Instruction: "<<cmd->getName()<<endl;
                    cq.put(cmd);

                }
                //print map and current instruction list
                cout<<"Starting Layout:"<<endl;
                printMap(map, MAPSZ, MAPSZ);
                cout<<"Current Program:"<<endl;
                cq.print();

            }while( cmd );
            
            //execute inputs, check if win state is achieved after each step

            //perform each action 
            cout<<"Activating Robot..."<<endl;
            //pause for dramatic effect
            time_t activationDelay = CLOCKS_PER_SEC*1.5;
            lastTime=clock();
            while(clock()-lastTime<activationDelay); //wait for delay length

            //check if game starts in winning state
            if (player.getX()==keyX&&player.getY()==keyY){
                cout<<"Your robot picked up the key!"<<endl;
                hasKey=true;
            }
            if(hasKey && player.getX()==doorX&&player.getY()==doorY){
                cout<<"Your robot unlocked the door to the next room!"<<endl;
                ++level;
                levelWon=true;

            }
            //if level wasn't won automatically, enter animation loop
            if(!levelWon){
                //get the next Command*
                cmd = cq.get();
                //set up our clock for the delays between execute calls
                lastTime=clock();
                //EXECUTION/ANIMATION LOOP
                time_t betweenFrames = CLOCKS_PER_SEC*0.60; 
                while(cmd){
                //if more time has passed than our min. time between frames
                    if (clock()-lastTime > betweenFrames ){
                        cout<<"Executing: "<<cmd->getName()<<endl;
                        //execute the next Command w/the player
                        cmd->execute(&player);
                        //call our function to push player back onto map
                        keepOnMap(&player, MAPSZ, MAPSZ);
                        //if player is standing on landmine...
                        short playerX=player.getX();
                        short playerY=player.getY();
                        for(int i = 0; i < mines && !levelLost ; i++){
                            if ( minesX[i]==playerX && minesY[i]==playerY){
                                //player dead
                                cout<<"Your robot exploded!"<<endl;
                                levelLost=true;
                                levelWon=false;
                                --level; //decrement an extra level for death
                                lastTime=clock();
                                //wait for delay length
                                while(clock()-lastTime<activationDelay*2); 
                                //break;
                                cmd=0;
            cout<<"It automatically retreats to attempt self-repairs."<<endl;
                            }
                        }
                        if (!levelLost){

                            //if player is standing on key...
                            if (player.getX()==keyX&&player.getY()==keyY){
                                cout<<"Your robot picked up the key!"<<endl;
                                hasKey=true;//set our key flag
                                //pause for dramatic effect
                                lastTime=clock();
                                //wait for delay length
                                while(clock()-lastTime<activationDelay); 
                            }
                            //if player has the key and is on the exit door...
                            if(hasKey && player.getX()==doorX && 
                                    player.getY()==doorY){
                                
                                cout<<"Your robot unlocked the door to the "
                                        "next room!"<<endl;
                                ++level;
                                levelWon=true;
                                //pause for dramatic effect
                                lastTime=clock();
                                //wait for delay length
                                while(clock()-lastTime<activationDelay);
                                //clear queue to stop executing instructions
                                cmd=0;
                                cq.clear();
                                //break;
                            }
                            //dequeue the next command
                            cmd = cq.get();
                            lastTime=clock();
                        }
                        else cmd=0; //break;
                    }
                }//end while commands are in the queue
                //END EXECUTION/ANIMATION LOOP

                if(!levelWon){
                    cout<<"Your robot is glitching out!"<<endl;
                    --level;
                    lastTime=clock();
                    //wait for delay length
                    while(clock()-lastTime<activationDelay); 

                    //build and output map
                    fillMap(map, MAPSZ, MAPSZ, C_FLOOR);
                    if (!hasKey) map[keyY][keyX]=C_KEY;
                    map[doorY][doorX]=C_DOOR;
                    //draw mine tiles
                    for(int i = 0; i < mines; i++){
                        map[ minesY[i] ][ minesX[i] ] = C_MINE;
                    }
                    map[player.getY()][player.getX()] = C_PLAYER;
                    printMap(map, MAPSZ, MAPSZ);
                }

                //clear queue
                cq.clear();

                if (level > 10){
                    cout<<"\nCONGRATULATIONS!\n"
                            "You guided the robot through the disaster!"<<endl;
                    lastTime=clock();
                    //wait for delay length
                    while(clock()-lastTime<activationDelay); 
                }
                else if(level>0){
                    cout<<"Press Enter to roll into room "<<level<<endl;
                    while(cin.get()!='\n');
                    while(cin.get()!='\n');
                }
            }
            //deallocate mine coordinate arrays
            delete [] minesX;
            delete [] minesY;
        }//end while level >0 && level<=10

        cout<<"GAME OVER"<<endl;

        lastTime=clock();
        while(clock()-lastTime<CLOCKS_PER_SEC*2); //wait for delay length

        cout<<"Would you like to play again?(Y/N): ";
        char quitInput;
        cin>>quitInput;
        if(quitInput=='Y'||quitInput=='y'){
            quit=false;
            cout<<"\n\n\n\n\n"<<endl;
        }
        else quit=true;
    }//end while not quit

    cout<<"GOODBYE"<<endl;
    return 0;
}//end main

////////////////////////////////////////////////////////////////////////////////
