#pragma once

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

//struct to store X & Y coordinates
typedef struct coordinate {
    float x, y;
} COORD;

typedef struct c_vector{
    float i,j;
} VECT;


float dot_product(COORD a, COORD b);


//Return distance between two points A(x,y) & B(x,y)
float findDistanceTwoPoints(COORD a, COORD b);

//Get the biggest float - variadic function
float max(int n, ...);

//Get the smallest float - variadic function
float min(int n, ...);

//Find the closest point on a line segment (AB) to a point P(x, y)
COORD findClosestPointLineSegment(COORD a, COORD b, COORD p);

//Find the closest point on a rectangle perimeter from a point P(x,y)
//Vertexes of a rectangle and Point should be entered as parameters in specific order as A B C D and P.
COORD findClosestPointRect(COORD a, COORD b, COORD c, COORD d, COORD p);

//Find global coordinate of a fish eye
COORD getFishEyeCoord(COORD global_center, COORD inner_eye_coord, float angle, float width, float height);

COORD getClosestFromPoint(COORD rect_center, float rect_width, float rect_height, float global_angle, COORD fish_eye);

void print();

float angle_between_two_coordinates(COORD coord1, COORD coord2);
