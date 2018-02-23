#include <iostream>
#include "QMath.h"

using namespace std;

//little structure to hold two variables to keep track of a point or vector
struct Coord{
    float x, y;
};

//little helper function to print coords over and over again
void print( Coord c){
    cout<<"("<<c.x<<", "<<c.y<<")";
}

//Our main driver
int main(int argc, char** argv) {

    Coord c1; c1.x=0; c1.y= 0;
    Coord c2; c2.x=3; c2.y = 4;
    
    //Distance should be 5, based on pythagorean triplet 3, 4, 5
    cout <<"Distance between ";
    print(c1);
    cout<<" and ";
    print(c2);
    //print results of dist function
    float d = dist(c1.x, c1.y, c2.x, c2.y);
    cout<<" is "<< d <<endl; 
    
    //Shrinking a vector (stored as a coordinate) to length 1
    cout<<"Normalizing Vector ";
    print(c2);
    cout<<"..."<<endl;
    Coord c2n; c2n.x=c2.x; c2n.y=c2.y; //make a copy of c2 to normalize it
    //call C function to quickly normalize vector
    normalize( &c2n.x, &c2n.y);
    cout<<"Normalized Vector: ";
    print(c2n);
    cout<<endl;
    
    
    //collision detection test
    cout<<"Testing circle collision function with point ";
    print(c1);
    cout<<" and circle with center ";
    print(c2);
    cout<<endl;
    
    cout<<"Testing radius "<< d+1 <<", which should reach the point..."<<endl;
    //call our C function to determine if point c1 touches circle @ c2, r=d+1
    if ( touchesCircle( c1.x, c1.y, c2.x, c2.y, d+1) ){
        cout<<"Point touches circle!"<<endl;
    }
    else cout<<"Point is outside of circle!"<<endl;
    
    cout<<"Testing radius "<< d-1 <<", which should fall short..."<<endl;
    //call our C function to determine if point c1 touches circle @ c2, r=d-1
    if ( touchesCircle( c1.x, c1.y, c2.x, c2.y, d-1) ){
        cout<<"Point touches circle!"<<endl;
    }
    else cout<<"Point is outside of circle!"<<endl;
    
    cout<<"Goodbye."<<endl;
    return 0;
}