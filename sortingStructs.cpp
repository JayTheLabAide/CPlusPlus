/*
        Fraction Tables -- Sorting Structs
        -----------------
        by Jason Lillard, 2018
	
    So the idea here is we're delirious imperialists with a silly measurement
    system and we need to figure out which fractions of an inch are bigger
    or smaller than other fractions of an inch, when you have halves, quarters,
    eighths, sixteenths, thirty-secondths, and sixty-fourths. 
    This exercise, by the way, is inspired by a chart in my dad's garage.

	
 */

//standard stuff
#include <iostream>
using namespace std;

/*
    It's The Big Shoooowwww...
    Wow, a wrestling reference from like back in 6th grade. Not sure where that
    came from, but anyways, here is the big show, finally underway:
    our struct thing.

    struct Fraction{
            //insidey parts
    };

     ^ At the end of the struct block is a semicolon -- the struct and
    class code blocks are the only blocks which do this. (BTW structs and
    classes are almost the same thing, except for that struct data is public
    by default and class data is private by default. You don't need to worry
    about that difference just yet, but we'll use structs to make our data
    easier to access when we're playing with our fractions.
 */
struct Fraction {
/*
    He're we're going to have three different things. Two of them are the
    things you need for a fraction, and the other we don't need, but will
    save us on some math work when it comes time to do the sorting and
    outputting of our table.
 */

    long top;
    long bottom; //I didn't have to use longs for this, but I did anyways.

    double value; // top/bottom=value, because that's how fractions work.

}; //end of struct Fraction

/*
    Notice our Fraction structs aren't especially "safe" in the sense that the
    denominator (bottom) of the fraction can be set to 0, or the value can
    be set to something other than top/bottom. If we were making this as a class
    instead of a struct we could regulate things like that using functions
    within the class, but for now we'll just program the thing like Pokemon Red
    and assume that none of our functions or data structures will ever be used
    incorrectly. (Note: this is a horrible assumption that leads to some of the
    most insane glitches ever. Only program like this if you have no extra space
    to store code, or you just give zero fucks whatsoever.)
 */


//Some short utility functions:

/*
    compareStructs takes in two fractions and does a classic compare operation
    on the "value" variables of each struct, meaning it returns a.value-b.value,
    and checking the sign of this result tells you about which is bigger or
    smaller.
    if a-b < 0, then b must be bigger than a
    if a-b = 0, then a and b must be the same value
    if a-b > 0, then a must be bigger than b
    In assembly language, this is how you determine if one value is greater,
    less than, or equal to another, with an operation like CMP X, Y
 */
double compareFracts(const Fraction &a, const Fraction &b) {
    return a.value - b.value; // compare a's and b's values
}

/*
    Notice that while compare can use constant references, meaning it is
    a read-only function, our swapFracts function just uses regular references
    so that we can actually change the data inside each fraction
 */
void swapFracts(Fraction & a, Fraction & b) {
    //Make a temporary variable
    Fraction t;

    //t = a (save a's data for later)
    t.top = a.top;
    t.bottom = a.bottom;
    t.value = a.value;

    // a = b (store b's data in a)
    a.top = b.top;
    a.bottom = b.bottom;
    a.value = b.value;

    // b = t (put what was a's data into b)
    b.top = t.top;
    b.bottom = t.bottom;
    b.value = t.value;
}

/*
    Bubble sort: The slowest sort, but this isn't about which sorting algorithm
    you use, it's about the idea of sorting structures (which have many values
    in them) based on one specific piece of information which serves as a kind
    of ID you can use to quickly tell one from another.
 */
void bubbleFracts(Fraction fArr[], const unsigned size) {
    //From Starting Out With C++, by Gaddis, Ch. 8, Searching & Sorting Arrays
    bool swapped = false;
    do {
        swapped = false;
        for (int i = 0; i < size - 1; i++) {
            if (compareFracts(fArr[i], fArr[i + 1]) > 0) {
                swapFracts(fArr[i], fArr[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

//Print our array with some minimal formatting

void printFracts(const Fraction fArr[], const unsigned size) {
    for (int i = 0; i < size; i++) {
        //print: top/bottom  = value
        cout << fArr[i].top << "/" << fArr[i].bottom << "\t= "
                << fArr[i].value << '\n';
    }
    cout << endl; //end line and flush buffer
}

/*
    Now let's make our main function to generate this fraction table and sort
    it based on its decimal values.
 */

int main() {
    //We need a fraction for each half, quarter, etc. except for 2/2, 4/4 etc.
    unsigned FRACTS = 2 - 1 + 4 - 1 + 8 - 1 + 16 - 1 + 32 - 1 + 64 - 1;
    //so we make an array of our Fraction structure.
    Fraction fracts[FRACTS];

    //Now let's fill the thing with data. This isn't sorting or printing it or
    //anything like that. Right now we're just making the data so we can sort it
    //later.

    int f = 0; //our counter/index for our Fraction array
    int top = 1; //our counter for the top parts
    int bottom = 2; //our counter for the bottom parts

    while (bottom <= 64 && f < FRACTS) {

        while (top < bottom && f < FRACTS) {
            //set the top and bottom
            fracts[f].top = top;
            fracts[f].bottom = bottom;
            //set the value, and make sure you cast
            //one of these longs to a double before the division
            fracts[f].value = top / (double) bottom;
            ++f;
            ++top;
        }
        //reset top counter
        top = 1; 
        //double the value of bottom counter( will be 2, 4, 8, 16, 32, then 64)
        bottom *= 2; 
    }

    /*
        Here's where we actually use
        the sort function we came up with (which is a function that uses our
        compareFracts function and our swapFracts function).
     */

    //bubble sort our Fraction array named fracts, which is of size FRACTS
    //and remember we're sorting based on each struct's "value" member
    bubbleFracts(fracts, FRACTS); 

    //now display our chart with some simple formatting
    printFracts(fracts, FRACTS);

    return 0;
}
