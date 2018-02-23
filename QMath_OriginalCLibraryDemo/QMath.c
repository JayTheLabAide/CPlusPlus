#include "QMath.h"
#include "math.h"

float abso(float n){
    if (n<0) return -n;
    else return n;
}

float dist( float x1, float y1, float x2, float y2){
    float xDist = abso( x1-x2);
    float yDist = abso( y1-y2);
    return sqrt( xDist*xDist+yDist*yDist);
}

void normalize( float * x, float * y){
    float d = dist(0, 0, *x, *y); //get magnitude of vector (length)
    *x = *x/d; //divide x by magnitude
    *y = *y/d; //divide y by magnitude
    //now distance from 0,0 to our point *x,*y is 1.0
}

char touchesCircle( float px, float py, float cx, float cy, float r){
    //if distance between point and circle center <= radius, return true
    //slightly slower version:
    //if ( dist(px, py, cx, cy)<=r ) return 1;
    /* 
     * This slightly faster version takes advantage of the fact that we
     * can square both sides of the equation:
     * sqrt( xDist*xDist+yDist*yDist) <= r
     * which eliminates the relatively slow function call to sqrt(),
     * trading it for a much quicker multiplication operation (r*r),
     * and our resulting equation is:
     * (xDist*xDist+yDist*yDist) <= r*r
    */
    float xDist = abso( px-cx);
    float yDist = abso( py-cy);
    if ( (xDist*xDist+yDist*yDist) <= r*r ) return 1;
    else return 0; //otherwise, test point is further than radius can reach
}
