/*
	Code by Jason Lillard, 2017
	===========================
	strtok test to break instruction of assembly-style code into
	tokens, then use strcmp to determine which opcode is given,
	then use enums and char arrays to help figure out source and 
	destination registers, then perform the requested operation
	with the given registers.
	Note: there's probably better ways of doing this, using pointers
	and switch statements and such, this could be much better organized.

*/

#include <cstring> //strtok, strcmp
#include <cstdio> //printf, puts
using namespace std;
//strtok
enum REG{ RA, RX, RY};

int main(){
	int i_regs[3] = { 8, 32, 128}; //virtual registers
	//initial output of registers (to prove MOV operation works)
	printf ("Register Dump:\nA:%9d\nX: %9d\nY: %9d\n", i_regs[RA], i_regs[RX], i_regs[RY] );	
	
	const char * c_regs = "AXY"; //char directory of registers
	
	const char * inst = "MOV A, X";
	const char * delims = ", ";
	const size_t LEN = sizeof(inst)+1;
	char* instCpy = new char[ LEN ];
	strncpy( instCpy, inst, LEN);
	char * token; //temp var to hold tokens
	
	//SPLIT COPY INTO TOKENS, parse instruction line more after each pop
	token = strtok ( instCpy, delims); //split off first token, the opcode
	if ( !strcmp (token, "MOV") ){ //if token is MOV
		//printf("Moving...");
		//convert register chars to numbers
		char* reg1 = strtok(0, delims); //dest register
		char* reg2 = strtok(0, delims); //src register
		
		if ( *reg1 == c_regs[ RA ] ){
			//dest is reg A
			if ( *reg2 == c_regs[ RX ] ){
				//src is reg x
				i_regs[ RA ] = i_regs[RX];
			}
			else if ( *reg2 == c_regs[ RY ] ){
				//src is reg y
				i_regs[ RA ] = i_regs[RY];
			}
			else puts("Invalid source register");
		}
		else if ( *reg1 == c_regs[ RX ] ){
			//dest is reg X
			if ( *reg2 == c_regs[ RA ] ){
				//src is reg a
				i_regs[ RX ] = i_regs[RA];
			}
			else if ( *reg2 == c_regs[ RY ] ){
				//src is reg y
				i_regs[ RX ] = i_regs[ RY] ;
			}
			else puts("Invalid source register");
		}
		else if ( *reg1 == c_regs[ RY ] ){
			//dest is reg Y
			if ( *reg2 == c_regs[ RA ] ){
				//src is reg a
				i_regs[ RY ] = i_regs [ RA ];
			}
			else if ( *reg2 == c_regs[ RY ] ){
				//src is reg y
				i_regs[ RY ] = i_regs [ RY ];
			}
			else puts("Invalid source register");
		}
		else{
			puts("Invalid destination register");
			
		}
		
	}
	//else if... other opcodes
	
	//else... invalid opcode
	
	//final output (mostly for demo purposes)
	printf ("Register Dump:\nA:%9d\nX: %9d\nY: %9d\n", i_regs[RA], i_regs[RX], i_regs[RY] );	
	

}
