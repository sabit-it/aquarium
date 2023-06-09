#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "actionc.h"
#include "../constants/defines.h"


float dot_product(COORD a, COORD b) {
    float result = a.x * b.x + a.y * b.y;
    return result;
}


//Return distance between two points A(x,y) & B(x,y)
float findDistanceTwoPoints(COORD a, COORD b) {
    return powf(powf(b.x - a.x, 2) + powf(b.y - a.y, 2), (float) 0.5);
}

//Get the biggest float - variadic function
float max(int n, ...) {
    va_list args;
    va_start(args, n);

    double result = 0, value;

    for (int i = 0; i < n; i++) {
        value = va_arg(args, double);
        result = value > result ? value : result;
    }
    va_end(args);
    return (float) result;
}

//Get the smallest float - variadic function
float min(int n, ...) {
    va_list args;
    va_start(args, n);

    double result = 0, value;

    for (int i = 0; i < n; i++) {
        value = va_arg(args, double);
        result = value < result ? value : result;
    }
    va_end(args);
    return (float) result;
}

//Find the closest point on a line segment (AB) to a point P(x, y)
COORD findClosestPointLineSegment(COORD a, COORD b, COORD p) {
    COORD vectorAToP = {p.x - a.x, p.y - a.y};    //vector A->P
    COORD vectorAToB = {b.x - a.x, b.y - a.y};    //vector A->B
    COORD closestPoint;

    //Find t parameter for parametric equation
    float d = powf(vectorAToB.x, 2) + powf(vectorAToB.y, 2);
    float t;
    if (d > 1e-20) {
        t = (vectorAToP.x * vectorAToB.x + vectorAToP.y * vectorAToB.y) / d;
    } else {
        t = 0;
    }
    if (t < 0.0f) {
        closestPoint.x = a.x;
        closestPoint.y = a.y;
    } else if (t > d) {
        closestPoint.x = b.x;
        closestPoint.y = b.y;
    } else {
        closestPoint.x = a.x + vectorAToB.x * t;
        closestPoint.y = a.y + vectorAToB.y * t;

    }

    float x_max = max(2, a.x, b.x);
    float x_min = min(2, a.x, b.x);
    float y_max = max(2, a.y, b.y);
    float y_min = min(2, a.y, b.y);

    //Conditions for found point to be in range
    int condition1 = x_min <= closestPoint.x && closestPoint.x <= x_max;
    int condition2 = y_min <= closestPoint.y && closestPoint.y <= y_max;

    if (condition1 && condition2) {
        return closestPoint;    //Closest point is in range
    } else {
        //Calculate distance from each point and return the closest one
        float distClosePointToA = findDistanceTwoPoints(p, a);
        float distClosePointToB = findDistanceTwoPoints(p, b);

        return distClosePointToA <= distClosePointToB ? a : b;
    }
}

//Find the closest point on a rectangle perimeter from a point P(x,y)
//Vertexes of a rectangle and Point should be entered as parameters in specific order as A B C D and P.
COORD findClosestPointRect(COORD a, COORD b, COORD c, COORD d, COORD p) {
    //List of adjacency of vertexes of a rectangle
    int indexList[4][2] = {{1, 3},
                           {0, 2},
                           {1, 3},
                           {2, 0}};

    COORD coordinates[] = {a, b, c, d};
    float distances[] = {
            findDistanceTwoPoints(p, a),    //P->A
            findDistanceTwoPoints(p, b),       //P->B
            findDistanceTwoPoints(p, c),    //P->C
            findDistanceTwoPoints(p, d)     //P->D
    };

    //Finding the closest Vertex of a rectangle
    int min_index = 0;
    for (int i = 0; i < 4; i++) {
        if (distances[i] < distances[min_index]) {
            min_index = i;
        }
    }

    //Find the closest points for two sides of the closest Vertex
    COORD pointAtLine1 = findClosestPointLineSegment(
            coordinates[min_index], coordinates[indexList[min_index][0]], p);

    COORD pointAtLine2 = findClosestPointLineSegment(
            coordinates[min_index], coordinates[indexList[min_index][1]], p);

    float distLine1 = findDistanceTwoPoints(p, pointAtLine1);   //Distance from P to a point found at line 1
    float distLine2 = findDistanceTwoPoints(p, pointAtLine2);   //Distance from P to a point found at line 2

    return distLine1 <= distLine2 ? pointAtLine1 : pointAtLine2;  //Return point with the smallest distance
}


//Find global coordinate of a fish eye
COORD getFishEyeCoord(COORD global_center, COORD inner_eye_coord, float angle, float width, float height) {
    COORD inner_center = {width / 2, height / 2};
    float distance_center_eye = findDistanceTwoPoints(inner_center, inner_eye_coord);
    float inner_a = inner_eye_coord.x - inner_center.x;
    float inner_angle = acos(inner_a / distance_center_eye) * 180 / M_PI;
    float global_angle = angle + inner_angle;
    float global_a = cos(global_angle * M_PI / 180) * distance_center_eye;
    float global_b = sin(global_angle * M_PI / 180) * distance_center_eye;
    COORD global_eye = {global_center.x + global_a, global_center.y + global_b};
    return global_eye;
}

COORD getClosestFromPoint(COORD rect_center, float rect_width, float rect_height, float global_angle, COORD fish_eye) {
    COORD a, b, c, d;
    float delta_x = rect_width / 2, delta_y = rect_height / 2;

    a.x = rect_center.x - delta_x * cos(global_angle * M_PI / 180) + delta_y * sin(global_angle * M_PI / 180);
    a.y = rect_center.y - delta_x * sin(global_angle * M_PI / 180) - delta_y * cos(global_angle * M_PI / 180);
    b.x = rect_center.x + delta_x * cos(global_angle * M_PI / 180) + delta_y * sin(global_angle * M_PI / 180);
    b.y = rect_center.y + delta_x * sin(global_angle * M_PI / 180) - delta_y * cos(global_angle * M_PI / 180);
    c.x = rect_center.x + delta_x * cos(global_angle * M_PI / 180) - delta_y * sin(global_angle * M_PI / 180);
    c.y = rect_center.y + delta_x * sin(global_angle * M_PI / 180) + delta_y * cos(global_angle * M_PI / 180);
    d.x = rect_center.x - delta_x * cos(global_angle * M_PI / 180) - delta_y * sin(global_angle * M_PI / 180);
    d.y = rect_center.y - delta_x * sin(global_angle * M_PI / 180) + delta_y * cos(global_angle * M_PI / 180);

    COORD result = findClosestPointRect(a, b, c, d, fish_eye);


    return result;
}

float angle_between_two_coordinates(COORD coord1, COORD coord2) {
    VECT vect1, vect2;

    float delta_x, delta_y, angle;
    delta_x = coord1.x - coord2.x;
    delta_y = coord1.y - coord2.y;
    vect1.i = delta_x;
    vect1.j = delta_y;
    vect2.i = delta_x;
    vect2.j = 0;

    angle = ANGLE_BY_DOT_PRODUCT(vect1, vect2);

    if (delta_x > 0 && delta_y < 0) {
        angle = -1;
    } else if (delta_x < 0 && delta_y < 0) {
        angle = (180 - angle)*(-1);
    } else if (delta_x < 0 && delta_y > 0) {
        angle = 180 - angle;
    }

    return angle;
}

