/*
	Dynamic Matrix Class Template
	-template class, Abstract Data Type
	-safe setter/getters
	-copy constructor
	-operator= override
	-throws exception (for invalid index parameter to getter)
	===========================
	Code by Jason Lillard, 2017
	===========================
*/
#ifndef DYNAMICMATRIXTEMPLATE_H
#define DYNAMICMATRIXTEMPLATE_H
using namespace std;
//Warning: template classes must be in a single file -- your main file or in a .h file 
//Template classes can't be split into .h and .cpp files!!!
template <class T> //template class 
class DynamicMatrix { //2D array of generic data type
	private:
		size_t width, height; //dimensions of matrix
		T ** matrix; //pointer pointer to hold row pointers
	public:
		//constructor
		DynamicMatrix(size_t height, size_t width ){ //HEIGHT, WIDTH
			this->width = (width >= 2 ? width : 2); //ensure width is at least 2
			this->height = (height >= 2 ? height : 2); //ensure height is at least 2
			//allocate row pointers
			matrix = new T*[height];
			//allocate each row
			for(int y = 0; y < height ; y++){
				matrix[y] = new T[width]; //make row, T array
			}
		}//end constructor
		
		//copy constructor
		DynamicMatrix( const DynamicMatrix &rhs){
			
			//copy sizes from right-hand side object (they will be valid)
			this->width = rhs.width; 
			this->height = rhs.height;
		
			//allocate row pointers
			this->matrix = new T*[height];
			//allocate each row
			for(int y = 0; y < height ; y++){
				this->matrix[y] = new T[width]; //make row, T array
			}
			//copy contents of rhs's matrix
			for( int y = 0; y < height ; y++){
				for (int x = 0; x < width ; x++){
					matrix[y][x] = rhs.matrix[y][x]; //copy data from right-hand side object
				}
			}
			
		}//end copy constructor
		
		//destructor
		~DynamicMatrix(){
			for(int y = 0; y < height ; y++){
				delete [] matrix[y]; //delete this row
			}
			delete [] matrix; //delete row pointers
		}//end destructor
		
		//operator= overload
		DynamicMatrix operator=( const DynamicMatrix &rhs){ 
			//DELETE CURRENT DATA
			//this code identical to destructor's
			for(int y = 0; y < height ; y++){
				delete [] matrix[y]; //delete this row
			}
			delete [] matrix; //delete row pointers
			//COPY RHS'S DATA
			//this code identical to copy constructor's
			//copy sizes from right-hand side object (they will be valid)
			this->width = rhs.width; 
			this->height = rhs.height;
			//allocate row pointers
			this->matrix = new T*[height];
			//allocate each row
			for(int y = 0; y < height ; y++){
				matrix[y] = new T[width]; //make row, T array
			}
			//copy contents of rhs's matrix
			for( int y = 0; y < height ; y++){
				for (int x = 0; x < width ; x++){
					//printf("[R%d:C%d]\n", y, x);
					//copy data from right-hand side object
					this->matrix[y][x] = rhs.matrix[y][x]; //unsafe copy
					//this->set(y, x, rhs.get(y, x)  ); //safe copy data from right-hand side object
				}
			}
			return *this; //return the current object (needed for chained/multiple assignment)
			//e.g. matrix1 = matrix2 = matrix3;
			//if this feature is irrelevant to you, operator= can be a void function
		}//end operator=
		
		
		//size getters
		size_t getHeight() const { return height; }
		size_t getWidth() const { return width; }
		
		//safe getter
		T get (size_t row, size_t col) const { //get from row, col -- params could be swapped to reflect (x,y) format
			if (row < height && col < width){
				return matrix[row][col]; //return item's value
			}
			//else, index is invalid:
			//return EOF; //could return EOF marker if index is invalid
			
			//could also throw exception, but if this isn't caught in a try-catch structure,
			//an invalid access attempt will crash the program.
			puts("Invalid Index sent to DynamicMatrix's function: get(row, col)");
			throw "Invalid Index!";
		}//end get
		
		//safe setter
		void set(size_t row, size_t col, T data){
			if (row < height && col < width){
				matrix[row][col] = data; //set element's value to given one
			}
			//if index is invalid, we can just ignore the request
			//because unlike T get(), we don't have to return a value or throw an exception.
		}//end set
		
};//end DynamicMatrix template class
#endif

/*
	Example Driver to test DynamicMatrixTemplate:
	#include <cstdio>
	//Make sure to manually add this .h file the folder with your .cpp with int main() :
	#include "DynamicMatrixTemplate.h" 
	using namespace std;

int main( ) {
	//building array
	DynamicMatrix<int> matrix(20, 8);
	int myInt = 42;
	//attempting invalid access with get
	try{
		//try to assign a new value to myInt
		myInt = matrix.get(-1, -1); //indices -1 & -1 are both invalid
	}
	catch( ... ){ //catch any kind of exception
		puts("Exception thrown from get() caught in main()!");
	}
	printf("myInt after try block: %d\n", myInt); //display myInt
	puts("Properly filled DynamicMatrix<int> object:");
	//filling & printing array
	size_t height = matrix.getHeight(), width = matrix.getWidth();
	for(int y = 0; y < height; y++){
		for (int x = 0; x < width ; x++){
			matrix.set(y, x, (y+1)*(x+1) );
			printf("%8d ", matrix.get(y, x) );
		}
		putchar('\n');
	}
	puts("matrix2:");
	DynamicMatrix<int> matrix2 (10, 4);
	size_t height2 = matrix2.getHeight(), width2 = matrix2.getWidth();
	for(int y = 0; y < height2; y++){
		for (int x = 0; x < width2 ; x++){
			matrix2.set(y, x, (y+10)*(x+10) );
			printf("%8d ", matrix2.get(y, x) );
		}
		putchar('\n');
	}
	
	matrix = matrix2; //overloaded operator= should copy dynamic matrix
	height2 = matrix.getHeight();
	width2 = matrix.getWidth();
	puts("Printing copied elements in matrix 1:");
	//matrix should now have matrix2's dimensions and data
	for(int y = 0; y < height2; y++){
		for (int x = 0; x < width2 ; x++){
			printf("%8d ", matrix.get(y, x) );
		}
		putchar('\n');
	}
	
	puts("Using Copy Constructor to build matrix3:");
	DynamicMatrix<int> matrix3(matrix2);
	size_t height3 = matrix3.getHeight();
	size_t width3 = matrix3.getWidth();
	//matrix3 should now have matrix2's dimensions and data
	for(int y = 0; y < height3; y++){
		for (int x = 0; x < width3 ; x++){
			printf("%8d ", matrix3.get(y, x) );
		}
		putchar('\n');
	}
	
	return 0;
}
*/
