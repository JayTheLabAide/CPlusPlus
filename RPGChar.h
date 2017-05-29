/*
	RPG Character Class  (Starter Example)
	Example of a container with a classic D20-type stat list
	Also implements a very basic Item & resizable Inventory system using dynamic memory
	--Some setters are not implemented yet. They should be easy enough to make if you can understand
	the basics of accessing data within classes (this RPGChar class has at least one example for you)
	Warning: Some implementations are in RPGChar.cpp, be sure to download/copy/save that file too
	===========================
	Code by Jason Lillard, 2017
	===========================
*/
#ifndef RPGCHAR_H
#define RPGCHAR_H
#include <cstring>
using namespace std;


enum ItemType{
	NONE, WEAPON, ARMOR, POTION, KEY
};

struct Item{
	static const size_t NAMESZ = 17;
	char name[NAMESZ]{};
	ItemType type;
	short impact;
	Item(){//default constructor
		type=NONE;
		impact=0;
	} 
	Item( const Item &rhs); //copy constructor
	Item operator=( const Item &rhs); //equal sign operator override
	void setName( const char * nameStr){
		strncpy(name, nameStr, NAMESZ-1); //copy to name from nameStr, leave null terminator
	}
};

//struct Spell{ ... };

class RPGChar{ //A skeletal structure for a generic role-playing-game character
	
	//private members, our character's stats
	private:
	short maxHP;
	short currentHP;
	short maxMagic;
	short currentMagic;
	
	short strength;
	short dexterity;
	short endurance;
	short charisma;
	short intelligence;
	short wisdom;
	short luck;
	
	unsigned long gold; //gotta have lots of space for gold
	
	public:
	static const size_t NAMESZ = 17; //constants like this are safe for public access
	
	private:
	char name[NAMESZ]{}; //Character Name
	
	//inventory members
	short inventoryMax;
	short inventoryCount;
	Item * inventoryPtr;
	
	//public members
	public:
		
		//constructor. Takes character name string as an optional parameter.
		RPGChar(const char * nameStr=""){
			setName(nameStr); //use member function to set name passed to constructor
			inventoryMax = 10;
			inventoryPtr = new Item[inventoryMax]; //allocate item array
			inventoryCount = 0;
		}
		
		//destructor, deallocates dynamic memory
		~RPGChar(){
			delete [] inventoryPtr;
		}

	public:
		//GETTERS
		short getMaxHP(){ return maxHP; }
		short getCurrentHP(){ return currentHP; }
		short getMaxMagic(){ return maxMagic;}
		short getCurrentMagic(){ return currentMagic;}
		short getStrength(){ return strength;}
		short getDexterity(){ return dexterity;}
		short getEndurance(){ return endurance; }
		short getCharisma(){ return charisma; }
		short getIntelligence(){ return intelligence;}
		short getWisdom(){ return wisdom; }
		short getLuck(){ return luck; }
		unsigned long getGold(){ return gold;}
		
		const char * getName(){ return name; } //return const pointer to name string
		short getInventoryMax(){ return inventoryMax;}
		short getInventoryCount(){return inventoryCount;}
		
		Item * getItem(size_t index); //get pointer to item from given index
		
		//SETTERS 
		void setMaxHP(short hp){ if (hp>0) maxHP = hp; } //example implementation
		// not implemented: these are easy, do them yourself
		void setCurrentHP(short); //not implemented
		void setMaxMagic(short); //not implemented
		void setCurrentMagic(short);  //not implemented
		void setStrength(short);  //not implemented
		void setDexterity(short);  //not implemented
		void setEndurance(short);  //not implemented
		void setCharisma(short);  //not implemented
		void setIntelligence(short);  //not implemented
		void setWisdom(short);  //not implemented
		void setLuck(short);  //not implemented
		void setGold(unsigned long); //not implemented
		
		//implemented:
		void setName( const char *); //update name with maximum available characters
		
		void addItem(Item & item); //add at end, increment inventoryCurrent
		void addItem(Item & item, size_t index); //add/overwite at place, increment inventoryCurrent
		void deleteItem(size_t index); //deallocate item and decrement inventoryCurrent
		
		void resizeInventory(size_t newMaxSize); //resize inventoryMax & inventoryPtr array with realloc
		
		void printItems(); //print inventory
		/*
			Further Suggestions:
			short getAttack() -- based on Strength, intensity score of WEAPON type items, etc.
			short getDefense() -- based on Endurance, intensity score of ARMOR type items, etc.
		
			Build in ability to differentiate between Equipped and Unequipped Items in Inventory
			
			Spell class, similar to Item class
			Spell* spellPtr, dynamic array of Spell objects, similar to Item* itemPtr array
			
			Moral/Social stats like reputation, faction alignment, etc.
			Survival stats like hunger, thirst, exhaustion, etc.
			
			Status Effects like poisoned, frozen, burned, supercharged, cursed, asleep etc.
		*/
		
};
#endif
