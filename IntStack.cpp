/*
	Easy Stack
	
	2017 Jason Lillard
*/

#include <cstdio>
using namespace std;

class IntStack{
	private:
	int * stackPtr; //pointer to hold dynamically allocated array
	int size;
	int endIndex;
	
	//constructor
	public:
	IntStack(int maxSize ){
		size = maxSize;
		stackPtr = new int [size];
		endIndex = -1;
	}
	
	//destructor
	~IntStack(){
		delete [] stackPtr;
	}
	
	
	//push
	void push(int num){
		if (endIndex < size-1 ){
			endIndex++;
			stackPtr[ endIndex ] = num;
		}
	}
	
	//pop
	int pop(){
		if ( endIndex >= 0){
			int result = stackPtr[endIndex];
			endIndex--;
			return result;
		}
	}
	
	//peek
	int peek(){
		return stackPtr[endIndex];
	}
	
	//clear
	void clear(){
		endIndex = -1;
		stackPtr[0] = 0;
	}
	
	//getCapacity
	int getCapacity(){ return size;}
	//getCurrentIndex
	int getCurrentIndex(){ return endIndex; }
};

int main(){
	IntStack stack(10);
	
	printf("Capacity: %d\n", stack.getCapacity() );
	
	for (int i = 0; i < 10; i++ ){
		printf("Current Index: %d\n", stack.getCurrentIndex() );
		
		int num = i;
		printf("Pushing %d onto stack.\n", num);
		stack.push( num );
		
		printf( "Current Peek Value: %d\n", stack.peek() );
	}
	
	puts("\n");
	
	for (int i = 0; i < 10; i++ ){
		printf("Current Index: %d\n", stack.getCurrentIndex() );
		printf( "%d\n", stack.pop() );
	}
}
