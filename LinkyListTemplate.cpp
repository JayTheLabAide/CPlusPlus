/*
	Double-ended linked list template class
	with push, pop, peek at front and back, and remove.
	Also has functions to return elements as forward or reversed dynamic arrays
	==========================
	Code by Jason Lillard 2018
*/
#include <cstdio> // for demo output, not needed for template class
using namespace std;

//put this in one header. Don't break up into a .h and .cpp (that wrecks it)!!!
/*
	BEGIN LINKYLIST.H
*/

//A double-ended linked list with push, pop, and peek at front and back
template <class T> //t will be our data type specified when we make a LinkyList
class LinkyList { 
private:
	
	//INNER NODE CLASS (doesn't have to be template class of the same type)
	struct Nd{
		T d; //data (based on our designated data type)
		Nd* p; //previous
		Nd* n; //next
	};
	
	//MEMBER VARS
	Nd * h; //head
	Nd * t;//tail
	unsigned s;//current size
	
	//MEMBER FUNCS
	
	//delete entire chain forward
	void delChain(Nd* nd){
		if( !nd )return; //if node is null, jump out
		Nd * next; //make node to store next after current is deleted
		do {
			next=nd->n;//store next
			delete nd;//delete current
			--s;//decrement size of list
			nd=next;//move nd forward
		} while(nd);//repeat if nd is not null
	}
	
	/* 
	//Not used
	//delete entire chain backwards
	void revDelChain(Nd* nd){
		if( !nd )return;
		Nd* prev;//node to store previous after current is deleted
		do {
			prev=nd->p;//store previous
			delete nd;//delete current
			--s;//decremnt size of list
			nd=prev;//move nd backward
		} while(nd);//repeat if nd is not null
	}
	*/
	
public:
	//ctor
	LinkyList(){
		//Set head and tail to null, size to 0
		h=t=0;
		s=0;
	}
	
	//dtor
	virtual ~LinkyList(){
		delChain(h);//forward delete from head node
	}
	
	//resetter
	void deleteAll(){
		delChain(h);
		h=t=0;
		s=0;
	}
	
	//Add data to front of list
	void pushFront(T d){
		
		if(h){ //if head exists
			//make node to add, set its data and next (current head)
			//and set head's previous to the new node
			h->p= new Nd {d, 0, h};
			//move head pointer backward to new node
			h=h->p;
			//increment size of list
		}
		else{ //if head doesn't exist
			//tail and head are now both the new node
			t = h = new Nd {d, 0, 0};
		}
		//increment size of list
		++s;
	}
	
	
	//Add data to back of list
	void pushBack(T d){
		if (t){
			//make node to add, set its data and previous node (current tail)
			//and set tail's next to the new node
			t->n= new Nd{d, t, 0};
			//move tail pointer forward to new node
			t=t->n;
		}
		else{
			//tail and head are now both the new node
			t = h = new Nd{d, 0, 0};			
		}
		//increment size of list
		++s;
	}
	
	//copy constructor
	LinkyList( const LinkyList<T> & list){
		//set reading node to list's head
		Nd* r = list.h;
		//while reader is not null
		while( r ){
			//add node's data to this
			this->pushBack ( r->d );
			//move reading node forward
			r=r->n;
		}
	}
	
	LinkyList& operator= (const LinkyList<T> & rhs){
		//erase current list's contents
		this->deleteAll();
		//set reading node to list's head
		Nd* r = rhs.h;
		//while reader is not null
		while( r ){
			//add node's data to this
			this->pushBack ( r->d );
			//move reading node forward
			r=r->n;
		}
		return *this; //return a reference to this
	}
	
	//Get data from front of list 
	T peekFront () const {
		if(!h) throw "List is Empty";
		return h->d;	
	}
	
	//Get data from front of list and remove it
	T popFront(){
		if(!h) throw "List is Empty";
		//store data to return
		T pop = h->d;
		//store current head to delete
		Nd* oh = h;
		//move head pointer forward
		h=h->n;
		//nullify new head's previous node pointer
		if (h) h->p=0;
		else t=0;
		//delete old head
		delete oh;
		//decrement list size
		--s;
		//return data popped from list
		return pop;
	}
	
	//Get data from back of list 
	T peekBack() const {
		if(!t) throw "List is Empty";
		return t->d;
	}
	
	//Get data from back of list and remove it
	T popBack(){
		if(!t) throw "List is Empty";
		//store data to return
		T pop = t->d;
		//store current tail to delete
		Nd* ot = t;
		//move tail pointer backwards
		t=t->p;
		//if tail still exists, nullify its next node pointer
		if (t) t->n=0;
		else h=0;
		//delete old tail
		delete ot;
		//decrement list size
		--s;
		//return data popped from list
		return pop;
	}
	
	//Get current size of list
	unsigned getSize() const {return s;}
	
	/*
		Get list as a dynamic array of contiguous memory
		(MAY BECOME STALE!)
		if you change the list after calling this function, the changes 
		WILL NOT be reflected in the array.
	*/
	T* getArray(unsigned * sz) const {
		if (!s) {
			if(sz)*sz=0;
			return 0;
		}
		//allocate array space on heap
		T* a = new T[s];
		//make reader, point it to head
		Nd* r = h;
		//traverse list, copying elements into array
		for(int i = 0; i < s; i++){
			*(a+i)=r->d; //copy data from reader node into array
			r=r->n; //move reader node forward
		}
		//if an address was given to return size of array, set it
		if(sz)*sz= s;
		return a; //return pointer to array
	}
	
	/*
		Get reversed list as a dynamic array of contiguous memory
		(MAY BECOME STALE!)
		if you change the list after calling this function, the changes
		WILL NOT be reflected in the array.
	*/
	T* getRevArray(unsigned * sz) const {
		if (!s) {
			if(sz)*sz=0;
			return 0;
		}
		//allocate array space on heap
		T* a= new T[s];
		//make reader, point it to tail
		Nd* r = t;
		//traverse list, copying elements into array
		for(int i = 0; i < s; i++){
			*(a+i)=r->d; //copy data from reader node into array
			r=r->p; //move reader node backwards
		}
		//if an address was given to return size of array, set it
		if(sz)*sz= s;
		return a; //return pointer to array
	}

	//linear search, starting at front
	bool search(T q){
		Nd* r = h;
		//while reader is not null
		while(r){
			//if match is found, return true
			if ( r->d == q ) return true;
			//move r forward
			r=r->n;
		}
		//not found, return false
		return false;
	}

	//linear search, starting at back
	bool revSearch(T q){
		Nd* r = t;
		//while reader is not null
		while(r){
			//if match is found, return true
			if ( r->d == q ) return true;
			//move r forward
			r=r->p;
		}
		//not found, return false
		return false;
	}
	
	bool remove(T q){
		Nd* r = h;
		Nd* toDel = 0;
		if (r && r->d == q){
			//save old head to delete
			toDel = r;
			//move head forward
			h=h->n;
			delete toDel;
			if (h) h->p = 0;
			else t = 0;
			--s;
			return true;
		}
		else{
			//remove middle or end
			while( r ){
				if (r->d==q){
					//prepare to delete reader's current node
					toDel = r;
					//move r forward
					r =  r->n;
					//set the previous node's next to the next node
					toDel->p->n = r;
					//if there is a next node, set it's previous to del's prev.
					if(r)r->p = toDel->p;
					else t = toDel->p;
					//delete node with matching data
					delete toDel;
					//reduce size of list
					--s;
					return true;
				}else{
					//move r forward
					r=r->n;
				}
			}
		}
		//not found, return false to indicate element was not removed
		return false;
	}
};
/*
	END LINKYLIST.H
*/


int main(){
	//List to test
	LinkyList< float > list;
	
	puts("Demo Driver for LinkyList Template Class");
	bool quit = false;
	do{

		
		puts (
			"\n\n1. Print List As Array\n"
			"2. Print List As Reversed Array\n"
			"3. Push to Front\n"
			"4. Push to Back\n"
			"5. Peek at Front\n"
			"6. Peek at Back\n"
			"7. Pop From Front\n"
			"8. Pop From Back\n"
			"9. Clear List\n"
			"A. Search From Front\n"
			"B. Search From Back\n"
			"C. Find and Delete Value\n"
			"Q. Quit Demo\n"
			"-----------------------------------"
		);
	
		char menuSelection = getchar();
		
		switch(menuSelection){
			case 'Q': case 'q':
				quit=true; 
				break;
				
			case '1':{
				puts("Current Array Made From List:");
				unsigned aSz;
				float* a = list.getArray(&aSz);
				for(int i = 0; i < aSz; i++){
					printf("%d: %f\n", i+1 , *(a+i) );
				}
				
				delete [] a;
			}
			break;
			
			case '2': {
				puts("Current Reversed Array Made From List:");
				unsigned aSz = list.getSize();
				float* ra = list.getRevArray(0);
				for(int i = 0; i < aSz; i++){
					printf( "%d: %f\n", i+1, *(ra+i) );
					
				}
				delete [] ra;
			}
			break;
			
			case '3':{
				printf("Enter a float to push to front of list:\n");
				float d;
				scanf( "%f", &d);
				list.pushFront( d );
			}
			break;
			
			case '4':{
				printf("Enter a float to push to back of list:\n");
				float d;
				scanf( "%f", &d);
				list.pushBack( d );
			}
			break;
			
			case '5':{
				try{
					printf("Peek: Value at front of list: \n%f\n", 
							list.peekFront() );
				}catch(const char * str){
					puts(str);
				}
			
			}
			break;
			
			case '6':{
				try{
					printf("Peek: Value at back of list: \n%f\n", 
							list.peekBack() );
				}catch(const char * str){
					puts(str);
				}
				
			}
			break;
			
			case '7':{
				try{
					printf("Pop: Value at front of list: \n%f\n",
							list.popFront() );
				}catch(const char * str){
					puts(str);
				}
			}
			break;
			
			case '8':{
				try{
					printf("Pop: Value at back of list: \n%f\n",
							list.popBack() );
				}catch(const char * str){
					puts(str);
				}
			}
			break;
			
			case '9':{
				list.deleteAll();
				puts("List Deleted");
			}
			break;

			case 'a': case 'A':{
				float f;
				printf("Enter a number to search for: ");
				scanf("%f", &f);
				printf("Number was %sfound!", (list.search(f)?"":"not "));
			}
			break;
				
			case 'b': case 'B':{
				float f;
				printf("Enter a number to search for: ");
				scanf("%f", &f);
				printf("Number was %sfound!", (list.revSearch(f)?"":"not "));				
			}
			break;
			
			case 'c': case 'C':{
				float f;
				printf("Enter a number to find and delete: ");
				scanf("%f", &f);
				printf("Number was %sremoved!", (list.remove(f)?"":"not "));
			}
			break;
			
			default: break;
		}
		while( getchar()!='\n');
	}while(!quit);
	return 0;
}
