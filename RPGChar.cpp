/*
	RPG Character Class  (Starter Example)
	Example of a container with a classic D20-type stat list
	
	Warning: Much of this will not make sense without the header file RPGChar.h
	===========================
	Code by Jason Lillard, 2017
	===========================
*/

#include "RPGChar.h"
#include <cstring> // for strncpy
#include <cstdlib> //for realloc
#include <cstdio> //for printItems

using namespace std;

//for initializing an object with another object
Item::Item( const Item &rhs){ //copy constructor -- rhs tradional name for "right-hand side" object
	this->type = rhs.type;
	this->impact = rhs.impact;
	strncpy( this->name, rhs.name, NAMESZ);
}
//for setting an object with another object
Item Item::operator=( const Item &rhs){ //equal sign operator override
	this->type = rhs.type;
	this->impact = rhs.impact;
	strncpy( this->name, rhs.name, NAMESZ);
}

//use strncpy to safely set name based on given string
void RPGChar::setName( const char * nameStr){
	strncpy(name, nameStr, NAMESZ-1); //copy to name from nameStr, leave null terminator
}

//return pointer to item if index is valid
Item * RPGChar::getItem(size_t index){
	if (index < inventoryMax){
		return (inventoryPtr+index);
	}
}
//add item to inventory
void RPGChar::addItem(Item &item){ //add at end, increment inventoryCurrent
	bool added = false;
	for( int i = 0; i < inventoryMax && !added ; i++){
		if (inventoryPtr[i].type == ItemType::NONE){ //find first blank space, if any
			inventoryPtr[i] = item; //assign added item using operator= override
			inventoryCount++;
			added = true;
		}
	}
	//if no blank space was found, do nothing with given item
}

//add item at given place
void RPGChar::addItem(Item &item, size_t index){ //add/overwite at place, increment inventoryCurrent
	if ( inventoryPtr[index].type == ItemType::NONE ){ //if item isn't replacing something
		inventoryCount++; //increment inventoryCurrent
	}
	inventoryPtr[index] = item; //assign item using operator= override
}


//delete item from given place
void RPGChar::deleteItem(size_t index){ //deallocate item and decrement inventoryCurrent
	if ( inventoryPtr[index].type == ItemType::NONE ){ //if item is deleting something
		inventoryCount--; //decrement inventoryCurrent
	}
	inventoryPtr[index] = Item(); //assign item to default Item using operator= override
}


//resize inventoryPtr array with realloc, update inventoryMax
void RPGChar::resizeInventory(size_t newMaxSize){ 
	if (newMaxSize == inventoryMax ) return;
	
	inventoryPtr = (Item*) realloc( inventoryPtr, sizeof(Item)*newMaxSize );
	inventoryMax = newMaxSize; //update max inventory size
	if (inventoryCount > inventoryMax) inventoryCount = inventoryMax; //adjust inventoryCount if items were lost
}

void RPGChar::printItems(){
	for(int i = 0; i < inventoryMax; i++){
		//cout<< i<<": "<<inventoryPtr[i].name <<" \t";
		printf("%d: %s, ", i, inventoryPtr[i].name );
		if ( (i+1)%4==0 ) putchar('\n');
	}
	putchar('\n');
}

/////////////////////////////////////////////////////////////////////
//Example driver for testing class:
	/*
	RPGChar player1("Jay");
	
	Item item1;
	item1.setName("Lightsaber");
	item1.type = ItemType::WEAPON;
	
	Item item2;
	item2.setName("Iron Boots");
	item2.type = ItemType::ARMOR;
	
	Item item3;
	item3.setName("Health Potion");
	item3.type = ItemType::POTION;
	
	Item item4;
	item4.setName("Dungeon Key");
	item4.type = ItemType::KEY;
	
	player1.addItem( item1 );
	player1.addItem( item2 );
	player1.addItem( item3 );
	player1.addItem( item4 );
	
	player1.printItems();
	
	puts("Deleting item 2....");
	player1.deleteItem( 2 );
	
	player1.printItems();
	*/

