

#ifndef QMATH_H
#define QMATH_H

#ifdef __cplusplus
extern "C" {
#endif

    float abso(float n);
    
    //calculate distance using primitive variables
    float dist( float x1, float y1, float x2, float y2);
 
    //shrink a vector to unit-length (magnitude 1)
    void normalize( float * x, float * y);
    
    //takes a point x and y, circle center x and y, and circle radius
    //returns 1 if the point is on or within the circle, 0 if point is too far
    char touchesCircle( float px, float py, float cx, float cy, float r);

#ifdef __cplusplus
}
#endif

#endif /* QMATH_H */

